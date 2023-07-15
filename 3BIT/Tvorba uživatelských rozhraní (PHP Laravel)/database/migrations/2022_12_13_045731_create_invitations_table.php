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
        Schema::create('invitations', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('ticket_id');
            $table->index('ticket_id','invitations_ticket_idx');
            $table->foreign('ticket_id','invitations_ticket_fk')->on('tickets')->references('id')->onDelete('cascade');;

            $table->unsignedBigInteger('user_id');
            $table->index('user_id','invitations_user_idx');
            $table->foreign('user_id','invitations_user_fk')->on('users')->references('id')->onDelete('cascade');;

            $table->boolean("approved")->default(false);

            $table->longText('content')->nullable(true);

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
        Schema::dropIfExists('invitations');
    }
};
