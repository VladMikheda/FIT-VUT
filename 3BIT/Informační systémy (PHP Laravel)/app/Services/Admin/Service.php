<?php

namespace App\Services\Admin;


use App\Models\Images;
use App\Models\Repairs;
use App\Models\Ticket;
use App\Models\Managers;
use App\Models\TicketComments;
use App\Models\Problems;
use App\Models\User;
use Illuminate\Database\Capsule\Manager;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class Service
{
    public function getAllProblems()
    {
        return Problems::join('users', 'users.id', '=', 'problems.manager_id')->select('users.name', 'users.lastname', 'problems.title','users.id')->where('state','!=',2)->paginate(10);
    }

    public function getAllUsers()
    {
        return User::where('approved', 1)->paginate(10);
    }

    public function getSolved()
    {
        return Problems::where('state', 2)->paginate(10);
    }

    public function getAllNewcomers()
    {
        return User::where('approved', 0)->paginate(10);
    }

    public function getAllManagers()
    {
        return Managers::join('users', 'users.id', '=', 'managers.user_id')->select('users.name', 'users.lastname','users.email', 'users.phone', 'managers.id')->where('managers.approved', 1)->paginate(10);
    }

    public function appliedManagers()
    {
        return Managers::join('users', 'users.id', '=', 'managers.user_id')->select('users.name', 'users.lastname','users.email', 'users.phone', 'managers.id')->where('managers.approved', '=', 0)->paginate(10);
    }

    public function viewAllTechs()
    {
        return User::join('repairs', 'repairs.user_id','=', 'users.id')->select('users.name','users.lastname', 'users.email', 'users.phone')->where('repairs.approved',1)->paginate(10);
    }
}
