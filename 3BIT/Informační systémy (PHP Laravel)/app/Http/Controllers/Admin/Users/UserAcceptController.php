<?php

namespace App\Http\Controllers\Admin\Users;

use App\Http\Controllers\Admin\BaseController;

class UserAcceptController extends BaseController
{
    public function __invoke()
    {
        $newcomers = $this->service->getAllNewcomers();

        return view('admin.user_accept', compact('newcomers'));
    }
}
