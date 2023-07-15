<?php

namespace App\Http\Controllers\Manager\Technicians;

use App\Http\Controllers\Manager\Problems\BaseController;

class IndexController extends BaseController
{

    public function __invoke()
    {
        $techs = $this->service->viewAllTechs();

        return view('technicians.view_techs_list', compact('techs'));
    }
}
