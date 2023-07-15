<?php

namespace App\Http\Controllers\Join;



use App\Http\Requests\Join\StoreRequest;
use App\Models\Admins;
use App\Models\Managers;
use App\Models\Repairs;
use Illuminate\Support\Facades\Auth;

class StoreController extends BaseController
{
    public function __invoke(StoreRequest $request)
    {

        $data = $request->validated();
        $reply = $this->service->store($data);


        if(!$reply['newItem']) {
            return redirect(route('join.create'))->withErrors([
                'formError' => $reply['message'],
            ]);
        }

        return redirect(route('join.create'))->withErrors([
            'notError' => 'Vaše žádost byla úspěšně přijata',
        ]);
    }
}
