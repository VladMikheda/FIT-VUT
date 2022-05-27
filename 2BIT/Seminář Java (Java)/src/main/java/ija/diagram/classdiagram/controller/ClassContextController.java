package ija.diagram.classdiagram.controller;

import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.*;
import ija.diagram.classdiagram.view.*;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;
import java.util.Timer;

import static ija.diagram.classdiagram.model.Item.returnModifier;
import static javafx.scene.input.KeyEvent.*;

/**
 * Ovladač pro kontextovou nabídku třídy
 * obsahuje metody pro vytvoření a odstranění metod, argumentů a odstranění třídy
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ClassContextController {
    /**
     * Instance hlavního ovladače
     */
    private final ControllerMain controllerMain;

    public ClassContextController(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

    /**
     * Přidává argument do třídy
     * @param mouseEvent akce využívání kontextové nabídky pro dodání argumentu
     */
    public void addArgument(Event mouseEvent){
        MenuItem menuItem = (MenuItem) mouseEvent.getSource();
        ViewClass viewClass = (ViewClass) menuItem.getUserData();
        DClass dClass = controllerMain.getViewDiagram().returnDClass(viewClass);
        Arguments argument = dClass.addArgument();
        controllerMain.getViewDiagram().addArguments(viewClass,argument);
    }

    /**
     * Přidává metod do třídy
     * @param mouseEvent akce využívání kontextové nabídky pro dodání metod
     */
    public void addMethod(Event mouseEvent){
        MenuItem menuItem = (MenuItem) mouseEvent.getSource();
        ViewClass viewClass = (ViewClass) menuItem.getUserData();
        DClass dClass = controllerMain.getViewDiagram().returnDClass(viewClass);
        Methods method = dClass.addMethod();
        controllerMain.getViewDiagram().addMethods(viewClass,method);
    }

    /**
     * Odstraní argument z třídy
     * @param mouseEvent akce využívaní kontextové nabídky pro odstranění argumentu
     */
    public void deleteArgument(Event mouseEvent){
        MenuItem menuItem = (MenuItem) mouseEvent.getSource();
        ArgumentItem argumentItem = (ArgumentItem) menuItem.getUserData();
        VBox vBox = (VBox) argumentItem.getParentItem();
        ViewClass viewClass = (ViewClass) vBox.getUserData();
        Arguments argument = viewClass.returnArgument(argumentItem);
        DClass dClass = controllerMain.getViewDiagram().returnDClass(viewClass);
        dClass.argumentDelete(argument);
        viewClass.deleteArgument(argumentItem);
        vBox.getChildren().remove(argumentItem);
    }

    /**
     * Odstraní metodu z třídy
     * @param mouseEvent akce využívaní kontextové nabídky pro odstranění metod
     */
    public void deleteMethod(Event mouseEvent){
        MenuItem menuItem = (MenuItem) mouseEvent.getSource();
        MethodItem methodItem = (MethodItem) menuItem.getUserData();
        VBox vBox = (VBox) methodItem.getParentItem();
        ViewClass viewClass = (ViewClass) vBox.getUserData();
        Methods method = viewClass.returnMethod(methodItem);
        DClass dClass = controllerMain.getViewDiagram().returnDClass(viewClass);
        dClass.methodDelete(method);
        viewClass.deleteMethod(methodItem);
        vBox.getChildren().remove(methodItem);
    }

    /**
     * Odstraní třídu
     * @param mouseEvent akce využívaní kontextové nabídky pro odstranění třídy
     */
    public void deleteClass(Event mouseEvent){
        MenuItem menuItem = (MenuItem) mouseEvent.getSource();
        ViewClass viewClass = (ViewClass) menuItem.getUserData();
        Pane mainPane = (Pane) viewClass.getParent();
        ViewDiagram viewDiagram = controllerMain.getViewDiagram();
        DClass dClass = viewDiagram.returnDClass(viewClass);
        ClassDiagram classDiagram = controllerMain.getClassDiagram();
        classDiagram.classDelete(dClass);
        viewDiagram.deleteClass(viewClass);
        mainPane.getChildren().remove(viewClass);
    }


    public void inputContextMethodName(KeyEvent keyEvent){
        TextField methodName = (TextField) keyEvent.getSource();
        MethodItem methodItem = (MethodItem) methodName.getUserData();
        ViewClass viewClass = (ViewClass) methodItem.getUserData();

        Methods method = viewClass.returnMethod(methodItem);
        method.setName(methodName.getText());
    }


    public void inputContextMethodModifier(Event event){
        ChoiceBox modifier = (ChoiceBox) event.getSource();
        MethodItem methodItem = (MethodItem) modifier.getUserData();
        ViewClass viewClass = (ViewClass) methodItem.getUserData();

        Methods method = viewClass.returnMethod(methodItem);

        if(method == null){
            return;
        }
        method.setAccessModifier(returnModifier(modifier.getValue().toString()));
    }

    public void inputContextArgumentName(KeyEvent keyEvent){
        TextField argumentName = (TextField) keyEvent.getSource();
        ArgumentItem argumentItem = (ArgumentItem) argumentName.getUserData();
        ViewClass viewClass = (ViewClass) argumentItem.getUserData();

        Arguments argument = viewClass.returnArgument(argumentItem);
        argument.setName(argumentName.getText());
    }

    public void inputContextArgumentType(KeyEvent keyEvent){
        TextField argumentType = (TextField) keyEvent.getSource();
        ArgumentItem argumentItem = (ArgumentItem) argumentType.getUserData();
        ViewClass viewClass = (ViewClass) argumentItem.getUserData();

        Arguments argument = viewClass.returnArgument(argumentItem);
        argument.setType(argumentType.getText());
    }


    public void inputContextArgumentModifier(ActionEvent event){
        ChoiceBox modifier = (ChoiceBox) event.getSource();
        ArgumentItem argumentItem = (ArgumentItem) modifier.getUserData();
        ViewClass viewClass = (ViewClass) argumentItem.getUserData();

        Arguments argument = viewClass.returnArgument(argumentItem);

        if(argument == null){
            return;
        }
        argument.setAccessModifier(returnModifier(modifier.getValue().toString()));
    }


    public void inputContextClassName(KeyEvent keyEvent){
        TextField className = (TextField) keyEvent.getSource();
        ViewClass viewClass = (ViewClass) className.getUserData();
        ViewDiagram viewDiagram = controllerMain.getViewDiagram();
        DClass dClass = viewDiagram.returnDClass(viewClass);
        ClassDiagram classDiagram = controllerMain.getClassDiagram();
        if(!classDiagram.setClassName(className.getText(),dClass)){
            if(keyEvent.getEventType() == KEY_TYPED){
                Label labelWarning = controllerMain.getLabelWarning();
                labelWarning.setPrefHeight(labelWarning.getHeight() + 15);
                DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
                Date date = new Date();
                labelWarning.setText(labelWarning.getText() + "\n[" + dateFormat.format(date) + "] сlass name already exists ");
//            className.setText(dClass.getName());
            }
            className.setId("classNameWarning");
            dClass.setReapedName(true);
        }else{
            className.setId("className");
            dClass.setReapedName(false);
        }
    }
}
