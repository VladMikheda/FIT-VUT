<?php

namespace App\Services\Registration;


use App\Models\User;
use Illuminate\Support\Facades\Auth;

class Service
{

    public function store($data)
    {
        $data['approved'] = false;

        $user = User::create($data);

        return $user;
    }
}
