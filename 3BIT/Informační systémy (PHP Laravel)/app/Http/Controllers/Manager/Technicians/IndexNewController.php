<?php

namespace App\Http\Controllers\Manager\Technicians;

use App\Http\Controllers\Manager\Problems\BaseController;

class IndexNewController extends BaseController
{

    public function __invoke()
    {
        $techs = $this->service->appliedTechs();

        return view('technicians.view_applicants', compact('techs'));
    }
}
