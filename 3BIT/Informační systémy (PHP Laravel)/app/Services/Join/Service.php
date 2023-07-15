<?php

namespace App\Services\Join;



use App\Models\Admins;
use App\Models\Managers;
use App\Models\Repairs;
use Illuminate\Support\Facades\Auth;

class Service
{
    public function store($data)
    {

        $userId = Auth::id();
        $user = Auth::user();
        $reply = [];
        $reply['message'] = 'Váš požadavek se nepodařilo uložit';
        $reply['newItem'] = null;

        if($user['specialization'] == 0) {
            if ($data['join'] == 1) {
                $reply['newItem'] = Admins::create(['user_id' => $userId]);
            } elseif ($data['join'] == 2) {
                $reply['newItem'] = Managers::create(['user_id' => $userId]);
            } elseif ($data['join'] == 3) {
                $reply['newItem'] = Repairs::create(['user_id' => $userId]);
            }else{
                return $reply;
            }

            $user->specialization = 1;
            $user->save();
        }else{
            $reply['message'] = "Můžete poslat pouze jednu přihlášku";
        }
        return $reply;

    }
}
