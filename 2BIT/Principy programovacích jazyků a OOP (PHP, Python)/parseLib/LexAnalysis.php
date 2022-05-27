<?php
/**
 * Project:  Analyzátor kódu v IPPcode22
 *
 * File:     LexAnalysis.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

include "Token.php";
include "error.php";

class LexAnalysis{

    //variable
    private $stream_stdin;
    private array $split_line;
    private int $count_instruction;
    private int $count_line;
    private Token $token;
    private int $count_request_check;
    private bool $eof;

    //const
    private const TOKEN_TYPE = [
        "INSTRUCTION" => "instruction",
        "VAR" => "var",
        "LABEL" => "label",
        "TYPE" => "type",
        "INT" => "int",
        "NIL" => "nil",
        "STRING" => "string",
        "BOOL" => "bool",
        "HEADER" => "header",
        "EOF" => "eof",
    ];
    private const INSTRUCTION_NAME = [
        "MOVE" => "MOVE",
        "CREATEFRAME" => "CREATEFRAME",
        "PUSHFRAME" => "PUSHFRAME",
        "POPFRAME" => "POPFRAME",
        "DEFVAR" => "DEFVAR",
        "CALL" => "CALL",
        "RETURN" => "RETURN",
        "PUSHS" => "PUSHS",
        "POPS" => "POPS",
        "ADD" => "ADD",
        "SUB" => "SUB",
        "MUL" => "MUL",
        "IDIV" => "IDIV",
        "LT" => "LT",
        "GT" => "GT",
        "EQ" => "EQ",
        "AND" => "AND",
        "OR" => "OR",
        "NOT" => "NOT",
        "INT2CHAR" => "INT2CHAR",
        "STRI2INT" => "STRI2INT",
        "READ" => "READ",
        "WRITE" => "WRITE",
        "CONCAT" => "CONCAT",
        "STRLEN" => "STRLEN",
        "GETCHAR" => "GETCHAR",
        "SETCHAR" => "SETCHAR",
        "TYPE" => "TYPE",
        "LABEL" => "LABEL",
        "JUMP" => "JUMP",
        "JUMPIFEQ" => "JUMPIFEQ",
        "JUMPIFNEQ" => "JUMPIFNEQ",
        "EXIT" => "EXIT",
        "DPRINT" => "DPRINT",
        "BREAK" => "BREAK",
    ];
    private const REGEX_CONST = [
        "INT" => "/^int@([+-]?[0-9][0-9]*|0[xX][0-9a-fA-F][0-9a-fA-F]*|0[0-7][0-7]*)$/",
        "STRING" => "/^string@([^\s#\\\\]|\\\\[0-9][0-9][0-9])*$/",
        "NIL" => "/^nil@nil$/",
        "BOOL" => "/^bool@(true|false)$/",
    ];
    private const REGEX_TYPE = [
        "TYPE_INT" => "/^int$/ ",
        "TYPE_STRING" => "/^string$/",
        "TYPE_BOOL"  => "/^bool$/",
        "TYPE_NIL" => "/^nil$/",
    ];
    private const VARIABLE = "/^[LTG]F@[_$&%*!?A-Za-z-][_$&%*!?a-zA-Z0-9-]*$/";
    private const LABEL = "/^[_$&%*!?a-zA-Z0-9-]*$/";
    private const HEADER = ".IPPcode22";


    //construction
    function __construct($stdin){
        $this->stream_stdin = $stdin;
        $this->token = new Token();
        $this->count_line = 0;
        $this->count_instruction = 0;
        $this->count_request_check = 0;
        $this->eof = false;
    }

    //methods

    //public
    public function get_token($expected_type){
        $this->token_selection($expected_type);
        return $this->token;
    }


    public function read_header(){
        $this->read_line();
        if($this->eof){
            $this->token_eof();
        }else{
            $this->token_selection("header");
        }

        if(count($this->split_line) != 1){
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::OTHER_LEX_SYN,
                "the header line cannot contain anything other than the header ",
                $this->count_line,$inter);
        }

        return $this->token;
    }

    /**
     * reads a line splits it into parts checks if the first part is a statement
     * can be called with a "header" parameter to check the header
     * @return Token
     */
    public function new_instruction(): Token
    {
        $this->read_line();
        if($this->eof){
            $this->token_eof();
        }else{
            $this->token_selection("instruction");
        }
        return $this->token;
    }

    /**
     * checks the number of elements in the read line
     * whether it matches the number of parameters of the instruction
     * @param $count
     * @param string $type
     */
    public function check_count_operands($count){
        if($count != (count($this->split_line) - 1)){
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::OTHER_LEX_SYN,
                "the number of operands in the string does not match from the instruction",
                $this->count_line,$inter);
        }
    }

    /**
     * function reads one line from stdin
     * and
     * split it for a few part
     */
    public function read_line(){

        while(true){
            //read line
            if(feof($this->stream_stdin)){
                $this->eof = true;
                return;
            }
            $string = fgets($this->stream_stdin);

            $this->count_line++;
            $this->count_request_check = 0;

            //if only comments read -> next read
            if (preg_match("/^[\s\t]*#(.)*$/", $string) == 1) {
                continue;
            }
            if (preg_match("/^[\s\t]*$/", $string) == 1) {
                continue;
            }

            //split read line for two: [0] line has no comments, [1] line has only comments or empty
            $two_line= explode("#",$string);


            //split a line into multiply lines by spaces and tabulators
            $this->split_line = preg_split("/[\s\t]+/", $two_line[0]);

            //remove empty strings from array
            $this->split_line = array_diff($this->split_line, array(''));
            $this->split_line = array_values($this->split_line);
            break;
        }

    }


    //private

    /**
     * check if the read parameter matches the type
     * @param $expected_type
     */
    private function token_selection($expected_type){
        $this->count_request_check++;
//        if($this->count_request_check > count($this->split_line)){
//            echo "Limited request";
//            return;
//        }

        switch($expected_type){

            case "var":
                $this->check_var();
                break;

            case "label":
                $this->check_label();
                break;

            case "symbol":
                $this->check_symbol();
                break;

            case "type":
                $this->check_type();
                break;

            case "instruction":
                $this->check_instruction();
                break;

            case "header":
                $this->check_header();
                break;
        }

    }

    /**
     * when accepting the end of the entry, set the token type eof
     */
    private function token_eof(){
        $this->token->set_all("EOF", self::TOKEN_TYPE["EOF"],$this->count_line,$this->count_instruction);
    }

    /**
     * fills the token
     * @param string $token_type
     */
    private function token_filling(string $token_type){
        $inter_word = $this->split_line[$this->count_request_check - 1];
        $this->token->set_all($inter_word, self::TOKEN_TYPE[$token_type],$this->count_line,$this->count_instruction);
    }

    private function check_var(){
        if(preg_match(self::VARIABLE, $this->split_line[$this->count_request_check - 1]) == 1){
            $this->token_filling("VAR");
        }else{
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::OTHER_LEX_SYN, "expected variable",$this->count_line,$inter);
        }
    }

    private function check_label(){
        if(preg_match(self::LABEL, $this->split_line[$this->count_request_check - 1]) == 1){
            $this->token_filling("LABEL");
        }else{
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::OTHER_LEX_SYN, "expected label name",$this->count_line,$inter);
        }
    }

    //variable or constant
    //const string@ -> string ...
    private function check_symbol(){
        if(preg_match(self::VARIABLE, $this->split_line[$this->count_request_check - 1]) == 1){
            $this->token_filling("VAR");
        }else{
            foreach(self::REGEX_CONST as $name => $value){
                if(preg_match($value, $this->split_line[$this->count_request_check - 1]) == 1){
                    $split_list = explode("@",$this->split_line[$this->count_request_check - 1]);
                    $this->split_line[$this->count_request_check - 1] = $split_list[1];
                    $this->token_filling($name);
                    return;
                }
            }
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::OTHER_LEX_SYN, "expected variable or constant",$this->count_line,$inter);
        }
    }

    //int -> type
    private function check_type(){
        foreach(self::REGEX_TYPE as $value){
            if(preg_match($value, $this->split_line[$this->count_request_check - 1]) == 1){
                $this->token_filling("TYPE");
                return;
            }
        }
        $inter = $this->split_line[$this->count_request_check - 1];
        MyError::error(MyError::OTHER_LEX_SYN, "expected type",$this->count_line, $inter);
    }

    private function check_instruction(){
        foreach (self::INSTRUCTION_NAME as $value){
            if(strcasecmp($value, $this->split_line[$this->count_request_check - 1]) == 0){
                $this->count_instruction++;
                $this->token_filling("INSTRUCTION");
                return;
            }
        }
        $inter = $this->split_line[$this->count_request_check - 1];
        MyError::error(MyError::INCORRECT_OPCODE, "Instruction entered incorrectly",$this->count_line,$inter);

    }

    private function check_header(){
        if(strcasecmp(self::HEADER, $this->split_line[$this->count_request_check - 1]) == 0){
            $this->token_filling("HEADER");
        }else{
            $inter = $this->split_line[$this->count_request_check - 1];
            MyError::error(MyError::NOT_FOUND_HEADER, "header not found or invalid",$this->count_line,$inter);
        }
    }

}
?>
