<?php

namespace App\Http\Controllers\Problems;

use App\Http\Controllers\Controller;
use App\Services\Problems\Service;


class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
