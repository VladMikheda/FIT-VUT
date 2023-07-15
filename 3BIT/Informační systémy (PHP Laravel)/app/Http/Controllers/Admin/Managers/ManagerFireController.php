<?php

namespace App\Http\Controllers\Admin\Managers;

use App\Http\Controllers\Admin\BaseController;
use App\Models\Managers;

class ManagerFireController extends BaseController
{
    public function __invoke(Managers $manager)
    {
        $manager->approved = 0;
        $manager->save();

        return redirect(route('admin.allManagers'));
    }
}
