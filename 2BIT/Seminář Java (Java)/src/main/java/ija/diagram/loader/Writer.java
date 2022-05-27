package ija.diagram.loader;

import ija.diagram.classdiagram.model.*;
import ija.diagram.sequencediagram.model.Message;
import ija.diagram.sequencediagram.model.SObject;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
/**
 * Uloží diagramu třídu do JSON souboru
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Writer {
    String path;
    JSONArray mainList = new JSONArray();
    public Writer(String path){
        this.path = path;
    }

    public void saveJSON(ClassDiagram classDiagram, SequenceDiagram sequenceDiagram1, SequenceDiagram sequenceDiagram2, SequenceDiagram sequenceDiagram3){
        writeClassJSON(classDiagram.getdClassList());
        writeRelationJSON(classDiagram.getRelationshipsList());
        writeSequenceJSON(sequenceDiagram1.getsObjectList(), 1);
        writeSequenceJSON(sequenceDiagram2.getsObjectList(), 2);
        writeSequenceJSON(sequenceDiagram3.getsObjectList(), 3);
        writeToJSON();

    }
    public void writeSequenceJSON(List<SObject> sObjectList, int num){
        if(!sObjectList.isEmpty()){
            JSONObject sequenceParams = new JSONObject();
            JSONObject finalParams = new JSONObject();
            JSONArray participantArray = new JSONArray();
            JSONArray messageList = new JSONArray();
            int len = 0;
            for(SObject sObject: sObjectList){
                JSONObject participantParams = new JSONObject();
                participantParams.put("name", sObject.getName());
                participantParams.put("x", sObject.getX());
                if(sObject.getActivationBox() != null){
                    participantParams.put("boxHeight", sObject.getActivationBox().getHeight());
                    participantParams.put("boxY", sObject.getActivationBox().getY());
                }
                participantArray.add(participantParams);
                if(sObject.getActivationBox() != null){
                    for (Message message : sObject.getActivationBox().getOutMessage()) {
                        JSONObject messageParams = new JSONObject();
                        messageParams.put("name", message.getName());
                        if(message.getClassStart() != null) {
                            messageParams.put("start", message.getClassStart().getName());
                            messageParams.put("end", message.getClassEnd().getName());
                        }
                        messageParams.put("x", message.getX());
                        messageParams.put("y", message.getY());
                        messageParams.put("len", message.getLen());
                        switch (message.getMessageType()) {
                            case SYNCHRONOUS:
                                messageParams.put("type", "sync");
                                break;
                            case ASYNCHRONOUS:
                                messageParams.put("type", "async");
                                break;
                            case DELETE:
                                messageParams.put("type", "delete");
                                break;
                            case REPLY:
                                messageParams.put("type", "reply");
                                break;
                        }
                        messageList.add(messageParams);
                    }
                }
            }
            sequenceParams.put("participants", participantArray);
            sequenceParams.put("message", messageList);
            switch (num){
                case 1:
                    finalParams.put("sequence1", sequenceParams);
                    break;
                case 2:
                    finalParams.put("sequence2", sequenceParams);
                    break;
                case 3:
                    finalParams.put("sequence3", sequenceParams);
                    break;
            }
            mainList.add(finalParams);
        }

    }
    /**
     * Získá dCLassList s daty ve třídách a vypíše vše do souboru ve formátu JSON
     */
    public void writeClassJSON(List<DClass> dClassList){
        for(DClass item: dClassList){
            JSONArray attrList = new JSONArray();
            JSONArray methodList = new JSONArray();
            JSONObject classList = new JSONObject();
            JSONObject classParams = new JSONObject();
            classParams.put("name", item.getName());
            classParams.put("xAxis", item.getX());
            classParams.put("yAxis", item.getY());
            for(Arguments argument: item.getArgumentsList()){
                JSONObject attrParams = new JSONObject();
                if(argument.getAccessModifier() != null)
                    attrParams.put("accessModifiers", argument.getAccessModifier().toString().toLowerCase());
                if(argument.getType() != null)
                    attrParams.put("type", argument.getType());
                attrParams.put("id", argument.getName());
                attrList.add(attrParams);
            }
            for(Methods method: item.getMethodsList()){
                JSONObject methodParams = new JSONObject();
                if(method.getAccessModifier() != null)
                    methodParams.put("accessModifiers", method.getAccessModifier().toString().toLowerCase());
                methodParams.put("id", method.getName());
                methodList.add(methodParams);
            }
            if(item.getArgumentsList().size() != 0)
                classParams.put("attributes", attrList);
            if(item.getMethodsList().size() != 0)
                classParams.put("operations", methodList);
            classList.put("class", classParams);
            mainList.add(classList);
        }
    }

    public void writeRelationJSON(List<Relationships> relationshipsList){
        for(Relationships relationships : relationshipsList){
            JSONObject relationList = new JSONObject();
            JSONObject relationArgument = new JSONObject();
            relationArgument.put("name", relationships.getName());
            relationArgument.put("start", relationships.getClassFrom().getName());
            if(relationships.getClassTo() == null){
                continue;
            }
            relationArgument.put("end", relationships.getClassTo().getName());

            relationArgument.put("type", relationships.getTypeShipString());
            relationArgument.put("startX", relationships.getStartX());
            relationArgument.put("startY", relationships.getStartY());
            relationArgument.put("endX", relationships.getEndX());
            relationArgument.put("endY", relationships.getEndY());
            if(!relationshipsList.isEmpty())
                relationList.put("relation", relationArgument);
                mainList.add(relationList);
        }
    }

    public void writeToJSON(){
        try (FileWriter file = new FileWriter(path)) {
            file.write(mainList.toJSONString());
            file.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
