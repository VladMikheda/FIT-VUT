package ija.diagram.loader;

import java.io.*;
import java.util.ArrayList;

import ija.diagram.classdiagram.model.Item;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
/**
 * Parser pro načtení souboru
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Parser {
    private ArrayList<objectJSON> itemList = new ArrayList<>();
    private String path;


    public Parser(String path){
        this.path = path;
    }

    /**
     * Analyzuje JSON soubor ze souboru input.json.
     * Vytvoří seznam objektů, které jsou reprezentovány jako třídy a vztahy.
     * Každý zadaný objekt obsahuje:
     *      název, typ (třída, vztah), seznam atributů, seznam metod, výška, šířka, Osa x, osa y.
     *      počáteční relace, koncová relace, typ relace (asociace, agregace, e.t. c).
     * Vrací výše uvedený seznam.
     */
    public ArrayList<objectJSON> parseJSON(){
        JSONArray jsonArr = fileOpen();

        //Objects parse
        if(jsonArr == null){
            return null;
        }
        for (Object o : jsonArr) {
            JSONObject object = (JSONObject) o;
            JSONObject objectClass = (JSONObject) object.get("class");
            JSONObject objectConnection = (JSONObject) object.get("relation");
            JSONObject objectSequence1 = (JSONObject) object.get("sequence1");
            JSONObject objectSequence2 = (JSONObject) object.get("sequence2");
            JSONObject objectSequence3 = (JSONObject) object.get("sequence3");
            //Classes parse
            boolean check = parseClass(objectClass);
            if (!check) {
                return null;
            }
            //Connections parse
            check = parseConnection(objectConnection);
            if (!check) {
                return null;
            }
            //Sequence parse
            check = parseSequence(objectSequence1);
            if(!check)
                return null;
            check = parseSequence(objectSequence2);
            if(!check)
                return null;
            check = parseSequence(objectSequence3);
            if(!check)
                return null;
        }
        return itemList;
    }


    private JSONArray fileOpen(){
        JSONParser jsonParser = new JSONParser();
        try(FileReader reader = new FileReader(path)){
            Object objects = jsonParser.parse(reader);
            JSONArray jsonArr = (JSONArray) objects;
            if (checkJSON(jsonArr) == -1)
                return null;
            return jsonArr;
        } catch (FileNotFoundException e) {
            System.err.println("Invalid input file");
            return null;
        } catch (IOException | ParseException e) {
//            e.printStackTrace();
            return null;
        }
    }
    private boolean parseSequence(JSONObject obj){
        if(obj != null){
            objectJSON newObject = new objectJSON();
            newObject.setType(objectJSON.ItemType.SEQUENCE);
            JSONArray participantList = (JSONArray) obj.get("participants");
            if(participantList == null)
                return false;
            for(int i = 0; i < participantList.size(); i++){
                JSONObject participantObj = (JSONObject) participantList.get(i);
                String name = (String) participantObj.get("name");
                double x = Double.parseDouble(participantObj.get("x").toString());
                double y = 90;
                double height = 30;
                if(participantObj.get("boxY") != null){
                y = Double.parseDouble(participantObj.get("boxY").toString());
                height = Double.parseDouble(participantObj.get("boxHeight").toString());
                }
                newObject.addParticipant(name, x, height, y);
            }
            JSONArray messageList = (JSONArray) obj.get("message");
            if(messageList == null)
                return false;
            for (Object o : messageList) {
                JSONObject message = (JSONObject) o;
                String name = (String) message.get("name");
                String nameFrom = (String) message.get("start");
                String nameTo = (String) message.get("end");
                String type = (String) message.get("type");
                double x = Double.parseDouble(message.get("x").toString());
                double y = Double.parseDouble(message.get("y").toString());
                int len = Integer.parseInt(message.get("len").toString());
                newObject.addMessageList(name, nameFrom, nameTo, type, x, y, len);
            }
            itemList.add(newObject);

        }
        return true;
    }

    private boolean setAttributeOperation(objectJSON newObject, JSONArray item, String nameItem){
        if(item != null){
            for(int j = 0; j < item.size(); j++){
                attrJSON aux = new attrJSON();
                JSONObject tmp = (JSONObject) item.get(j);
                String id = (String) tmp.get("id");
                if(id == null) {
                    return false;
                }
                aux.setName(id);
                String accessModifiers = (String) tmp.get("accessModifiers");
                if(accessModifiers == null)
                    aux.setAccessModifiers(null);
                else{
                    switch (accessModifiers){
                        case "public":
                            aux.setAccessModifiers(Item.AccessModifier.PUBLIC);
                            break;
                        case "protected":
                            aux.setAccessModifiers(Item.AccessModifier.PROTECTED);
                            break;
                        case "private":
                            aux.setAccessModifiers(Item.AccessModifier.PRIVATE);
                            break;
                        case "visible":
                            aux.setAccessModifiers(Item.AccessModifier.VISIBLE);
                            break;
                    }
                }
                String type = (String) tmp.get("type");
                aux.setType(type);
                if(nameItem.equals("operations")) {
                    newObject.addOperation(aux);
                }else if (nameItem.equals("attributes")){
                    newObject.addAttribute(aux);
                }
            }
        }
        else{
            if(nameItem.equals("operations")) {
                newObject.setOperations(null);
            }else if (nameItem.equals("attributes")){
                newObject.setAttributes(null);
            }
        }
        return true;
    }

    private boolean parseClass(JSONObject objectClass){
        if(objectClass != null){
            objectJSON newObject = new objectJSON();
            newObject.setType(objectJSON.ItemType.CLASS);
            String name = (String) objectClass.get("name");
            newObject.setName(name);
            JSONArray operations = (JSONArray) objectClass.get("operations");
            //Operations parse
            boolean check = setAttributeOperation(newObject, operations, "operations");
            if(!check){
                return false;
            }
            //Attributes parse
            JSONArray attributes = (JSONArray) objectClass.get("attributes");
            check = setAttributeOperation(newObject, attributes, "attributes");
            if(!check){
                return false;
            }
            if(objectClass.get("height") == null){
                newObject.setHeight(0);
            }
            else{
                long height = (long) objectClass.get("height");
                newObject.setHeight((int) height);
            }
            if(objectClass.get("width") == null){
                newObject.setWidth(0);
            }
            else{
                long width = (long) objectClass.get("width");
                newObject.setWidth((int) width);
            }
            if(objectClass.get("xAxis") == null){
                newObject.setxAxis(0);
            }
            else{
                double x = Double.parseDouble((objectClass.get("xAxis")).toString());
                newObject.setxAxis(x);
            }
            if(objectClass.get("yAxis") == null){
                newObject.setyAxis(0);
            }
            else{
                double y =  Double.parseDouble(objectClass.get("yAxis").toString());
                newObject.setyAxis(y);
            }

            itemList.add(newObject);
        }
        return true;
    }

    private boolean parseConnection(JSONObject objectConnection){
        if(objectConnection != null){
            objectJSON newObject = new objectJSON();
            newObject.setType(objectJSON.ItemType.CONNECTION);
            String name = (String) objectConnection.get("name");
            newObject.setName(name);
            if(objectConnection.get("startX") == null){
                newObject.setStartX(0);
            }
            else{
                double x = Double.parseDouble((objectConnection.get("startX")).toString());
                newObject.setStartX(x);
            }
            if(objectConnection.get("startY") == null){
                newObject.setStartY(0);
            }
            else{
                double y = Double.parseDouble((objectConnection.get("startY")).toString());
                newObject.setStartY(y);
            }
            if(objectConnection.get("endX") == null){
                newObject.setEndX(0);
            }
            else{
                double x = Double.parseDouble((objectConnection.get("endX")).toString());
                newObject.setEndX(x);
            }

            if(objectConnection.get("endY") == null){
                newObject.setEndY(0);
            }
            else{
                double y = Double.parseDouble((objectConnection.get("endY")).toString());
                newObject.setEndY(y);
            }
            String start = (String) objectConnection.get("start");
            String end = (String) objectConnection.get("end");
            String type = (String) objectConnection.get("type");
            newObject.setStartConnection(start);
            newObject.setEndConnection(end);
            if(type == null)
                newObject.setConType(objectJSON.ConType.NONE);
            else{
                switch (type) {
                    case "association":
                        newObject.setConType(objectJSON.ConType.ASSOCIATION);
                        break;
                    case "reflexive":
                        newObject.setConType(objectJSON.ConType.REFLEXIVE_ASSOCIATION);
                        break;
                    case "aggregation":
                        newObject.setConType(objectJSON.ConType.AGGREGATION);
                        break;
                    case "composition":
                        newObject.setConType(objectJSON.ConType.COMPOSITION);
                        break;
                    case "inheritance":
                        newObject.setConType(objectJSON.ConType.INHERITANCE);
                        break;
//                    case "multiplicity":
//                        newObject.setConType(objectJSON.ConType.MULTIPLICITY);
//                        break;
                    case "realization":
                        newObject.setConType(objectJSON.ConType.REALIZATION);
                        break;
                }
            }
            String notation = (String) objectConnection.get("notation");
            if(notation == null)
                newObject.setNotation(objectJSON.Notation.NONE);
            else{
                switch(notation){
                    case "1":
                        newObject.setNotation(objectJSON.Notation.ONE_TO_NONE);
                        break;
                    case "0..*":
                        newObject.setNotation(objectJSON.Notation.ZERO_MANY_TO_NONE);
                        break;
                    case "1..*":
                        newObject.setNotation(objectJSON.Notation.ONE_MANY_TO_NONE);
                        break;
                    case "1--1":
                        newObject.setNotation(objectJSON.Notation.ONE_TO_ONE);
                        break;
                    case "1--1..*":
                        newObject.setNotation(objectJSON.Notation.ONE_TO_ONE_MANY);
                        break;
                    case "1--0..*":
                        newObject.setNotation(objectJSON.Notation.ONE_TO_ZERO_MANY);
                        break;
                    case "1..*--1":
                        newObject.setNotation(objectJSON.Notation.ONE_MANY_TO_ONE);
                        break;
                    case "1..*--1..*":
                        newObject.setNotation(objectJSON.Notation.ONE_MANY_TO_ONE_MANY);
                        break;
                    case "1..*--0..*":
                        newObject.setNotation(objectJSON.Notation.ONE_MANY_TO_ZERO_MANY);
                        break;
                    case "0..*--1":
                        newObject.setNotation(objectJSON.Notation.ZERO_MANY_TO_ONE);
                        break;
                    case "0..*--1..*":
                        newObject.setNotation(objectJSON.Notation.ZERO_MANY_TO_ONE_MANY);
                        break;
                    case "0..*--0..*":
                        newObject.setNotation(objectJSON.Notation.ZERO_MANY_TO_ZERO_MANY);
                        break;
                }
            }
                /*
                ONE_TO_NONE,            1
                ZERO_MANY_TO_NONE,      0..*
                ONE_MANY_TO_NONE,       1..*
                ONE_TO_ONE,             1--1
                ONE_TO_ONE_MANY,        1--1..*
                ONE_TO_ZERO_MANY,       1--0..*
                ONE_MANY_TO_ONE,        1..*--1
                ONE_MANY_TO_ONE_MANY,   1..*--1..*
                ONE_MANY_TO_ZERO_MANY,  1..*--0..*
                ZERO_MANY_TO_ONE,       0..*--1
                ZERO_MANY_TO_ONE_MANY,  0..*--1..*
                ZERO_MANY_TO_ZERO_MANY  0..*--0..*
                 */
            itemList.add(newObject);
        }
        return true;
    }

//    public static void

    /**
     * Kontroluje JSON Soubor pro chyby syntaxe.
     * @return Vrací -1 v případě chyb jinak 0.
     */
    private static int checkJSON(JSONArray jsonArr){
        if(jsonArr == null){
            return -1;
        }
        return 0;
    }
}
