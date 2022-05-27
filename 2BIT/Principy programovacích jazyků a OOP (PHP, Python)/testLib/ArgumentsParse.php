<?php
/**
 * Project:  Test
 *
 * File:     ArgumentsParse.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
class ArgumentsParse
{
    //Parse input arguments

    public $arguments_array = [
        "directory" => "",
        "recursive" => false,
        "int-script" => "",
        "parse-script" => "",
        "parse-only" => false,
        "int-only" => false,
        "jexampath" => "",
        "noclean" => false,

    ];
    private $input_arguments;
    private $test_files = [];

    function __construct($argv){
        $this->input_arguments = $argv;
    }
    public function arguments(){
        // parse arguments and add to array
        foreach ($this->input_arguments as $arg){
            $arguments = explode("=", $arg);
            switch ($arguments[0]){
                case "--help":
                    echo "php test.php <--directory=path> <--recursive> <--parse-script=file> <--int-script=file> <--parse-only> <--int-only> <--jexampath=path> <--noclean>";
                    echo "\n --directory=path looks for tests in the given directory, if not specified searches in this directory";
                    echo "\n --recursive searches for tests recursively";
                    echo "\n --parse-script=file path to parse.php file, if not specified searches in this directory";
                    echo "\n --int-script=file path to interpret.php file, if not specified searches in this directory";
                    echo "\n --parse-only only the parser will be tested";
                    echo "\n --int-only only the interpret will be tested";
                    echo "\n --jexampath=path path to jexamxml.jar file, if not specified searches in /pub/courses/ipp/jexamxml/";
                    echo "\n --noclean will not delete temporary files";
                    echo "\n if --parse-only is specified, --int-only, --int-script cannot be specified";
                    echo "\n if --int-only is specified,  --parse-only, --parse-script, --jexampath cannot be specified \n";
                    $len = count($this->input_arguments);
                    if ($len > 2){
                        exit(10);
                    }
                    exit(0);
                case "--directory":
                    $this->arguments_array["directory"] = $arguments[1];
                    break;
                case "--recursive":
                    $this->arguments_array["recursive"] = true;
                    break;
                case "--parse-script":
                    $this->arguments_array["parse-script"] = $arguments[1];
                    break;
                case "--int-script":
                    $this->arguments_array["int-script"] = $arguments[1];
                    break;
                case "--parse-only":
                    $this->arguments_array["parse-only"] = true;
                    break;
                case "--int-only":
                    $this->arguments_array["int-only"] = true;
                    break;
                case "--jexampath":
                    $this->arguments_array["jexampath"] = $arguments[1];
                    break;
                case "--noclean":
                    $this->arguments_array["noclean"] = true;
                    break;
                case $this->input_arguments[0]:
                    break;
                default:
                    exit(10);
            }
        }

        // checking the correctness of setting arguments
         $jexampath =  $this->arguments_array["jexampath"];
         $pars_only =  $this->arguments_array["parse-only"];
         $parse_script =  $this->arguments_array["parse-script"];
         $int_only =  $this->arguments_array["int-only"];
         $int_script =  $this->arguments_array["int-script"];
         if( $pars_only && ($int_only || $int_script)){
             exit(10);
         }
         if( $int_only && ($pars_only || $parse_script || $jexampath)){
             exit(10);
         }
    }

    public function parse_file(){
        //parse files
        $directory = $this->arguments_array["directory"];
        if($directory == ""){
            $directory = posix_getcwd();
        }
        if(!is_readable($directory)){
            exit(41);
        }
        $file_directory =  new RecursiveDirectoryIterator($directory);
        if($this->arguments_array["recursive"] == true) {
            //recursive parse files in directory
            $file_directory_iterator = new RecursiveIteratorIterator($file_directory);
        }else{
            //not recursive parse files in directory
            $file_directory_iterator = new IteratorIterator($file_directory);
        }
        $pattern = "/^.+\.src$/i";
        $mode = RecursiveRegexIterator::GET_MATCH;
        // find all files that end in .src
        $file_directory_regex = new RegexIterator($file_directory_iterator, $pattern, $mode);
        foreach ($file_directory_regex as $file_path){

            $file_name = explode("/", $file_path[0]);
            $file_name = explode(".src", end($file_name));
            $file_name = $file_name[0];
            $directory_file = explode($file_name . ".src", $file_path[0])[0];

            //check exists files and create if not exist
            if (!is_writable($directory_file . $file_name . ".in")) {
                $file = fopen($directory_file . $file_name . ".in", "w");
                fclose($file);
            }

            if (!is_writable($directory_file . $file_name . ".out")) {
                $file = fopen($directory_file . $file_name . ".out", "w");
                fclose($file);
            }

            if (!is_writable($directory_file . $file_name . ".rc")) {
                $file = fopen($directory_file . $file_name . ".rc", "w");
                fwrite($file,"0");
                fclose($file);
            }

            $this->test_files[$directory_file][$file_name] = $directory_file . $file_name;
            array_multisort($this->test_files);

            }
    }

    public function get_arguments(): array
    {
        return $this->arguments_array;
    }

    public  function get_test_files(){
        return $this->test_files;
    }

}

?>