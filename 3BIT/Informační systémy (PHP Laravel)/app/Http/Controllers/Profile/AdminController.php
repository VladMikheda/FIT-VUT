<?php

namespace App\Http\Controllers\Profile;

use App\Http\Controllers\Controller;
use App\Models\Admins;
use App\Models\Managers;
use App\Models\Repairs;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class AdminController extends Controller
{
    public function __invoke()
    {
        $user_id = Auth::id();
        $user = Auth::user();

        $is_manager = !empty(Managers::where('user_id',$user_id)->where('approved','1')->get()->toArray());
        $is_repair = !empty(Repairs::where('user_id',$user_id)->where('approved','1')->get()->toArray());
        return view('profile_admin',compact(['user', 'is_manager', 'is_repair']));
    }
}
