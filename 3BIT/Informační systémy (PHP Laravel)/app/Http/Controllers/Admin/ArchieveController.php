<?php


namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Services\Admin;
use Illuminate\Support\Facades\Auth;

class ArchieveController extends BaseController
{
    public function __invoke()
    {
        $problems = $this->service->getSolved();

        return view('admin.problems_archieve', compact('problems'));
    }
}
