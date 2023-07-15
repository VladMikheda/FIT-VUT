<?php
/**
 *Project: Volunteer System
 *
 *File: Invite.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 **/
namespace App\Http\Middleware;

use App\Models\TaskBoard;
use App\Models\Ticket;
use App\Models\User;
use Closure;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class Invite
{
    /**
     * Handle an incoming request.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \Closure(\Illuminate\Http\Request): (\Illuminate\Http\Response|\Illuminate\Http\RedirectResponse)  $next
     * @return \Illuminate\Http\Response|\Illuminate\Http\RedirectResponse
     */
    public function handle(Request $request, Closure $next)
    {

        $patch = explode('/',$_SERVER['REQUEST_URI'],PHP_INT_MAX);
        $boardNumber = end($patch);
        $board = TaskBoard::find($boardNumber);

        if($board){
            $ticketNumber = $board->ticket_id;

            $checkInvite = User::whereIn('id',function ($query) use($ticketNumber){
                $query->from('invitations')
                    ->select('user_id')
                    ->where('invitations.ticket_id','=',$ticketNumber)->where('invitations.approved','=','1');})
                ->where('users.id','=',Auth::id())->get();

            $ticket = Ticket::find($ticketNumber);

            if($ticket){
                if(!empty($checkInvite->toArray()) || $ticket->user_id == Auth::id()){
                    return $next($request);
                }
            }

        }

        return redirect(route('ticket.public'));

    }
}
