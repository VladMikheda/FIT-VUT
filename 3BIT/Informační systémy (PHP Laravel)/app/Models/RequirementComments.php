<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class RequirementComments extends Model
{
    use HasFactory;
    protected $table = 'requirement_comments';
    protected $guarded = [];
}
