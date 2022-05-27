package ija.diagram.classdiagram.Actions;

import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.controller.ViewClassController;
import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Relationships;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import ija.diagram.classdiagram.view.ViewRelationships;
import ija.diagram.loader.Loader;
import ija.diagram.sequencediagram.controller.ContextObjectController;
import ija.diagram.sequencediagram.controller.CreateMessageController;
import ija.diagram.sequencediagram.controller.NotLoadObjectController;
import ija.diagram.sequencediagram.model.Message;
import ija.diagram.sequencediagram.model.SObject;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import ija.diagram.sequencediagram.view.ViewActiveBox;
import ija.diagram.sequencediagram.view.ViewMessage;
import ija.diagram.sequencediagram.view.ViewObject;
import ija.diagram.sequencediagram.view.ViewSequenceDiagram;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * Spustí parser pro soubor s daty a vytvoří nové třídy a zobrazí je
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class LoadFileAction implements Action{
    private FileChooser fileChooser;
    private Stage stage;
    private ViewDiagram viewDiagram;
    private Pane mainPane;
    private ClassDiagram classDiagram;
    private SequenceDiagram sequenceDiagram1;
    private SequenceDiagram sequenceDiagram2;
    private SequenceDiagram sequenceDiagram3;
    private Label labelWarning;
    private ViewClassController viewClassController;
    private ControllerMain controllerMain;

    public LoadFileAction(FileChooser fileChooser, Stage stage, ViewDiagram viewDiagram, Pane mainPane, ClassDiagram classDiagram,
                          SequenceDiagram sequenceDiagram1, SequenceDiagram sequenceDiagram2, SequenceDiagram sequenceDiagram3,
                          Label labelWarning, ViewClassController viewClassController, ControllerMain controllerMain) {
        this.fileChooser = fileChooser;
        this.stage = stage;
        this.viewDiagram = viewDiagram;
        this.mainPane = mainPane;
        this.classDiagram = classDiagram;
        this.sequenceDiagram1 = sequenceDiagram1;
        this.sequenceDiagram2 = sequenceDiagram2;
        this.sequenceDiagram3 = sequenceDiagram3;
        this.labelWarning = labelWarning;
        this.viewClassController = viewClassController;
        this.controllerMain = controllerMain;
    }


    @Override
    public void run() {
        File file = fileChooser.showOpenDialog(this.stage);
        if(file == null){
            return;
        }

        String path = file.getAbsolutePath();

        for(ViewClass viewClass : viewDiagram.getDiagramClassMap().keySet()){
            mainPane.getChildren().remove(viewClass);
        }
        for(Line line : viewDiagram.getRelationshipsLineMap().keySet()){
            mainPane.getChildren().remove(line);
        }
        classDiagram.deleteAll();
        viewDiagram.deleteAll();
        ViewSequenceDiagram viewSequenceDiagram1 = controllerMain.getViewSequenceDiagram1();
        ViewSequenceDiagram viewSequenceDiagram2 = controllerMain.getViewSequenceDiagram2();
        ViewSequenceDiagram viewSequenceDiagram3 = controllerMain.getViewSequenceDiagram3();

        for(ViewObject viewObject : viewSequenceDiagram1.getObjectSequenceMap().keySet()){
            controllerMain.getSequencePane1().getChildren().remove(viewObject);
            controllerMain.getSequencePane1().getChildren().remove(viewObject.returnMainLabel());
        }
        for(ViewObject viewObject : viewSequenceDiagram2.getObjectSequenceMap().keySet()){
            controllerMain.getSequencePane2().getChildren().remove(viewObject);
            controllerMain.getSequencePane2().getChildren().remove(viewObject.returnMainLabel());
        }
        for(ViewObject viewObject : viewSequenceDiagram3.getObjectSequenceMap().keySet()){
            controllerMain.getSequencePane3().getChildren().remove(viewObject);
            controllerMain.getSequencePane3().getChildren().remove(viewObject.returnMainLabel());
        }

        sequenceDiagram1.deleteAll();
        sequenceDiagram2.deleteAll();
        sequenceDiagram3.deleteAll();
        viewSequenceDiagram1.deleteAll();
        viewSequenceDiagram2.deleteAll();
        viewSequenceDiagram3.deleteAll();


        Loader loader = new Loader(classDiagram, sequenceDiagram1,sequenceDiagram2,sequenceDiagram3, path);
        loader.loading();
        classDiagram.setAllReaped();
        List<DClass> dClassListCopy = new ArrayList<>(classDiagram.getdClassList());
        for(DClass dClass : dClassListCopy){
            if(dClass.getReapedName()){
                labelWarning.setPrefHeight(labelWarning.getHeight() + 30);
                DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
                Date date = new Date();
                labelWarning.setText(labelWarning.getText() + "\n[" + dateFormat.format(date) + "] class named " + dClass.getName() + "\nremoved due to name repetition \nand its relation ");
                continue;
            }
            ViewClass viewClass = viewDiagram.addNewClass(dClass);
            this.mainPane.getChildren().add(viewClass);
        }
        List<Relationships> relationshipsList = classDiagram.getRelationshipsList();
        List<Relationships> relationshipsListCopy =  new ArrayList<>(relationshipsList);
        for(Relationships relationships : relationshipsListCopy){
            ViewRelationships line = new ViewRelationships();
            this.mainPane.getChildren().add(line);
            line.setViewClassController(viewClassController);
            if(viewDiagram.addRelationships(relationships,line) == null){
                this.mainPane.getChildren().remove(line);
                classDiagram.deleteRelation(relationships);
                continue;
            }
            line.setUserData(mainPane);
            line.setMainPane(mainPane);
            line.addArrow();
            line.setType(relationships.getTypeShipString());
        }


        for(SObject sObject : sequenceDiagram1.getsObjectList()){
            ViewObject viewObject = viewSequenceDiagram1.addNewObject(sObject);
            ContextObjectController contextObjectController = controllerMain.getContextObjectController();
            ViewClass viewClass = controllerMain.getViewDiagram().getViewClass(sObject.getThisClass());
            viewClass.returnClassNameField().textProperty().addListener((observable, oldValue, newValue) ->
            {
                viewObject.returnMainLabel().setText(newValue);
                sObject.setName(newValue);
            });
            controllerMain.getSequencePane1().getChildren().add(viewObject);
            viewObject.returnMainLabel().addEventHandler(MouseEvent.MOUSE_CLICKED, contextObjectController::addNewMessage);
            viewObject.returnMainLabel().setLayoutX(viewObject.getLayoutX());
            viewObject.returnMainLabel().setLayoutY(viewObject.getLayoutY() - 30);
            controllerMain.getSequencePane1().getChildren().add(viewObject.returnMainLabel());
            if(sObject.getActivationBox() != null){
                ViewActiveBox viewActiveBox = viewObject.addViewActionBox(sObject.getActivationBox());
                viewObject.getChildren().add(viewActiveBox);
                for(Message message : sObject.getActivationBox().getOutMessage()){
                    ViewMessage viewMessage = viewActiveBox.addViewMessage(message);
                    viewActiveBox.getChildren().add(viewMessage);
                }
            }
        }

        for(SObject sObject : sequenceDiagram2.getsObjectList()){
            ViewObject viewObject = viewSequenceDiagram2.addNewObject(sObject);
            ContextObjectController contextObjectController = controllerMain.getContextObjectController();
            ViewClass viewClass = controllerMain.getViewDiagram().getViewClass(sObject.getThisClass());
            viewClass.returnClassNameField().textProperty().addListener((observable, oldValue, newValue) ->
            {
                viewObject.returnMainLabel().setText(newValue);
                sObject.setName(newValue);
            });
            controllerMain.getSequencePane2().getChildren().add(viewObject);
            viewObject.returnMainLabel().addEventHandler(MouseEvent.MOUSE_CLICKED, contextObjectController::addNewMessage);
            viewObject.returnMainLabel().setLayoutX(viewObject.getLayoutX());
            viewObject.returnMainLabel().setLayoutY(viewObject.getLayoutY() - 30);
            controllerMain.getSequencePane2().getChildren().add(viewObject.returnMainLabel());
            if(sObject.getActivationBox() != null){
                ViewActiveBox viewActiveBox = viewObject.addViewActionBox(sObject.getActivationBox());
                viewObject.getChildren().add(viewActiveBox);
                for(Message message : sObject.getActivationBox().getOutMessage()){
                    ViewMessage viewMessage = viewActiveBox.addViewMessage(message);
                    viewActiveBox.getChildren().add(viewMessage);
                }
            }
        }


        for(SObject sObject : sequenceDiagram3.getsObjectList()){
            ViewObject viewObject = viewSequenceDiagram3.addNewObject(sObject);
            ContextObjectController contextObjectController = controllerMain.getContextObjectController();
            ViewClass viewClass = controllerMain.getViewDiagram().getViewClass(sObject.getThisClass());
            viewClass.returnClassNameField().textProperty().addListener((observable, oldValue, newValue) ->
            {
                viewObject.returnMainLabel().setText(newValue);
                sObject.setName(newValue);
            });
            controllerMain.getSequencePane3().getChildren().add(viewObject);
            viewObject.returnMainLabel().addEventHandler(MouseEvent.MOUSE_CLICKED, contextObjectController::addNewMessage);
            viewObject.returnMainLabel().setLayoutX(viewObject.getLayoutX());
            viewObject.returnMainLabel().setLayoutY(viewObject.getLayoutY() - 30);
            controllerMain.getSequencePane3().getChildren().add(viewObject.returnMainLabel());
            if(sObject.getActivationBox() != null){
                ViewActiveBox viewActiveBox = viewObject.addViewActionBox(sObject.getActivationBox());
                viewObject.getChildren().add(viewActiveBox);
                for(Message message : sObject.getActivationBox().getOutMessage()){
                    ViewMessage viewMessage = viewActiveBox.addViewMessage(message);
                    viewActiveBox.getChildren().add(viewMessage);
                }
            }
        }

        ViewSequenceDiagram notLoadViewSequenceDiagram = new ViewSequenceDiagram();
        for(SObject sObject : loader.getNotLoadSequenceDiagram().getsObjectList()){
            ViewObject viewObject = notLoadViewSequenceDiagram.addNewObject(sObject);
            viewObject.setId("notLode");
            NotLoadObjectController notLoadObjectController = controllerMain.getNotLoadObjectController();
            notLoadObjectController.setAll(sObject.getName(), loader.getNotLoadSequenceDiagram(), notLoadViewSequenceDiagram);
            controllerMain.getSequencePane1().getChildren().add(viewObject);
            viewObject.returnMainLabel().addEventHandler(MouseEvent.MOUSE_CLICKED, notLoadObjectController::addModel);
            viewObject.returnMainLabel().setLayoutX(viewObject.getLayoutX());
            viewObject.returnMainLabel().setLayoutY(viewObject.getLayoutY() - 30);
            controllerMain.getSequencePane1().getChildren().add(viewObject.returnMainLabel());
            if(sObject.getActivationBox() != null){
                ViewActiveBox viewActiveBox = viewObject.addViewActionBox(sObject.getActivationBox());
                viewObject.getChildren().add(viewActiveBox);
                for(Message message : sObject.getActivationBox().getOutMessage()){
                    ViewMessage viewMessage = viewActiveBox.addViewMessage(message);
                    viewActiveBox.getChildren().add(viewMessage);
                }
            }
        }

    }

    @Override
    public void undo() {
        for(ViewClass viewClass: viewDiagram.getDiagramClassMap().keySet()){
            mainPane.getChildren().remove(viewClass);
        }
        for(ViewRelationships viewRelationships: viewDiagram.getRelationshipsLineMap().keySet()){
            mainPane.getChildren().remove(viewRelationships);
        }
    }
}
