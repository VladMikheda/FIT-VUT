<?php

namespace App\Http\Controllers\Tickets\Manager;

use App\Http\Controllers\Controller;
use App\Models\Managers;
use App\Models\Ticket;
use App\Models\TicketStatuses;
use Illuminate\Database\Capsule\Manager;
use Illuminate\Support\Facades\Auth;

class ShowController extends Controller
{
    public function __invoke(Ticket $ticket)
    {
        if($ticket->manager_id == null || $ticket->manager_id == (Managers::where('user_id',Auth::id())->get()->toArray())[0]['id']) {
            $images = $ticket->image()->take(3)->get();

            $comments = $ticket->ticketComment()->paginate(10);

            $status = TicketStatuses::find($ticket->ticket_status_id);

            $manager = Managers::where('user_id', Auth::id())->get();
            $problems = $manager[0]->problems;
            $manager_id  =  (Managers::where('user_id',Auth::id())->get()->toArray())[0]['id'];
            return view('tickets.manager_show', compact('ticket', 'status', 'images', 'comments', 'problems','manager_id'));
        }else{
            return redirect(route('manager.tickets.index'))->withErrors([
                'formError' => 'Tento tiket nespravujete',
            ]);
        }
    }
}
