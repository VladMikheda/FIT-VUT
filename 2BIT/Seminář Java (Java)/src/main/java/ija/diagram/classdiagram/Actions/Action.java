package ija.diagram.classdiagram.Actions;

import ija.diagram.classdiagram.model.ClassDiagram;
import ija.diagram.classdiagram.view.ViewDiagram;

/**
 * Rozhrání pro implementace undo přikazu
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public interface Action {
    void run();
    void undo();
}
