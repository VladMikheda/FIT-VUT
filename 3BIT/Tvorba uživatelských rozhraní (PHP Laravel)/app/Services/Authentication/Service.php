<?php
/**
 *Project: Volunteer System
 *
 *File: Service.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 * the file was taken from the IIS project
 **/
namespace App\Services\Authentication;

use Illuminate\Support\Facades\Auth;

class Service
{
    public function check($data): bool
    {
//        dd($data);
        return Auth::attempt(['email'=> $data['email'],'password'=>$data['password']],$data['remember']);
    }
}
