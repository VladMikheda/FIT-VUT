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
        Schema::create('managers', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('user_id')->unique();
            $table->index('user_id','managers_user_idx');
            $table->foreign('user_id','managers_user_fk')->on('users')->references('id');
            $table->boolean("approved")->default(false);
            $table->timestamps();
        });

        DB::table('managers')->insert(array('user_id' => '1', 'approved' => true,));
        DB::table('managers')->insert(array('user_id' => '7', 'approved' => true,));
        DB::table('managers')->insert(array('user_id' => '8', 'approved' => true,));
        DB::table('managers')->insert(array('user_id' => '18', 'approved' => true,));
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('managers');
    }
};
