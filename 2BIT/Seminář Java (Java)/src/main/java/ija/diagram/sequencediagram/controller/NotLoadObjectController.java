package ija.diagram.sequencediagram.controller;

import ija.diagram.ControllerMain;
import ija.diagram.sequencediagram.model.SequenceDiagram;
import ija.diagram.sequencediagram.view.ViewObject;
import ija.diagram.sequencediagram.view.ViewSequenceDiagram;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;

/**
 * Ovladač pro kontrolu nekonzistence diagramu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class NotLoadObjectController {

    private ControllerMain controllerMain;
    private String name;
    private SequenceDiagram sequenceDiagram;
    private ViewSequenceDiagram viewSequenceDiagram;

    public NotLoadObjectController(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

    public void addModel(MouseEvent mouseEvent){
        ViewObject viewObject = (ViewObject) ((Label) mouseEvent.getSource()).getUserData();;
        if(viewObject.isOpen()) {
            if (mouseEvent.getButton() == MouseButton.SECONDARY) {
                FXMLLoader loader = new FXMLLoader(ContextObjectController.class.getResource("/main/notLoad.fxml"));
                WindowNotLoadController windowNotLoadController = new WindowNotLoadController(controllerMain, name, sequenceDiagram, viewSequenceDiagram);
                loader.setController(windowNotLoadController);
                Scene scene = null;
                try {
                    scene = new Scene(loader.load());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                Stage createNewMessage = new Stage();
                createNewMessage.setUserData(viewObject);
                createNewMessage.setScene(scene);
                createNewMessage.initModality(Modality.APPLICATION_MODAL);
                createNewMessage.setResizable(false);
                createNewMessage.showAndWait();
            }
        }
    }

    public String getName() {
        return name;
    }

    public void setAll(String name, SequenceDiagram sequenceDiagram, ViewSequenceDiagram viewSequenceDiagram) {
        this.name = name;
        this.sequenceDiagram = sequenceDiagram;
        this.viewSequenceDiagram = viewSequenceDiagram;
    }
}
