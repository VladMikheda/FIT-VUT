<?php

//use App\Http\Controllers\Test;
use App\Models\Ticket;
use App\Models\User;
use Illuminate\Support\Facades\Route;
//use App\Http\Controllers\Registration as Registration;
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

Route::name('admin.')
    ->namespace('App\Http\Controllers\Admin\Users')
    ->middleware('auth')
    ->middleware('admin')
    ->group(function () {
        Route::get('/admin/users', 'UsersController')->name("users");
        Route::get('/admin/user_accept', 'UserAcceptController')->name("userAccept");
        Route::get('/admin/user_allow/{user}', 'UserAllowController')->name("userAllow");
        Route::get('/admin/user_deny/{user}', 'UserDenyController')->name("userDeny");
    });

Route::name('admin.')
    ->namespace('App\Http\Controllers\Admin\Managers')
    ->middleware('auth')
    ->middleware('admin')
    ->group(function () {
        Route::get('/admin/managers', 'ManagersController')->name("allManagers");
        Route::get('/admin/managers_approve', 'ManagerApproveController')->name("managerApprove");
        Route::get('/admin/manager_hire/{manager}', 'ManagerHireController')->name("managerHire");
        Route::get('/admin/manager_fire/{manager}', 'ManagerFireController')->name("managerFire");
    });


Route::name('admin.')
    ->namespace('App\Http\Controllers\Admin')
    ->middleware('auth')
    ->middleware('admin')
    ->group(function () {
        Route::get('/admin/problems', 'ViewProbsController')->name("allProblems");
        Route::get('/admin/problems/archieve', 'ArchieveController')->name("archProbs");
    });

//manager
Route::name('technician.')
    ->namespace('App\Http\Controllers\Manager\Technicians')
    ->middleware('auth')
    ->middleware('manager')
    ->group(function () {
        Route::get('/manager/technicians', 'IndexController')->name('index');
        Route::get('/manager/technicians/new', 'IndexNewController')
            ->name('index.new');
        Route::get('/manager/technicians/new/{tech}','AddController')
            ->name('add');
        Route::get('/manager/technicians/{tech_id}/fire', 'FireController')->name('fire');
    });

Route::name('manager.problems.')
    ->namespace('App\Http\Controllers\Manager\Problems')
    ->middleware('auth')
    ->middleware('manager')
    ->group(function () {
        Route::get('/manager/problems', 'IndexController')->name('index');
        Route::get('/manager/problems/old', 'IndexOldController')->name("index.old");

    });

//manager
Route::name('problem.')
    ->namespace('App\Http\Controllers\Problems')
    ->middleware('auth')
    ->middleware('manager')
    ->group(function () {
        Route::get('/problems/create', 'CreateController')->name("createProb");
        Route::post('/problems/create', 'StoreController')->name("storeProb");
        Route::get('/problems/{problem}', 'ShowController')->name("showProb");
        Route::get('/problems/{problem}/solved', 'SolvedController')->name("solveProb");
        Route::get('/problems/{problem}/unsolve', 'UnsolveController')->name("unsolveProb");
        Route::post('/manager/ticket/{ticket}/problem', 'AddTicketController')->name("add.ticket");
        //Route::get('/problems/all', 'IndexOldController')->name("archProbs");
    });

//manager
Route::name('manager.tickets.')
    ->namespace('App\Http\Controllers\Tickets\Manager')
    ->middleware('auth')
    ->middleware('manager')
    ->group(function () {
        Route::get('/manager/tickets', 'IndexController')->name("index");
        Route::get('/manager/ticket/{ticket}', 'ShowController')->name("show");
        Route::post('/manager/ticket/{ticket}', 'AddCommentController')->name("add.comment");
    });






// -----------------------------------------
Route::get('/', function () {
    return redirect(route('authentication.index'));
})->name("main");



