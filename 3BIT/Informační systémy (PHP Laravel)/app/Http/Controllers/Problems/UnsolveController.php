<?php

namespace App\Http\Controllers\Problems;

use App\Http\Controllers\Controller;
use App\Models\Managers;
use App\Models\Requirements;
use App\Models\Ticket;
use App\Models\Problems;
use App\Models\TicketStatuses;
use Illuminate\Support\Facades\Auth;

class UnsolveController extends Controller
{
    public function __invoke(Problems $problem)
    {
        if($problem->manager_id == (Managers::where('user_id',Auth::id())->get()->toArray())[0]['id']) {
            $problem->state = 1;
            $problem->save();

            $tickets = Ticket::where('problem_id', $problem->id)->get();

            foreach ($tickets as $ticket)
            {
                $ticket->ticket_status_id = 2;
                $ticket->save();
            }

            return redirect(route('manager.problems.index.old'));
        }
        else {
            return redirect(route('manager.problems.index'))->withErrors([
                'formError' => 'Tento problem nespravujete',
            ]);
        }

    }
}
