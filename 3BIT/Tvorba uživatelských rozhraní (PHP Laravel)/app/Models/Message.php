<?php
/**
 *Project: Volunteer System
 *
 *File: Message.php
 *Subject: ITU 2022
 *
 * @author: Vladislav Mikheda xmikhe00
 * @author: Vladislav Khrisanov xkhris00
 * @author: Denis Karev xkarev00
 **/
namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Message extends Model
{
    use HasFactory;

    protected $guarded = [];

    public function fromChat()
    {
        return $this->belongsTo(Chat::class);
    }

    public function fromUser()
    {
        return $this->belongsTo(User::class);
    }
}
