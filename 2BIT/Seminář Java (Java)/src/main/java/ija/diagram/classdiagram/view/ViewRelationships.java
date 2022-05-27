package ija.diagram.classdiagram.view;

import ija.diagram.classdiagram.controller.ClassContextController;
import ija.diagram.classdiagram.controller.ViewClassController;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
/**
 * Třída reprezentuje zobrazení relací v diagramu
 * obsahuje metody pro vytvoření a odstranění zobrazení relací
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewRelationships extends Line {

    private ViewClass classFrom;
    private ViewClass classTo = null;
    private double startClassX;
    private double startClassY;
    private double endClassX;
    private double endClassY;
    private Pane arrow;
    private Pane mainPane;
    private ViewClassController viewClassController;

    public ViewRelationships() {
        super();
        super.setId("relation");

    }

    public void setViewClassController(ViewClassController viewClassController) {
        this.viewClassController = viewClassController;
    }

    public void setController() {
        this.addEventFilter(MouseEvent.MOUSE_DRAGGED, viewClassController::extensionLine);
        this.addEventFilter(MouseEvent.MOUSE_CLICKED,viewClassController::lineMenu);
    }


    public void addArrow(){
        arrow = new Pane();
        arrow.setPrefWidth(10);
        arrow.setPrefHeight(10);
        arrow.setRotate(45);
        arrow.setTranslateY(-5);
        arrow.setTranslateX(-3);

        arrow.layoutXProperty().bind(this.endXProperty());
        arrow.layoutYProperty().bind(this.endYProperty());
        arrow.setId("arrowInvisible");
        mainPane.getChildren().add(arrow);
    }

    public void deleteArrow(){
        mainPane.getChildren().remove(arrow);
    }

    public void setAggregation(){
        this.setId("relation");
        this.arrow.setId("arrowAggregation");
    }

    public void setAssociation(){
        this.setId("relation");
        this.arrow.setId("arrowInvisible");
    }

    public void setComposition(){
        this.setId("relation");
        this.arrow.setId("arrowComposition");
    }

    public void setInheritance(){
        this.setId("relation");
        this.arrow.setId("arrowInheritance");
    }

    public void setRealization(){
        this.setId("realizationLine");
        this.arrow.setId("arrowInvisible");
    }

    public void setType(String type){
        switch (type){
            case "association":
                setAssociation();
                return;
            case "aggregation":
                setAggregation();
                return;
            case "composition":
               setComposition();
               return;
            case "inheritance":
                setInheritance();
                return;
            case "realization":
                setRealization();
        }
    }


    public void setClassFrom(ViewClass classFrom) {
        this.classFrom = classFrom;
    }

    public ViewClass getClassFrom() {
        return classFrom;
    }

    public double getStartClassX() {
        return startClassX;
    }

    public void setStartClassX(double startClassX) {
        this.startClassX = startClassX;
    }

    public double getStartClassY() {
        return startClassY;
    }

    public void setStartClassY(double startClassY) {
        this.startClassY = startClassY;
    }

    public double getEndClassX() {
        return endClassX;
    }

    public void setEndClassX(double endClassX) {
        this.endClassX = endClassX;
    }

    public double getEndClassY() {
        return endClassY;
    }

    public void setEndClassY(double endClassY) {
        this.endClassY = endClassY;
    }

    public Pane getArrow(){
        return this.arrow;
    }

    public void setMainPane(Pane mainPane){
        this.mainPane = mainPane;
    }

    public Pane getMainPane(){
        return this.mainPane;
    }

    public ViewClass getClassTo() {
        return classTo;
    }

    public void setClassTo(ViewClass classTo) {
        this.classTo = classTo;
    }
}
