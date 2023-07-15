<?php

namespace App\Http\Controllers\Profile;

use App\Http\Controllers\Controller;
use App\Models\Admins;
use App\Models\Managers;
use App\Models\Repairs;
use App\Models\User;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;

class IndexController extends Controller
{
    public function __invoke()
    {
        $user = Auth::user();
        $user_id = Auth::id();
        $is_admin = !empty(Admins::where('user_id',$user_id)->where('approved','1')->get()->toArray());
        $is_manager = !empty(Managers::where('user_id',$user_id)->where('approved','1')->get()->toArray());
        $is_repair = !empty(Repairs::where('user_id',$user_id)->where('approved','1')->get()->toArray());

        return view('profile',compact(['user', 'is_admin', 'is_manager', 'is_repair']));
    }
}
