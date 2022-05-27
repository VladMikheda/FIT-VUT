<?php
/**
 * Project:  Test
 *
 * File:     TestParseInter.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

class TestParseInter
{
    //start tests
    private $jexampath = "/pub/courses/ipp/jexamxml/";
    private $pars_only;
    private $test_dirs = [];
    private $noclean;
    private $parse_script;
    private $main_dir;
    private $html_writer;
    private $jexampath_opt;
    private $int_only;
    private $int_script;
    private $file_test_next = [];
    private $arguments = [];

    function __construct($arguments, $test_dirs, $html_writer){
        // setting all file paths
        $this->html_writer = $html_writer;
        if($arguments["parse-script"] == ""){
            $this->parse_script = posix_getcwd() . "/parse.php";
        }else{
            $this->parse_script = $arguments["parse-script"];
        }
        if($arguments["jexampath"] == ""){
            $path = $this->jexampath;
            $this->jexampath = $this->jexampath . "jexamxml.jar";
            $this->jexampath_opt = $path . "options";
        }else{
            $this->jexampath = $arguments["jexampath"] . "jexamxml.jar";
            $this->jexampath_opt = $arguments["jexampath"] . "options";
        }
        $this->test_dirs = $test_dirs;
        $this->noclean = $arguments["noclean"];
        if($arguments["int-script"] == ""){
            $this->int_script = posix_getcwd() . "/interpret.py";
        }else{
            $this->int_script = $arguments["int-script"];
        }
        $this->int_only = $arguments["int-only"];
        $this->pars_only = $arguments["parse-only"];
        $this->main_dir = posix_getcwd() . "/";
    }

    public function test_start(){
        //check file exist and allowed reading
        if((!is_readable($this->jexampath)) && $this->pars_only){
            fwrite(STDERR, "path not correct or files not allowed reading");
            exit(41);
        }
        if((!is_readable($this->parse_script)) && !$this->int_only){
            fwrite(STDERR, "path not correct or files not allowed reading");
            exit(41);
        }
        if((!is_readable($this->int_script)) && !$this->pars_only){
            fwrite(STDERR, "path not correct or files not allowed reading");
            exit(41);
        }
        $all_test = 0;
        $test_success = 0;
        $test_not_success = 0;
        //start test loop
        foreach ($this->test_dirs as $dir => $test_folder){
            foreach($test_folder as $test){
                $array = explode("/", $test);
                $name = end($array);
                //output temporary files for tests
                $name_temporary_file = $this->main_dir . $name . "_" . bin2hex(random_bytes(10)) . ".out";
                $name_temporary_file_py = $this->main_dir  . $name . "_" . "py". bin2hex(random_bytes(10)) . ".out";
                $out_code = "";

                //start parse.php
                if(!$this->int_only){
                    exec("php8.1 " . $this->parse_script . " < " . $test . ".src " . " > " . $name_temporary_file, result_code: $out_code);
                }

                //if testing only parse.php check the output and write to html
                if($this->pars_only){
                    $out_code_rc = file_get_contents($test . ".rc");
                    if ($out_code != 0) {
                        if ($out_code == $out_code_rc) {
                            $test_success += 1;
                            $this->html_writer->ok_box($name, $dir);
                        } else {
                            $test_not_success += 1;
                            $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                        }
                    } else {
                        exec("java -jar " . $this->jexampath . " " . $test . ".out " . $name_temporary_file . " /dev/null " . $this->jexampath_opt, $output, $out_code);
                        if ($out_code == 0) {
                            $test_success += 1;
                            $this->html_writer->ok_box($name, $dir);
                        } else {
                            $test_not_success += 1;
                            $this->html_writer->not_box($name, $dir, "JEXAMPATH" . $out_code, $out_code_rc);
                        }
                    }

                    if (!$this->noclean) {
                        exec("rm " . $name_temporary_file);
                    }
                }elseif($this->int_only){
                    //if testing only interpret.php check the output and write to html
                    $out_code_rc = file_get_contents($test . ".rc");
                    $input_file = $test . ".in";
                    exec("python3.8 " . $this->int_script . " --input=" . $input_file ." < " . $test . ".src " . " > " . $name_temporary_file_py, result_code: $out_code);
                    if ($out_code != 0) {
                        if ($out_code == $out_code_rc) {
                            $test_success += 1;
                            $this->html_writer->ok_box($name, $dir);
                        } else {
                            $test_not_success += 1;
                            $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                        }
                    } else {
                        exec("diff " . $test . ".out " . $name_temporary_file_py, $output, $out_code);
                        if ($out_code == 0) {
                            $test_success += 1;
                            $this->html_writer->ok_box($name, $dir);
                        } else {
                            $test_not_success += 1;
                            $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                        }
                    }

                    if (!$this->noclean) {
                        exec("rm " . $name_temporary_file_py);
                    }
                }else{
                    //if testing parse.php and interpret.py check the output and write to html
                    $out_code_rc = file_get_contents($test . ".rc");
                    if ($out_code != 0) {
                        if ($out_code == $out_code_rc) {
                            $test_success += 1;
                            $this->html_writer->ok_box($name, $dir);
                        } else {
                            $test_not_success += 1;
                            $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                        }
                    } else {
                        $input_file = $test . ".in";
                        exec("python3.8 " . $this->int_script . " --input=" . $input_file ." < " . $name_temporary_file  . " > " . $name_temporary_file_py, result_code: $out_code);
                        if ($out_code != 0) {
                            if ($out_code == $out_code_rc) {
                                $test_success += 1;
                                $this->html_writer->ok_box($name, $dir);
                            } else {
                                $test_not_success += 1;
                                $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                            }
                        } else {
                            exec("diff " . $test . ".out " . $name_temporary_file_py, $output, $out_code);
                            if ($out_code == 0) {
                                $test_success += 1;
                                $this->html_writer->ok_box($name, $dir);
                            } else {
                                $test_not_success += 1;
                                $this->html_writer->not_box($name, $dir, $out_code, $out_code_rc);
                            }
                        }

                        if (!$this->noclean) {
                            exec("rm " . $name_temporary_file_py);
                        }
                    }
                    if (!$this->noclean) {
                        exec("rm " . $name_temporary_file);
                    }
                }

                $all_test += 1;
            }
        }
        $percent = 0;
        if($all_test != 0){
            $percent = ($test_success * 100) / $all_test;
        }
        //write to html end html files and percent tests
        $this->html_writer->set_load($percent);
        $this->html_writer->set_table($test_success, $test_not_success, $all_test);
        $this->html_writer->write_html();
    }

}

?>