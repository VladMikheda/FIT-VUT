<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('task_lists', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('task_board_id');
            $table->index('task_board_id','task_lists_dash_board_idx');
            $table->foreign('task_board_id','task_lists_dash_board_fk')->on('task_boards')->references('id')->onDelete('cascade');;

            $table->string('list_title',255)->nullable(true);
            $table->unsignedBigInteger('list_number');


            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('task_lists');
    }
};
