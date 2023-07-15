<?php

namespace App\Http\Controllers\Tickets\Manager;

use App\Http\Requests\Tickets\AddCommentRequest;
use App\Http\Requests\Tickets\AddImageRequest;
use App\Models\Managers;
use App\Models\Ticket;
use App\Models\TicketComments;
use Illuminate\Support\Facades\Auth;


class AddCommentController extends BaseController
{
    public function __invoke(Ticket $ticket,AddCommentRequest $request)
    {

        if($ticket->manager_id != (Managers::where('user_id',Auth::id())->get()->toArray())[0]['id']){
            return redirect(route('manager.tickets.index'))->withErrors([
                'formError' => 'Tento tiket nespravujete',
            ]);
        }

        $data = $request->validated();

        $message = $this->service->addComment($data,$ticket);

        if(!$message){
            return redirect(route('manager.tickets.show',$ticket->id))->withErrors([
                'content' => $message,
            ]);
        }

        return redirect((route('manager.tickets.show',$ticket->id)));

    }
}
