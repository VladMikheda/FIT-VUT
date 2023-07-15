<?php

namespace App\Http\Controllers\Join;

use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Auth;

class CreateController extends Controller
{
    public function __invoke()
    {
        return view('join');
    }
}
