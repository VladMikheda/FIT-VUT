package ija.diagram.sequencediagram.model;

import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.model.Item;
import ija.diagram.classdiagram.model.Methods;
import ija.diagram.classdiagram.model.Relationships;

import java.util.ArrayList;
import java.util.List;

/**
 * Třída reprezentuje sekvenční diagram
 * obsahuje metody pro vytvoření jednotlivých objektu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class SequenceDiagram {
    private List<SObject> sObjectList = new ArrayList<>();
    private final int indent = 250;


    public SObject addObject(DClass dClass){
        SObject sObject =  getObject(dClass);
        if(sObject != null){
            return null;
        }
        sObject = new SObject();
        sObject.setName(dClass.getName());
        sObject.setThisClass(dClass);
        sObject.setX(sObjectList.size() * indent);
        sObjectList.add(sObject);
        return sObject;
    }

    public SObject addObject(SObject sObject, int number){
        sObjectList.add(number,sObject);
        return sObject;
    }


    public SObject addObject(String name){
        SObject sObject =  new SObject(name);
        sObject.setX(sObjectList.size() * indent);
        sObjectList.add(sObject);
        return sObject;
    }

    public List<SObject> getsObjectList() {
        return sObjectList;
    }

    private SObject getObject(DClass dClass){
        for(SObject sObject : sObjectList){
            if (sObject.getName().equals(dClass.getName())){
                return sObject;
            }
        }
        return null;
    }

    public SObject getObject(String name){
        for(SObject sObject: sObjectList){
            if(sObject.getName().equals(name)){
                return sObject;
            }
        }
        return null;
    }

    public void deleteAll(){
        sObjectList.clear();
    }
    public void deleteObject(SObject sObject){
        sObjectList.remove(sObject);
    }

    public int getObjectNumber(SObject sObject){
        return sObjectList.indexOf(sObject);
    }

}
