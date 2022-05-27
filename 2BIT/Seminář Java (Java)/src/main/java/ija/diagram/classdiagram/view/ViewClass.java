package ija.diagram.classdiagram.view;

import ija.diagram.classdiagram.controller.ClassContextController;
import ija.diagram.classdiagram.controller.ViewClassController;
import ija.diagram.classdiagram.model.*;
import javafx.event.Event;
import javafx.scene.control.*;
import javafx.scene.input.DragEvent;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Reprezentuje zobrazení třídy v diagramu tříd
 * obsahuje metody pro vytvoření a odstranění zobrazení metod a zobrazení argumentů
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewClass extends VBox {

    private VBox arguments;
    private VBox methods;
    private TextField className = new TextField();
    private Label mainLabel = new Label("Class");
    private ContextMenu contextMenu = new ContextMenu();
    private Map<ArgumentItem, Arguments> argumentsMap = new HashMap<ArgumentItem, Arguments>();
    private Map<MethodItem, Methods> methodsMap = new HashMap<MethodItem, Methods>();

    public ViewClass(){
        super();
    }

    private void setVisualOptions(){
//        super.setWidth(161);
//        super.setHeight(130);
//        super.setStyle("-fx-background-color: black");
        super.setId("classBox");
    }

    /**
     * Nastaví parametry pro normální zařazení
     * @param classContextController ovladač
     */
    private void mainConstructClass(ClassContextController classContextController){
        this.addContextMenu(classContextController);
        mainLabel.setContextMenu(contextMenu);
//        mainLabel.setPrefWidth();
        mainLabel.setId("classLabel");
        mainLabel.setPrefWidth(300);
        className.setUserData(this);
        className.addEventHandler(KeyEvent.ANY, classContextController::inputContextClassName);
        className.setId("className");
        super.getChildren().add(mainLabel);
        super.getChildren().add(className);
        arguments = new VBox();
        methods = new VBox();
        arguments.setId("classArg");
        arguments.setUserData(this);
        methods.setUserData(this);
        super.getChildren().add(arguments);
        super.getChildren().add(methods);
    }

    /**
     *
     * Nastaví kontextovou nabídku pro zobrazení třídy
     * @param classContextController ovladač pro kontextovou nabídku
     */
    private void addContextMenu(ClassContextController classContextController){
        MenuItem menuItem1 = new MenuItem("Add new argument");
        menuItem1.setUserData(this);
        menuItem1.addEventHandler(Event.ANY, classContextController::addArgument);
        MenuItem menuItem2 = new MenuItem("Add new method");
        menuItem2.setUserData(this);
        menuItem2.addEventHandler(Event.ANY, classContextController::addMethod);
        MenuItem menuItem3 = new MenuItem("Delete class");
        menuItem3.setUserData(this);
        menuItem3.addEventHandler(Event.ANY, classContextController::deleteClass);
        contextMenu.getItems().addAll(menuItem1,menuItem2,menuItem3);
    }

    /**
     * Nastaví ovladač pro zobrazení třídy a připraví ji k zobrazení
     * @param classContextController ovladač
     * @param viewClassController  ovladač
     */
    public void show(ClassContextController classContextController, ViewClassController viewClassController){
        this.mainConstructClass(classContextController);
        this.setVisualOptions();
        super.addEventFilter(MouseEvent.MOUSE_DRAGGED, viewClassController::classDraggedMouse);
        super.addEventFilter(MouseEvent.MOUSE_PRESSED, viewClassController::clickToLine);
//        super.addEventFilter(MouseEvent.ANY, viewClassController::relationMoved);
    }
//------------------------------------------------------------------------------------------------------//

    /**
     * Vytvoří instance zobrazení argumentu a nastaví ovladač
     * @param argument argument
     * @param classContextController ovladač
     */
    public void addArgument(Arguments argument, ClassContextController classContextController){
        ArgumentItem argumentItem = new ArgumentItem();
        argumentItem.setUserData(this);
//        argumentItem.setUserData(this);
        argumentItem.mainConstruct(classContextController);
        argumentItem.setArgumentName(argument.getName());
        argumentItem.setArgumentType(argument.getType());
        String accessModifierString = Item.returnString(argument.getAccessModifier());
        argumentItem.setAccessModifier(accessModifierString);
        arguments.getChildren().add(argumentItem);
        argumentsMap.put(argumentItem, argument);
//        arguments.setUserData(this);
    }

    /**
     * Vytvoří instance zobrazeni metodu a nastaví ovladač
     * @param method metod
     * @param classContextController ovladač
     */
    public MethodItem addMethod(Methods method ,ClassContextController classContextController){
        MethodItem methodItem = new MethodItem();
        methodItem.setUserData(this);
        methodItem.mainConstruct(classContextController);
        methodItem.setMethodName(method.getName());
        String accessModifierString = Item.returnString(method.getAccessModifier());
        methodItem.setAccessModifier(accessModifierString);
        methods.getChildren().add(methodItem);
        methodsMap.put(methodItem, method);
        return methodItem;
//        methods.setUserData(this);
    }

    public void deleteArgument(ArgumentItem argumentItem){
        argumentsMap.remove(argumentItem);
    }

    public void deleteMethod(MethodItem argumentItem){
        methodsMap.remove(argumentItem);
    }

    public Arguments returnArgument(ArgumentItem argumentItem){
        return argumentsMap.get(argumentItem);
    }

    public Methods returnMethod(MethodItem methodItem){
        return  methodsMap.get(methodItem);
    }

    public MethodItem returnMethodItem(Methods method){
        Set<Map.Entry<MethodItem,Methods>> methodList = methodsMap.entrySet();
        for(Map.Entry<MethodItem, Methods> map: methodList){
            if(map != null){
                if(method.equals(map.getValue())){
                    return map.getKey();
                }
            }
        }
        return null;
    }

    public void setX(double x){
        super.setLayoutX(x);
    }

    public void setY(double y){
        super.setLayoutY(y);
    }

    public void setClassName(String className){
        this.className.setText(className);
    }

    public void setIdClassName(String id){
        className.setId(id);
    }

    public TextField returnClassNameField(){
        return className;
    }
}
