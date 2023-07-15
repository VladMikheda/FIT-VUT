<?php

namespace App\Http\Controllers\Admin\Users;

use App\Http\Controllers\Admin\BaseController;
use App\Models\User;
use Illuminate\Support\Facades\Auth;

class UserDenyController extends BaseController
{
    public function __invoke(User $user)
    {
        $user->approved = 0;
        $user->save();

        return redirect(route('admin.users'));
    }
}
