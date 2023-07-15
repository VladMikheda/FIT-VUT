<?php

use App\Models\Friend;
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
        Schema::create('friends', function (Blueprint $table) {
            $table->id();
            $table->unsignedBigInteger('user_id');
            $table->unsignedBigInteger('friend_id');
            $table->index('user_id','friends_user_idx');
            $table->foreign('user_id','friends_user_fk')->on('users')->references('id')->onDelete('cascade');;
            $table->index('friend_id','friends_friend_idx');
            $table->foreign('friend_id','friends_friend_fk')->on('users')->references('id')->onDelete('cascade');;
            $table->boolean("approved")->default(false);
            $table->timestamps();

        });
        Friend::upsert([
            ['user_id' => '1', 'friend_id' => '2', 'approved' => true],
            ['user_id' => '2', 'friend_id' => '1', 'approved' => true]
        ], ['user_id', 'friend_id']);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('friends');
    }
};
