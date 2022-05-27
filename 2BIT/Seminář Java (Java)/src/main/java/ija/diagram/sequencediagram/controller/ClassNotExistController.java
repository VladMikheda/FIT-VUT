package ija.diagram.sequencediagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.view.ViewClass;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

/**
 * Ovladač pro kontrolu existence třidy v diagramu
 * obsahuje metodu pro vytvoření třidy v diagramu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ClassNotExistController {

    @FXML
    private Button createClass;

    @FXML
    private Button notCreate;

    private ControllerMain controllerMain;
    private String name;

    public ClassNotExistController(ControllerMain controllerMain, String name){
        this.controllerMain = controllerMain;
        this.name = name;
    }

    public void initialize(){
        createClass.addEventHandler(ActionEvent.ACTION,this::createNewClass);
        notCreate.addEventHandler(ActionEvent.ACTION,this::notCreateClass);

    }

    public void createNewClass(ActionEvent actionEvent){
        Stage stage = (Stage)createClass.getScene().getWindow();
        DClass dClass = controllerMain.getClassDiagram().addClass(name);
        ViewClass viewClass = controllerMain.getViewDiagram().addNewClass(dClass);
        controllerMain.getMainPane().getChildren().add(viewClass);
        stage.close();
    }

    private void notCreateClass(ActionEvent actionEvent){
        Stage stage = (Stage)notCreate.getScene().getWindow();
        stage.close();
    }


}
