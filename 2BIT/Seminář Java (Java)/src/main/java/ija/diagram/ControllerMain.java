package ija.diagram;
import ija.diagram.classdiagram.Actions.Action;
import ija.diagram.classdiagram.Actions.AddNewClassAction;
import ija.diagram.classdiagram.Actions.LoadFileAction;
import ija.diagram.classdiagram.controller.ClassContextController;
import ija.diagram.classdiagram.controller.NameRepeatedController;
import ija.diagram.classdiagram.controller.ViewClassController;
import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.view.ViewDiagram;
import ija.diagram.loader.Writer;
import ija.diagram.sequencediagram.controller.AddObjectController;
import ija.diagram.sequencediagram.controller.ContextObjectController;
import ija.diagram.sequencediagram.controller.NotLoadObjectController;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import ija.diagram.sequencediagram.view.ViewSequenceDiagram;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.Pane;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.File;
import java.util.*;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

/**
 * Hlavní ovladač,
 * kontroluje hlavní rozhraní
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ControllerMain {
    private ArrayDeque<Action> history = new ArrayDeque<>();
    private ViewClassController viewClassController;
    private ClassContextController classContextController;
    private final SequenceDiagram sequenceDiagram1;
    private final SequenceDiagram sequenceDiagram2;
    private final SequenceDiagram sequenceDiagram3;
    private final ViewSequenceDiagram viewSequenceDiagram1;
    private final ViewSequenceDiagram viewSequenceDiagram2;
    private final ViewSequenceDiagram viewSequenceDiagram3;
    private final ClassDiagram classDiagram;
    private final ViewDiagram viewDiagram;
    private Stage stage;
    private ContextObjectController contextObjectController;
    private NotLoadObjectController notLoadObjectController = new NotLoadObjectController(this);
    private FileChooser fileChooser;

    /**
     * Obsahuje instance třídy tlačítka pro dodávaná třídy
     */
    @FXML
    private Button buttonAdd;

    /**
     * Obsahuje instance třídy tlačítka pro načtení souborů
     */
    @FXML
    private Button buttonLoad;

    /**
     * Obsahuje instance třídy tlačítka pro uložení souborů
     */
    @FXML
    private Button buttonSave;

    /**
     * Obsahuje instance třídy hlavního pole
     */
    @FXML
    private Pane mainPane;

    @FXML
    private Label labelWarning;

    @FXML
    private RadioButton choice1;

    @FXML
    private RadioButton choice2;

    @FXML
    private RadioButton choice3;

    @FXML
    private Pane sequencePane1;

    @FXML
    private Pane sequencePane2;

    @FXML
    private Pane sequencePane3;

    @FXML
    private Button buttonUndo;
    @FXML
    private Button buttonAddObject;


    ToggleGroup sequenceGroup = new ToggleGroup();

    /**
     * Konstruktér ovladače
     * předáváme do lokálních parametrů instance tříd
     * @param classDiagram instance třídy {@link ClassDiagram}
     * @param viewDiagram instance třídy {@link ViewDiagram}
     */
    public ControllerMain(ClassDiagram classDiagram, ViewDiagram viewDiagram,
                          SequenceDiagram sequenceDiagram1, SequenceDiagram sequenceDiagram2, SequenceDiagram sequenceDiagram3,
                          ViewSequenceDiagram viewSequenceDiagram1, ViewSequenceDiagram viewSequenceDiagram2, ViewSequenceDiagram viewSequenceDiagram3,
                          FileChooser fileChooser, Stage stage){
            this.classDiagram = classDiagram;
            this.viewDiagram = viewDiagram;
            this.sequenceDiagram1 = sequenceDiagram1;
            this.sequenceDiagram2 = sequenceDiagram2;
            this.sequenceDiagram3 = sequenceDiagram3;
            this.viewSequenceDiagram1 = viewSequenceDiagram1;
            this.viewSequenceDiagram2 = viewSequenceDiagram2;
            this.viewSequenceDiagram3 = viewSequenceDiagram3;
            this.stage = stage;
            this.fileChooser = fileChooser;
    }


    /**
     * Metoda je spuštěna jen jednou při spuštění programu, pro inicializaci ovladače
     * pro elementy hlavního rozhraní (add,load)
     */
    public void initialize(){
        buttonAdd.addEventFilter(ActionEvent.ACTION,this::addClassAction);
        buttonLoad.addEventFilter(ActionEvent.ACTION,this::loadFile);
        buttonSave.addEventFilter(ActionEvent.ACTION,this::saveFile);
        buttonUndo.addEventFilter(ActionEvent.ACTION,this::buttonUndo);
        buttonAddObject.addEventFilter(ActionEvent.ACTION, this::addObject);
        choice1.setToggleGroup(sequenceGroup);
        choice2.setToggleGroup(sequenceGroup);
        choice3.setToggleGroup(sequenceGroup);
        choice1.fire();
    }
    private void run(Action action){
        history.addLast(action);

        action.run();
    }

    /**
     * Metoda bude spuštěna při zatlačeni tlačítka add
     * vytvoří model a view třídy a zobrazí je
     * @param event přenáší akce tlačení na tlačítko
     */
    private void addClassAction(ActionEvent event){
        run(new AddNewClassAction(classDiagram, viewDiagram, mainPane));
    }

    private void buttonUndo(ActionEvent event){
        if(history.isEmpty())
            return;

        var lastAction = history.removeLast();
        lastAction.undo();
    }


    private void saveFile(ActionEvent event){

        if(classDiagram.checkAllClassName()){
            FXMLLoader loader = new FXMLLoader(ControllerMain.class.getResource("/main/nameRepeat.fxml"));
            NameRepeatedController nameRepeatedController = new NameRepeatedController();
            nameRepeatedController.setControllerMain(this);
            loader.setController(nameRepeatedController);
            Scene scene = null;
            try {
                scene = new Scene(loader.load());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Stage repeatWindow = new Stage();
            repeatWindow.setScene(scene);
            repeatWindow.initModality(Modality.APPLICATION_MODAL);
            repeatWindow.setResizable(false);
            repeatWindow.showAndWait();

            labelWarning.setPrefHeight(labelWarning.getHeight() + 15);
            DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
            Date date = new Date();
            labelWarning.setText(labelWarning.getText() + "\n[" + dateFormat.format(date) + "] Please save again ");
            return;
        }

        File file = fileChooser.showSaveDialog(stage);
        if(file == null){
            return;
        }

        String path = file.getAbsolutePath();

        Writer writer = new Writer(path);
        writer.saveJSON(classDiagram, sequenceDiagram1, sequenceDiagram2, sequenceDiagram3);
    }

    /**
     * Metoda bude spuštěna při zatlačení tlačítka load
     * spustí parser pro soubor s daty a vytvoří nové třídy a zobrazí je
     * @param event přenáší akce tlačení na tlačítko
     */
    private void loadFile(ActionEvent event){
        run(new LoadFileAction(fileChooser, stage, viewDiagram, mainPane, classDiagram, sequenceDiagram1,
                sequenceDiagram2, sequenceDiagram3, labelWarning, viewClassController,this));
    }


    public ViewClassController getViewClassController(){
        return viewClassController;
    }

    public ClassContextController getClassContextController(){
        return classContextController;
    }

    public void setClassContextController(ClassContextController classContextController){
        this.classContextController = classContextController;
    }

    public void setViewClassController(ViewClassController viewClassController){
        this.viewClassController = viewClassController;
    }

    public void addObject(ActionEvent actionEvent){
        if(classDiagram.getdClassList().isEmpty()){
            writeLabelWarning("Transformation warning:\n---There are no entities.");
            return;
        }

        FXMLLoader loader = new FXMLLoader(ControllerMain.class.getResource("/main/objectNewWindow.fxml"));
        AddObjectController addObjectController = new AddObjectController();
        addObjectController.setControllerMain(this);
        loader.setController(addObjectController);
        Scene scene = null;
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        Stage addObjectWindow = new Stage();
        addObjectWindow.setScene(scene);
        addObjectWindow.initModality(Modality.APPLICATION_MODAL);
        addObjectWindow.setResizable(false);
        addObjectWindow.showAndWait();
    }

    public SequenceDiagram getSequenceDiagram1() {
        return sequenceDiagram1;
    }
    public SequenceDiagram getSequenceDiagram2() {
        return sequenceDiagram2;
    }
    public SequenceDiagram getSequenceDiagram3() {
        return sequenceDiagram3;
    }

    public Pane getSequencePane1() {
        return sequencePane1;
    }
    public Pane getSequencePane2() {
        return sequencePane2;
    }
    public Pane getSequencePane3() {
        return sequencePane3;
    }


    public SequenceDiagram getSequenceDiagram() {
        RadioButton selectedRadioButton = (RadioButton) sequenceGroup.getSelectedToggle();
        switch (selectedRadioButton.getText()){
            case "1":
                return sequenceDiagram1;
            case "2":
                return sequenceDiagram2;
            case "3":
                return sequenceDiagram3;
        }
        return sequenceDiagram1;
    }

    public ViewSequenceDiagram getViewSequenceDiagram(){
        RadioButton selectedRadioButton = (RadioButton) sequenceGroup.getSelectedToggle();
        switch (selectedRadioButton.getText()){
            case "1":
                return viewSequenceDiagram1;
            case "2":
                return viewSequenceDiagram2;
            case "3":
                return viewSequenceDiagram3;
        }
        return viewSequenceDiagram1;
    }
    public ViewSequenceDiagram getViewSequenceDiagram1() {
        return viewSequenceDiagram1;
    }
    public ViewSequenceDiagram getViewSequenceDiagram2() {
        return viewSequenceDiagram2;
    }
    public ViewSequenceDiagram getViewSequenceDiagram3() {
        return viewSequenceDiagram3;
    }

    public ClassDiagram getClassDiagram(){
        return classDiagram;
    }

    public ViewDiagram getViewDiagram(){
        return viewDiagram;
    }

    public Label getLabelWarning(){
        return labelWarning;
    }


    public Pane getSequencePane(){
        RadioButton selectedRadioButton = (RadioButton) sequenceGroup.getSelectedToggle();
        switch (selectedRadioButton.getText()){
            case "1":
                return sequencePane1;
            case "2":
                return sequencePane2;
            case "3":
                return sequencePane3;
        }
        return sequencePane1;
    }


    public Pane getMainPane(){
        return mainPane;
    }

    public void setContextObjectController(ContextObjectController contextObjectController){
        this.contextObjectController = contextObjectController;
    }

    public ContextObjectController getContextObjectController(){
        return this.contextObjectController;
    }

    public void writeLabelWarning(String text){
        labelWarning.setPrefHeight(labelWarning.getHeight() + 30);
        DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
        Date date = new Date();
        labelWarning.setText(labelWarning.getText() + "\n[" + dateFormat.format(date) + "] " + text);
    }

    public NotLoadObjectController getNotLoadObjectController() {
        return notLoadObjectController;
    }
}
