<?php

namespace App\Http\Controllers\Manager\Problems;

class IndexController extends BaseController
{

    public function __invoke()
    {
        $problems = $this->service->getAllMyProblems();

        return view('problems.index', compact('problems'));
    }
}
