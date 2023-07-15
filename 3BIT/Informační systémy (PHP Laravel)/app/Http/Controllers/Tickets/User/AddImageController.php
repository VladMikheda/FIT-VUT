<?php

namespace App\Http\Controllers\Tickets\User;

use App\Http\Requests\Tickets\AddImageRequest;
use App\Models\Ticket;
use App\Models\TicketComments;
use Illuminate\Support\Facades\Auth;


class AddImageController extends BaseController
{
    public function __invoke(Ticket $ticket, AddImageRequest $request)
    {

        if($ticket->user_id !== Auth::id()){
            redirect(route('profile.index'));
        }
        $data = $request->validated();

        if(empty($data)){
            return redirect(route('user.tickets.show',$ticket->id))->withErrors([
                'image.*' => "Musíte vybrat alespoň jeden obrázek",
            ]);
        }

        $message = $this->service->addImage($data,$ticket);

        if(!$message){
            return redirect(route('user.tickets.show',$ticket->id))->withErrors([
                'image.*' => $message,
            ]);
        }

        return redirect((route('user.tickets.show',$ticket->id)));

    }
}
