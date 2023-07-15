<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Services\Admin;
use Illuminate\Support\Facades\Auth;

class ViewProbsController extends BaseController
{
    public function __invoke()
    {
        $problems = $this->service->getAllProblems();

        return view('admin.all_problems', compact('problems'));
    }
}
