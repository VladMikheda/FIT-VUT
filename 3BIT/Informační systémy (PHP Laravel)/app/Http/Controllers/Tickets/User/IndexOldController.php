<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Controllers\Controller;
use App\Http\Requests\Tickets\FilterRequest;
use Illuminate\Support\Facades\Auth;

class IndexOldController extends BaseController
{
    public function __invoke(FilterRequest $request)
    {
        $data = $request->validated();

        $tickets = $this->service->indexOld(Auth::user(),$data);

//        dd($tickets);
        $old = true;

        return view('tickets.index',compact('tickets','old'));

    }
}
