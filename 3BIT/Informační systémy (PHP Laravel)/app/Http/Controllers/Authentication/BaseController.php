<?php

namespace App\Http\Controllers\Authentication;

use App\Http\Controllers\Controller;
use App\Services\Authentication\Service;

class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
