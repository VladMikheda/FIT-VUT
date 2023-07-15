<?php

namespace App\Http\Controllers\Manager\Technicians;

use App\Http\Controllers\Admin\BaseController;
use App\Models\Managers;
use App\Models\Repairs;

class FireController extends BaseController
{
    public function __invoke($tech_id)
    {
        $repair = Repairs::find($tech_id);
        $repair->approved = 0;
        $repair->save();

        return redirect(route('technician.index'));
    }
}
