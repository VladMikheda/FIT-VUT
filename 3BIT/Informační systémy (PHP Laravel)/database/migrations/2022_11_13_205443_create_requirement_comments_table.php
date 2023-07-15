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
        Schema::create('requirement_comments', function (Blueprint $table) {
            $table->id();
            $table->unsignedBigInteger('user_id');
            $table->unsignedBigInteger('requirement_id');
            $table->string('content',"10000");

            $table->index('user_id','requirement_comments_user_idx');
            $table->index('requirement_id','requirement_comments_requirement_idx');

            $table->foreign('user_id','requirement_comments_user_fk')->on('users')->references('id');
            $table->foreign('requirement_id','requirement_comments_requirement_fk')->on('requirements')->references('id');

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
        Schema::dropIfExists('requirement_comments');
    }
};
