<?php

namespace App\Http\Controllers\Manager\Problems;

use App\Http\Controllers\Controller;
use App\Services\Citymanager\Service;


class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
