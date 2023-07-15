<?php
/**
 *Project: Volunteer System
 *
 *File: ManageTicket.php
 *Subject: ITU 2022
 *
 *@author: Denis Karev xkarev00
 **/

namespace App\Http\Livewire\Tickets;

use App\Models\Invitation;
use App\Models\Ticket;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Livewire\Component;

class ManageTicket extends Component
{
    public $ticket;

    public $title;
    public $description;
    public $address;
    public $invitations = [];

    protected $rules = [
        'title' => 'required|string',
        'description' => 'required|string',
        'address' => 'required|string',
        //'price' => 'required|numeric',
    ];

    public function mount($ticket) {
        $this->ticket = Ticket::find($ticket);

        if ($this->ticket == null) {
            abort(404);
        }

        if (Auth::id() != $this->ticket->user_id) {
            abort(403);
        }

        $this->title = $this->ticket->title;
        $this->description = $this->ticket->description;
        $this->address = $this->ticket->address;
        $this->price = $this->ticket->price;

        $this->invitations = $this->ticket->invitations->sortByDesc('created_at')->sortByDesc('approved');
    }

    public function render() {
        $this->invitations = $this->ticket->invitations->sortByDesc('created_at')->sortByDesc('approved');
        return view('livewire.tickets.manage')->extends('layouts.app');
    }

    public function save() {
        $this->validate();
        $this->ticket->update([
            'title' => $this->title,
            'description' => $this->description,
            'address' => $this->address,
            'price' => $this->price,
        ]);
    }

    public function delete() {
        $this->ticket->delete();
        return redirect(route('ticket.public'));
//        return redirect()->to('/tickets/public');
    }

    public function approveInvitation($invitationId) {
        $invitation = Invitation::find($invitationId);
        $invitation->update([
            'approved' => true,
        ]);
        $this->mount($this->ticket->id);
    }

    public function rejectInvitation($invitationId) {
        $invitation = Invitation::find($invitationId);
        $invitation->delete();
        $this->mount($this->ticket->id);
    }

    public function openTicketPage() {
        return redirect()->to('/tickets/public/' . $this->ticket->id);
    }

    public function openTakenPage() {
        return redirect()->to('/tickets/taken/' . $this->ticket->id);
    }
}
