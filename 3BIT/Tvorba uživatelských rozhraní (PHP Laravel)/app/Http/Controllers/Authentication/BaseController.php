<?php
/**
 *Project: Volunteer System
 *
 *File: BaseController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 * the file was taken from the IIS project
 **/
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
