<?php

namespace App\Http\Controllers\Manager\Technicians;

use App\Http\Controllers\Manager\Problems\BaseController;
use App\Models\Repairs;

class AddController extends BaseController
{

    public function __invoke(Repairs $tech)
    {
        $tech->approved = 1;
        $tech->save();
        return redirect(route('technician.index.new'));
    }
}
