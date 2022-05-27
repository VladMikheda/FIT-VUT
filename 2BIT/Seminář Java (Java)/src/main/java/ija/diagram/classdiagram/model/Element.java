package ija.diagram.classdiagram.model;


/**
 * Abstraktni třída reprezentuje jednotlivý element
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
abstract class Element {
    private String name;

    public Element(String name) {
        this.name = name;
    }

    public Element(){
        this.name = "";
    }

    public void setName(String name){
        this.name = name;
    }

    public String getName(){
        return this.name;
    }
}
