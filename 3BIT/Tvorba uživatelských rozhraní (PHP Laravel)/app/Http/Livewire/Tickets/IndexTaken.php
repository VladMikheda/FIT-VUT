<?php
/*
 * Project: Volunteer System
 * File: IndexTaken.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Invitation;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;
use Livewire\Component;

class IndexTaken extends Component
{
    public $category_id;
    public $dateOrder;
    public $reward;
    public $search = '';
    public $tickets;
    public $hidden = true;
    public $invitation_to_give_up;
    protected $listeners = ['showResults'];

    //find all the tickets by the user through approved invitations
    public function mount() {
        $this->tickets = DB::table('tickets')
            ->join('invitations', 'tickets.id', 'invitations.ticket_id')
            ->where('invitations.user_id', Auth::id())
            ->where('invitations.approved', true)
            ->get();
    }

    //filter setup with data passed from the outside controller
    public function showResults($category_id, $dateOrder, $reward) {
        $this->dateOrder = $dateOrder;
        $this->category_id = $category_id;
        $this->reward = $reward;
    }

    //request from user to give up the ticket
//    public function giveUpRequest($invitation_id) {
//        $this->hidden = false;
//        $this->invitation_to_give_up = $invitation_id;
//    }

    public function giveUpRequest($ticket_id) {
        $this->hidden = false;
        $inv = DB::table('invitations')
            ->where('ticket_id', '=', $ticket_id)
            ->where('user_id','=', Auth::id())
            ->where('approved','=', true)
            ->first();
        $this->invitation_to_give_up = $inv->id;
    }

    public function cancelGiveUp() {
        $this->hidden = true;
    }

    public function giveUp() {
        $invitationToGiveUp = Invitation::find($this->invitation_to_give_up);
        $invitationToGiveUp->delete();
        $this->hidden = true;
    }

    //render and conditionally apply filters
    public function render()
    {
//        $this->tickets = DB::table('tickets')
//            ->join('invitations', 'tickets.id', 'invitations.ticket_id')
//            ->where('invitations.user_id', Auth::id())
//            ->where('invitations.approved', true);
        $this->tickets = DB::table('tickets')
            ->join('invitations', 'tickets.id', '=' ,'invitations.ticket_id')
            ->where('invitations.user_id', Auth::id())
            ->where('invitations.approved', true)
            ->select('tickets.*');

        if($this->category_id != 0) {
            $this->tickets = $this->tickets->where('category_id', $this->category_id);
        }

        if($this->dateOrder == 'newest') {
            $this->tickets = $this->tickets->latest();
        } elseif($this->dateOrder == 'oldest') {
            $this->tickets = $this->tickets->oldest();
        }

        if($this->reward == 'highest') {
            $this->tickets = $this->tickets->orderBy('price', 'desc');
        } elseif($this->reward == 'lowest') {
            $this->tickets = $this->tickets->orderBy('price', 'asc');
        }

        if($this->search) {
            $this->tickets = $this->tickets->where('title', 'like', '%'.$this->search.'%');
        }

        $this->tickets = $this->tickets->get();

        return view('livewire.tickets.index-taken')->extends('layouts.app');
    }
}
