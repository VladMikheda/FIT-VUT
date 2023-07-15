<?php
/**
 *Project: Volunteer System
 *
 *File: IndexController.php
 *Subject: ITU 2022
 *
 *@author: Vladislav Mikheda xmikhe00
 **/

namespace App\Http\Livewire\Board;

use App\Models\Task;
use App\Models\TaskBoard;
use App\Models\TaskList;
use App\Models\Ticket;
use App\Models\User;
use Livewire\Component;

/*
 * The class that controls actions on the task dock
 */
class IndexController extends Component
{

    public $taskBoard = [];
    public $inviteUser;
    public $update;

//    public $listNamesArr = [];
//    protected $idBoard;

    /*
     * initialization method
     */
    public function mount(TaskBoard $id){
        $this->update = false;
//        $this->idBoard = $id->id;
        $this->getAllLists( $id->id);
    }

    /*
     * update all method
     */
    protected function getAllLists($taskBoard){
//        dd($this->idBoard);
        $lists = TaskBoard::find($taskBoard)->taskList()->orderBy('list_number','asc')->get();
        $this->taskBoard = [
            'taskBoard' => $taskBoard,
            'lists' => [],
        ];

        foreach ($lists as $indexList => $list){
            $tasks = $list->task()->orderBy('task_number','asc')->get();

            $this->taskBoard['lists'][$indexList] = [
                'taskBoard' => $taskBoard,
                'listId' => $list->id,
                'listTitle' => $list->list_title,
                'listNumber' => $list->list_number,
                'tasks' => []
            ];

            foreach ($tasks as $indexTask => $task){

                $taskOwner = User::find($task->task_owner);
                $taskOwnerName = '';
                $taskOwnerLastname = '';
                if($taskOwner != null){
                    $taskOwnerName = $taskOwner->name;
                    $taskOwnerLastname = $taskOwner->lastname;
                }
//                dd($taskOwner);
                $this->taskBoard['lists'][$indexList]['tasks'][$indexTask] =[
                    'taskId' => $task->id,
                    'taskNumber' => $task->task_number,
                    'taskTitle' => $task->task_title,
                    'taskDescription' => $task->task_description,
                    'taskOwner' => $task->task_owner,
                    'taskOwnerName' => $taskOwnerName,
                    'taskOwnerLastname' => $taskOwnerLastname,
                    'taskCompleted' => $task->completed
                ];
            }
//           dd($tasks);
        }


        $ticket = Ticket::find(TaskBoard::find($taskBoard)->ticket_id);
        $this->inviteUser =  User::whereIn('id',function ($query) use($ticket){
            $query->from('invitations')
                ->select('user_id')
                ->where('invitations.ticket_id','=',$ticket->id)->where('invitations.approved','=','1');})->get();

    }

