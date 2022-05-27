<?php
/**
* Project:  Analyzátor kódu v IPPcode22
*
* File:     error.php
* Subject:  IPP 2022
*
* @author:  Vladislav Mikheda  xmikhe00
*/

class MyError{

    //const error
    public const THIS_IS_OK = 0;
    public const NOT_EXIST_PARAM = 10;
    public const NOT_FOUND_HEADER = 21;
    public const INCORRECT_OPCODE = 22;
    public const OTHER_LEX_SYN = 23;
    public const INTERNAL_ERROR = 99;
    //const
    public const NOT_LINE_NUMBER = -1;

    public static function error($number_error, $message_error,$line_number,$inter){
        if($line_number != -1){
            fwrite(STDERR,"LINE #$line_number: ");
        }
        fwrite(STDERR,"ERROR($number_error):$message_error");
        if($inter){
            fwrite(STDERR, "\n -> $inter");
        }
        exit($number_error);
    }



}


?>