<?php
/**
 *Project: Volunteer System
 *
 *File: Ticket.php
 *Subject: ITU 2022
 *
 * @author: Vladislav Mikheda xmikhe00
 * @author: Vladislav Khrisanov xkhris00
 * @author: Denis Karev xkarev00
 **/
namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Ticket extends Model
{
    use HasFactory;

    protected $guarded = [];

    public function category() {
        return $this->belongsTo(Category::class);
    }

    public function user() {
        return $this->belongsTo(User::class);
    }

    public function comments()
    {
        return $this->hasMany(Comment::class);
    }

    public function taskBoards() {
        return $this->hasMany(TaskBoard::class);
    }

    public function invitations()
    {
        return $this->hasMany(Invitation::class);
    }

    public function friends() {
        return $this->hasMany(Friend::class);
    }

    public function groupMessages()
    {
        return $this->hasMany(GroupMessage::class);
    }
}
