<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Requirements extends Model
{
    use HasFactory;
    protected $table = 'requirements';
    protected $guarded = [];

    public function requirementComment(): \Illuminate\Database\Eloquent\Relations\HasMany
    {
        return $this->hasMany(RequirementComments::class,'requirement_id', 'id');
    }
}
