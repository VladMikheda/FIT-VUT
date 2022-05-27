package ija.diagram.sequencediagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Methods;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

/**
 * Ovladač kontroluje existence metod v diagramu třid
 * obsahuje metod pro vytvoření metody v třidě
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class MethodNotExistController {

    @FXML
    private Button createMethodButton;

    @FXML
    private Button notCreateButton;

    private String name;
    private ControllerMain controllerMain;
    private DClass dClass;

    public  MethodNotExistController(ControllerMain controllerMain, String name, DClass dClass){
        this.controllerMain = controllerMain;
        this.name = name;
        this.dClass = dClass;
    }

    public void initialize(){
        createMethodButton.addEventHandler(ActionEvent.ACTION, this::createMethod);
        notCreateButton.addEventHandler(ActionEvent.ACTION, this::notCreateMethod);
    }


    public void createMethod(ActionEvent actionEvent){
        Stage stage = (Stage)createMethodButton.getScene().getWindow();
        Methods method = dClass.addMethod(name);
        ViewDiagram viewDiagram = controllerMain.getViewDiagram();
        ViewClass viewClass = viewDiagram.getViewClass(dClass);
        viewDiagram.addMethods(viewClass,method);
        stage.close();
    }

    public void notCreateMethod(ActionEvent actionEvent){
        Stage stage = (Stage)notCreateButton.getScene().getWindow();
        stage.close();
    }


}
