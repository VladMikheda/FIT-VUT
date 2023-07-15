<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/chats', App\Http\Livewire\Chat\ChatIndex::class)->middleware('auth')->name('chats');
Route::get('/tickets/public', App\Http\Livewire\Tickets\IndexPublic::class)->middleware('auth')->name('ticket.public');
Route::get('/tickets/public/{ticket}', App\Http\Livewire\Tickets\ShowPublic::class)->middleware('auth')->name('public.show');
Route::get('/tickets/created', App\Http\Livewire\Tickets\IndexCreated::class)->middleware('auth')->name('ticket.created');;
Route::get('/tickets/created/{ticket}', App\Http\Livewire\Tickets\ShowCreated::class)->middleware('auth');
Route::get('/tickets/manage/{ticket}', App\Http\Livewire\Tickets\ManageTicket::class)->middleware('auth')->name('manage');
Route::get('/tickets/taken', App\Http\Livewire\Tickets\IndexTaken::class)->middleware('auth')->name('ticket.taken');
Route::get('/tickets/taken/{ticket}', App\Http\Livewire\Tickets\ShowTaken::class)->middleware('auth')->name('taken.show');
Route::get('/tickets/create', \App\Http\Livewire\Tickets\CreateController::class)->middleware('auth')->name('ticket.create');
Route::get('/profile', \App\Http\Livewire\ProfileController::class)->middleware('auth')->name('profile');
Route::get('/',\App\Http\Controllers\IndexController::class)->name('index');


Route::name('friends.')
    ->namespace('App\Http\Livewire\Friends')
    ->middleware('auth')
    ->group(function () {
        Route::get('/friends', 'AddController')->name("index");
    });


Route::name('board.')
    ->namespace('App\Http\Livewire\Board')
    ->middleware('auth')
    ->middleware('invite')
    //todo hwo choose ticket
    ->group(function () {
        Route::get('/task_board/{id}', 'IndexController')->name("index");
    });




Route::name('authentication.')
    ->namespace('App\Http\Controllers\Authentication')
    ->middleware('auth.is')
    ->group(function () {
        Route::get('/login', 'IndexController')->name("index");
        Route::post('/login', 'CheckController')->name("check");
        Route::get('/logout', 'LogoutController')->name("exit")->withoutMiddleware('auth.is');
    });

Route::get('/test', \App\Http\Livewire\Tickets\CreateController::class);

//full-page componennts
//Route::get('/', ShowPosts::class);
