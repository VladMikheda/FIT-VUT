<?php

use App\Models\User;
use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Hash;
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
        Schema::create('users', function (Blueprint $table) {
            $table->id();
            $table->string("name","255");
            $table->string("lastname","255");
            $table->string("email","255")->unique("email");
            $table->string("password","255");
            $table->string("remember_token")->nullable(true);
            $table->boolean("approved")->default(true);
            $table->timestamps();
        });
        User::upsert([
            ['name' => 'Jan', 'lastname' => 'Dvořák', 'email' => '1@user.cz', 'password' => Hash::make('123'), 'approved' => true],
            ['name' => 'Jiří', 'lastname' => 'Poděbradský', 'email' => '2@user.cz', 'password' => Hash::make('123'), 'approved' => true],
            ['name' => 'Radmila', 'lastname' => 'Fialová', 'email' => '3@user.cz', 'password' => Hash::make('123'), 'approved' => true],
            ['name' => 'Zdeněk', 'lastname' => 'Svoboda', 'email' => '4@user.cz', 'password' => Hash::make('123'), 'approved' => true],
            ['name' => 'Milena', 'lastname' => 'Nováková', 'email' => '5@user.cz', 'password' => Hash::make('123'), 'approved' => true],

        ], ['name', 'lastname']);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('users');
    }
};
