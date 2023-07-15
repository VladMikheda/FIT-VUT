<?php

use App\Models\Chat;
use App\Models\Message;
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
        Schema::create('messages', function (Blueprint $table) {
            $table->id();
            $table->foreignId('chat_id')->constrained('chats')->onDelete('cascade');;
            $table->foreignId('user_id')->constrained('users')->onDelete('cascade');;
            $table->longText('content');

            $table->timestamps();
        });
        Message::upsert([
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'five'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
////            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'five'],
//            //            ['chat_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia.'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'Fusce aliquam vestibulum ipsum. Nam quis nulla.'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Nunc tincidunt ante vitae massa. Integer lacinia. Maecenas fermentum, sem in pharetra pellentesque'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Donec iaculis gravida nulla. Phasellus et lorem id felis nonummy placerat. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Curabitur bibendum justo non orci. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Duis viverra diam non justo. Nullam rhoncus aliquam metus.'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'Aenean vel massa quis mauris vehicula lacinia. Fusce aliquam vestibulum ipsum. Nam quis nulla.'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'Aenean vel massa quis mauris vehicula lacinia.'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'Fusce aliquam vestibulum ipsum. Nam quis nulla.'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '2', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '1', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '2', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '2', 'user_id' => '1', 'content' => 'five'],
//            ['chat_id' => '2', 'user_id' => '3', 'content' => 'five'],
//            ['chat_id' => '2', 'user_id' => '3', 'content' => 'five'],
//            ['chat_id' => '2', 'user_id' => '3', 'content' => 'five'],
////
////            ['chat_id' => '1', 'content' => 'one'],
////            ['chat_id' => '1', 'content' => 'two'],
////            ['chat_id' => '1', 'content' => 'three'],
            ['user_id' => '1', 'chat_id' => '1', 'content' => 'Thank you for your help :)'],
            ['user_id' => '1', 'chat_id' => '2', 'content' => 'My congratulations!'],
        ], ['chat_id', 'user_id', 'content']);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('messages');
    }
};
