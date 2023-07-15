<?php
/*
 * Project: Volunteer System
 * File: IndexFilter.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Category;
use Livewire\Component;

//component for filtering the publicly available tickets
class IndexFilter extends Component
{
    public $category = 0;
    public $dateOrder = '';
    public $reward = '';

    //get chosen filters from the view and emit event
    public function filter() {
        $this->emitTo('tickets.index-public', 'showResults', $this->category, $this->dateOrder, $this->reward);
    }

    public function render()
    {
        $categories = Category::all();
        return view('livewire.tickets.index-filter', [
            'categories' => $categories
        ])->extends('layouts.app');
    }
}
