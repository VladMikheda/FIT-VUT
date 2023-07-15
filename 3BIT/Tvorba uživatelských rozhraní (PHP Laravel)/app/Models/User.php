<?php
/**
 *Project: Volunteer System
 *
 *File: User.php
 *Subject: ITU 2022
 *
 * @author: Vladislav Mikheda xmikhe00
 * @author: Vladislav Khrisanov xkhris00
 * @author: Denis Karev xkarev00
 **/
namespace App\Models;

// use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;
use Illuminate\Support\Facades\Hash;
use Laravel\Sanctum\HasApiTokens;


class User extends Authenticatable
{
    use HasApiTokens, HasFactory, Notifiable;
    protected $table = 'users';
    /**
     * The attributes that are mass assignable.
     *
     * @var array<int, string>
     */
    protected $fillable = [
        'name',
        'lastname',
        'email',
        'password',
    ];

    /**
     * The attributes that should be hidden for serialization.
     *
     * @var array<int, string>
     */
    protected $hidden = [
        'password',
        'remember_token',
    ];

    /**
     * The attributes that should be cast.
     *
     * @var array<string, string>
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];


    public function setPasswordAttribute($password){
        $this->attributes['password'] = Hash::make($password);
    }


    public function scopeSearch($query, $term){
        $query->where(function ($query) use ($term){
            $query->where('name','like','%'.$term.'%')->orWhere('lastname','like','%'.$term.'%');
        });
    }

    public function chats() {
        return $this->hasMany(Chat::class);
    }

    public function friend(){
        return $this->hasMany(Friend::class);
    }

    public function invitations() {
        return $this->hasMany(Invitation::class);
    }

    public function tickets() {
        return $this->hasMany(Ticket::class);
    }
}
