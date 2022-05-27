package ija.diagram.sequencediagram.view;

import ija.diagram.classdiagram.model.DClass;
import ija.diagram.classdiagram.view.ViewClass;
import ija.diagram.sequencediagram.model.Message;
import javafx.scene.layout.Pane;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Třída reprezentuje zobrazení doby zpracovávání v sekvenčním diagramu
 * obsahuje metody pro vytvoření zobrazení textu zpravy
 * @author Vladislav Mikheda : xmikhe00
 * @author Anvar Kilybayev : xkilyb00
 * @version 0.7.5
 */
public class ViewActiveBox extends Pane {

    private Map<ViewMessage, Message> messageLineMap = new HashMap<ViewMessage, Message>();

    public ViewActiveBox(){
        super();
        super.setId("chunkVisible");
        super.setPrefWidth(26);
        super.setPrefHeight(30);
    }


    public ViewMessage addViewMessage(Message message){
        ViewMessage viewMessage = new ViewMessage(message.getLen(), message.getMessageType());
        viewMessage.setElement();
        viewMessage.setText(message.getName());
        viewMessage.setLayoutX(message.getX());
        viewMessage.setLayoutY(message.getY());
        messageLineMap.put(viewMessage,message);
        return viewMessage;
    }

    public ViewMessage getViewMessage(Message message){
        Set<Map.Entry<ViewMessage, Message>> messageCollection = messageLineMap.entrySet();
        for(Map.Entry<ViewMessage, Message> map: messageCollection){
            if(map != null){
                if(message.equals(map.getValue())){
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
}
