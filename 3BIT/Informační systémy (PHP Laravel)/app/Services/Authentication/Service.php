<?php

namespace App\Services\Authentication;



use Illuminate\Support\Facades\Auth;

class Service
{
    public function check($data): bool
    {
        return Auth::attempt(['email'=> $data['email'],'password'=>$data['password']],$data['remember']);
    }
}
