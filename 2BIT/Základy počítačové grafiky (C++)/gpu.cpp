/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <cmath>
#include <student/gpu.hpp>
#include <iostream>
#include <cstring>

typedef struct Sprimitive{
    OutVertex points[3];
}Primitive;


typedef struct Sclipped{
    Primitive clipping;
}ClippedPrimitive;

auto backfaceCulling(Primitive primitive){
    glm::vec4 vec[3];
    for(u_int8_t i = 0; i < 3; i++){
        vec[i] = primitive.points[i].gl_Position;
    }

    return (vec[1].x - vec[0].x) * (vec[2].y - vec[0].y) - (vec[2].x - vec[0].x) * (vec[1].y- vec[0].y);

}

void viewportTransformation(Primitive &primitive, Frame frame){
    for(auto & point : primitive.points){
        point.gl_Position.x =  (point.gl_Position.x - (-1)) / 2 * (float)frame.width;
        point.gl_Position.y =  (point.gl_Position.y - (-1)) / 2 * (float)frame.height;
    }
}

void runPerspectiveDivision(Primitive &primitive){
    for(OutVertex & point : primitive.points){
        point.gl_Position.x /=  point.gl_Position.w;
        point.gl_Position.y /=  point.gl_Position.w;
        point.gl_Position.z /=  point.gl_Position.w;
    }
}


auto triangleArea(glm::vec4 vec1, glm::vec4 vec2, glm::vec4 vec3){
    return std::abs((vec1.x - vec3.x) * (vec2.y - vec3.y) + (vec2.x - vec3.x) * (vec3.y - vec1.y));
}



void fragmentInterpolation(InFragment &inF, float l0, float l1, float l2, float s, Primitive primitive, Program prg){
    float ld0 = l0 / (primitive.points[0].gl_Position.w * s);
    float ld1 = l1 / (primitive.points[1].gl_Position.w * s);
    float ld2 = l2 / (primitive.points[2].gl_Position.w * s);


//    float c1 = primitive.points[0].attributes->v4.x * ld0 + primitive.points[1].attributes->v4.x * ld1 + primitive.points[2].attributes->v4.x * ld2;
//    float c2 = primitive.points[0].attributes->v4.y * ld0 + primitive.points[1].attributes->v4.y * ld1 + primitive.points[2].attributes->v4.y * ld2;
//    float c3 = primitive.points[0].attributes->v4.z * ld0 + primitive.points[1].attributes->v4.z * ld1 + primitive.points[2].attributes->v4.z * ld2;
//    float c4 = primitive.points[0].attributes->v4.w * ld0 + primitive.points[1].attributes->v4.w * ld1 + primitive.points[2].attributes->v4.w * ld2;

    for(int i = 0; i < maxAttributes; i++){
        float c1 = primitive.points[0].attributes[i].v4.x * ld0 + primitive.points[1].attributes[i].v4.x * ld1 + primitive.points[2].attributes[i].v4.x * ld2;
        float c2 = primitive.points[0].attributes[i].v4.y * ld0 + primitive.points[1].attributes[i].v4.y * ld1 + primitive.points[2].attributes[i].v4.y * ld2;
        float c3 = primitive.points[0].attributes[i].v4.z * ld0 + primitive.points[1].attributes[i].v4.z * ld1 + primitive.points[2].attributes[i].v4.z * ld2;
        float c4 = primitive.points[0].attributes[i].v4.w * ld0 + primitive.points[1].attributes[i].v4.w * ld1 + primitive.points[2].attributes[i].v4.w * ld2;
        AttributeType attType = prg.vs2fs[i];
        switch (attType){
            case AttributeType::VEC4:
                inF.attributes[i].v4 = glm::vec4 (c1,c2,c3,c4);
                break;
            case AttributeType::VEC3:
                inF.attributes[i].v3 = glm::vec3 (c1,c2,c3);
                break;
            case AttributeType::VEC2:
                inF.attributes[i].v2 = glm::vec2 (c1,c2);
                break;
            case AttributeType::FLOAT:
                inF.attributes[i].v1 = c1;
                break;
            case AttributeType::EMPTY:
                break;
        }

    }
}

void colorFrameSetup(float alpha, Frame &frame, int index, InFragment inFragment, OutFragment out){
    if(alpha > 0.5){
        frame.depth[index] = inFragment.gl_FragCoord.z;
    }

    float blending = 1.f - alpha;

    u_int8_t r = (u_int8_t)std::max(std::min(((float)frame.color[index * 4] * blending + out.gl_FragColor.r * alpha * 255.f),255.f),0.f);
    u_int8_t g = (u_int8_t)std::max(std::min(((float)frame.color[index * 4 + 1] * blending + out.gl_FragColor.g * alpha * 255.f),255.f),0.f);
    u_int8_t b = (u_int8_t)std::max(std::min(((float)frame.color[index * 4 + 2] * blending + out.gl_FragColor.b * alpha * 255.f),255.f),0.f);

    frame.color[index * 4] = r;//std::min(r, 255);
    frame.color[index * 4 + 1] = g;//std::min(g, 255);
    frame.color[index * 4 + 2] = b;//std::min(b, 255);


}

