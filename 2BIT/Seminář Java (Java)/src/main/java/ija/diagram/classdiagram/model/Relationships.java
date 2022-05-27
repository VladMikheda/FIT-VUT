package ija.diagram.classdiagram.model;

/**
 * Třída reprezentuje vztahy mezi třídami
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class Relationships{
//    private String nameClassFrom; // todo String ?
    private DClass classTo;   // todo String ?
    private DClass classFrom;
    private Type typeShip;
    private String name = "";

    private double startX;
    private double startY;
    private double endX;
    private double endY;


    /**
     * Enum přístupových modifikátoru
     */
    public enum Type{
        ASSOCIATION,
        /*--------------*/
//        REFLEXIVE,
        AGGREGATION,
        /*------------<>*/
        COMPOSITION,
        /*-------------<<>>*/
        INHERITANCE_GENERALIZATION,
        /*--------------|>*/
        REALIZATION,
        /*- - - - - - - */
        }

    /**
     * Vytvoří instance vztahů
     * @param classFrom jméno třídy od které jde vztah
     * @param typeShip typ
     */
    public Relationships(DClass classFrom, Type typeShip){
        this.classFrom = classFrom;
        this.typeShip = typeShip;
    }

    /**
     * Vytvoří instance vztahu
     * @param classFrom jméno třídy ke které jde vztah
     * @param typeFrom typ začátku vztahu
     * @param startX souřadnice začátku
     * @param startY souřadnice začátku
     * @param endX koncová souřadnice
     * @param endY koncová souřadnice
     */
    public Relationships(DClass classFrom, Type typeFrom, double startX, double startY, double endX, double endY){
        this.classFrom = classFrom;
        this.typeShip = typeFrom;
        this.startX = startX;
        this.startY = startY;
        this.endX = endX;
        this.endY = endY;
    }
    public Relationships(DClass classFrom, DClass classTo, Type typeFrom, double startX, double startY, double endX, double endY){
        this.classFrom = classFrom;
        this.classTo = classTo;
        this.typeShip = typeFrom;
        this.startX = startX;
        this.startY = startY;
        this.endX = endX;
        this.endY = endY;
    }

    /**
     * Vytvoří instance vztahu
     * automaticky dodává typ přístupových modifikátoru
     * @param classFrom jméno třídy ke které jde vztah
     */
    public Relationships(DClass classFrom){
        this.classFrom = classFrom;
        this.typeShip= Type.ASSOCIATION;
    }

    public DClass getClassTo() {
        return this.classTo;
    }

    public void setClassTo(DClass classTo) {
        this.classTo = classTo;
    }

    public DClass getClassFrom() {
        return this.classFrom;
    }

    public void setClassFrom(DClass classFrom) {
        this.classFrom = classFrom;
    }

    public Type getTypeShip() {
        return typeShip;
    }

    public String getTypeShipString() {
        switch (typeShip){
            case ASSOCIATION:
                return "association";
//            case REFLEXIVE:
//                return  "reflexive";
            case AGGREGATION:
                return  "aggregation";
            case COMPOSITION:
                return  "composition";
            case INHERITANCE_GENERALIZATION:
                return "inheritance";
            case REALIZATION:
                return  "realization";
        }
        return "association";
    }

    public void setTypeShip(Type typeFrom) {
        this.typeShip = typeFrom;
    }


    public void setTypeString(String type) {
        switch (type){
            case "association":
                this.typeShip = Type.ASSOCIATION;
                return;
            case "aggregation":
                this.typeShip = Type.AGGREGATION;
                return;
            case "composition":
                this.typeShip = Type.COMPOSITION;
                return;
            case "inheritance":
                this.typeShip = Type.INHERITANCE_GENERALIZATION;
                return;
            case "realization":
                this.typeShip = Type.REALIZATION;
        }
    }



    public double getStartX() {
        return startX;
    }

    public void setStartX(double startX) {
        this.startX = startX;
    }

    public double getStartY() {
        return startY;
    }

    public void setStartY(double startY) {
        this.startY = startY;
    }

    public double getEndX() {
        return endX;
    }

    public void setEndX(double endX) {
        this.endX = endX;
    }

    public double getEndY() {
        return endY;
    }

    public void setEndY(double endY) {
        this.endY = endY;
    }


    public String getName(){
        return name;
    }
}
