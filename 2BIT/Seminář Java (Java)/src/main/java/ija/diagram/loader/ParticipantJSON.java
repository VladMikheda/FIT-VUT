package ija.diagram.loader;

/**
 * Třída reprezentuje jednotlivý atribut v {@link objectJSON}
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ParticipantJSON {
    private String name;
    double x;
    double boxHeight;
    double boxY;

    public ParticipantJSON(String name, double x, double boxHeight, double boxY){
        this.name = name;
        this.x = x;
        this.boxHeight = boxHeight;
        this.boxY = boxY;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getX() {
        return x;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public double getBoxHeight() {
        return boxHeight;
    }

    public double getBoxY() {
        return boxY;
    }

    public void setBoxHeight(double boxHeight) {
        this.boxHeight = boxHeight;
    }

    public void setBoxY(double boxY) {
        this.boxY = boxY;
    }
}