Route::name('registration.')
    ->namespace('App\Http\Controllers\Registration')
    ->middleware('auth.is')
    ->group(function () {
        Route::get('/registration', 'CreateController')->name("create");
        Route::post('/registration', 'StoreController')->name("store");
    });

Route::name('authentication.')
    ->namespace('App\Http\Controllers\Authentication')
    ->middleware('auth.is')
    ->group(function () {
        Route::get('/login', 'IndexController')->name("index");
        Route::post('/login', 'CheckController')->name("check");
        Route::get('/logout', 'LogoutController')->name("exit")->withoutMiddleware('auth.is');
    });

Route::name('join.')
    ->namespace('App\Http\Controllers\Join')
    ->middleware('auth')
    ->group(function () {
        Route::get('/profile/join', 'CreateController')->name("create");
        Route::post('/profile/join', 'StoreController')->name("store");
    });



Route::name('user.tickets.')
    ->namespace('App\Http\Controllers\Tickets\User')
    ->middleware('auth')
    ->group(function () {
        Route::get('user/tickets', 'IndexController')->name("index");
        Route::get('user/tickets/old', 'IndexOldController')->name("index.old");
        Route::get('user/tickets/create', 'CreateController')->name("create");
        Route::post('user/tickets', 'StoreController')->name("store");
        Route::post('user/tickets/{ticket}', 'AddCommentController')->name("add.comment");
        Route::get('user/tickets/image/{ticket}', 'ShowImagesController')->name("show.images");
        Route::post('user/tickets/image/{ticket}', 'AddImageController')->name("add.images");
        Route::get('user/tickets/{ticket}', 'ShowController')->name("show");
    });

Route::name('profile.')
    ->namespace('App\Http\Controllers\Profile')
    ->middleware('auth')
    ->group(function () {
        Route::get('/profile', 'IndexController')->name("index");
        Route::get('/profile/edit', 'EditController')->name("edit");
        Route::get('/profile/manager', 'ManagerController')->name("manager")->middleware('manager');
        Route::get('profile/technician', 'TechnicianController')->name("technician")->middleware('repairs');
        Route::get('/profile/admin', 'AdminController')->name("admin")->middleware("admin");
        Route::post('/profile/edit', 'UpdatePasswordController')->name("update.password");
        Route::post('/profile', 'UpdateController')->name("update");
    });

Route::name('manager.requirements.')
    ->namespace('App\Http\Controllers\Requirements\Manager')
    ->middleware('auth')
    ->middleware('manager')
    ->group(function () {
        Route::get('manager/requirements', 'RequirementController@index')->name("index");
        Route::get('manager/requirements/old', 'RequirementController@indexOld')->name("index.old");
        Route::get('manager/requirements/create', 'RequirementController@create')->name("create");
        Route::post('manager/requirements', 'RequirementController@store')->name("store");
        Route::get('manager/requirements/{requirement}/show', 'RequirementController@show')->name("show");
        Route::post('manager/requirements/{requirement}/show', 'RequirementController@addComment')->name("comment");
        Route::get('manager/requirements/{requirement}/edit', 'RequirementController@edit')->name("edit");
        Route::post('manager/requirements/{requirement}', 'RequirementController@update')->name("update");
    });

Route::name('technician.requirements.')
    ->namespace('App\Http\Controllers\Requirements\Technician')
    ->middleware('auth')
    ->middleware('repairs')
    ->group(function () {
        Route::get('technician/requirements', 'RequirementController@index')->name("index");
        Route::get('technician/requirements/old', 'RequirementController@indexOld')->name("index.old");
        Route::get('technician/requirements/{requirement}/show', 'RequirementController@show')->name("show");
        Route::post('technician/requirements/{requirement}/show', 'RequirementController@addComment')->name("comment");
        Route::get('technician/requirements/{requirement}/edit', 'RequirementController@edit')->name("edit");
        Route::post('technician/requirements/{requirement}', 'RequirementController@update')->name("update");
    });
