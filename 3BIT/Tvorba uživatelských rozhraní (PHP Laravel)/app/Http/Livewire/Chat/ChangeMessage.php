<?php
/*
 * Project: Volunteer System
 * File: ChangeMessage.php
 * Subject: ITU 2022
 * @author: Vladislav Khrisanov(xkhris00)
 */
namespace App\Http\Livewire\Chat;

use App\Models\Message;
use Livewire\Component;

//controller for changing the content of the message
class ChangeMessage extends Component
{
    public $contentToChange;
    public $updatedMessage;
    public $hidden = true;

    //listen to the outside event 'showPanel' that activates change window
    protected $listeners = ['showPanel' => 'setup'];

    //initialize needed data
    public function setup($hiddenValue, $message_id) {
        $this->hidden = $hiddenValue;
        $this->updatedMessage = Message::find($message_id);
        $this->contentToChange = $this->updatedMessage->content;
    }

    //abort change and hide
    public function hidePanel(){
        $this->hidden = true;
        $this->reset('updatedMessage');
        $this->reset('contentToChange');
    }

    //change message and hide
    public function updateMessage() {
        $this->updatedMessage->content = $this->contentToChange;
        $this->updatedMessage->save();
        $this->hidden = true;
        $this->reset('updatedMessage');
        $this->reset('contentToChange');
    }

    public function render()
    {
        return view('livewire.chat.change-message');
    }
}
