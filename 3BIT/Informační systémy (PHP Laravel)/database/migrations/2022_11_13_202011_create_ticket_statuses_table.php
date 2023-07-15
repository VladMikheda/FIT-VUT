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
        Schema::create('ticket_statuses', function (Blueprint $table) {
            $table->id();
            $table->string('name','255');
            $table->timestamps();
        });

        DB::table('ticket_statuses')->insert(array('name' => 'podano'));
        DB::table('ticket_statuses')->insert(array('name' => 'v průběhu'));
        DB::table('ticket_statuses')->insert(array('name' => 'vyřešeno'));
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('ticket_statuses');
    }
};
