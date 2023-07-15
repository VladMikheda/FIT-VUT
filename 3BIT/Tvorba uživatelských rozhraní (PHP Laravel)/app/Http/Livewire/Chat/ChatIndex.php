<?php
/*
 * Project: Volunteer System
 * File: ChatIndex.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Chat;

use App\Models\Chat;
use App\Models\Message;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Livewire\Component;
use Carbon\Carbon;

//controller for managing chats
class ChatIndex extends Component
{
    public $selectedChat;
    public $messageContent;
    public $contentToChange;
    public $updatedMessage;
    public $my_id;
    public bool $hidden = true;
    public bool $deleteHidden = true;
    public $messageToDelete;
    public $search = '';

    //request rules
    protected $rules = [
        'messageContent' => 'required|string',
    ];

    //initial setup
    public function mount() {
        $this->my_id = Auth::id();

        //find chats for the user
        $this->selectedChat = Chat::query()
                ->where('from_user_id', Auth::id())
                ->orWhere('to_user_id', Auth::id())
                ->orderBy('updated_at', 'desc')
                ->latest()
                ->first();

        if(!isset($this->selectedChat)) {
            $this->selectedChat = null;
        }

    }

    //activate change window and dispatch the event for listening livewire component
    public function showPanel($message_id){
        $this->emit('showPanel', false, $message_id);
    }

    //send message and update the window
    public function sendMessage() {
        $this->validate();
        Message::create([
            'chat_id' => $this->selectedChat->id,
            'user_id' => Auth::id(),
            'content' => $this->messageContent
        ]);

        $now = Carbon::now();
        $chat = Chat::find($this->selectedChat->id);
        $chat->updated_at = $now;
        $chat->save();

        $this->reset('messageContent');
        $this->displayChat($this->selectedChat->id);
        $this->dispatchBrowserEvent('chatToBottom');
    }

    public function deleteVerify($message_id) {
        $this->messageToDelete = $message_id;
        $this->deleteHidden = false;
    }

    public function cancelDelete() {
        $this->deleteHidden = true;
        $this->reset('messageToDelete');
    }

    public function deleteMessage(){
        $toDelete = Message::find($this->messageToDelete);
        $toDelete->delete();
        $this->deleteHidden = true;
        $this->reset('messageToDelete');
    }

    public function displayChat($chat_id) {
        $this->selectedChat = Chat::find($chat_id);
        $this->dispatchBrowserEvent('chatToBottom');
    }

    public function render()
    {
        if(!isset($this->selectedChat)) {
            $chosen_id = 0;
        }
        else {
            $chosen_id = $this->selectedChat->id;
        }

        $chats = Chat::query()
            ->where('from_user_id', Auth::id())
            ->orWhere('to_user_id', Auth::id())
            ->orderBy('updated_at', 'desc')
            ->get();
        return view('livewire.chat.chat-index', [
            'chats' => $chats,
            'chosen_id' => $chosen_id,
        ])->extends('layouts.app');
    }
}