void fragmentSetup(glm::vec4 point, Primitive primitive, InFragment &inFragment, Program program, Frame &frame){
    glm::vec4 vec[3];
    for(u_int8_t i = 0; i < 3; i++){
        vec[i] = primitive.points[i].gl_Position;
    }


    float trArea = triangleArea(vec[0],vec[1],vec[2]);
    float trArea1 = triangleArea(point,vec[1],vec[2]);
    float trArea2 = triangleArea(vec[0],point,vec[2]);
    float trArea3 = triangleArea(vec[0],vec[1],point);

    if(std::lround(trArea) != std::lround(trArea1 + trArea2 + trArea3)){
        return;
    }

    float l0 = trArea1/trArea;
    float l1= trArea2/trArea;
    float l2 = trArea3/trArea;
    float s = l0 / vec[0].w + l1 / vec[1].w + l2 / vec[2].w;


    fragmentInterpolation(inFragment,l0,l1,l2,s,primitive,program);

    inFragment.gl_FragCoord.x = point.x;
    inFragment.gl_FragCoord.y = point.y;
    inFragment.gl_FragCoord.z = vec[0].z * l0 + vec[1].z * l1 + vec[2].z * l2;
    OutFragment out;
    program.fragmentShader(out,inFragment,program.uniforms);
    int index = (int)point.x + (int)point.y * (int)frame.width;

    if(inFragment.gl_FragCoord.z < frame.depth[index]) {
        float alpha = out.gl_FragColor.w;
        colorFrameSetup(alpha, frame, index, inFragment, out);
    }

}

void rasterizeTriangle(Frame frame, Primitive primitive,Program prg){
    glm::vec4 vec[3];
    for(u_int8_t i = 0; i < 3; i++){
        vec[i] = primitive.points[i].gl_Position;
//        printf("%d,%d",(int)vec[i].x , (int)vec[i].y);
//        printf("\n");
    }
    if(triangleArea(vec[0],vec[1],vec[2]) == 0){
        return;
    }

    int minX = (int)std::min(std::min(vec[0].x,vec[1].x),vec[2].x);
    int minY = (int)std::min(std::min(vec[0].y,vec[1].y),vec[2].y);
    int maxX = (int)std::max(std::max(vec[0].x,vec[1].x),vec[2].x);
    int maxY = (int)std::max(std::max(vec[0].y,vec[1].y),vec[2].y);

    minX = std::max(minX,0);
    minY = std::max(minY,0);
    maxX = std::min(maxX,(int)(frame.width - 1.0));
    maxY = std::min(maxY, (int)(frame.height - 1.0));
//    printf("%d,%d",minX , maxX);
//    printf("\n");
//    printf("%d,%d",minY , maxY);
//    printf("\n");
    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){
            InFragment inFragment;
            glm::vec4 point;
            point.x = (float)(x + 0.5);
            point.y = (float)(y + 0.5);
            fragmentSetup(point,primitive,inFragment, prg,frame);
        }
    }
}



void readAttributes(VertexArray const &voa, InVertex &inVertex){

    for(auto i = 0; i < maxAttributes; i++){

        VertexAttrib attrib = voa.vertexAttrib[i];

        if(attrib.type == AttributeType::EMPTY){
            continue;
        }

        if(attrib.type == AttributeType::FLOAT){
            inVertex.attributes[i].v1 = *(float*)((uint8_t *)attrib.bufferData + attrib.offset + attrib.stride * inVertex.gl_VertexID);
        }else if(attrib.type == AttributeType::VEC2){
            inVertex.attributes[i].v2 = *(glm::vec2 *)((uint8_t *)attrib.bufferData  + attrib.offset + attrib.stride *inVertex.gl_VertexID);
        }else if(attrib.type == AttributeType::VEC3){
            inVertex.attributes[i].v3 = *(glm::vec3 *)((uint8_t *)attrib.bufferData  + attrib.offset + attrib.stride *inVertex.gl_VertexID);
        }else if(attrib.type == AttributeType::VEC4){
            inVertex.attributes[i].v4 = *(glm::vec4 *)((uint8_t *)attrib.bufferData  + attrib.offset + attrib.stride *inVertex.gl_VertexID);
        }
    }

}

