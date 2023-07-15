<?php
/**
 *Project: Volunteer System
 *
 *File: AddController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 **/
namespace App\Http\Livewire\Friends;

use App\Models\Chat;
use App\Models\Friend;
use App\Models\User;
use Carbon\Carbon;
use Illuminate\Support\Facades\Auth;
use Livewire\Component;
use Livewire\WithPagination;

/**
 * The class controls activities with friends
 */
class AddController extends Component
{
    use WithPagination;

//    public $allPeople = [];
    public $search;
    public $chosenFunction;
    public $searchFriend;
    public $friendRequest;
    public $myRequest;
    public $myFriends;

    /*
     * Initialization method
     */
    public function mount(){
        $this->chosenFunction = 'addFriend';
        $this->searchFriend = true;
        $this->friendRequest = false;
        $this->myRequest = false;
        $this->myFriends = false;
    }

    /*
     * Method switches applications to friend serch mode
     */
    public function switchSearchFriend(){
        $this->chosenFunction = 'addFriend';
        $this->searchFriend = true;
        $this->friendRequest = false;
        $this->myRequest = false;
        $this->myFriends = false;
    }

    /*
     * Method switches applications to views of new friend requests mode
     */
    public function switchNewFriend(){
        $this->chosenFunction = 'acceptFriend';
        $this->searchFriend = false;
        $this->friendRequest = true;
        $this->myRequest = false;
        $this->myFriends = false;
    }

    /*
    * Method switches applications to views of my requests mode
    */
    public function switchMyRequest(){
        $this->chosenFunction = 'deleteRequest';
        $this->searchFriend = false;
        $this->friendRequest = false;
        $this->myRequest = true;
        $this->myFriends = false;
    }

    /*
   * Method switches applications to views of my friends mode
   */
    public function switchMyFriend(){
        $this->chosenFunction = 'deleteFriend';
        $this->searchFriend = false;
        $this->friendRequest = false;
        $this->myRequest = false;
        $this->myFriends = true;
    }


    /*
     * Method implements the function of adding friends
     */
    public function addFriend($id){
        $exist = Friend::where('friend_id','=',$id)->where('user_id','=',Auth::id())->get()->toArray();
        if(empty($exist)){
            $newFriend  = [];
            $newFriend['user_id'] = Auth::id();
            $newFriend['friend_id'] = $id;
            $newFriend['approved'] = false;
            Friend::create($newFriend);
        }
    }

    /*
     * Method implements the function of delete friends
     */
    public function deleteFriend($id){
        $exist = Friend::where('friend_id','=',$id)->where('user_id','=',Auth::id())->first();
        if(!empty($exist)){
            $exist->delete();
            $accept = Friend::where('user_id','=',$id)->where('friend_id','=',Auth::id())->first();
            $accept->approved = false;
            $accept->save();
        }
    }

    /*
     * Method implements the function of delete request friends
     */
    public function deleteRequest($id){
        $exist = Friend::where('friend_id','=',$id)->where('user_id','=',Auth::id())->first();
        if(!empty($exist)){
            $exist->delete();
        }
    }

    /*
    * Method implements the function of accept friends
    */
    public function acceptFriend($id){
        $accept = Friend::where('user_id','=',$id)->where('friend_id','=',Auth::id())->first();
        $accept->approved = true;
        $accept->save();
        $exist = Friend::where('friend_id','=',$id)->where('user_id','=',Auth::id())->get()->toArray();
        if(empty($exist)){
            $newFriend  = [];
            $newFriend['user_id'] = Auth::id();
            $newFriend['friend_id'] = $id;
            $newFriend['approved'] = true;
            Friend::create($newFriend);
        }

    }

    public function startChat($person_id)
    {
        $user_id = Auth::id();

        $passedChat = Chat::query()
            ->where('from_user_id', $person_id)
            ->where('to_user_id', $user_id)
            ->first();
        if(!isset($passedChat)) {
            $passedChat = Chat::query()
                ->where('from_user_id', $user_id)
                ->where('to_user_id', $person_id)
                ->first();
        }
        if(!isset($passedChat)) {
            $passedChat = Chat::create([
                'from_user_id' => $user_id,
                'to_user_id' => $person_id
            ]);
        }

        $now = Carbon::now();
        $chat = Chat::find($passedChat->id);
        $chat->updated_at = $now;
        $chat->save();

        return redirect()->route('chats');
    }

    /*
     * Render method
     */
    public function render()
    {
        $people = [];
        if($this->myFriends){
            $people =  User::whereIn('id',function ($query){
            $query->from('friends')
                ->select('friends.friend_id')
                ->where('friends.user_id','=',Auth::id())->where('friends.approved','=','1');})
            ->where('users.id','!=',Auth::id())->search(trim($this->search))->paginate(12);
        }else if($this->friendRequest){
            $people =  User::whereIn('id',function ($query){
                $query->from('friends')
                    ->select('friends.user_id')
                    ->where('friends.friend_id','=',Auth::id())->where('friends.approved','=','0');})
                ->where('users.id','!=',Auth::id())->search(trim($this->search))->paginate(12);
        }else if($this->myRequest){
            $people =  User::whereIn('id',function ($query){
                $query->from('friends')
                    ->select('friends.friend_id')
                    ->where('friends.user_id','=',Auth::id())->where('friends.approved','=','0');})
                ->where('users.id','!=',Auth::id())->search(trim($this->search))->paginate(12);
        }else{
            $people =  User::whereNotIn('id',function ($query){
                $query->from('friends')
                    ->select('friends.friend_id')
                    ->where('friends.user_id','=',Auth::id());})
                ->whereNotIn('id', function ($query){
                    $query->from('friends')
                        ->select('friends.user_id')
                        ->where('friends.friend_id','=',Auth::id());
                })
                ->where('users.id','!=',Auth::id())->search(trim($this->search))->paginate(12);
        }
//        $people =  User::whereIn('id',function ($query){
//            $query->from('friends')
//                ->select('friends.friend_id')
//                ->where('friends.user_id','=',Auth::id());})
//            ->where('users.id','!=',Auth::id())->search(trim($this->search))->paginate(12);
        return view('friends.index',[
            'allPeople' => $people,
        ])->extends('layouts.app');
    }
}


//->where('name','like','%'.$this->search.'%')->where('lastname','like','%'.$this->search.'%')
