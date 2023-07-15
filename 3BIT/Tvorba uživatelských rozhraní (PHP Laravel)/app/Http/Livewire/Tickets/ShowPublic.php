<?php
/*
 * Project: Volunteer System
 * File: ShowPublic.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\Chat;
use App\Models\Comment;
use App\Models\Invitation;
use App\Models\Message;
use App\Models\Ticket;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;
use Livewire\Component;

//controller for managing the public page of the ticket
//the page has the comment section
class ShowPublic extends Component
{
    public $comments;
    public $ticket;
    public $hidden = true;
    public $invitationMessage;
    public $commentContent;
    public $invitationExists;
    public $deleteHidden = true;
    public $changeHidden = true;
    public $commentToDelete;
    public $updatedComment;
    public $contentToChange;
    public $my_id;

    protected $rules = [
        'commentContent' => 'required|string',
    ];

    //initial setup
    public function mount($ticket)
    {
        $this->my_id = Auth::id();
        $this->ticket = Ticket::find($ticket);
        $this->comments = Comment::query()
            ->where('user_id', Auth::id())
            ->where('ticket_id', $ticket)
            ->get();
    }

    //send comment and update the window
    public function sendComment() {
        $this->validate();
        Comment::create([
            'ticket_id' => $this->ticket->id,
            'user_id' => Auth::id(),
            'content' => $this->commentContent
        ]);

        $this->reset('commentContent');
        $this->ticket = Ticket::find($this->ticket->id);
        $this->dispatchBrowserEvent('chatToBottom');
    }

    //start or open if exists the chat with the author
    public function startChatAuthor()
    {
        $from_user_id = Auth::id();
        $to_user_id = $this->ticket->user_id;


        $passedChat = Chat::query()
            ->where('from_user_id', $from_user_id)
            ->where('to_user_id', $to_user_id)
            ->first();
        if(!isset($passedChat)) {
            $passedChat = Chat::query()
                ->where('from_user_id', $to_user_id)
                ->where('to_user_id', $from_user_id)
                ->first();
        }
        if(!isset($passedChat)) {
            $passedChat = Chat::create([
                'from_user_id' => $from_user_id,
                'to_user_id' => $to_user_id
            ]);
        }

        return redirect()->route('chats', $passedChat);
    }

    //triggering and setting up the invitation form
    public function invitationForm() {
        $this->hidden = false;
        //check if already exist
        $invitation = DB::table('invitations')
            ->where('user_id', '=', Auth::id())
            ->where('ticket_id', '=', $this->ticket->id)
            ->first();
        if(isset($invitation)) {
            $this->invitationExists = true;
        }
        else {
            $this->invitationExists = false;
        }
    }

    public function cancelInvitation() {
        $this->hidden = true;
    }

    //adding invitation to the database
    public function createInvitation() {
        Invitation::create([
            'user_id' => Auth::id(),
            'ticket_id' => $this->ticket->id,
            'content' => $this->invitationMessage
        ]);
        $this->hidden = true;
    }

    //verify comment deletion
    public function deleteVerify($message_id) {
        $this->commentToDelete = $message_id;
        $this->deleteHidden = false;
    }

    public function cancelDelete() {
        $this->deleteHidden = true;
        $this->reset('commentToDelete');
    }

    public function deleteComment(){
        $toDelete = Comment::find($this->commentToDelete);
        $toDelete->delete();
        $this->deleteHidden = true;
        $this->ticket = Ticket::find($this->ticket->id);
        $this->reset('commentToDelete');
    }

    //change comment
    public function changeWindow($message_id){
        $this->changeHidden = false;
        $this->updatedComment = Comment::find($message_id);
        $this->contentToChange = $this->updatedComment->content;
    }

    public function updateComment() {
        $this->updatedComment->content = $this->contentToChange;
        $this->updatedComment->save();
        $this->changeHidden = true;
        $this->ticket = Ticket::find($this->ticket->id);
        $this->reset('updatedComment');
        $this->reset('contentToChange');
    }

    //hide change window
    public function hidePanel(){
        $this->changeHidden = true;
        $this->reset('updatedComment');
        $this->reset('contentToChange');
    }

    public function render()
    {
//        $ticket = Ticket::find($this->ticket_id);
//        dd($ticket);
        return view('livewire.tickets.show-public')->extends('layouts.app');
    }
}
