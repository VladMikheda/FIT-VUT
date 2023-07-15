<?php
/**
 *Project: Volunteer System
 *
 *File: TaskBoard.php
 *Subject: ITU 2022
 *
 * @author: Vladislav Mikheda xmikhe00
 * @author: Vladislav Khrisanov xkhris00
 * @author: Denis Karev xkarev00
 **/
namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class TaskBoard extends Model
{
    use HasFactory;
    protected $guarded = [];

    public function taskList(){
        return $this->hasMany(TaskList::class);
    }
}
