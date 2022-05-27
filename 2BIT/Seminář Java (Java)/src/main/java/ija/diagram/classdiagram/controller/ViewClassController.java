
package ija.diagram.classdiagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.Main;
import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Relationships;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import ija.diagram.classdiagram.view.ViewRelationships;
import javafx.event.Event;
import javafx.event.EventTarget;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SplitMenuButton;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

import static java.lang.Math.abs;

/**
 * Ovladač kontroluje akce s vizuální částí,
 * posunutí třídy, dodaní vztahu(beta)
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewClassController{

    /**Instance hlavního ovladače*/
    private final ControllerMain controllerMain;
    /**Proměna pro zavádění vztahu*/
    private ViewRelationships newLine = null;
    private boolean setStart = false;
    public ViewClassController(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

    /**
     * Připravuje vazbu
     * @param mouseEvent akce tlačení levým tlačítkem myši na třídu
     */
    public void clickToLine(MouseEvent mouseEvent){
        if(mouseEvent.getButton() == MouseButton.PRIMARY) {
            double X = mouseEvent.getX();
            double Y = mouseEvent.getY();
            ViewClass viewClass = (ViewClass) mouseEvent.getSource();
            newLine = new ViewRelationships();
            if(X < 10 || X > viewClass.getWidth() - 10 || Y < 10 || Y > viewClass.getHeight() - 10){
                newLine.setId("relation");
                Pane mainPane = (Pane) viewClass.getParent();
                double newX = 0.0;
                double newY = 0.0;

                if(X < 10){
                    if(X > 5 && Y <= 5){
                        newX = X;
                        newY = 0.0;
                    }else if(X <= 5 && Y > 5){
                        newX = 0.0;
                        newY = Y;
                    }else if(X < 5 && Y <= viewClass.getHeight() - 5){
                        newX = 0.0;
                        newY = Y;
                    }else if(X >= 5 && Y > viewClass.getHeight() - 5){
                        newX = X;
                        newY = viewClass.getHeight();
                    }else{
                        newX = 0.0;
                        newY = Y;

                    }
                }else if(X > viewClass.getWidth() - 10){
                    if(X < viewClass.getWidth() - 5 && Y <= 5){
                        newX = X;
                        newY = 0.0;
                    }else if(X >= viewClass.getWidth() -5 && Y > 5){
                        newX = viewClass.getWidth();
                        newY = Y;
                    }else if(X < viewClass.getWidth() - 5 && Y <= viewClass.getHeight() - 5){
                        newX = viewClass.getWidth();
                        newY = Y;
                    }else if(X >= viewClass.getWidth() - 5 && Y > viewClass.getHeight() - 5){
                        newX = X;
                        newY = viewClass.getHeight();
                    }else{
                        newX =  viewClass.getWidth();
                        newY = Y;

                    }
                }
                else if(Y < 10){
                    newX = X;
                    newY = 0;

                }else if(Y > viewClass.getHeight() - 10){
                    newX = X;
                    newY = viewClass.getHeight();
                }
                double endX = viewClass.getLayoutX() + newX;
                double endY = viewClass.getLayoutY() + newY;

                ViewDiagram viewDiagram = controllerMain.getViewDiagram();
                ClassDiagram classDiagram = controllerMain.getClassDiagram();
                DClass dClass = viewDiagram.returnDClass(viewClass);
                Relationships relationships = classDiagram.addRelationship(dClass,Relationships.Type.ASSOCIATION,newX,newY,endX, endY);
                viewDiagram.addRelationship(newLine, relationships);
                newLine.startXProperty().bind(viewClass.layoutXProperty().add(newX));
                newLine.startYProperty().bind(viewClass.layoutYProperty().add(newY));
                newLine.setEndX(viewClass.getLayoutX() + newX);
                newLine.setEndY(viewClass.getLayoutY() + newY);
                mainPane.getChildren().add(newLine);
                newLine.setClassFrom(viewClass);
                newLine.setStartClassX(newX);
                newLine.setStartClassY(newY);
                newLine.setUserData(mainPane);
                newLine.setMainPane(mainPane);
                newLine.setViewClassController(this);
                setStart = true;
                newLine.setController();
            }
        }
    }
    /**
     * Přenáší třídu do nového místa nebo přenáší vztah
     * @param mouseEvent akce hýbání třídou, pomocí myší se stisknutým středním tlačítkem
     */
    public void classDraggedMouse(MouseEvent mouseEvent){
        if(mouseEvent.getButton() == MouseButton.MIDDLE) {
            ViewClass viewClass = (ViewClass) mouseEvent.getSource();
            DClass dClass = controllerMain.getViewDiagram().returnDClass(viewClass);
            double X = mouseEvent.getX();
            double Y = mouseEvent.getY();
            double nx = viewClass.getLayoutX() - (viewClass.getWidth() / 2) + X;
            double ny = viewClass.getLayoutY() + Y;
            if (nx < 0 && ny > 0) {
                viewClass.setLayoutY(ny);
            } else if (ny < 0 && nx > 0) {
                viewClass.setLayoutX(nx);
            } else if (nx > 0 && ny > 0) {
                viewClass.setLayoutX(nx);
                viewClass.setLayoutY(ny);
            }
            dClass.setX(nx);
            dClass.setY(ny);
        } else if(setStart && mouseEvent.getButton() == MouseButton.PRIMARY){
            ViewClass viewClass = (ViewClass) mouseEvent.getSource();
            double X = mouseEvent.getX();
            double Y = mouseEvent.getY();
            double endX = viewClass.getLayoutX() + X;
            double endY = viewClass.getLayoutY() + Y;
            if (endX < 0 && endY > 0) {
                newLine.setEndY(endY);
            } else if (endY < 0 && endX > 0) {
                newLine.setEndX(endX);
            } else if (endX > 0 && endY > 0) {
                if(Y > 0){
                    endY -= 4;
                }else if(Y < 0){
                    endY += 4;
                }

                if(X > 0){
                    endX -= 4;
                }else if(X < 0){
                    endX += 4;
                }
                newLine.setEndX(endX);
                newLine.setEndY(endY);
            }

            if(setStart && Objects.equals(mouseEvent.getPickResult().getIntersectedNode().getTypeSelector(), "ViewClass")){
                lineConnect(mouseEvent,newLine);
//                ViewClass viewClass2 = (ViewClass) mouseEvent.getPickResult().getIntersectedNode();
//                if(viewClass2 != viewClass){
//                    newLine.addArrow();
//                    newLine.setClassTo(viewClass2);
//                    ViewDiagram viewDiagram = controllerMain.getViewDiagram();
//                    Relationships relationships = viewDiagram.getRelationShip(newLine);
//                    relationships.setClassTo(viewDiagram.returnDClass(viewClass2));
//                    relationships.setEndX(mouseEvent.getPickResult().getIntersectedPoint().getX());
//                    relationships.setEndY(mouseEvent.getPickResult().getIntersectedPoint().getY());
//                    newLine.endXProperty().bind(viewClass2.layoutXProperty().add(mouseEvent.getPickResult().getIntersectedPoint().getX()));
//                    newLine.endYProperty().bind(viewClass2.layoutYProperty().add(mouseEvent.getPickResult().getIntersectedPoint().getY()));
//                    setStart = false;
//                }
            }
        }

    }



    public void extensionLine(MouseEvent mouseEvent){
        if(mouseEvent.getButton() == MouseButton.PRIMARY) {
            ViewRelationships line = (ViewRelationships) mouseEvent.getSource();
            if(line.getClassTo() == null){
                double X = mouseEvent.getX();
                double Y = mouseEvent.getY();
                line.setEndX(X - 3);
                line.setEndY(Y);
                if(setStart && Objects.equals(mouseEvent.getPickResult().getIntersectedNode().getTypeSelector(), "ViewClass")){
                    lineConnect(mouseEvent,line);
                }
            }
        }
    }


    public void lineMenu(MouseEvent mouseEvent){
        if(mouseEvent.getButton() == MouseButton.SECONDARY){
            ViewRelationships line = (ViewRelationships) mouseEvent.getSource();
            FXMLLoader loader = new FXMLLoader(ViewClassController.class.getResource("/main/lineMenu.fxml"));
            ViewRelationshipController viewRelationshipController = new ViewRelationshipController();
            viewRelationshipController.setControllerMain(controllerMain);
            loader.setController(viewRelationshipController);
            Scene scene = null;
            try {
                scene = new Scene(loader.load());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Stage lineMenu = new Stage();
            lineMenu.setUserData(line);
            lineMenu.setScene(scene);
            lineMenu.initModality(Modality.APPLICATION_MODAL);
            lineMenu.setResizable(false);
            lineMenu.showAndWait();
        }
    }

    private void lineConnect(MouseEvent mouseEvent, ViewRelationships line){
        ViewClass viewClass = (ViewClass) mouseEvent.getPickResult().getIntersectedNode();
        if(viewClass != line.getClassFrom()) {
            line.addArrow();
            line.setClassTo(viewClass);
            ViewDiagram viewDiagram = controllerMain.getViewDiagram();
            Relationships relationships = viewDiagram.getRelationShip(line);
            relationships.setClassTo(viewDiagram.returnDClass(viewClass));
            relationships.setEndX(mouseEvent.getPickResult().getIntersectedPoint().getX());
            relationships.setEndY(mouseEvent.getPickResult().getIntersectedPoint().getY());
            line.endXProperty().bind(viewClass.layoutXProperty().add(mouseEvent.getPickResult().getIntersectedPoint().getX()));
            line.endYProperty().bind(viewClass.layoutYProperty().add(mouseEvent.getPickResult().getIntersectedPoint().getY()));
            setStart = false;
        }
    }
}


//
//    double nxe =  (X - (relationships.getEndX() - X));
//    double nye =  Y;
//    double nxs =  (X - (X - relationships.getStartX()));
//    double nys = Y;


// line.startXProperty().bind(viewClass.layoutXProperty().add(viewClass.widthProperty().divide(2)));
//         line.startYProperty().bind(viewClass.layoutYProperty().add(0));
//                double nxs = (X + ((relationships.getEndX() - relationships.getStartX()) / 2));
//                double nys = Y;
