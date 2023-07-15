<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Requests\Tickets\StoreRequest;

class StoreController extends BaseController
{
    public function __invoke(StoreRequest $request)
    {
        $data = $request->validated();

        $message = $this->service->store($data);


        if($message){
            return redirect(route('user.tickets.create'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect((route('user.tickets.index')));

    }
}
