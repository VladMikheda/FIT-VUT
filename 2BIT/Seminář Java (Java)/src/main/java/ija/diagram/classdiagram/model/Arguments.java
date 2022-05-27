package ija.diagram.classdiagram.model;


/**
 * Argument třídy
 * obsahuje metody pro dadání položek argumentu a jeho změny
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Arguments extends Item{
    public String type;

    public Arguments(String name, AccessModifier accessModifier) {
        super(name,accessModifier);
    }

    public Arguments(){
        super();
        type = "";
    }
    public void setType(String type){
        this.type = type;
    }

    /**
     * @return typ argumentu
     */
    public String getType(){
        return this.type;
    }
}
