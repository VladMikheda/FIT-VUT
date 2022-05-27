package ija.diagram.sequencediagram.model;

import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Methods;

import java.util.Random;

/**
 * Třída reprezentuje zpravy mezi objekty
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Message {
    public enum MessageType{
        SYNCHRONOUS,
        ASYNCHRONOUS,
        REPLY,
        DELETE
    }
    private String name;
    private MessageType messageType;
    private double Y;
    private double X = 26;
    private DClass classStart;
    private DClass classEnd;
    private int len = 224;

    public Message(String name, MessageType messageType){
        this.name = name;
        this.messageType = messageType;
    }
    public Message(String name){
        this.name = name;
        this.messageType = MessageType.ASYNCHRONOUS;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public MessageType getMessageType() {
        return messageType;
    }

    public void setMessageType(MessageType messageType) {
        this.messageType = messageType;
    }

    static public MessageType convertType(String string){
        switch (string){
            case "Synchronous":
                return MessageType.SYNCHRONOUS;
            case "Asynchronous":
                return MessageType.ASYNCHRONOUS;
            case "Reply":
                return MessageType.REPLY;
            case "Delete":
                return MessageType.DELETE;
            default:
                return MessageType.ASYNCHRONOUS;
        }
    }

    public double getY() {
        return Y;
    }

    public void setY(double y) {
        Y = y;
    }

    public double getX() {
        return X;
    }

    public void setX(double x) {
        X = x;
    }

    public DClass getClassStart() {
        return classStart;
    }

    public void setClassStart(DClass classStart) {
        this.classStart = classStart;
    }

    public DClass getClassEnd() {
        return classEnd;
    }

    public void setClassEnd(DClass classEnd) {
        this.classEnd = classEnd;
    }

    public void setLen(int len){
        this.len = len;
    }

    public int getLen(){
        return this.len;
    }
}
