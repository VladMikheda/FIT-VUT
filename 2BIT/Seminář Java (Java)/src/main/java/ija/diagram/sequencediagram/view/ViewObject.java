package ija.diagram.sequencediagram.view;

import ija.diagram.ControllerMain;
import ija.diagram.sequencediagram.controller.ContextObjectController;
import ija.diagram.sequencediagram.controller.NotLoadObjectController;
import ija.diagram.sequencediagram.model.ActivationBox;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;

/**
 * Reprezentuje zobrazení objektu v sekvenčním diagramu
 * obsahuje metody pro vytvoření a odstranění zobrazení objektu, vytvoření a odstranění zobrazení doby zpracovávání
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewObject extends Pane {
    private Label mainLabel = new Label("Object");
    private Line lifeLine = new Line();
    private ViewActiveBox viewActiveBox = null;
    private boolean open = true;

    public ViewObject(){
        super();
    }
    private void setVisualOptions(){
        mainLabel.setUserData(this);
        mainLabel.setId("objectLabel");
        lifeLine.setId("lifeLine");
        lifeLine.setStartX(100);
        lifeLine.setStartY(80);
        lifeLine.setEndX(100);
        lifeLine.setEndY(600);
        mainLabel.setPrefWidth(200);
        mainLabel.setPrefHeight(80);
        super.setPrefHeight(600);
        super.setPrefWidth(200);
        super.getChildren().add(lifeLine);
//        super.getChildren().add(mainLabel);
    }

    public void show(){
        this.setVisualOptions();
    }

    public void setX(double x){
        super.setLayoutX(x);
    }
    public void setY(double y){
        super.setLayoutY(y);
    }
    public double getX(){
        return super.getLayoutX();
    }
    public double getY(){
        return super.getLayoutY();
    }

    public void setObjectName(String objectName) {
        this.mainLabel.setText(objectName);
    }

    public ViewActiveBox getViewActiveBox(){
        return this.viewActiveBox;
    }

    public ViewActiveBox addViewActionBox(ActivationBox activationBox){
        viewActiveBox = new ViewActiveBox();
        viewActiveBox.setY(activationBox.getY());
        viewActiveBox.setX(activationBox.getX());
        viewActiveBox.setPrefHeight(activationBox.getHeight());
        return  viewActiveBox;
    }

    public Label returnMainLabel(){
        return mainLabel;
    }

    public void removeHendler(ControllerMain controllerMain){
        NotLoadObjectController notLoadObjectController = controllerMain.getNotLoadObjectController();
        this.removeEventHandler(MouseEvent.MOUSE_CLICKED,notLoadObjectController::addModel);
        super.removeEventHandler(MouseEvent.MOUSE_CLICKED,notLoadObjectController::addModel);
        mainLabel.removeEventHandler(MouseEvent.MOUSE_CLICKED,notLoadObjectController::addModel);
        lifeLine.removeEventHandler(MouseEvent.MOUSE_CLICKED,notLoadObjectController::addModel);
        viewActiveBox.removeEventHandler(MouseEvent.MOUSE_CLICKED,notLoadObjectController::addModel);
    }

    public boolean isOpen() {
        return open;
    }

    public void setOpen(boolean open) {
        this.open = open;
    }
}
