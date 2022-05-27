<?php
/**
 * Project:  Analyzátor kódu v IPPcode22
 *
 * File:     parse.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
require ("./parseLib/SynAnalysis.php");


function help($argv){
    if($argv[1] == "--help" || $argv[1] == "-h"){
        echo "skript parse.php provadi lexikalni a syntakticku kontrolu pro jazyk IPPcode22\nz standartneho vstupu a prevadi ho do XML formatu";
        echo "Pouziti:\n";
        echo "\tphp8.1 parse.php [--help / -h]  vypise help spravu\n";
        echo "\t--help /-h: vypise help spravu\n";
        exit(MyError::THIS_IS_OK);
    }else{
        MyError::error(MyError::NOT_EXIST_PARAM,"only the <--help> argument can be used\n",MyError::NOT_LINE_NUMBER,"");
    }
}


if($argc == 2){
    help($argv);
}elseif($argc > 2){
    MyError::error(MyError::NOT_EXIST_PARAM,"many arguments used\n",MyError::NOT_LINE_NUMBER,"");
}

ini_set('display_errors', 'stderr');
//open stream
$std_sream = fopen("php://stdin", 'r');
//todo error
$parser = new SynAnalysis($std_sream);
$parser->pars();
$parser->out_xml();

?>