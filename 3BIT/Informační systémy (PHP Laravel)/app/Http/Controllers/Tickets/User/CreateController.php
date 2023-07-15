<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Auth;

class CreateController extends BaseController
{
    public function __invoke()
    {
        return view('tickets.create');
    }
}
