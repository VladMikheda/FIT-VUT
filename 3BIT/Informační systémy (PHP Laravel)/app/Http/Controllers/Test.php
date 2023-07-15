<?php

namespace App\Http\Controllers;

use App\Models\Problem;
use App\Models\TechnicalSpecialist;
use App\Models\User;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller as BaseController;
use Illuminate\Support\Facades\Hash;
use Illuminate\Testing\Fluent\Concerns\Has;

class Test extends BaseController
{
    public function index(Request $request): \Illuminate\Contracts\View\Factory|\Illuminate\Contracts\View\View|\Illuminate\Contracts\Foundation\Application
    {

        return view("register");
    }


    public function register(Request $request): \Illuminate\Http\RedirectResponse
    {
        $user = User::create([
            "name" => $request->get("name"),
            "lastname" => $request->get("lastname"),
            "birthday" => $request->date("birthday"),
            "birth_number" => $request->get("birthNumber"),
            "phone_number" => $request->get("phone"),
            "password" => Hash::make($request->get("password"))

        ]);

        dd($user);

//        TechnicalSpecialist::create([
//            "spec_id" => 99,
//        ]);


//        $spec = $user->technicalSpecialist()->create();
//        $problem = Problem::create([
//            "title" => "hello",
//            "description" => "2",
//            "state" => "state",
//        ]);
////        $spec = TechnicalSpecialist::create();
//        $problem->requirement()->create([
//            "technical_specialist_id" => 88
//        ]);

        dd($user);
        return to_route('home');
    }
}
