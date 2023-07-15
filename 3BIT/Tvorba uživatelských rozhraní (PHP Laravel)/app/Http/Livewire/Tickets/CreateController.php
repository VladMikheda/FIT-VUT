<?php
/**
 *Project: Volunteer System
 *
 *File: CreateController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 **/

namespace App\Http\Livewire\Tickets;

use App\Models\categories;
use App\Models\Category;
use App\Models\Invitation;
use App\Models\Ticket;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Livewire\Component;
use Livewire\WithPagination;

class CreateController extends Component
{
    use WithPagination;

    public bool $hidden;

    public $title;
    public $address;
    public $category;
    public $number;
    public $price;
    public $description;
    public $invitePeople = [];
//    public $inviteText;
    public $allFriend = [];
    public $allCategories = [];

    /*
    * Initialization method
    */
    public function mount(){
        $this->hidden = true;
        $this->allCategories = Category::all()->toArray();
//        $this->inviteText = 'I invite you to help me do one thing my friend';
//        dd($this->allCategories);
    }


    /*
    * Method implements the function of invite friends
    */
    public function inviteFriends($id){
        $user = User::find($id);
//        dd($user);
        if(in_array($user->toArray(),$this->invitePeople)){
            $index = array_search($user->toArray(),$this->invitePeople);
            unset($this->invitePeople[$index]);
        }else{
            array_push($this->invitePeople,$user);
        }
    }

    /*
    * Method implements the show friends list
    */
    public function doShow(){
        $this->allFriend = [];

        $friends = User::whereIn('id',function ($query){
            $query->from('friends')
                ->select('friends.friend_id')
                ->where('friends.user_id','=',Auth::id())->where('friends.approved','=','1');})
            ->where('users.id','!=',Auth::id())->get();

        foreach($friends as $index => $fiend){
            if(!in_array($fiend->toArray(), $this->invitePeople)) {
                array_push($this->allFriend, $fiend);

            }
        }
        $this->hidden = false;
    }

    /*
     * Method hides the window
     */
    public function doHidden(){
        $this->hidden = true;
    }


    /*
     * Method removes from invitees
     */
    public function del($index){
        $this->allFriend = [];
        unset($this->invitePeople[$index]);
    }




    protected $rules = [
        'title' => 'required',
        'address' => 'required',
        'category' => 'required',
        'number' => 'nullable|numeric',
        'price' => 'nullable|numeric',
        'description'  => 'required',
        'invitePeople' => ['array'],
        'invitePeople.*' => 'required|distinct',
//        'inviteText' => 'nullable'
    ];


    /*
     * Method creates a ticket
     */
    public function saveTicket(){
        $validatedData = $this->validate();
//        dd($validatedData);

        $newTicket = [];
        $newTicket['user_id'] = Auth::id();
        $newTicket['title'] = $this->title;
        $newTicket['description'] = $this->description;
        $newTicket['address'] = $this->address;
        $newTicket['number_people'] = $this->number;
        $newTicket['price'] = $this->price;
        if(!$this->price){
            $newTicket['price'] = 0;
        }
        $newTicket['category_id'] = $this->category;

        $ticket = Ticket::create($newTicket);

        $newInvite = [];
        $newInvite['ticket_id'] = $ticket->id;
        $newInvite['approved'] = true;
        foreach ($this->invitePeople as $invite){
            $newInvite['user_id'] = $invite["id"];
//            $newInvite['content'] = $this->inviteText;
            Invitation::create($newInvite);
        }

        $this->title = null;
        $this->address = null;
        $this->category = null;
        $this->number = null;
        $this->price = null;
        $this->description = null;
//        $this->inviteText = 'I invite you to help me do one thing my friend';
        $this->invitePeople = [];


    }

    /*
     * Render method
     */
    public function render()
    {
        return view('tickets.create')->extends('layouts.app');
    }
}
