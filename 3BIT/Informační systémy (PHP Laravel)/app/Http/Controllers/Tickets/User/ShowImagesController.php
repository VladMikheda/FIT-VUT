<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Controllers\Controller;
use App\Models\Ticket;
use Illuminate\Support\Facades\Auth;

class ShowImagesController extends BaseController
{
    public function __invoke(Ticket $ticket)
    {
        if($ticket->user_id !== Auth::id()){
            redirect(route('profile.index'));
        }

        $images = $ticket->image()->paginate(6);

//        dd($tickets);
        return view('tickets.show_images',compact('images','ticket'));

    }
}
