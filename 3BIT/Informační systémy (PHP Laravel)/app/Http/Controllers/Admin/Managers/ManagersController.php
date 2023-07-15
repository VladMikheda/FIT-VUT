<?php

namespace App\Http\Controllers\Admin\Managers;

use App\Http\Controllers\Admin\BaseController;

class ManagersController extends BaseController
{
    public function __invoke()
    {
        $managers = $this->service->getAllManagers();

        return view('admin.managers', compact('managers'));
    }
}
