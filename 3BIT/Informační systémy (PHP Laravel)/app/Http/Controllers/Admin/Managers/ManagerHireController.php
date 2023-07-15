<?php

namespace App\Http\Controllers\Admin\Managers;

use App\Http\Controllers\Admin\BaseController;
use App\Models\Managers;

class ManagerHireController extends BaseController
{
    public function __invoke(Managers $manager)
    {
        $manager->approved = 1;
        $manager->save();

        return redirect(route('admin.managerApprove'));
    }
}
