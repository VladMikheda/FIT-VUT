<?php

namespace App\Http\Controllers\Problems;

use App\Http\Controllers\Controller;
use App\Models\Managers;
use App\Models\Ticket;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use MongoDB\Driver\Manager;

class CreateController extends Controller
{
    public function __invoke()
    {
        return view('problems.create');
    }
}
