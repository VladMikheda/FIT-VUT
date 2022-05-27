package ija.diagram.classdiagram.view;

import ija.diagram.classdiagram.controller.ClassContextController;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventType;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 * Reprezentuje zobrazení metod ve třídě
 * obsahuje metody pro vytvoření a změnu metod
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class MethodItem extends HBox implements ViewItem{

    private final ChoiceBox<String> accessModifier = new ChoiceBox<String>();
    private TextField argumentName = new TextField();
    ContextMenu contextMenu = new ContextMenu();

    public MethodItem(){
        super();
        accessModifier.getItems().add("-");
        accessModifier.getItems().add("+");
        accessModifier.getItems().add("#");
        accessModifier.getItems().add("~");

    }

    public void mainConstruct(ClassContextController classContextController){
        accessModifier.setId("classChoice");
        accessModifier.setUserData(this);
        accessModifier.addEventHandler(ActionEvent.ACTION, classContextController::inputContextMethodModifier);
        argumentName.setId("classField2");
        argumentName.setUserData(this);
        argumentName.addEventHandler(KeyEvent.ANY,classContextController::inputContextMethodName);
        super.getChildren().add(accessModifier);
        super.getChildren().add(argumentName);
        initContextMenu(classContextController);
        accessModifier.setContextMenu(contextMenu);
        argumentName.setContextMenu(contextMenu);
//        argumentName.setPrefWidth(212); //todo normal


        argumentName.setPrefHeight(27);
        accessModifier.setPrefWidth(45);
        argumentName.setPrefWidth(255);

    }

    private void initContextMenu(ClassContextController classContextController){
        MenuItem menuItem1 = new MenuItem("Delete");
        menuItem1.setUserData(this);
        menuItem1.addEventHandler(Event.ANY, classContextController::deleteMethod);
        contextMenu.getItems().add(menuItem1);
    }


    public void setMethodName(String argumentName){
        this.argumentName.setText(argumentName);
    }

    public void setAccessModifier(String accessModifier){
        this.accessModifier.setValue(accessModifier);
    }


    public VBox getParentItem(){
        return (VBox) this.getParent();
    }

    public ChoiceBox<String> getAccessModifier() {
        return accessModifier;
    }

    public TextField getArgumentName() {
        return argumentName;
    }

    public void newColor(){
        accessModifier.setId("m2");
        argumentName.setId("m1");
    }
}
