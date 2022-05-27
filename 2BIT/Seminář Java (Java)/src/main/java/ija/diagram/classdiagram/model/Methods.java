package ija.diagram.classdiagram.model;

/**
 * Třída reprezentuje jednotlivou metodu ve třídě
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Methods extends Item{

    public Methods(String name, AccessModifier accessModifier) {
        super(name, accessModifier);
    }
    public Methods(Methods methods){
        super(methods.getName(),methods.getAccessModifier());
    }
    public Methods(String name) {
        super(name);
    }

    public Methods(){
        super();
    }
}
