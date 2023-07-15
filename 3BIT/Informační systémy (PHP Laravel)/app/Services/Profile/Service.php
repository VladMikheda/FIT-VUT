<?php

namespace App\Services\Profile;


use App\Models\Images;
use App\Models\Ticket;
use App\Models\TicketComments;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Hash;

class Service
{

    public function update($data)
    {

        $logout = false;


        $user = Auth::user();

        if(isset($data['name'])){
            $user->name = $data['name'];
        }
        if(isset($data['lastname'])){
            $user->lastname = $data['lastname'];
        }
        if(isset($data['birthday'])){
            $user->birthday = $data['birthday'];
        }
        if(isset($data['phone'])){
            $user->phone = $data['phone'];
        }

        if(isset($data['image'])){
            $image = $data['image'];
            $path = $image->store('public/images/tickets');
            $path = str_replace('public/','storage/',$path);
            $user->photo = $path;
        }

        if(isset($data['email'])){
            $user->email = $data['email'];
            $logout = true;
        }

        $user->save();

        return $logout;
    }

    public function updatePassword($data){

        $user = Auth::user();

        if(!Hash::check($data['password'], $user->getAuthPassword())){
            return 'Staré heslo se neshoduje';
        }

        $user->setPasswordAttribute($data['new_password']);

        $user->save();

        return null;


    }

}
