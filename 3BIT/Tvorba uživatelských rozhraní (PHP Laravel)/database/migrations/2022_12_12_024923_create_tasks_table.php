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
        Schema::create('tasks', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('task_list_id');
            $table->index('task_list_id','tasks_task_list_idx');
            $table->foreign('task_list_id','tasks_task_list_fk')->on('task_lists')->references('id')->onDelete('cascade');;

            $table->unsignedBigInteger('task_number');
            $table->string('task_title',255)->nullable(true);
            $table->string("task_description",1000)->nullable(true);
            $table->boolean('completed')->default(false);
            //todo
            $table->unsignedBigInteger('task_owner')->nullable(true);
            $table->index('task_owner','tasks_task_owner_idx');
            $table->foreign('task_owner','tasks_task_owner_fk')->on('users')->references('id')->onDelete('cascade');;


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
        Schema::dropIfExists('tasks');
    }
};
