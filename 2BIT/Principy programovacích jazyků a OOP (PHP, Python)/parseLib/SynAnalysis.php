<?php
/**
 * Project:  Analyzátor kódu v IPPcode22
 *
 * File:     SynAnalysis.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

include "LexAnalysis.php";
include "XML.php";

class SynAnalysis{

    //variable
    private XML $xml;
    private LexAnalysis $lexer;
    private array $operands;
    private Token $token;
    private bool $eof;
    private string $instruction_name;
    private string $type_variable;

    //methods
    function __construct($stdin){
        $this->xml = new XML();
        $this->lexer = new LexAnalysis($stdin);
        $this->eof = false;
    }

    /**
     * function requests from lex,
     * read the first line and check if it is a header or not
     * and
     * write starts program to the xml buffer
     */
    private function pars_first_token(){

        $this->token = $this->lexer->read_header();
        if($this->token->get_token_type() == "eof"){
            $this->eof = true;
            return;
        }
        $this->xml->start_program();
    }

    /**
     * function requests from lex,
     * read new line and check amount of elements in line,
     * depending on the instruction
     */
    private function pars_instruction(){
        $this->token = $this->lexer->new_instruction();
        if($this->token->get_token_type() == "eof"){
            $this->eof = true;
            return;
        }
        $this->instruction_name = strtoupper($this->token->get_inter());
        $this->operands = $this->return_arguments();
//        $this->operands = self::INSTRUCTION[$this->instruction_name];
        $this->lexer->check_count_operands(count($this->operands));

    }

    private function return_arguments(){
        return match ($this->instruction_name) {
            "CREATEFRAME", "PUSHFRAME", "POPFRAME", "RETURN", "BREAK" => [],
            "DEFVAR", "POPS" => ["var"],
            "LABEL", "JUMP", "CALL" => ["label"],
            "PUSHS", "WRITE", "EXIT", "DPRINT" => ["symbol"],
            "READ" => ["var", "type"],
            "MOVE", "NOT", "INT2CHAR", "TYPE", "STRLEN" => ["var", "symbol"],
            "ADD", "SUB", "MUL", "IDIV", "LT", "GT", "EQ", "AND", "OR", "STRI2INT", "CONCAT", "GETCHAR", "SETCHAR" => ["var", "symbol", "symbol"],
            "JUMPIFEQ", "JUMPIFNEQ" => ["label", "symbol", "symbol"]
        };
    }

    /**
     * function takes an argument iter,
     * the argument in which contains the number of the array element
     * in which the operands type is located
     * @param $iter
     */
    private function arg_check($iter){
//        switch($this->instruction_name){
//            case "ADD":
//            case "SUB":
//            case "MUL":
//            case "IDIV":
//            case "INT2CHAR":
//                if($iter == 2 || $iter == 3){
//                    if($this->token->get_token_type() != "int" && $this->token->get_token_type() != "var" ){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type int or variable",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "LT":
//            case "GT":
//            case "EQ":
//                if($iter == 2){
//                    if($this->token->get_token_type() != "nil") {
//                        $this->type_variable = $this->token->get_token_type();
//                    }else{
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "instruction does not support type nil",$this->token->get_countline(),$inter);
//                    }
//                }elseif($iter == 3){
//                    if($this->token->get_token_type() != "nil"){
//                        if($this->type_variable == "var"){
//                            break;
//                        }
//                        if ($this->token->get_token_type() != $this->type_variable) {
//                            $inter = $this->token->get_inter();
//                            MyError::error(MyError::OTHER_LEX_SYN, "the second argument must be the same type as the first",$this->token->get_countline(),$inter);
//                        }
//                    }else{
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "instruction does not support type nil",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "AND":
//            case "OR":
//            case "NOR":
//                if($iter == 2 || $iter == 3){
//                    if($this->token->get_token_type() != "bool" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "instruction only supports bool type",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "STRI2INT":
//            case "GETCHAR":
//                if($iter == 2){
//                    if($this->token->get_token_type() != "string" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type string or variable",$this->token->get_countline(),$inter);
//                    }
//                }elseif($iter == 3){
//                    if($this->token->get_token_type() != "int" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type int or variable",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "CONCAT":
//            case "STRLEN":
//                if($iter == 2 || $iter == 3){
//                    if($this->token->get_token_type() != "string" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type string or variable",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "SETCHAR":
//                if($iter == 2){
//                    if($this->token->get_token_type() != "int" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type int or variable",$this->token->get_countline(),$inter);
//                    }
//                }elseif($iter == 3){
//                    if($this->token->get_token_type() != "string" && $this->token->get_token_type() != "var"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type string or variable",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            case "JUMPIFEQ":
//            case "JUMPIFNEQ":
//                if($iter == 2){
//                        $this->type_variable = $this->token->get_token_type();
//                }elseif($iter == 3){
//                    if($this->type_variable == "var" || $this->type_variable == "nil" || $this->token->get_token_type() == "nil"){
//                        break;
//                    }
//                    if ($this->token->get_token_type() != $this->type_variable) {
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "the second argument must be the same type as the first",$this->token->get_countline(),$inter);
//                    }
//                }
//               break;
//
//            case "EXIT":
//                if($this->token->get_token_type() != "int" && $this->token->get_token_type() != "var"){
//                    $inter = $this->token->get_inter();
//                    MyError::error(MyError::OTHER_LEX_SYN, "expected constant of type int or variable",$this->token->get_countline(),$inter);
//                }
//                break;
//
//            case "READ":
//                if($iter == 2){
//                    if($this->token->get_inter() == "nil"){
//                        $inter = $this->token->get_inter();
//                        MyError::error(MyError::OTHER_LEX_SYN, "instruction does not support type nil",$this->token->get_countline(),$inter);
//                    }
//                }
//                break;
//
//            default:
//                break;
//        }
    }

    /**
     *  main function in pars
     *  function pars first token (first token is always header),
     *  next function in cycle parse line and split it on instruction and operands
     *  next check instruction and operands
     *  if check is normal, instruction and operands writes to xml buffer
     */
    public function pars(){
        $this->pars_first_token();

        while(true){
            $this->pars_instruction();

            //if reads the end of the program,
            // the end of the program write to the xml buffer
            if($this->eof){
                $this->xml->end_program();
                break;
            }

            $text_order = $this->token->get_count_instruction();
            $text_opcode = $this->token->get_inter();
            $this->xml->instruction("$text_order","$text_opcode" );

            $iter = 1;
            foreach($this->operands as $item){
                $this->lexer->get_token($item);
                $this->arg_check($iter);
                $text = $this->token->get_inter();
                $type = $this->token->get_token_type();
                $this->xml->args($type,$iter,$text);
                $iter++;

            }
            $this->xml->end_element();
        }
    }

    public function out_xml(){
        $xml_buffer = $this->xml->get_string();
        echo "$xml_buffer";
    }
}

?>