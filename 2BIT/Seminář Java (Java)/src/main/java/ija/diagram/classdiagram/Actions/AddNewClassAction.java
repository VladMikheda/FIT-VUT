package ija.diagram.classdiagram.Actions;

import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import javafx.scene.layout.Pane;

/**
 * Vytvoří model a view třídy a zobrazí je
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class AddNewClassAction implements Action {
    ClassDiagram classDiagram;
    ViewDiagram viewDiagram;
    Pane mainPane;
    ViewClass viewClass;

    private DClass dClass;

    public AddNewClassAction(ClassDiagram classDiagram, ViewDiagram viewDiagram, Pane mainPane){
        this.classDiagram = classDiagram;
        this.viewDiagram = viewDiagram;
        this.mainPane = mainPane;
    }

    @Override
    public void run() {
        dClass = classDiagram.addClass();
        viewClass = viewDiagram.addNewClass(dClass);
        mainPane.getChildren().add(viewClass);
    }

    @Override
    public void undo() {
        mainPane.getChildren().remove(viewClass);
        classDiagram.classDelete(dClass);
    }
}
