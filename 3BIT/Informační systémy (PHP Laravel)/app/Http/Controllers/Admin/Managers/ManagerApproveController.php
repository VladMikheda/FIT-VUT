<?php

namespace App\Http\Controllers\Admin\Managers;

use App\Http\Controllers\Controller;
use App\Services\Admin;
use Illuminate\Support\Facades\Auth;

class ManagerApproveController extends BaseController
{
    public function __invoke()
    {
        $newcomers = $this->service->appliedManagers();

        return view('admin.manager_approve', compact('newcomers'));
    }
}
