<?php

/**
 * Project:  Test
 *
 * File:     test.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
ini_set('display_errors', 'stderr');
require("./testLib/ArgumentsParse.php");
require("./testLib/TestParseInter.php");
require("./testLib/HTMLwriter.php");

// create instance classes
$argclass = new ArgumentsParse($argv);
$html_writer = new HTMLwriter();
$argclass->arguments();
$argclass->parse_file();
$parse_test = new TestParseInter($argclass->get_arguments(), $argclass->get_test_files(), $html_writer);
$parse_test->test_start();
//arguments($argv);

?>
