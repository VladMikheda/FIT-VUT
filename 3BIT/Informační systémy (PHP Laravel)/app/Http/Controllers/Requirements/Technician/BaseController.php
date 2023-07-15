<?php

namespace App\Http\Controllers\Requirements\Technician;

use App\Http\Controllers\Controller;
use App\Services\Requirements\Service;


class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
