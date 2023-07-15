<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;
use Illuminate\Support\Facades\DB;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('tickets', function (Blueprint $table) {
            $table->id();
            $table->string("title","255");
            $table->string("description","15000")->nullable(true);
            $table->string("address","255");

            $table->unsignedBigInteger("ticket_status_id");
            $table->unsignedBigInteger('user_id')->default('1');
            $table->unsignedBigInteger('manager_id')->nullable(true);
            $table->unsignedBigInteger('problem_id')->nullable(true);

            $table->index('ticket_status_id','tickets_ticket_status_idx');
            $table->index('user_id','tickets_user_idx');
            $table->index('manager_id','tickets_manager_idx');
            $table->index('problem_id','tickets_problem_idx');

            $table->foreign('ticket_status_id','tickets_ticket_status_fk')->on('ticket_statuses')->references('id');
            $table->foreign('user_id','tickets_user_fk')->on('users')->references('id');
            $table->foreign('manager_id','tickets_manager_fk')->on('managers')->references('id');
            $table->foreign('problem_id','tickets_problem_fk')->on('problems')->references('id');
            $table->timestamps();
        });

        DB::table('tickets')->insert(array('title' => 'Shořela žárovka věřejného osvětlení',
                                            'description' => 'Kvůli shoření žárovky na sloupu věřejného osvětleni včerní a noční procházky jsou nebezpečné',
                                            'address' => 'Francouzská 58',
                                            'ticket_status_id' => 1,
                                            'user_id' => 10));

        DB::table('tickets')->insert(array('title' => 'Rozbité vodovodní potrubí',
                                    'description' => 'Vodovodní potrubí prasklo, za několik hodin celá čvtrť bude plavat',
                                    'address' => 'Valchařská',
                                    'ticket_status_id' => 1,
                                    'user_id' => 5));

        DB::table('tickets')->insert(array('title' => 'promačklý plot',
                                    'description' => 'po velke nehode na silnici zustal vedle meho domu promackly plot',
                                    'address' => 'Olomoucká 118ž',
                                    'ticket_status_id' => 1,
                                    'user_id' => 2));


        DB::table('tickets')->insert(array('title' => 'Skazený asfalt',
                                    'description' => 'ASFALT TADY SE NEOPRAVOVAL UZ 2 STOLETÍ, UDELEJTE S TIM NECO, PADOUŠI',
                                    'address' => 'Manželů Suchých 24',
                                    'ticket_status_id' => 1,
                                    'user_id' => 14));

        DB::table('tickets')->insert(array('title' => 'odpadky se vysypaly z popelářského vozu',
                                    'description' => 'z popelářského vozu se vysypaly odpadky a do večera je nikdo neodklidil',
                                    'address' => 'Vlašská 23',
                                    'ticket_status_id' => 1,
                                    'user_id' => 4));

        DB::table('tickets')->insert(array('title' => 'Ztracené dítě',
                                    'description' => 'Šel jsem se svou malou sestrou, byl jsem vyrušen a ona zmizela! URGENTNĚ POMOZ, MÁMA MĚ ZABÍ',
                                    'address' => 'Pražská 38b',
                                    'ticket_status_id' => 1,
                                    'user_id' => 12));

        DB::table('tickets')->insert(array('title' => 'Vítr povalil strom',
                                    'description' => 'Po silném větru spadl strom, přetrhl elektrické vedení a spadl na auta',
                                    'address' => 'Kuršova 1',
                                    'ticket_status_id' => 1,
                                    'user_id' => 7));
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('tickets');
    }
};