uint32_t newVertexID(VertexArray const &vao, uint32_t index){
    if(vao.indexBuffer) {
        if (vao.indexType == IndexType::UINT8) {
            auto *indexArr = (u_int8_t *) vao.indexBuffer;
            return indexArr[index];
        } else if (vao.indexType == IndexType::UINT16) {
            auto *indexArr = (u_int16_t *) vao.indexBuffer;
            return indexArr[index];
        } else if (vao.indexType == IndexType::UINT32) {
            auto *indexArr = (u_int32_t *) vao.indexBuffer;
            return indexArr[index];
        }
    }
    return index;
}

void vertexAssembly(VertexArray const &vao, InVertex &inVertex,uint32_t index){

    inVertex.gl_VertexID = newVertexID(vao,index);
    readAttributes(vao,inVertex);
}


void primitiveAssembly(Primitive &primitive, VertexArray &vao, u_int32_t index, Program &prg){
    for(u_int32_t i = index - 3; i < index; i++){
        InVertex inVertex;
        vertexAssembly(vao,inVertex,i);
        prg.vertexShader(primitive.points[i % 3],inVertex,prg.uniforms);
    }
}

void checkPoints(int numPlain, OutVertex ver, int *outPoints, int *inPoints, u_int8_t &countOut, int num){
    switch (numPlain) {
        case 0:
            //near
            if(-ver.gl_Position.w > ver.gl_Position.z){
                outPoints[countOut++] = num;
            }else{
                inPoints[num - countOut] = num;
            }
            break;
        case 1:
            //left
            if(ver.gl_Position.w < ver.gl_Position.x){
                outPoints[countOut++] = num;
            }else{
                inPoints[num - countOut] = num;
            }
            break;
        case 2:
            //right
            if(-ver.gl_Position.w > ver.gl_Position.x){
                outPoints[countOut++] = num;
            }else{
                inPoints[num - countOut] = num;
            }
            break;
        case 3:
            //top
            if(ver.gl_Position.w < ver.gl_Position.y){
                outPoints[countOut++] = num;
            }else{
                inPoints[num - countOut] = num;
            }
            break;
        case 4:
            //bottom
            if(-ver.gl_Position.w > ver.gl_Position.y){
                outPoints[countOut++] = num;
            }else{
                inPoints[num - countOut] = num;
            }
            break;
        default:
            break;

    }
}

float newPoint(OutVertex A,OutVertex B, int numPlain){
    float Aw = A.gl_Position.w;
    float Ax = A.gl_Position.x;
    float Ay = A.gl_Position.y;
    float Az = A.gl_Position.z;

    float Bw = B.gl_Position.w;
    float Bx = B.gl_Position.x;
    float By = B.gl_Position.y;
    float Bz = B.gl_Position.z;

    switch(numPlain){
        case 0:
            return (-Aw - Az) / ((Bw - Aw) + (Bz - Az));
        case 1:
            return (Aw - Ax)  / ((Bx - Ax) - (Bw - Aw));
        case 2:
            return (-Aw - Ax) / ((Bw - Aw) + (Bx - Ax));
        case 3:
            return (Aw - Ay)  / ((By - Ay) - (Bw - Aw));
        case 4:
            return (-Aw - Ay) / ((Bw - Aw) + (By - Ay));
        default:
           return 0.0;
    }

}

OutVertex newPointInterpInterpolation(OutVertex A, OutVertex B, float &t, Program prg){
    OutVertex newOut;
    for(int i = 0; i < maxAttributes; i++){
        float px = A.attributes[i].v4.x + t * (B.attributes[i].v4.x - A.attributes[i].v4.x);
        float py = A.attributes[i].v4.y + t * (B.attributes[i].v4.y - A.attributes[i].v4.y);
        float pz = A.attributes[i].v4.z + t * (B.attributes[i].v4.z - A.attributes[i].v4.z);
        float pw = A.attributes[i].v4.w + t * (B.attributes[i].v4.w - A.attributes[i].v4.w);
        AttributeType attType = prg.vs2fs[i];
        switch (attType){
            case AttributeType::VEC4:
                newOut.attributes[i].v4 = glm::vec4 (px,py,pz,pw);
                break;
            case AttributeType::VEC3:
                newOut.attributes[i].v3 = glm::vec3 (px,py,pz);
                break;
            case AttributeType::VEC2:
                newOut.attributes[i].v2 = glm::vec2 (px,py);
                break;
            case AttributeType::FLOAT:
                newOut.attributes[i].v1 = px;
                break;
            case AttributeType::EMPTY:
                break;
        }
    }

    newOut.gl_Position.x = A.gl_Position.x + t * (B.gl_Position.x - A.gl_Position.x);
    newOut.gl_Position.y = A.gl_Position.y + t * (B.gl_Position.y - A.gl_Position.y);
    newOut.gl_Position.z = A.gl_Position.z + t * (B.gl_Position.z - A.gl_Position.z);
    newOut.gl_Position.w = A.gl_Position.w + t * (B.gl_Position.w - A.gl_Position.w);

    return newOut;

}

