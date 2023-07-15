<?php
/*
 * Project: Volunteer System
 * File: ShowTaken.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Tickets;

use App\Models\GroupMessage;
use App\Models\Invitation;
use App\Models\TaskBoard;
use App\Models\Ticket;
use Illuminate\Support\Facades\Auth;
use Livewire\Component;

//controller for managing the page of the ticket for people who took it
//the page has the chat
class ShowTaken extends Component
{
    public $deleteHidden = true;
    public $changeHidden = true;

    public $hidden = true;
    public $invitation_to_give_up;

    public $messageContent;
    public $messageToDelete;
    public $updatedMessage;
    public $contentToChange;

    public $ticket;
    public $my_id;

    protected $rules = [
        'messageContent' => 'required|string',
    ];

    //initial setup
    public function mount($ticket)
    {
        $this->my_id = Auth::id();
        $this->ticket = Ticket::find($ticket);
    }

    //send message to the private chat and update the window
    public function sendMessage() {
        $this->validate();
        GroupMessage::create([
            'ticket_id' => $this->ticket->id,
            'user_id' => Auth::id(),
            'content' => $this->messageContent
        ]);

        $this->reset('messageContent');
        $this->ticket = Ticket::find($this->ticket->id);
        $this->dispatchBrowserEvent('chatToBottom');
    }

    //verify message deletion
    public function deleteVerify($message_id) {
        $this->messageToDelete = $message_id;
        $this->deleteHidden = false;
    }

    public function cancelDelete() {
        $this->deleteHidden = true;
        $this->reset('messageToDelete');
    }

    //change message
    public function deleteMessage(){
        $toDelete = GroupMessage::find($this->messageToDelete);
        $toDelete->delete();
        $this->deleteHidden = true;
        $this->ticket = Ticket::find($this->ticket->id);
        $this->reset('messageToDelete');
    }

    public function changeWindow($message_id){
        $this->changeHidden = false;
        $this->updatedMessage = GroupMessage::find($message_id);
        $this->contentToChange = $this->updatedMessage->content;
    }

    public function updateMessage() {
        $this->updatedMessage->content = $this->contentToChange;
        $this->updatedMessage->save();
        $this->changeHidden = true;
        $this->ticket = Ticket::find($this->ticket->id);
        $this->reset('updatedMessage');
        $this->reset('contentToChange');
    }

    //hide change message window
    public function hidePanel(){
        $this->changeHidden = true;
        $this->reset('updatedMessage');
        $this->reset('contentToChange');
    }

    //request to give up the ticket
    public function giveUpRequest($ticket_id) {
        $this->hidden = false;
        $this->invitation_to_give_up = Invitation::query()
            ->where('ticket_id', $ticket_id)
            ->where('user_id', $this->my_id)
            ->first();
    }

    public function cancelGiveUp() {
        $this->hidden = true;
    }

    public function giveUp() {
        $invitationToGiveUp = Invitation::find($this->invitation_to_give_up->id);
        $invitationToGiveUp->delete();
        $this->hidden = true;
        return redirect()->route('ticket.taken');
    }

    //open task list of the ticket
    public function taskList($ticketId){
        $board = TaskBoard::where('ticket_id','=',$ticketId)->first();
        $newBoard = [];
        if(!$board){
            $newBoard['ticket_id'] = $ticketId;
            $board = TaskBoard::create($newBoard);
        }

        return redirect(route('board.index',$board->id));

    }

    public function render()
    {
        return view('livewire.tickets.show-taken')->extends('layouts.app');
    }
}
