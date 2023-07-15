<?php

namespace App\Http\Controllers\Profile;

use App\Http\Controllers\Controller;
use App\Http\Requests\Profile\UpdatePasswordRequest;
use App\Http\Requests\Profile\UpdateRequest;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Hash;

class UpdatePasswordController extends BaseController
{
    public function __invoke(UpdatePasswordRequest $request)
    {

        $data = $request->validated();


        $message = $this->service->updatePassword($data);


        if($message){
            return redirect(route('profile.edit'))->withErrors([
                'password' => $message]);
        }


        Auth::logout();

        return redirect(route('authentication.index'));
    }
}
