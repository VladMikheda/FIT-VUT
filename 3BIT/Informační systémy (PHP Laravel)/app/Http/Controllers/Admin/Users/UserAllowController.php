<?php

namespace App\Http\Controllers\Admin\Users;

use App\Http\Controllers\Admin\BaseController;
use App\Models\User;

class UserAllowController extends BaseController
{
    public function __invoke(User $user)
    {
        $user->approved = 1;
        $user->save();

        return redirect(route('admin.userAccept'));
    }
}
