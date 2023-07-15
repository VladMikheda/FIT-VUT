<?php

namespace App\Http\Controllers\Problems;

use App\Http\Controllers\Controller;
use App\Models\Managers;
use App\Models\Ticket;
use App\Models\Problems;
use App\Models\TicketStatuses;
use Illuminate\Support\Facades\Auth;

class ShowController extends Controller
{
    public function __invoke(Problems $problem)
    {

        if($problem->manager_id == (Managers::where('user_id',Auth::id())->get()->toArray())[0]['id']) {

            $status = $problem->state;

            $manager = Managers::where('user_id', Auth::id())->get();
            $problems = $manager[0]->problems;

            $tickets = Ticket::where('problem_id', $problem->id)->get();

            return view('problems.show', compact('problem', 'status', 'tickets'));
        }else{
            return redirect(route('manager.tickets.index'))->withErrors([
                'formError' => 'Tento problem nespravujete',
            ]);
        }
    }
}
