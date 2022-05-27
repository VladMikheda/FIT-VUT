package ija.diagram.classdiagram.view;

import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.*;
import javafx.scene.control.Label;
import javafx.scene.shape.Line;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;


/**
 * Třída reprezentuje zobrazení diagramu tříd
 * obsahuje metody pro manipulace s jednotlivými třídami a vztahy
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewDiagram {

    /**Uchovává instance třídy a instance která reprezentuje zobrazení třídy*/
    private Map<ViewClass, DClass> diagramClassMap = new HashMap<ViewClass, DClass>();
    private ControllerMain controllerMain;

    /**Uchovává instance vztahu a instance která reprezentuje zobrazení vztahu*/
    private Map<ViewRelationships, Relationships> relationshipsLineMap = new HashMap<ViewRelationships, Relationships>(); //todo

    public void setControllerMain(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }

    /**
     * Vytvoří instance která reprezentuje zobrazení třídy a uchová ji
     * @param modelClass instance třídy
     * @return vrátí vytvořenou třídu
     */
    public ViewClass addNewClass(DClass modelClass){
        ViewClass viewClass = new ViewClass();
        viewClass.show(controllerMain.getClassContextController(), controllerMain.getViewClassController());
        String className = modelClass.getName();
        List<Arguments> argumentsList = modelClass.getArgumentsList();
        List<Methods> methodsList = modelClass.getMethodsList();
        viewClass.setClassName(className);
        addArguments(viewClass, argumentsList);
        addMethods(viewClass, methodsList);
        diagramClassMap.put(viewClass, modelClass);
        viewClass.setX(modelClass.getX());
        viewClass.setY(modelClass.getY());
        //todo x, y
        return viewClass;
    }

    /**
     * Dodává zobrazení argumentu do instance zobrazení třídy
     * @param viewClass instance zobrazeni třídy
     * @param argumentsList seznam argumentů
     */
    private void addArguments(ViewClass viewClass, List<Arguments> argumentsList){
        for(Arguments argument : argumentsList){
            viewClass.addArgument(argument, controllerMain.getClassContextController());
        }
    }

    /**
     * Dodává zobrazení argumentu do instance zobrazeni třídy
     * @param viewClass instance zobrazeni třídy
     * @param argument argument
     */
    public void addArguments(ViewClass viewClass, Arguments argument){
        viewClass.addArgument(argument, controllerMain.getClassContextController());

    }

    /**
     * Dodává zobrazení metod do instance zobrazení třídy
     * @param viewClass instance zobrazeni třídy
     * @param methodsList seznam metodu
     */
    private void addMethods(ViewClass viewClass, List<Methods> methodsList){
        for(Methods method : methodsList){
            viewClass.addMethod(method, controllerMain.getClassContextController());
        }
    }

    /**
     * Dodává zobrazení argumentu do instance zobrazení třídy
     * @param viewClass instance zobrazení třídy
     * @param method metod
     */
    public void addMethods(ViewClass viewClass, Methods method){
        viewClass.addMethod(method, controllerMain.getClassContextController());
    }

    public DClass returnDClass(ViewClass viewClass){
        return diagramClassMap.get(viewClass);
    }

    public void deleteClass(ViewClass viewClass){
       diagramClassMap.remove(viewClass);
    }

    public void deleteViewRelationship(ViewRelationships viewRelationships){
        relationshipsLineMap.remove(viewRelationships);
    }

    public ViewRelationships addRelationships(Relationships relationships, ViewRelationships viewRelation){
        ViewClass classFrom = getViewClass(relationships.getClassFrom());
        ViewClass classTo = getViewClass(relationships.getClassTo());
        if(classFrom != null){
            viewRelation.startXProperty().bind(classFrom.layoutXProperty().add(relationships.getStartX()));
            viewRelation.startYProperty().bind(classFrom.layoutYProperty().add(relationships.getStartY()));
        }else{
            return null;
        }

        if(classTo != null){
            viewRelation.endXProperty().bind(classTo.layoutXProperty().add(relationships.getEndX()));
            viewRelation.endYProperty().bind(classTo.layoutYProperty().add(relationships.getEndY()));
        }else {
            return null;
        }
        viewRelation.setClassFrom(classFrom);
        viewRelation.setClassTo(classTo);
        viewRelation.setStartClassY(relationships.getStartX());
        viewRelation.setStartClassY(relationships.getStartY());
        viewRelation.setEndClassX(relationships.getEndX());
        viewRelation.setEndClassY(relationships.getEndY());
        viewRelation.setController();

        relationshipsLineMap.put(viewRelation, relationships);
        return viewRelation;
    }

    public void deleteAll(){
        diagramClassMap.clear();
        deleteAllArrow();
        relationshipsLineMap.clear();
    }

    public Map<ViewClass,DClass> getDiagramClassMap(){
        return diagramClassMap;
    }


    public void addRelationship(ViewRelationships viewRelationships, Relationships relationships){
        relationshipsLineMap.put(viewRelationships, relationships);
    }
    public Relationships getRelationShip(ViewRelationships viewRelationships){
        return relationshipsLineMap.get(viewRelationships);
    }

    public Map<ViewRelationships,Relationships> getRelationshipsLineMap(){
        return relationshipsLineMap;
    }

    public ViewClass getViewClass(DClass dClass){
        Set<Map.Entry<ViewClass,DClass>>viewClassCollation = diagramClassMap.entrySet();
        for(Map.Entry<ViewClass, DClass> map: viewClassCollation){
            if(map != null){
                if(dClass.equals(map.getValue())){
                    return map.getKey();
                }
            }
        }
        return null;
    }

    public void deleteAllArrow(){
        Set<Map.Entry<ViewRelationships, Relationships>> viewRelationshipMap = relationshipsLineMap.entrySet();
        for(Map.Entry<ViewRelationships, Relationships> map: viewRelationshipMap){
                map.getKey().deleteArrow();
            }
    }

}
