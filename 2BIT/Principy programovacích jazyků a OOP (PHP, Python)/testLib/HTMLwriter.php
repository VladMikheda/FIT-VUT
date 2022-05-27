<?php

/**
 * Project:  Test
 *
 * File:     HTMLwriter.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

class HTMLwriter
{
    //add html text to variables
    private $html_start = '<!DOCTYPE html><html lang="en"><meta charset="UTF-8">';
    private $html_style = '<style>
    *{
        padding: 0;
        margin: 0;
        border: 0;
    }
    *,*:before,*:after{
        -moz-box-sizing: border-box;
        -webkit-box-sizing: border-box;
        box-sizing: border-box;
    }

    html,body{
        height: 100%;
        width: 100%;
        line-height: 1;
        font-size: 14px;
    }
    h1,h2,h3,h4,h5,h6{font-size:inherit;font-weight: 400;}
    /*--------------------*/
    .main {
        max-width: 75%;
        margin: auto;
    }

    .load {
        height: 50px;
        position: relative;
        background: #949494;
        border-radius: 25px;
    }
    .load > span {
        display: block;
        height: 100%;
        border-radius: 25px;
        background-color: rgb(43,194,83);
        position: relative;
        overflow: hidden;
    }

    .percent{
        font-size: 30px;
        color: white;
        position: absolute;
        top: 50%;
        left: 50%;
        margin-right: -50%;
        transform: translate(-50%, -50%)
    }
    .main{
        background: black;
    }

    .main_header{
        font-size: 50px;
        color: white;
        padding: 10px;
    }

    .table-ch{
        background: #58f59d;
        border-right:  1px solid #FFFFFFFF;
        border-bottom: 1px solid #FFFFFFFF;
        border-left:  1px solid #FFFFFFFF;
        padding: 10px;
        float: left;
        width: 31%;
        font-size: 20px;
        color: black;

    }
    .table-ch:first-child{
        margin-left: 3.5%;
        border-bottom-left-radius: 25px;
    }

    .table-ch:last-child {
        margin-right: 3.5%;
        margin-bottom: 10px;
        border-bottom-right-radius: 25px;
    }

    .table{
        margin-bottom: 60px;
    }

    hr{
        border: none;
        background-color: white;
        color: black;
        height: 2px;
    }

    .OK-box{
        margin-top: 1%;
        padding-top: 6px;
        padding-bottom: 6px;
        display: table;
        width: 94%;
        background: #013d00;
        margin-left: 3.5%;
        margin-right: 3.5%;
        border-radius: 25px;
    }
    .text-ok{
        display: table-cell;
        vertical-align: middle;
        color: white;
    }
    .text-ok:first-child{
        width: 10%;
        font-size: 20px;
        display: table-cell;
        text-align: center;
    }

    .NOT-box{
        margin-top: 1%;
        padding-top: 6px;
        padding-bottom: 6px;
        display: table;
        width: 94%;
        background: #ef0526;
        margin-left: 3.5%;
        margin-right: 3.5%;
        border-radius: 25px;
    }
    .text-not{
        display: table-cell;
        vertical-align: middle;
        color: white;
    }
    .text-not:first-child{
        width: 10%;
        font-size: 20px;
        display: table-cell;
        text-align: center;
    }
</style>';

    private $html_end = '</body> </html>';
    private $html_body = '<head> <title>Test</title> </head> <body class="main"> <h1 class="main_header">Test:</h1>';
    private $html_load = '';
    private $html_final_table = "";
    private $items = [];

    public function set_load($number){
        $this->html_load = '<div>
    <div class="load">
        <span style="width:'. strval($number) . '%"><span class="percent">' . strval($number) . '%</span></span>
    </div>
</div>';
    }

    public function set_table($success, $not_success, $all){
        $first_item = '<div class="table-ch">Successful: ' . strval($success) . '</div>';
        $second_item = '<div class="table-ch">Falied:' . strval($not_success) .'</div>';
        $third_item = '<div class="table-ch">Total:' . strval($all) . '</div>';
        $this->html_final_table ='<div class="table">' . $first_item . $second_item . $third_item . '</div><hr>';
    }

    public function ok_box($test_name, $path){
        $name_item = '<p>Test: ' . $test_name . '</p>';
        $path_item = '<p>Path: ' . $path . '</p>';

        $box_ok = '<div class="OK-box">
    <div class="text-ok"><p Class="ok">OK</p></div>
    <div class="text-ok">' . $name_item . $path_item . ' </div></div>';
        $this->items[] = $box_ok;
//        print_r($this->items);
    }

    public function not_box($test_name, $path, $error, $excepted){
        $name_item = '<p>Test: ' . $test_name . '</p>';
        $path_item = '<p>Path: ' . $path . '</p>';
        $error_item = '<p>ERROR: ' . $error . '</p>';
        $excepted_item = '<p>Excepted: ' . $excepted . '</p>';

        $box_not = '<div class="NOT-box">
    <div class="text-not"><p Class="not">NOT</p></div>
    <div class="text-not">' . $name_item . $path_item . $error_item . $excepted_item . '</div></div>';
        $this->items[] = $box_not;
    }

    public function write_html(){
        //html assembly
        echo $this->html_start;
        echo $this->html_style;
        echo $this->html_body;
        echo $this->html_load;
        echo $this->html_final_table;

        foreach ($this->items as $item){
            echo $item;
        }

        echo $this->html_end;
    }
}

?>