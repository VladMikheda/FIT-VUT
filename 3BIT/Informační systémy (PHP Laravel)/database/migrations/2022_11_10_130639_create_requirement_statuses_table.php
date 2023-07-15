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
        Schema::create('requirement_statuses', function (Blueprint $table) {
            $table->id();
            $table->string('name','255');
            $table->timestamps();
        });

        DB::table('requirement_statuses')->insert(array('name' => 'Přiřazen'));
        DB::table('requirement_statuses')->insert(array('name' => 'Vyřizuje se'));
        DB::table('requirement_statuses')->insert(array('name' => 'Vyřízeno'));
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('requirement_statuses');
    }
};
