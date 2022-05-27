package ija.diagram.classdiagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Methods;
import ija.diagram.classdiagram.model.Relationships;
import ija.diagram.classdiagram.view.*;
import ija.diagram.sequencediagram.view.ViewMessage;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.MenuItem;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

/**
 * Ovladač pro kontextovou nabídku relací
 * obsahuje metody pro změnu relace
 * včetně agregace, asociace, compozice, realizce, dědičnosti a zrušeni relace
 * @author Vladislav Mikheda : xmikhe0
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewRelationshipController {

    @FXML
    private MenuItem aggregationButton;

    @FXML
    private MenuItem associationButton;

    @FXML
    private MenuItem compositionButton;

    @FXML
    private MenuItem deleteButton;

    @FXML
    private MenuItem inheritanceButton;

    @FXML
    private MenuItem realizationButton;

    @FXML
    private AnchorPane linePane;

    private ControllerMain controllerMain;

    public void initialize(){
        aggregationButton.addEventHandler(ActionEvent.ACTION,this::aggregationAction);
        associationButton.addEventHandler(ActionEvent.ACTION,this::associationAction);
        compositionButton.addEventHandler(ActionEvent.ACTION,this::compositionAction);
        inheritanceButton.addEventHandler(ActionEvent.ACTION,this::inheritanceAction);
        realizationButton.addEventHandler(ActionEvent.ACTION,this::realizationAction);
        deleteButton.addEventHandler(ActionEvent.ACTION,this::deleteAction);
    }

    void aggregationAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            Relationships relationships = controllerMain.getViewDiagram().getRelationShip(line);
            relationships.setTypeShip(Relationships.Type.AGGREGATION);
            line.setAggregation();
        }
        stage.close();
    }

    void associationAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            Relationships relationships = controllerMain.getViewDiagram().getRelationShip(line);
            relationships.setTypeShip(Relationships.Type.ASSOCIATION);
            line.setAssociation();
        }
        stage.close();
    }

    void compositionAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            Relationships relationships = controllerMain.getViewDiagram().getRelationShip(line);
            relationships.setTypeShip(Relationships.Type.COMPOSITION);
            line.setComposition();
        }
        stage.close();
    }

    void deleteAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            line.deleteArrow();
        }
        Pane mainPane = line.getMainPane();
        mainPane.getChildren().remove(line);
        ViewDiagram viewDiagram= controllerMain.getViewDiagram();
        ClassDiagram classDiagram = controllerMain.getClassDiagram();
        Relationships relationships = viewDiagram.getRelationShip(line);
        viewDiagram.deleteViewRelationship(line);
        classDiagram.deleteRelation(relationships);
        stage.close();
    }

    void inheritanceAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            Relationships relationships = controllerMain.getViewDiagram().getRelationShip(line);
            DClass dClassFrom = relationships.getClassFrom();
            DClass dClassTo = relationships.getClassTo();
            for(Methods method1 : dClassTo.getMethodsList()){
                for(Methods method2 : dClassFrom.getMethodsList()){
                    if(method1.getName().equals(method2.getName())){
                        ViewClass viewClass = controllerMain.getViewDiagram().getViewClass(dClassFrom);
                        MethodItem methodItem = viewClass.returnMethodItem(method2);
                        methodItem.newColor();
                    }
                }
            }
            relationships.setTypeShip(Relationships.Type.INHERITANCE_GENERALIZATION);
            line.setInheritance();
        }
        stage.close();
    }

    void realizationAction(ActionEvent event) {
        Stage stage = (Stage)linePane.getScene().getWindow();
        ViewRelationships line = (ViewRelationships) stage.getUserData();
        if(line.getClassTo() != null) {
            Relationships relationships = controllerMain.getViewDiagram().getRelationShip(line);
            relationships.setTypeShip(Relationships.Type.REALIZATION);
            line.setRealization();
        }
        stage.close();
    }

    public void setControllerMain(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

}
