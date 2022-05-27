package ija.diagram.classdiagram.view;

import ija.diagram.classdiagram.controller.ClassContextController;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 * Reprezentuje zobrazení argumentu ve třídě
 * obsahuje metody pro vytvoření a změnu argumentu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ArgumentItem extends HBox implements ViewItem {

    private final ChoiceBox<String> accessModifier = new ChoiceBox<String>();
    private TextField argumentName = new TextField();
    private TextField argumentType = new TextField();
    ContextMenu contextMenu = new ContextMenu();

    public ArgumentItem(){
        super();
        accessModifier.getItems().add("-");
        accessModifier.getItems().add("+");
        accessModifier.getItems().add("#");
        accessModifier.getItems().add("~");

    }

    private void initContextMenu(ClassContextController classContextController){
        MenuItem menuItem1 = new MenuItem("Delete");
        menuItem1.setUserData(this);
        menuItem1.addEventHandler(Event.ANY, classContextController::deleteArgument);
        contextMenu.getItems().add(menuItem1);
    }

    public void mainConstruct(ClassContextController classContextController){
        accessModifier.setId("classChoice");
        argumentName.setId("classField1");
        argumentType.setId("classField2");
        accessModifier.setUserData(this);
        argumentName.setUserData(this);
        argumentType.setUserData(this);

        accessModifier.addEventHandler(ActionEvent.ACTION,classContextController::inputContextArgumentModifier);
        argumentName.addEventHandler(KeyEvent.ANY, classContextController::inputContextArgumentName);
        argumentType.addEventHandler(KeyEvent.ANY, classContextController::inputContextArgumentType);

        super.getChildren().add(accessModifier);
        super.getChildren().add(argumentName);
        super.getChildren().add(argumentType);
        initContextMenu(classContextController);
        accessModifier.setContextMenu(contextMenu);
        argumentName.setContextMenu(contextMenu);
        argumentType.setContextMenu(contextMenu);
//        accessModifier.setPrefHeight(22);
        argumentName.setPrefHeight(27);
        argumentType.setPrefHeight(27);
        argumentType.setPrefWidth(108);
        accessModifier.setPrefWidth(45);
        argumentName.setPrefWidth(146.9);

    }

    public void setArgumentName(String argumentName){
        this.argumentName.setText(argumentName);
    }

    public void setAccessModifier(String accessModifier){
        this.accessModifier.setValue(accessModifier);
    }

    public void setArgumentType(String typeName){
        this.argumentType.setText(typeName);
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

    public TextField getArgumentType() {
        return argumentType;
    }
}
