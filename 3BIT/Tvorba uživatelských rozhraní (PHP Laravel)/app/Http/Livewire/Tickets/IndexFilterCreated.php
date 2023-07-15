<?php
/*
 * Project: Volunteer System
 * File: IndexFilterCreated.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Category;
use Livewire\Component;

//component for filtering tickets created by the user
class IndexFilterCreated extends Component
{
    public $category = 0;
    public $dateOrder = '';
    public $reward = '';

    //get chosen filters from the view and emit event
    public function filter() {
        $this->emitTo('tickets.index-created', 'showResults', $this->category, $this->dateOrder, $this->reward);
    }

    public function render()
    {
        $categories = Category::all();
        return view('livewire.tickets.index-filter-created', [
            'categories' => $categories
        ])->extends('layouts.app');
    }
}
