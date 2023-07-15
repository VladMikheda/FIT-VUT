<?php

namespace App\Http\Controllers\Profile;

use App\Http\Controllers\Controller;
use App\Models\Admins;
use App\Models\Managers;
use Illuminate\Support\Facades\Auth;

class TechnicianController extends Controller
{
    public function __invoke()
    {
        $user_id = Auth::id();
        $user = Auth::user();

        $is_admin = !empty(Admins::where('user_id',$user_id)->where('approved','1')->get()->toArray());
        $is_manager = !empty(Managers::where('user_id',$user_id)->where('approved','1')->get()->toArray());

        return view('profile_technician',compact(['user', 'is_admin', 'is_manager']));
    }
}

