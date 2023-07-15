<?php
/**
 *Project: Volunteer System
 *
 *File: ProfileController.php
 *Subject: ITU 2022
 *
 *@author: Denis Karev xkarev00
 **/

namespace App\Http\Livewire;

use App\Models\Friend;
use Illuminate\Support\Facades\Hash;
use Livewire\Component;

class ProfileController extends Component
{
    public $user;

    public $name;
    public $email;
    public $registrationDate;
    public $tickets;
    public $ticketsCreated;
    public $friends;
    public $formActive = false;

    protected $listeners = [
        'deleteAccount' => 'deleteAccount',
    ];

    public function mount() {
        $this->user = auth()->user();

        $this->name = $this->user->name . ' ' . $this->user->lastname;
        $this->email = $this->user->email;
        $this->registrationDate = $this->user->created_at->format('d.m.Y H:i:s');
        $this->tickets = $this->user->tickets;
        $this->ticketsCreated = $this->tickets->count();
        $this->friends = Friend::where('user_id', $this->user->id)->count();
    }

    public function save() {
        $this->validate([
            'name' => 'required|string',
            'email' => 'required|email',
        ]);

        $firstName = explode(' ', $this->name)[0];
        $lastName = substr($this->name, strlen($firstName) + 1);

        $this->user->update([
            'name' => $firstName,
            'lastname' => $lastName,
            'email' => $this->email,
        ]);

        $this->deactivateForm();
    }

    public function deleteTicket($ticketId) {
        $ticket = $this->user->tickets->find($ticketId);

        $ticket->invitations()->delete();
        $ticket->taskBoards()->delete();

        $ticket->delete();
        $this->tickets = $this->user->tickets;
        $this->ticketsCreated = $this->tickets->count();
    }

    function deleteAccount() {
        auth()->logout();
        $this->user->delete();
        return redirect(route('index'));
    }

    public function activateForm() {
        $this->formActive = true;
    }

    public function deactivateForm() {
        $this->formActive = false;
    }

    public function render() {
        return view('livewire.profile')->extends('layouts.app');
    }
}
