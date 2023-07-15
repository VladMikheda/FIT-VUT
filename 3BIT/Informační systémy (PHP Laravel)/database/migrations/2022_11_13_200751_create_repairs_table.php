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
        Schema::create('repairs', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('user_id')->unique();
            $table->index('user_id','repairs_user_idx');
            $table->foreign('user_id','repairs_user_fk')->on('users')->references('id');
            $table->boolean("approved")->default(false);
            $table->timestamps();
        });

        DB::table('repairs')->insert(array('user_id' => '5', 'approved' => true,));
        DB::table('repairs')->insert(array('user_id' => '11', 'approved' => true,));
        DB::table('repairs')->insert(array('user_id' => '12', 'approved' => true,));
        DB::table('repairs')->insert(array('user_id' => '15', 'approved' => true,));
        DB::table('repairs')->insert(array('user_id' => '19', 'approved' => true,));

    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('repairs');
    }
};
