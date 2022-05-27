package ija.diagram.sequencediagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Methods;
import ija.diagram.sequencediagram.model.ActivationBox;
import ija.diagram.sequencediagram.model.Message;
import ija.diagram.sequencediagram.model.SObject;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import ija.diagram.sequencediagram.view.ViewActiveBox;
import ija.diagram.sequencediagram.view.ViewMessage;
import ija.diagram.sequencediagram.view.ViewObject;
import ija.diagram.sequencediagram.view.ViewSequenceDiagram;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

import static ija.diagram.sequencediagram.model.Message.convertType;
import static java.lang.Math.abs;

/**
 * Ovladač pro vytvoření zpravy v diagramu
 * kontroluje stav přepínače a nastaví podle toho typ zpravy
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class CreateMessageController {

    @FXML
    private RadioButton Asynchronous;

    @FXML
    private RadioButton Delete;

    @FXML
    private RadioButton Synchronous;

    @FXML
    private RadioButton Reply;

    @FXML
    private Button createMessage;

    @FXML
    private TextField message;

    @FXML
    private Button deleteObjectButton;

    @FXML
    private TextField objectName;

    @FXML
    private TextField NumberOfConnect;


    private ControllerMain controllerMain;

    private ToggleGroup messageGroup = new ToggleGroup();


    public CreateMessageController(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

    public void initialize(){
        Asynchronous.setToggleGroup(messageGroup);
        Synchronous.setToggleGroup(messageGroup);
        Delete.setToggleGroup(messageGroup);
        Reply.setToggleGroup(messageGroup);
        Synchronous.fire();
        createMessage.addEventHandler(ActionEvent.ACTION, this::createNewMessage);
        deleteObjectButton.addEventHandler(ActionEvent.ACTION, this::deleteObject);
    }

    public void deleteObject(ActionEvent actionEvent){
        Stage stage = (Stage)deleteObjectButton.getScene().getWindow();
        SequenceDiagram sequenceDiagram = controllerMain.getSequenceDiagram();
        ViewSequenceDiagram viewSequenceDiagram = controllerMain.getViewSequenceDiagram();
        ViewObject viewObject = (ViewObject) stage.getUserData();
        SObject sObject = viewSequenceDiagram.returnObject(viewObject);
        if(sObject.getActivationBox() != null){
            for(Message message : sObject.getActivationBox().getInMessage()){
                DClass dClass = message.getClassStart();
                SObject sObject1 = sequenceDiagram.getObject(dClass.getName());
                if(sObject1 != null){
                    ViewObject viewObject1  =  viewSequenceDiagram.getViewObject(sObject1);
                    ViewActiveBox viewActiveBox = viewObject1.getViewActiveBox();
                    ViewMessage viewMessage = viewActiveBox.getViewMessage(message);
                    if(viewMessage != null){
                        viewActiveBox.getChildren().remove(viewMessage);
                    }
                }
            }
        }
        Pane mainPane = controllerMain.getSequencePane();
        mainPane.getChildren().remove(viewObject);
        mainPane.getChildren().remove(viewObject.returnMainLabel());
        viewSequenceDiagram.deleteObject(viewObject);
        sequenceDiagram.deleteObject(sObject);
        stage.close();

    }


    public void createNewMessage(ActionEvent actionEvent){
        if(NumberOfConnect.getText().equals("")){
            return;
        }
        Integer number = 0;
        try {
            number = Integer.valueOf(NumberOfConnect.getText());
        }catch (NumberFormatException e) {
            controllerMain.writeLabelWarning("It is not number");
            return;
        }

        Stage stage = (Stage)createMessage.getScene().getWindow();
        //get all diagram
        SequenceDiagram sequenceDiagram = controllerMain.getSequenceDiagram();
        ViewSequenceDiagram viewSequenceDiagram = controllerMain.getViewSequenceDiagram();
        //get names
        String name  = objectName.getText();
        String messageName = message.getText();

        //objects
        ViewObject viewObjectLeft = (ViewObject) stage.getUserData();
        SObject sObjectLeft = viewSequenceDiagram.returnObject(viewObjectLeft);
        SObject sObjectRight = sequenceDiagram.getObject(name);
        if(sObjectRight == null){
            FXMLLoader loader = new FXMLLoader(CreateMessageController.class.getResource("/main/objectDontExist.fxml"));
            ObjectNotExistController objectNotExistController = new ObjectNotExistController(controllerMain, name);
            loader.setController(objectNotExistController);
            Scene scene = null;
            try {
                scene = new Scene(loader.load());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Stage addClass = new Stage();
            addClass.setScene(scene);
            addClass.initModality(Modality.APPLICATION_MODAL);
            addClass.setResizable(false);
            addClass.showAndWait();

            sObjectRight = sequenceDiagram.getObject(name);
            if(sObjectRight == null){
                return;
            }
        }

        DClass dClass = controllerMain.getClassDiagram().returnClass(name);
        List<Methods> methodsList = dClass.getMethodsList();
        Methods method = null;
        RadioButton selectedRadioButton = (RadioButton) messageGroup.getSelectedToggle();
        Message.MessageType messageType = convertType(selectedRadioButton.getText());


        if(messageType != Message.MessageType.DELETE && messageType != Message.MessageType.REPLY){
            for (Methods m : methodsList) {
                if (m.getName().equals(messageName)) {
                    method = m;
                }
            }
            if (method == null) {
                FXMLLoader loader = new FXMLLoader(CreateMessageController.class.getResource("/main/MethodNotExist.fxml"));
                MethodNotExistController methodNotExistController = new MethodNotExistController(controllerMain, messageName, dClass);
                loader.setController(methodNotExistController);
                Scene scene = null;
                try {
                    scene = new Scene(loader.load());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                Stage addClass = new Stage();
                addClass.setScene(scene);
                addClass.initModality(Modality.APPLICATION_MODAL);
                addClass.setResizable(false);
                addClass.showAndWait();

                for (Methods m : methodsList) {
                    if (m.getName().equals(messageName)) {
                        method = m;
                    }
                }
                if (method == null) {
                    return;
                }
            }
        }

        int numberLeftObject = sequenceDiagram.getObjectNumber(sObjectLeft);
        int numberRightObject = sequenceDiagram.getObjectNumber(sObjectRight);
        int len = numberRightObject - numberLeftObject;

        if(sObjectLeft == sObjectRight){
            controllerMain.writeLabelWarning("messages to self is not supported");
            return;
        }
        if(len < 0 && messageType != Message.MessageType.REPLY){
            controllerMain.writeLabelWarning("only reply can be sent back");
            return;
        }else if(len >= 0 && messageType == Message.MessageType.REPLY){
            controllerMain.writeLabelWarning("response cannot be sent\n to next object");
            return;
        }
        if (sObjectLeft.isObjectDelete() || sObjectRight.isObjectDelete()) {
            controllerMain.writeLabelWarning("you cannot send messages \nfrom or to a remote object");
            return;
        }

        if(sObjectLeft.getActivationBox() != null){
            if(sObjectLeft.getActivationBox().getOutMessage().size() != 0) {
                Message lastOutMessage = sObjectLeft.getActivationBox().getOutMessage().get(sObjectLeft.getActivationBox().getOutMessage().size() -1);
                Message lastInMessage = null;
                if(sObjectLeft.getActivationBox().getInMessage().size() != 0){
                    lastInMessage = sObjectLeft.getActivationBox().getInMessage().get(sObjectLeft.getActivationBox().getInMessage().size() - 1);
                }
                if (lastOutMessage != null) {
                    if (lastOutMessage.getMessageType() == Message.MessageType.SYNCHRONOUS) {
                        if (lastInMessage == null) {
                            controllerMain.writeLabelWarning("object expected response");
                            return;
                        } else if (lastInMessage.getMessageType() != Message.MessageType.REPLY) {
                            controllerMain.writeLabelWarning("object expected response");
                            return;
                        } else {
                            if (!lastOutMessage.getName().equals(lastInMessage.getName())) {
                                controllerMain.writeLabelWarning("object expected response");
                                return;
                            }
                        }
                    }
                }
            }
        }
        if(messageType == Message.MessageType.REPLY){
            int countRequest = 0;
            int countResponse = 0;
            if(sObjectRight.getActivationBox() == null){
                controllerMain.writeLabelWarning("the response can only \nbe given to the request");
                return;
            }
            List<Message> messagesOut = sObjectRight.getActivationBox().getOutMessage();
            for(Message m: messagesOut){
                if(m.getName().equals(messageName) && m.getMessageType() != Message.MessageType.REPLY){
                    countRequest++;
                }
            }

            List<Message> messagesIn = sObjectRight.getActivationBox().getInMessage();
            for(Message m: messagesIn){
                if(m.getName().equals(messageName) && m.getMessageType() == Message.MessageType.REPLY){
                    countResponse++;
                }
            }

            if(countRequest == countResponse){
                controllerMain.writeLabelWarning("the response can only \nbe given to the request");
                return;
            }
        }

        if(messageType == Message.MessageType.DELETE && !sObjectRight.isObjectActive()){
            controllerMain.writeLabelWarning("can't delete \nan inactive object");
            return;
        }

        if(messageType == Message.MessageType.DELETE){
            sObjectRight.setObjectDelete(true);
        }else{
            sObjectRight.setObjectActive(true);
        }


        ActivationBox activationBoxLeft = sObjectLeft.getActivationBox();
        ViewActiveBox viewActiveBoxLeft = viewObjectLeft.getViewActiveBox();
        if(activationBoxLeft == null){
            activationBoxLeft = sObjectLeft.addActiveBox();
            viewActiveBoxLeft = viewObjectLeft.addViewActionBox(activationBoxLeft);
            viewObjectLeft.getChildren().add(viewActiveBoxLeft);
        }


        Message message = activationBoxLeft.addNewOutMessage(messageName, convertType(selectedRadioButton.getText()), number);



        if(len < 0){
            len = abs(len);
        }
        if(numberRightObject - numberLeftObject != 1) {
            message.setLen((message.getLen() * (len)) + ((len) - 1) * 26);
        }

        ViewObject viewObjectRight = viewSequenceDiagram.getViewObject(sObjectRight);
        ActivationBox activationBoxRight = sObjectRight.getActivationBox();
        ViewActiveBox viewActiveBoxRight = viewObjectRight.getViewActiveBox();

        if(activationBoxRight == null){
            activationBoxRight = sObjectRight.addActiveBox(message);
            viewActiveBoxRight = viewObjectRight.addViewActionBox(activationBoxRight);
            viewObjectRight.getChildren().add(viewActiveBoxRight);
        }

        message.setClassStart(sObjectLeft.getThisClass());
        message.setClassEnd(sObjectRight.getThisClass());
        activationBoxRight.addNewInMessage(message);
        ViewMessage viewMessage = viewActiveBoxLeft.addViewMessage(message);
        viewActiveBoxLeft.setPrefHeight(activationBoxLeft.getHeight());
        viewActiveBoxLeft.getChildren().add(viewMessage);

        viewActiveBoxRight.setPrefHeight(activationBoxRight.getHeight());
        stage.close();
    }
}
