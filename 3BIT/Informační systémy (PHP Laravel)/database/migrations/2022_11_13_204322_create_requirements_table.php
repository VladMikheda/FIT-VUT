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
        Schema::create('requirements', function (Blueprint $table) {
            $table->id();
            $table->date("estimated_time")->nullable(true);
            $table->unsignedInteger("price")->nullable(true);

            $table->string("title","255");
            $table->string("description","15000")->nullable(true);
            $table->string("address","255");

            $table->unsignedBigInteger("requirement_status_id");
            $table->unsignedBigInteger('problem_id');
            $table->unsignedBigInteger('repair_id');

            $table->index('requirement_status_id','requirements_requirement_status_idx');
            $table->index('problem_id','requirements_problem_idx');
            $table->index('repair_id','requirements_repair_idx');

            //$table->foreign('ticket_status_id','tickets_ticket_status_fk')->on('ticket_statuses')->references('id');
            $table->foreign('requirement_status_id', 'requirements_requirement_status_fk')->on('requirement_statuses')->references('id');
            $table->foreign('problem_id','requirements_problem_fk')->on('problems')->references('id');
            $table->foreign('repair_id','requirements_repair_fk')->on('repairs')->references('id');

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
        Schema::dropIfExists('requirements');
    }
};
