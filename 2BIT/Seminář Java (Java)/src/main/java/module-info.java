module ija.diagram.gui {
    requires javafx.controls;
    requires javafx.graphics;
    requires javafx.fxml;
    requires json.simple;
    exports ija.diagram;
    opens ija.diagram;
    exports ija.diagram.classdiagram.view;
    opens ija.diagram.classdiagram.view;
    exports ija.diagram.classdiagram.controller;
    opens ija.diagram.classdiagram.controller;
    exports  ija.diagram.sequencediagram.controller;
    opens  ija.diagram.sequencediagram.controller;
    exports ija.diagram.sequencediagram.view;
    opens ija.diagram.sequencediagram.view;
}