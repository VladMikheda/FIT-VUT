<?php

namespace App\Http\Controllers\Tickets\Manager;

use App\Http\Controllers\Controller;
use App\Services\Citymanager;
use Illuminate\Support\Facades\Auth;

class IndexController extends BaseController
{

    public function __invoke()
    {
        $tickets = $this->service->viewNewUnsolved();

        return view('tickets.manager_index', compact('tickets'));
    }
}
