<?php

namespace App\Http\Controllers\Authentication;

use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Auth;

class LogoutController extends Controller
{
    public function __invoke()
    {
        if(Auth::check()){
            Auth::logout();
        }

        return redirect(route('authentication.index'));
    }
}
