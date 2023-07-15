<?php

use App\Models\Ticket;
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
        Schema::create('tickets', function (Blueprint $table) {
            $table->id();

            $table->unsignedBigInteger('user_id');
            $table->index('user_id','tickets_user_idx');
            $table->foreign('user_id','tickets_user_fk')->on('users')->references('id')->onDelete('cascade');;

            $table->string("title","255");
            $table->string("description","15000");
            $table->string("address","255");
            $table->unsignedBigInteger("price")->default(0);
            $table->unsignedBigInteger("number_people")->nullable(true);

            $table->unsignedBigInteger('category_id');
            $table->index('category_id','tickets_category_idx');
            $table->foreign('category_id','tickets_category_fk')->on('categories')->references('id');

            $table->timestamps();
        });

        Ticket::upsert([
            ['user_id' => '1','title' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '1',
                'price' => '10',
                'created_at' => '2023-01-09 01:27:20'],
            ['user_id' => '2','title' => 'Ut condimentum justo volutpat purus pulvinar ultrices.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '2', 'price' => '5', 'created_at' => '2023-01-01 02:27:20'],
            ['user_id' => '2','title' => 'Curabitur varius elit dolor, sed blandit orci accumsan sed. Morbi mollis enim at augue faucibus.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '3', 'price' => '5000', 'created_at' => '2023-01-04 02:27:20'],
            ['user_id' => '3','title' => 'Nunc eu commodo mi. Vestibulum tristique dolor nulla.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '4', 'price' => '6000', 'created_at' => '2023-01-03 02:27:20'],
            ['user_id' => '4','title' => 'Curabitur fringilla porta velit, et mollis mi.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '4', 'price' => '1000', 'created_at' => '2023-01-07 02:27:20'],
            ['user_id' => '4','title' => 'Xurabitur fringilla porta velit, et mollis mi.',
                'address' => 'Massa lectus in est. Curabitur fringilla porta velit, et mollis mi.',
                'description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.' ,
                'category_id' => '4', 'price' => '5000', 'created_at' => '2023-01-07 02:27:20'],

        ], ['user_id','title', 'description', 'address']);
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
