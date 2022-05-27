<?php
/**
 * Project:  Analyzátor kódu v IPPcode22
 *
 * File:     Token.php
 * Subject:  IPP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

class Token{

    private string $inter;
    private string $token_type;
    private int $count_instruction;
    private int $count_line;

    public function set_all($inter, $token_type, $count_line, $count_instruction = 0){
        $this->inter = $inter;
        $this->token_type = $token_type;
        $this->count_instruction = $count_instruction;
        $this->count_line = $count_line;
    }

    /**
     * @return string
     */
    public function get_inter(): string
    {
        return $this->inter;
    }

    /**
     * @return string
     */
    public function get_token_type(): string
    {
        return $this->token_type;
    }

    /**
     * @return int
     */
    public function get_count_instruction(): int
    {
        return $this->count_instruction;
    }

    /**
     * @return int
     */
    public function get_countline(): int
    {
        return $this->count_line;
    }

}



?>