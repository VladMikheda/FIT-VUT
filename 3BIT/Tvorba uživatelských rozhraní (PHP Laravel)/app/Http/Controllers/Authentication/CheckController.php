<?php
/**
 *Project: Volunteer System
 *
 *File: CheckController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 * the file was taken from the IIS project
 **/
namespace App\Http\Controllers\Authentication;

use App\Http\Controllers\Controller;
use App\Http\Requests\Authentication\LoginRequest;
use App\Models\User;
use Illuminate\Support\Facades\Auth;

class CheckController extends BaseController
{
    public function __invoke(LoginRequest $request)
    {
        $data = $request->validated();

        //
        $user = empty(User::where('email',$request->email)->where('approved','1')->get()->toArray());

        if($user){
            return redirect(route('authentication.index'))->withErrors([
                'formError' => 'Váš účet ještě nebyl schválen, čekejte prosím',
            ]);
        }

//        dd($data);
        $result = $this->service->check($data);

        if($result){
            return redirect(route('index'));
        }

        return redirect(route('authentication.index'))->withErrors([
            'password' => 'Neplatné heslo',
        ]);

    }
}
