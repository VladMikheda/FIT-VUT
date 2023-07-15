<?php
/*
 * Project: Volunteer System
 * File: IndexPublic.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Invitation;
use App\Models\Ticket;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;
use Livewire\Component;

//component for displaying the list of public tickets
class IndexPublic extends Component
{
    public $category_id;
    public $dateOrder;
    public $reward;
    public $search = '';
    public $tickets;
    public $changeHidden = true;
    public $previewHidden = true;
    public $invitationMessage;
    public $invitationToTicket;
    public $ticketToPreview;
    public $my_id;
    public $invitationExists;
    protected $listeners = ['showResults'];

    //initial setup
    public function mount() {
        $this->tickets = Ticket::get();
        $this->my_id = Auth::id();
    }

    //filter setup with data passed from the outside controller
    public function showResults($category_id, $dateOrder, $reward) {
        $this->dateOrder = $dateOrder;
        $this->category_id = $category_id;
        $this->reward = $reward;
    }

    //triggering and setting up the invitation form
    public function invitationForm($ticket_id) {
        $this->invitationToTicket = $ticket_id;
        $this->changeHidden = false;

        //check if already exist
        $invitation = DB::table('invitations')
            ->where('user_id', '=', Auth::id())
            ->where('ticket_id', '=', $ticket_id)
            ->first();
        if(isset($invitation)) {
            $this->invitationExists = true;
        }
        else {
            $this->invitationExists = false;
        }
    }

    public function cancelInvitation() {
        $this->changeHidden = true;
        $this->reset('invitationMessage');
        $this->reset('invitationExists');
    }

    //adding invitation to the database
    public function createInvitation() {
        Invitation::create([
            'user_id' => Auth::id(),
            'ticket_id' => $this->invitationToTicket,
            'content' => $this->invitationMessage
        ]);
        $this->changeHidden = true;
        $this->reset('invitationMessage');
        $this->reset('invitationExists');
    }

    //show preview of the chosen ticket
    public function showPreview($ticket_id) {
        $this->ticketToPreview = Ticket::find($ticket_id);
        $this->previewHidden = false;
    }

    public function hidePreview() {
        $this->previewHidden = true;
    }

    //render and conditionally apply filters
    public function render()
    {
        $this->tickets = Ticket::query();

        if($this->category_id != 0) {
            $this->tickets = $this->tickets->where('category_id', $this->category_id);
        }

        if($this->dateOrder == 'newest') {
            $this->tickets = $this->tickets->orderBy('created_at', 'desc');
        } elseif($this->dateOrder == 'oldest') {
            $this->tickets = $this->tickets->orderBy('created_at', 'asc');
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

        return view('livewire.tickets.index-public')->extends('layouts.app');
    }
}
