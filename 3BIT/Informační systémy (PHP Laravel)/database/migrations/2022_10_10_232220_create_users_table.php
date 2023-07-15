<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;
use \Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Hash;

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
            $table->date("birthday")->nullable(true);
            $table->string("phone","15")->unique()->nullable(true);
            $table->string('photo')->nullable(true);
            $table->boolean("specialization")->default(false);
            $table->boolean("approved")->default(false);
            $table->timestamps();
        });

        DB::table('users')->insert(array('name' => 'Kirill', 'lastname' => 'Mikhailov',
            'email' => 'xmikha00@admin.cz', 'password' => Hash::make('123456'),
            'birthday' => '2001-02-15', 'phone' => '773249612',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Vladislav', 'lastname' => 'Mikheda',
            'email' => 'xmikhe00@admin.cz', 'password' => Hash::make('123456'),
            'birthday' => '2001-03-30', 'phone' => '773389412',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Vladislav', 'lastname' => 'Khrisanov',
            'email' => 'xkhris00@admin.cz', 'password' => Hash::make('123456'),
            'birthday' => '2001-12-05', 'phone' => '775341423',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Jan', 'lastname' => 'Novák',
            'email' => 'jnovak82@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1983-11-13', 'phone' => '775365445',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Marek', 'lastname' => 'Hrbáček',
            'email' => 'hrbaty@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1999-05-21', 'phone' => '775582492',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Lucie', 'lastname' => 'Máchova',
            'email' => 'luckylucka@google.com', 'password' => Hash::make('123'),
            'birthday' => '2002-03-14', 'phone' => '779242823',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Sylvie', 'lastname' => 'Altrichterova',
            'email' => 'altright@google.com', 'password' => Hash::make('123'),
            'birthday' => '2001-06-12', 'phone' => '774566490',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Vesemír', 'lastname' => 'Zaklináč',
            'email' => 'whitchersdaddy@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1935-09-01', 'phone' => '772228932',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Katarína', 'lastname' => 'Láska',
            'email' => 'katherine9392@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1993-07-04', 'phone' => '775423532',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Diana', 'lastname' => 'Královna',
            'email' => 'imprincessbeatch@gmail.com', 'password' => Hash::make('123'),
            'birthday' => '1992-05-21', 'phone' => '455431349',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Samuel', 'lastname' => 'Vaňo',
            'email' => 'whoissamko@seznam.cz', 'password' => Hash::make('123'),     // 11
            'birthday' => '2003-10-09', 'phone' => '772792492',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Filip', 'lastname' => 'Růžička',
            'email' => 'ruzovavoda@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1994-02-10', 'phone' => '772981542',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Jakub', 'lastname' => 'Kulhánek',
            'email' => 'stfuzubar@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1988-08-19', 'phone' => '738983912',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Iveta', 'lastname' => 'Hanákova',
            'email' => 'ivhanak3210@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1958-04-12', 'phone' => '775932438',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Milan', 'lastname' => 'Slanina',
            'email' => 'slaninamilan@seznam.cz', 'password' => Hash::make('123'),
            'birthday' => '1972-05-21', 'phone' => '795391432',
            'specialization' => true, 'approved' => true,));
//16
        DB::table('users')->insert(array('name' => 'Jan', 'lastname' => 'Obyvatel',
            'email' => 'user@user.cz', 'password' => Hash::make('123'),
            'birthday' => '1973-05-21', 'phone' => '796782432',
            'specialization' => false, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Jiří', 'lastname' => 'Administrátor',
            'email' => 'admin@admin.cz', 'password' => Hash::make('123'),
            'birthday' => '1971-05-21', 'phone' => '795391781',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Marie', 'lastname' => 'Správceměstová',
            'email' => 'manager@manager.cz', 'password' => Hash::make('123'),
            'birthday' => '1970-05-21', 'phone' => '798931432',
            'specialization' => true, 'approved' => true,));

        DB::table('users')->insert(array('name' => 'Michal', 'lastname' => 'Servisnítechnik',
            'email' => 'tech@tech.cz', 'password' => Hash::make('123'),
            'birthday' => '1976-05-21', 'phone' => '798753211432',
            'specialization' => true, 'approved' => true,));

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
