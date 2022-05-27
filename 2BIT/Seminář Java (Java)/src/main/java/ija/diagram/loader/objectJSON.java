package ija.diagram.loader;

import ija.diagram.classdiagram.model.DClass;
import ija.diagram.sequencediagram.model.Message;
import ija.diagram.sequencediagram.model.SObject;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
/**
 * Třída reprezentuje jednotlivou reprezentaci třídy nebo vztahu v JSON souboru
 * obsahuje metody pro uchování položek a práci s nimi
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class objectJSON {
    public enum ItemType{
        CLASS,
        CONNECTION,
        SEQUENCE
    }
    public enum ConType{
        ASSOCIATION,
        REFLEXIVE_ASSOCIATION,
        MULTIPLICITY,
        AGGREGATION,
        COMPOSITION,
        INHERITANCE,
        REALIZATION,
        NONE
    }
    public enum Notation{
        ONE_TO_NONE,
        ZERO_MANY_TO_NONE,
        ONE_MANY_TO_NONE,
        ONE_TO_ONE,
        ONE_TO_ONE_MANY,
        ONE_TO_ZERO_MANY,
        ONE_MANY_TO_ONE,
        ONE_MANY_TO_ONE_MANY,
        ONE_MANY_TO_ZERO_MANY,
        ZERO_MANY_TO_ONE,
        ZERO_MANY_TO_ONE_MANY,
        ZERO_MANY_TO_ZERO_MANY,
        NONE
    }
    String name;
    ItemType type;
    ArrayList<attrJSON> attributes = new ArrayList<>();
    ArrayList<attrJSON> operations = new ArrayList<>();
    HashSet<ParticipantJSON> participantList = new HashSet<>();
    ArrayList<Message> messageList = new ArrayList<>();
    ConType conType;
    String startConnection;
    String endConnection;
    Notation notation;
    double height;
    double width;
    double xAxis;
    double yAxis;
    double len;

    double startX;
    double startY;
    double endX;
    double endY;

    public void addOperation(attrJSON operation){
        this.operations.add(operation);

    }
    public void addAttribute(attrJSON attribute){
        this.attributes.add(attribute);
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setType(ItemType type) {
        this.type = type;
    }

    public ItemType getType() {
        return type;
    }

    public void setOperations(ArrayList<attrJSON> operations) {
        this.operations = operations;
    }

    public List<attrJSON> getOperations() {
        return operations;
    }

    public void setEndConnection(String endConnection) {
        this.endConnection = endConnection;
    }

    public String getEndConnection() {
        return endConnection;
    }

    public void setStartConnection(String startConnection) {
        this.startConnection = startConnection;
    }

    public String getStartConnection() {
        return startConnection;
    }

    public void setAttributes(ArrayList<attrJSON> attributes) {
        this.attributes = attributes;
    }

    public List<attrJSON> getAttributes() {
        return attributes;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public double getHeight() {
        return height;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getWidth() {
        return width;
    }

    public ConType getConType() {
        return conType;
    }

    public void setConType(ConType conType) {
        this.conType = conType;
    }

    public void setNotation(Notation notation) {
        this.notation = notation;
    }

    public Notation getNotation() {
        return notation;
    }

    public void setxAxis(double xAxis) {
        this.xAxis = xAxis;
    }

    public double getxAxis() {
        return xAxis;
    }

    public void setyAxis(double yAxis) {
        this.yAxis = yAxis;
    }

    public double getyAxis() {
        return yAxis;
    }

    public double getStartX() {
        return startX;
    }

    public void setStartX(double starX) {
        this.startX = starX;
    }

    public double getStartY() {
        return startY;
    }

    public void setStartY(double startY) {
        this.startY = startY;
    }

    public double getEndX() {
        return endX;
    }

    public void setEndX(double endX) {
        this.endX = endX;
    }

    public double getEndY() {
        return endY;
    }

    public void setEndY(double endY) {
        this.endY = endY;
    }

    public void addParticipant(String name, double x, double boxHeight, double boxY) {
        ParticipantJSON participant = new ParticipantJSON(name, x, boxHeight, boxY);
        this.participantList.add(participant);
    }

    public boolean isClass(){
        if(this.type.equals(ItemType.CLASS))
            return true;
        else
            return false;
    }

    public HashSet<ParticipantJSON> getParticipantList() {
        return participantList;
    }

    public ArrayList<Message> getMessageList() {
        return messageList;
    }

    public void addMessageList(String name, String startObject, String endObject, String type, double x, double y, int len) {
        DClass start = new DClass(startObject);
        DClass end = new DClass(endObject);
        Message message = new Message(name);
        message.setClassStart(start);
        message.setClassEnd(end);
        message.setX(x);
        message.setY(y);
        message.setLen(len);
        switch(type){
            case "sync":
                message.setMessageType(Message.MessageType.SYNCHRONOUS);
                break;
            case "async":
                message.setMessageType(Message.MessageType.ASYNCHRONOUS);
                break;
            case "delete":
                message.setMessageType(Message.MessageType.DELETE);
                break;
            case "reply":
                message.setMessageType(Message.MessageType.REPLY);
                break;
        }
        this.messageList.add(message);
    }

    public double getLen() {
        return len;
    }

    public void setLen(double len) {
        this.len = len;
    }
}
