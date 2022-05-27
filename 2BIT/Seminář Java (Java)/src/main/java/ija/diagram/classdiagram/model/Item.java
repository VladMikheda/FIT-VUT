package ija.diagram.classdiagram.model;

//import static sun.awt.X11.XBaseWindow.VISIBLE;

/**
 * Abstraktní třída reprezentuje jednotlivý item v třídě
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
abstract public class Item extends Element{

    public AccessModifier accessModifier;

    public enum AccessModifier{
        PRIVATE,    // -
        PUBLIC,     // +
        PROTECTED,  // #
        VISIBLE,    // ~
    }

    public Item(String name, AccessModifier accessModifier) {
        super(name);
        this.accessModifier = accessModifier;
    }

    public Item(String name){
        super(name);
        this.accessModifier =AccessModifier.PUBLIC;
    }

    public Item(){
        super();
        this.accessModifier = AccessModifier.PUBLIC;
    }

    public void setAccessModifier(AccessModifier accessModifier){
        this.accessModifier = accessModifier;
    }

    public AccessModifier getAccessModifier(){
        return accessModifier;
    }

    /**
     * Metoda převádí enum typ v String
     * @param accessModifier enum přístupový modifikátor
     * @return String
     */
    public static String returnString(AccessModifier accessModifier){
        switch (accessModifier){
            case PRIVATE:
                return "-";
            case PROTECTED:
                return  "#";
            case PUBLIC:
                return  "+";
            case VISIBLE:
                return  "~";
            //todo add method, for read warning if access modifier not correct
        }
        return "+";
    }


    public static AccessModifier returnModifier(String accessModifier){
        switch (accessModifier){
            case "-":
                return AccessModifier.PRIVATE;
            case "#":
                return  AccessModifier.PROTECTED;
            case "+":
                return  AccessModifier.PUBLIC;
            case "~":
                return  AccessModifier.VISIBLE;
            //todo add method, for read warning if access modifier not correct
        }
        return AccessModifier.PUBLIC;
    }
}
