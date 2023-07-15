<?php

namespace App\Http\Controllers\Join;

use App\Http\Controllers\Controller;
use App\Services\Join\Service;


class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
