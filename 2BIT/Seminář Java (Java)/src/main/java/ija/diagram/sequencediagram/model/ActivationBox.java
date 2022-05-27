package ija.diagram.sequencediagram.model;

import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Methods;

import java.util.ArrayList;
import java.util.List;

/**
 * Třída reprezentuje dobu zpracovávání zpravy
 * obsahuje metody pro přidávání zprav(voláni nebo odpovědi)
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ActivationBox{

    private SObject thisObject;
    private List<Message> outMessage = new ArrayList<>();
    private List<Message> inMessage = new ArrayList<>();
    private double x = 87;
    private double y = 90;
    private double height = 30;
    private final int weight = 26;
    private boolean isDelete = false;
    private boolean reply = false;
    private double plush = 0.0;


    public SObject getThisObject() {
        return thisObject;
    }

    public void setThisObject(SObject thisObject) {
        this.thisObject = thisObject;
    }

    public List<Message> getOutMessage() {
        return outMessage;
    }


    public void addOutMessage(Message outMessage) {
        this.outMessage.add(outMessage);
    }


    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public Message addNewOutMessage(String name, Message.MessageType messageType, int number){
        Message message = new Message(name, messageType);
//        if(reply){
//            message.setY((outMessage.size() + inMessage.size()) *  16 + 16 + plush);
//            plush += 16;
//            reply = false;
//        }else{
//            if(inMessage.size() != 0){
//                message.setY((outMessage.size() + inMessage.size()+1) *  16 + plush);
//                plush = 0;
//            }else{
//                message.setY((outMessage.size()) *  16 + plush);
//                plush = 0;
//            }
//        }

        message.setY(number * 16);
        outMessage.add(message);
        if(height <  number * 16 + 16) {
            height = number * 16 + 16;
        }
        return message;
    }


    public void addNewInMessage(Message message){
        if(message.getMessageType() == Message.MessageType.REPLY){
            reply = true;
        }
        if(height < message.getY()){
            height = message.getY() + 20;
        }else{
            height += 20;
        }
        inMessage.add(message);
    }
    public void addNewInMessageLoad(Message message){
        if(message.getMessageType() == Message.MessageType.REPLY){
            reply = true;
        }
        inMessage.add(message);
    }

    public Message addNewOutMessageLoad(DClass classStart, DClass classEnd, String name, Message.MessageType messageType, double X, double Y, int len){
        Message message = new Message(name, messageType);
        message.setClassStart(classStart);
        message.setClassEnd(classEnd);
        if(messageType == Message.MessageType.REPLY){
            message.setY(Y);
        }else{
            message.setY(Y);
        }
        message.setX(X);
        message.setLen(len);
        outMessage.add(message);
        return message;
    }


    public List<Message> getInMessage() {
        return inMessage;
    }

    public boolean isDelete() {
        return isDelete;
    }

    public void setDelete(boolean delete) {
        isDelete = delete;
    }

    public void deleteActivationBox(){
        this.thisObject.deleteActivationBox();
    }
}
