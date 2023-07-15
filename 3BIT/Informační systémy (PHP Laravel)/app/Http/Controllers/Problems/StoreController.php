<?php

namespace App\Http\Controllers\Problems;

use App\Http\Requests\Tickets\StoreRequest;

class StoreController extends BaseController
{
    public function __invoke(StoreRequest $request)
    {
        $data = $request->validated();

        $message = $this->service->store($data);

        if(!$message){
            return redirect(route('problem.createProb'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect((route('manager.problems.index')));

    }
}
