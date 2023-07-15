<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

use \Illuminate\Support\Facades\DB;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('admins', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('user_id')->unique();
            $table->index('user_id','admins_user_idx');
            $table->foreign('user_id','admins_user_fk')->on('users')->references('id');
            $table->boolean("approved")->default(false);
            $table->timestamps();
        });

        DB::table('admins')->insert(array('user_id' => '1', 'approved' => true,));
        DB::table('admins')->insert(array('user_id' => '2', 'approved' => true,));
        DB::table('admins')->insert(array('user_id' => '3', 'approved' => true,));
        DB::table('admins')->insert(array('user_id' => '17', 'approved' => true,));

    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('admins');
    }
};