void clipping(ClippedPrimitive &clipped,GPUContext &ctx,int numPlain = 0){

    int outPoint[3] = {-1,-1,-1};
    int inPoint[3] = {-1,-1,-1};
    u_int8_t countOutPoint = 0;

    if(numPlain == 5){
        runPerspectiveDivision(clipped.clipping);
        viewportTransformation(clipped.clipping,ctx.frame);
        if(ctx.backfaceCulling && backfaceCulling(clipped.clipping) < 0.0){
            return;
        }
        rasterizeTriangle(ctx.frame, clipped.clipping,ctx.prg);
        return;
    }

       for(u_int8_t i = 0; i < 3; i++){
           checkPoints(numPlain,clipped.clipping.points[i],outPoint, inPoint,countOutPoint,i);
       }

       switch(countOutPoint){
           case 0:
               numPlain++;
               clipping(clipped,ctx,numPlain);
               break;
           case 1: {
               OutVertex outsidePoint = clipped.clipping.points[outPoint[0]];
               OutVertex insidePoint1 = clipped.clipping.points[inPoint[0]];
               OutVertex insidePoint2 = clipped.clipping.points[inPoint[1]];
               float t = newPoint(outsidePoint,insidePoint1,numPlain);
               OutVertex point = newPointInterpInterpolation(outsidePoint, insidePoint1,t, ctx.prg);
               ClippedPrimitive newClipped = clipped;
               newClipped.clipping.points[outPoint[0]] = point;

               t = newPoint(outsidePoint,insidePoint2,numPlain);
               clipped.clipping.points[outPoint[0]] = newPointInterpInterpolation(outsidePoint, insidePoint2,t, ctx.prg);
               clipped.clipping.points[inPoint[0]] = point;

               numPlain++;
               clipping(clipped,ctx,numPlain);
               clipping(newClipped,ctx,numPlain);
               break;
           }
           case 2: {
               OutVertex outsidePoint1 = clipped.clipping.points[outPoint[0]];
               OutVertex outsidePoint2 = clipped.clipping.points[outPoint[1]];
               OutVertex insidePoint = clipped.clipping.points[inPoint[0]];
               float t = newPoint(outsidePoint1,insidePoint,numPlain);
               clipped.clipping.points[outPoint[0]] = newPointInterpInterpolation(outsidePoint1, insidePoint, t, ctx.prg);
               t = newPoint(outsidePoint2,insidePoint,numPlain);
               clipped.clipping.points[outPoint[1]] = newPointInterpInterpolation(outsidePoint2,insidePoint,t, ctx.prg);
               numPlain++;
               clipping(clipped,ctx,numPlain);
               break;
           }
           case 3:
               return;

           default:
               numPlain++;
               clipping(clipped,ctx,numPlain);

       }
}


//! [drawImpl]
void drawImpl(GPUContext &ctx,uint32_t nofVertices){
    (void)ctx;
    (void)nofVertices;
    for(auto i = 3; i <= nofVertices; i = i + 3){
        Primitive primitive;
        ClippedPrimitive clipped;
        primitiveAssembly(primitive,ctx.vao,i,ctx.prg);
        clipped.clipping = primitive;
        clipping(clipped,ctx);
    }
}
//! [drawImpl]

/**
 * @brief This function reads color from texture.
 *
 * @param texture texture
 * @param uv uv coordinates
 *
 * @return color 4 floats
 */
glm::vec4 read_texture(Texture const&texture,glm::vec2 uv){
    if(!texture.data)return glm::vec4(0.f);
    auto uv1 = glm::fract(uv);
    auto uv2 = uv1*glm::vec2(texture.width-1,texture.height-1)+0.5f;
    auto pix = glm::uvec2(uv2);
    //auto t   = glm::fract(uv2);
    glm::vec4 color = glm::vec4(0.f,0.f,0.f,1.f);
    for(uint32_t c=0;c<texture.channels;++c)
        color[c] = texture.data[(pix.y*texture.width+pix.x)*texture.channels+c]/255.f;
    return color;
}

/**
 * @brief This function clears framebuffer.
 *
 * @param ctx GPUContext
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel
 */
void clear(GPUContext&ctx,float r,float g,float b,float a){
    auto&frame = ctx.frame;
    auto const nofPixels = frame.width * frame.height;
    for(size_t i=0;i<nofPixels;++i){
        frame.depth[i] = 10e10f;
        frame.color[i*4+0] = static_cast<uint8_t>(glm::min(r*255.f,255.f));
        frame.color[i*4+1] = static_cast<uint8_t>(glm::min(g*255.f,255.f));
        frame.color[i*4+2] = static_cast<uint8_t>(glm::min(b*255.f,255.f));
        frame.color[i*4+3] = static_cast<uint8_t>(glm::min(a*255.f,255.f));
    }
}

