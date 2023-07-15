<?php

namespace App\Http\Controllers\Admin\Users;

use App\Http\Controllers\Admin\BaseController;

class UsersController extends BaseController
{
    public function __invoke()
    {
        $users = $this->service->getAllUsers();

        return view('admin.users', compact('users'));
    }
}
