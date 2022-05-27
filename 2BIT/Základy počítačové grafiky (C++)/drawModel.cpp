/*!
 * @file
 * @brief This file contains functions for model rendering
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */
#include <student/drawModel.hpp>
#include <student/gpu.hpp>
#include <cstdio>

void drawNode(GPUContext &ctx, const Node& node, Model  model, glm::mat4 matrix,glm::mat4 const&proj,glm::mat4 const&view, glm::vec3 const&light, glm::vec3 const&camera){
    matrix = matrix * node.modelMatrix;
    if(node.mesh >= 0){
        auto meshes = model.meshes[node.mesh];

        ctx.vao.vertexAttrib[0].bufferData = meshes.position.bufferData;
        ctx.vao.vertexAttrib[0].type = meshes.position.type;
        ctx.vao.vertexAttrib[0].stride = meshes.position.stride;
        ctx.vao.vertexAttrib[0].offset = meshes.position.offset;

        ctx.vao.vertexAttrib[1].bufferData = meshes.normal.bufferData;
        ctx.vao.vertexAttrib[1].type = meshes.normal.type;
        ctx.vao.vertexAttrib[1].stride = meshes.normal.stride;
        ctx.vao.vertexAttrib[1].offset = meshes.normal.offset;


        ctx.vao.vertexAttrib[2].bufferData = meshes.texCoord.bufferData;
        ctx.vao.vertexAttrib[2].type = meshes.texCoord.type;
        ctx.vao.vertexAttrib[2].stride = meshes.texCoord.stride;
        ctx.vao.vertexAttrib[2].offset = meshes.texCoord.offset;

        ctx.vao.indexType= meshes.indexType;
        ctx.vao.indexBuffer = meshes.indices;


        ctx.prg.uniforms.uniform[1].m4 = matrix;
        ctx.prg.uniforms.uniform[2].m4 = glm::transpose(glm::inverse(ctx.prg.uniforms.uniform[1].m4));
        ctx.prg.uniforms.uniform[3].v3 = light;
        ctx.prg.uniforms.uniform[4].v3 = camera;
        ctx.prg.uniforms.uniform[5].v4 = meshes.diffuseColor;

        if(meshes.diffuseTexture >= 0){
            ctx.prg.uniforms.uniform[6].v1 = 1.f;
            ctx.prg.uniforms.textures[0] = model.textures[meshes.diffuseTexture];

        }else{
            ctx.prg.uniforms.uniform[6].v1 = 0.f;
            ctx.prg.uniforms.textures[0] = {};
        }
        ctx.prg.vertexShader = drawModel_vertexShader;
        ctx.prg.fragmentShader = drawModel_fragmentShader;
        ctx.prg.vs2fs[0] = AttributeType::VEC3;
        ctx.prg.vs2fs[1] = AttributeType::VEC3;
        ctx.prg.vs2fs[2] = AttributeType::VEC2;

        draw(ctx, meshes.nofIndices);

    }

    for(const auto & i : node.children){
        drawNode(ctx,i,model,matrix,proj,view, light, camera);
    }

}

/**
 * @brief This function renders a model
 *
 * @param ctx GPUContext
 * @param model model structure
 * @param proj projection matrix
 * @param view view matrix
 * @param light light position
 * @param camera camera position (unused)
 */
//! [drawModel]
void drawModel(GPUContext &ctx, Model const&model, glm::mat4 const&proj, glm::mat4 const&view, glm::vec3 const&light, glm::vec3 const&camera){
  glm::mat4 unitMatrix = glm::mat4(1.f);
  ctx.backfaceCulling = false;
  ctx.prg.uniforms.uniform[0].m4 = proj * view;

  for(auto i = 0; i < model.roots.size(); i++){
      drawNode(ctx, model.roots[i], model, unitMatrix, proj, view, light, camera);
  }

  /// \todo Tato funkce vykreslí model.<br>
  /// Vaším úkolem je správně projít model a vykreslit ho pomocí funkce draw (nevolejte drawImpl, je to z důvodu testování).
  /// Bližší informace jsou uvedeny na hlavní stránce dokumentace.
}
//! [drawModel]

/**
 * @brief This function represents vertex shader of texture rendering method.
 *
 * @param outVertex output vertex
 * @param inVertex input vertex
 * @param uniforms uniform variables
 */
//! [drawModel_vs]
void drawModel_vertexShader(OutVertex &outVertex, InVertex const&inVertex, Uniforms const&uniforms){
  (void)outVertex;
  (void)inVertex;
  (void)uniforms;

    outVertex.gl_Position =  uniforms.uniform[0].m4 * (uniforms.uniform[1].m4 * glm::vec4(inVertex.attributes[0].v3,1.f));
    outVertex.attributes[0].v4 = uniforms.uniform[1].m4 * glm::vec4(inVertex.attributes[0].v3,1.f);
    outVertex.attributes[1].v4 = uniforms.uniform[2].m4 * glm::vec4(inVertex.attributes[1].v3,0.f);
    outVertex.attributes[2].v4 = inVertex.attributes[2].v4;


}

//! [drawModel_vs]

/**
 * @brief This functionrepresents fragment shader of texture rendering method.
 *
 * @param outFragment output fragment
 * @param inFragment input fragment
 * @param uniforms uniform variables
 */
//! [drawModel_fs]
void drawModel_fragmentShader(OutFragment&outFragment,InFragment const&inFragment,Uniforms const&uniforms){
    float const aF = 0.2;
    glm::vec3 const positionTriangle = inFragment.attributes[0].v3;
    glm::vec3 L = glm::normalize(uniforms.uniform[3].v3 - positionTriangle);


    glm::vec3 N = glm::normalize(inFragment.attributes[1].v3);
    if(uniforms.uniform[7].v1 == 1.f && (glm::dot(N ,uniforms.uniform[4].v3 - positionTriangle) < 0.0)){
        N *= -1.f;
    }

    auto dF = glm::clamp(glm::dot(N,L),0.f,1.f);

    glm::vec4 dC;
    if(uniforms.uniform[6].v1 == 1.f)
        dC = read_texture(uniforms.textures[0], inFragment.attributes[2].v2);
    else
        dC = uniforms.uniform[5].v4;


    glm::vec3 aL = dC * aF;
    glm::vec3 dL = dC * dF;

    outFragment.gl_FragColor = glm::vec4(aL + dL, dC.a);





}
//! [drawModel_fs]

