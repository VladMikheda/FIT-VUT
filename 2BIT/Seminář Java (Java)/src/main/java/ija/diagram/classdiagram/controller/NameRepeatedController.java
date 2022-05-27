package ija.diagram.classdiagram.controller;
import ija.diagram.ControllerMain;
import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.classdiagram.view.ViewDiagram;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

import java.util.List;
import java.util.Random;

/**
 * Ovladač kontroluje nazvý třid
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class NameRepeatedController {

    @FXML
    private Button itNotOk;

    @FXML
    private Button itOk;

    ControllerMain controllerMain;

    public void initialize(){
        itOk.addEventHandler(ActionEvent.ACTION,this::ok);
        itNotOk.addEventHandler(ActionEvent.ACTION,this::notOk);
    }


    private void ok(ActionEvent actionEvent){
        Stage stage = (Stage)itOk.getScene().getWindow();
        stage.close();
    }
    private void notOk(ActionEvent actionEvent){
        Stage stage = (Stage)itNotOk.getScene().getWindow();
        String abcString="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        Random random = new Random();
        StringBuffer stringBuffer = new StringBuffer();
        List<DClass> dClassList = controllerMain.getClassDiagram().getdClassList();
        ViewDiagram viewDiagram = controllerMain.getViewDiagram();
        for(DClass dClass: dClassList){
            if(dClass.getReapedName()){
                for(int i=0;i< 10 ;i++) {
                    int number = random.nextInt(abcString.length());
                    stringBuffer.append(abcString.charAt(number));
                }
                stringBuffer.append(dClass.getName());
                dClass.setName(stringBuffer.toString());
                dClass.setReapedName(false);
                ViewClass viewClass = viewDiagram.getViewClass(dClass);
                viewClass.setClassName(stringBuffer.toString());
                viewClass.setIdClassName("className");
            }
        }
        stage.close();
    }

    public void setControllerMain(ControllerMain controllerMain){
        this.controllerMain = controllerMain;
    }
}
