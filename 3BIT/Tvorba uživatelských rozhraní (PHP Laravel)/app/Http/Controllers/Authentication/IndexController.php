<?php
/**
 *Project: Volunteer System
 *
 *File: IndexController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 * the file was taken from the IIS project
 **/
namespace App\Http\Controllers\Authentication;

use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Auth;

class IndexController extends Controller
{
    public function __invoke()
    {
        return view('login_form');
    }
}
