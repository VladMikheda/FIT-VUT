package ija.diagram.sequencediagram.view;

import ija.diagram.sequencediagram.model.Message;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;

/**
 * Třída reprezentuje zobrazení zprav v sekvenčním diagramu
 * obsahuje metody pro vytvoření zobrazení zprav a zobrazení šipky
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewMessage extends AnchorPane {

    private Pane line;
    private Pane arrow;
    private Label text;
    private double len =104;
    private Message.MessageType messageType;

    public ViewMessage(int len, Message.MessageType messageType){
        super();
        super.prefHeight(16);
        this.len = len;
        this.messageType = messageType;
    }


    public void setElement(){
        this.setPrefWidth(this.len);
        line = new Pane();
        line.setPrefHeight(2);
        line.setPrefWidth(len);
        line.setId("synchronAsyncronLine");
        AnchorPane.setTopAnchor(line,5.0);
        AnchorPane.setLeftAnchor(line, 0.0);
        AnchorPane.setRightAnchor(line, 0.0);

        arrow = new Pane();
        arrow.setPrefHeight(12);
        arrow.setPrefWidth(12);
        AnchorPane.setTopAnchor(arrow,0.0);
        AnchorPane.setRightAnchor(arrow, 0.0);
        arrow.setId("synchronArrow");

        text = new Label();
        AnchorPane.setTopAnchor(text,-10.0);
        AnchorPane.setBottomAnchor(text,7.0);
//        AnchorPane.setRightAnchor(text, 100.0);
        text.setText("message");
        text.setId("message");

        switch (messageType){
            case SYNCHRONOUS:
                break;
            case ASYNCHRONOUS:
                arrow.setId("sharpArrow");
                break;
            case REPLY:
                setReplay();
                break;
            case DELETE:
                arrow.setId("deleteArrow");
                break;
        }


        this.getChildren().addAll(text,line,arrow);
    }


    private void setReplay(){
        line.setId("replayLine");
        arrow.setId("sharpArrow");
        this.setRotate(180);
        this.setTranslateX(-len - 26);
//        AnchorPane.setTopAnchor(text,-7.0);
        AnchorPane.setBottomAnchor(text,14.0);
        text.setRotate(180);
    }




    public void setText(String name){
        this.text.setText(name);
    }




}
