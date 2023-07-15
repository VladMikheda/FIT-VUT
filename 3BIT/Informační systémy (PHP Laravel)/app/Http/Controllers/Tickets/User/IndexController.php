<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Controllers\Controller;
use App\Http\Requests\Tickets\FilterRequest;
use Illuminate\Support\Facades\Auth;

class IndexController extends BaseController
{
    public function __invoke(FilterRequest $request)
    {
        $data = $request->validated();
        $tickets = $this->service->index(Auth::user(),$data);

//        dd($tickets);
        return view('tickets.index',compact('tickets'));

    }
}
