<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Ticket extends Model
{
    use HasFactory;
    protected $table = 'tickets';
    protected $guarded = [];


    public function image(): \Illuminate\Database\Eloquent\Relations\HasMany
    {
        return $this->hasMany(Images::class);
    }

    public function ticketComment(): \Illuminate\Database\Eloquent\Relations\HasMany
    {
        return $this->hasMany(TicketComments::class);
    }

}
