<?php

namespace App\Http\Controllers\Admin\Users;

use App\Http\Controllers\Controller;
use App\Services\Admin\Service;


class BaseController extends Controller
{

    public Service $service;

    public function __construct(Service $service)
    {
        $this->service = $service;
    }


}
