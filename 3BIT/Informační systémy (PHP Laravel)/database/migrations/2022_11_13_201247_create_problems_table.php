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
        Schema::create('problems', function (Blueprint $table) {
            $table->id();
            $table->string("title","255");
            $table->string("address","255");
            $table->string("description","15000")->nullable(true);
            $table->unsignedTinyInteger("state"); // 0 - not even in process, 1 - processing(manager attached), 2(done)
            $table->unsignedBigInteger('manager_id');
            $table->index('manager_id','problems_manager_idx');
            $table->foreign('manager_id','problems_manager_fk')->on('managers')->references('id');

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
        Schema::dropIfExists('problems');
    }
};
