package ija.diagram.sequencediagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import ija.diagram.sequencediagram.model.Message;
import ija.diagram.sequencediagram.model.SObject;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import ija.diagram.sequencediagram.view.ViewObject;
import ija.diagram.sequencediagram.view.ViewSequenceDiagram;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

/**
 * Ovladač pro kontextovou nabidku při nekonzistence diagramu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class WindowNotLoadController {

    @FXML
    private Button createClassButton;

    @FXML
    private Button notCreateButton;
    @FXML
    private TextField numberObject;

    private ControllerMain controllerMain;
    private String name;
    private SequenceDiagram sequenceDiagram;
    ViewSequenceDiagram viewSequenceDiagram;

    public WindowNotLoadController(ControllerMain controllerMain, String name, SequenceDiagram sequenceDiagram, ViewSequenceDiagram viewSequenceDiagram){
        this.controllerMain = controllerMain;
        this.name = name;
        this.sequenceDiagram = sequenceDiagram;
        this.viewSequenceDiagram = viewSequenceDiagram;
    }

    public void initialize(){
        createClassButton.addEventHandler(ActionEvent.ACTION, this::createModel);
        notCreateButton.addEventHandler(ActionEvent.ACTION, this::notCreateModel);
    }

    public void createModel(ActionEvent actionEvent){
        Stage stage = (Stage)notCreateButton.getScene().getWindow();
        Integer number = 0;
        try {
            number = Integer.valueOf(numberObject.getText());
        }catch (NumberFormatException e) {
            controllerMain.writeLabelWarning("It is not number");
            return;
        }
        number--;
        DClass dClass = controllerMain.getClassDiagram().addClass(name);
        SObject sObject = sequenceDiagram.getObject(name);
        if(sObject.getActivationBox()!= null){
            for(Message message :sObject.getActivationBox().getInMessage()){
                dClass.addMethod(message.getName());
            }
        }
        ViewObject viewObject = (ViewObject) stage.getUserData();
        controllerMain.getSequenceDiagram().addObject(sObject, number);
        controllerMain.getViewSequenceDiagram().addObject(viewObject,sObject);
        ViewClass viewClass = controllerMain.getViewDiagram().addNewClass(dClass);
        NotLoadObjectController notLoadObjectController = controllerMain.getNotLoadObjectController();
        ContextObjectController contextObjectController = controllerMain.getContextObjectController();
//        viewObject.removeEventHandler(MouseEvent.ANY,notLoadObjectController::addModel);
        viewObject.removeHendler(controllerMain);
        viewObject.setOpen(false);
        viewObject.returnMainLabel().addEventHandler(MouseEvent.MOUSE_CLICKED,contextObjectController::addNewMessage);
        viewObject.setId("target");
        viewClass.returnClassNameField().textProperty().addListener((observable, oldValue, newValue) ->
        {
            viewObject.returnMainLabel().setText(newValue);
            sObject.setName(newValue);
        });
        controllerMain.getMainPane().getChildren().add(viewClass);
        stage.close();

    }

    public void notCreateModel(ActionEvent actionEvent){
        Stage stage = (Stage)notCreateButton.getScene().getWindow();
        ViewObject viewObject = (ViewObject) stage.getUserData();
        controllerMain.getSequencePane().getChildren().remove(viewObject);
        controllerMain.getSequencePane().getChildren().remove(viewObject.returnMainLabel());
        stage.close();
    }


}
