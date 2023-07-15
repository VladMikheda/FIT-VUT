<?php
/*
 * Project: Volunteer System
 * File: IndexCreated.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Invitation;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;
use Livewire\Component;

//controllers that manages the display of the created tickets
class IndexCreated extends Component
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
            ->where('tickets.user_id', Auth::id());
    }

    //initialize the data and trigger the filter component that is listening to this event
    public function showResults($category_id, $dateOrder, $reward) {
        $this->dateOrder = $dateOrder;
        $this->category_id = $category_id;
        $this->reward = $reward;
    }

    //rendering and conditionally applying filters
    public function render()
    {   $this->tickets = DB::table('tickets')
            ->where('tickets.user_id', Auth::id());

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

        return view('livewire.tickets.index-created')->extends('layouts.app');
    }
}
