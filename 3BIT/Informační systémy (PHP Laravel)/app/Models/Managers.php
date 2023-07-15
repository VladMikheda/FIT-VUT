<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Managers extends Model
{
    use HasFactory;
    protected $table = 'managers';
    protected $guarded = [];

    public function problems(): \Illuminate\Database\Eloquent\Relations\HasMany
    {
        return $this->hasMany(Problems::class,'manager_id','id');
    }
}
