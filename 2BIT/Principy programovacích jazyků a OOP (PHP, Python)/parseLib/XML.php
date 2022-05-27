<?php
/**
 * Project:  Analyzátor kódu v IPPcode22
 *
 * File:     XML.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

class XML{
    private XMLwriter $xml_strig;

    function __construct(){
        $this->xml_strig = new XMLwriter();
        $this->xml_strig->openMemory();
        $this->xml_strig->setIndent(true);
    }

    public function start_program(){
        $this->xml_strig->startDocument("1.0","utf-8");
        $this->xml_strig->startElement("program"); // non close element
        $this->xml_strig->startAttribute("language");
        $this->xml_strig->text("IPPcode22");
        $this->xml_strig->endAttribute();
    }

    public function instruction($text_order, $text_opcode){
        $this->xml_strig->startElement("instruction");
        $this->xml_strig->startAttribute("order");
        $this->xml_strig->text("$text_order");
        $this->xml_strig->startAttribute("opcode");
        $this->xml_strig->text(strtoupper($text_opcode));
        $this->xml_strig->endAttribute();
    }

    public function args($name, $number, $text){
        $this->xml_strig->startElement("arg$number");
        $this->xml_strig->startAttribute("type");
        $this->xml_strig->text("$name");
        $this->xml_strig->endAttribute();
        if($name == "label"){
            $this->xml_strig->writeRaw("$text");
        }else{
            $this->xml_strig->text("$text");
        }
        $this->xml_strig->endElement();
    }

    public function end_element(){
        $this->xml_strig->endElement();
    }

    public function end_program(){
        $this->xml_strig->endElement();//todo
        $this->xml_strig->endDocument();
//        $buffer = $this->xml_strig->outputMemory();//todo
//        echo "$buffer \n"; //todo
    }

    public function get_string(): string
    {
        return $this->xml_strig->outputMemory();
    }


}

?>