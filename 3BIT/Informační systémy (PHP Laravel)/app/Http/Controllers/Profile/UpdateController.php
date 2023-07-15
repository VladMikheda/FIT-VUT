<?php

namespace App\Http\Controllers\Profile;

use App\Http\Controllers\Controller;
use App\Http\Requests\Profile\UpdateRequest;
use App\Models\User;
use Illuminate\Support\Facades\Auth;

class UpdateController extends BaseController
{
    public function __invoke(UpdateRequest $request)
    {

        $data = $request->validated();

        $logout = $this->service->update($data);

        if($logout){
            Auth::logout();
            return redirect(route('authentication.index'));
        }

        return redirect(route('profile.edit'));
    }
}