    /*
     * The method that implements adding lists to the board
     */
    public function addList(){
        $endList = end($this->taskBoard['lists']);
        $listNumber = 1;
        if(!empty($endList)){
            $listNumber = $endList['listNumber'] + 1;
        }
        $newList = [];
        $newList['task_board_id'] = $this->taskBoard['taskBoard'];
        $newList['list_number'] = $listNumber;
//        $newList['list_title'] = 12121;
        TaskList::create($newList);
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
     * The method that implements adding tasks to the sheet
     */
    public function addTask($indexList){
        $list = $this->taskBoard['lists'][$indexList];
        $list = TaskList::find($list['listId']);
        if($list!=null){
            $lastTask = end($this->taskBoard['lists'][$indexList]['tasks']);
            $taskNumber = 1;
            if(!empty($lastTask)){
                $taskNumber = $lastTask['taskNumber'] + 1;
            }
            $newTask = [];
            $newTask['task_list_id'] = $this->taskBoard['lists'][$indexList]['listId'];
            $newTask['task_number'] = $taskNumber;
            $newTask['task_title'] = 'New task';
    //        $newTask['task_description'] = 'New task';
    //        $newTask['task_owner'] = 2;
            Task::create($newTask);
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
     * The method is implemented by adding a transferred card to the database
     */
    public function moveCard($data){
//        dd($this->taskBoard);


        $oldList = $data[0];
        $nextList = $data[1];
        $card = $data[2];
        $cardBefore = $data[3];


        $list = $this->taskBoard['lists'][$nextList];
        $list = TaskList::find($list['listId']);
        if($list != null) {

            $cardData = $this->taskBoard['lists'][$oldList]['tasks'][$card];

            if(Task::find($cardData['taskId']) != null){

                $allTasksList = TaskList::find($this->taskBoard['lists'][$oldList]['listId'])->task()->where('task_number', '>', $cardData['taskNumber'])->get();
                foreach ($allTasksList as $changeTask) {
                    $changeTask->task_number--;
                    $changeTask->save();
                }


                $taskNumberBefore = 0;
                if ($cardBefore != -1) {
                    $taskNumberBefore = $this->taskBoard['lists'][$nextList]['tasks'][$cardBefore]['taskNumber'];
                }
                $allTasksList = TaskList::find($this->taskBoard['lists'][$nextList]['listId'])->task()->where('task_number', '>', $taskNumberBefore)->get();

                foreach ($allTasksList as $changeTask) {
                    $changeTask->task_number++;
                    $changeTask->save();
                }


                $task = Task::find($cardData['taskId']);
                $task->task_list_id = $this->taskBoard['lists'][$nextList]['listId'];
                $task->task_number = $taskNumberBefore + 1;
                $task->save();
            }

        }
        $this->getAllLists($this->taskBoard['taskBoard']);

    }

    /*
     * The method makes the task complete
     */
   public function taskComplete($indexList,$indexTask){
       $taskArr = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask];
       $task = Task::find($taskArr['taskId']);
       if($task != null) {
           if ($task->completed == false) {
               $task->completed = true;
           } else {
               $task->completed = false;
           }
           $task->save();
       }
       $this->getAllLists($this->taskBoard['taskBoard']);
   }

    /*
     * The method makes the task delete
     */
    public function taskDelete($indexList,$indexTask){
        $taskArr = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask];
        $task = Task::find($taskArr['taskId']);
        if($task != null ) {
            $allTasksList = TaskList::find($this->taskBoard['lists'][$indexList]['listId'])->task()->where('task_number', '>', $taskArr['taskNumber'])->get();
            foreach ($allTasksList as $changeTask) {
                $changeTask->task_number--;
                $changeTask->save();
            }
            $task->delete();
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
    * The method makes the list delete
    */
    public function listDelete($indexList){
        $listArr = $this->taskBoard['lists'][$indexList];
        $list = TaskList::find($listArr['listId']);
        if($list != null) {
            $allTasks = $list->task()->get();
            foreach ($allTasks as $task) {
                $task->delete();
            }
            $list->delete();
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
    * The method change list name
    */
    public function listName($indexList){
//        dd($this->taskBoard['lists'][$indexList]);
        $listArr = $this->taskBoard['lists'][$indexList];
        $list = TaskList::find($listArr['listId']);
        if($list != null) {
//        dd($this->taskBoard['lists'][$indexList]);
            $list->list_title = $this->taskBoard['lists'][$indexList]['listTitle'];
            $list->save();
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }


   /*
   * The method change task name
   */
    public function taskName($indexList,$indexTask){
        $taskArr = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask];
        $task = Task::find($taskArr['taskId']);
        if($task != null) {
            $task->task_title = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask]['taskTitle'];
            $task->save();
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
     * The method change task description
     */
    public function taskDescription($indexList,$indexTask){
       $taskArr = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask];
       $task = Task::find($taskArr['taskId']);
       if($task != null) {
           $task->task_description = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask]['taskDescription'];
           $task->save();
       }
        $this->getAllLists($this->taskBoard['taskBoard']);

    }

    /*
     * The method change task owner
     */
    public function taskOwner($indexList,$indexTask){
        $taskArr = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask];
        $task = Task::find($taskArr['taskId']);
        if($task != null) {
            if ($this->taskBoard['lists'][$indexList]['tasks'][$indexTask]['taskOwner'] == 'null') {
                $task->task_owner = null;
            } else {
                $task->task_owner = $this->taskBoard['lists'][$indexList]['tasks'][$indexTask]['taskOwner'];
            }
            $task->save();
        }
        $this->getAllLists($this->taskBoard['taskBoard']);
    }

    /*
     * rules for validator
     */
    public $rules = [
        'taskBoard.lists.*.listTitle' => 'string',
        'taskBoard.lists.*.tasks.*.taskTitle' => 'string',
        'taskBoard.lists.*.tasks.*.taskOwner' => '',
        'taskBoard.lists.*.tasks.*.taskDescription' => '',

    ];

    /*
     * render funktion
     */
    public function render()
    {
        $this->getAllLists($this->taskBoard['taskBoard']);

//        $this->dispatchBrowserEvent('boardUpdate');
        return view('board.index',[
            'boardList' => $this->taskBoard,
            'invitedPeople' => $this->inviteUser,
        ])->extends('layouts.app');
    }
}
