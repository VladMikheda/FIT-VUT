<?php

namespace App\Http\Controllers\Problems;

use App\Http\Controllers\Controller;
use App\Http\Requests\Problems\AddTicketRequest;
use App\Models\Problems;
use App\Models\Ticket;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class AddTicketController extends BaseController
{
    public function __invoke(AddTicketRequest $request, Ticket $ticket)
    {
        $data = $request->validated();
        $message = $this->service->addTicket($data, $ticket);


        if($message){
            return redirect(route('manager.tickets.index'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect(route('manager.tickets.index'))->withErrors([
            'notError' => 'Tiket úspěšně přidán do vybraného problému',
        ]);

    }
}
