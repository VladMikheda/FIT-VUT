{{--

    Project: Volunteer System

    File: index.blade.php
    Subject: ITU 2022

    @author: Vladislav Mikheda xmikhe00

--}}
<div>
{{--Top menu--}}
<div class="top-0 ">
    <div class="flex flex-row justify-center">
        <div class="bg-blue-100 w-full max-w-[95%] shadow-md">
            <div class="flex flex-row justify-between">
                <p class="font-semibold text-2xl mx-7 my-3">Task board</p>
                <div class="bg-blue-100 flex flex-row items-center justify-end flex-wrap mx-5 mb-1">
                    <div class="flex p-1 rounded-lg ">
                        <div class="py-2" x-data="{open: false}" @mouseover="open = true" @mouseleave="open = false">
                            <div class="relative flex rounded-lg items-center space-x-1 cursor-pointer text-sm font-medium">
                                <x-heroicon-s-bars-3  class="h-8 w-8 text-blue-700  hover:text-blue-800" />
                                <div class="origin-top-right mt-3 absolute top-6 right-0 w-40 rounded-md shadow-lg bg-white ring-1 ring-black ring-opacity-5 focus:outline-none" x-show="open" x-cloak>
                                    <div class="py-1 rounded-t-md bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("profile")}}" class="text-white block px-4 py-2 text-sm">Profile</a>
                                    </div>
                                    <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("ticket.create")}}" class="text-white block px-4 py-2 text-sm">Create tasks</a>
                                    </div>
                                    <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("ticket.public")}}" class="text-white block px-4 py-2 text-sm">Available tasks</a>
                                    </div>
                                    <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("ticket.created")}}" class="text-white block px-4 py-2 text-sm">Created tasks</a>
                                    </div>
                                    <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("ticket.taken")}}" class="text-white block px-4 py-2 text-sm">Taken tasks</a>
                                    </div>

                                    <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("friends.index")}}" class="text-white block px-4 py-2 text-sm">Friends</a>
                                    </div>

                                    <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                        <a href="{{route("chats")}}" class="text-white block px-4 py-2 text-sm">Chats</a>
                                    </div>

                                    <div class="py-1 border-t-2 border-t-white rounded-b-md bg-red-400 hover:bg-red-500 ">
                                        <a href="{{route("authentication.exit")}}" class="text-white block px-4 py-2 text-sm">Sign Out</a>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
{{--body--}}
<div  class="flex justify-center h-full">
   <div class="bg-white w-full max-w-[95%] h-full max-h-[90%] mt-1 mb-12 flex-col flex justify-center ">
            <div class="h-screen p-6 bg-slate-300 rounded-xl shadow w-fit min-w-full overflow-auto">
                <div wire:poll.10000ms class="flex flex-row" >
                    @foreach($boardList['lists'] as $indexList => $list)
                    {{--start list--}}
                    <div class="max-w-sm w-fit min-w-fit py-3 px-1 h-fit mx-2 my-3 bg-white border border-gray-200 rounded-lg shadow-md">
                        <div class="flex flex-col  justify-center ">
                            {{--title--}}
                            <div class="border-b-2 mb-3 border-gray-600 flex flex-row px-2">
                               <input type="text" wire:model.lazy="taskBoard.lists.{{$indexList}}.listTitle" wire:keydown.enter="listName({{$indexList}})"    placeholder="List title"  class=" mb-1  w-full h-10 bg-white rounded-lg px-2">
                                <button wire:click="listDelete({{$indexList}})"  class="w-6 h-6">
                                    <div class="text-center font-bold text-2xl text-sm hover:text-red-600 text-red-500">
                                        &#10005;
                                    </div>
                                </button>
                            </div>
                            {{--title end--}}

                            <div class="list min-h-[40px]" name="{{$indexList}}">
                                @foreach($list['tasks'] as $indexTask => $task)
                                {{--start close card--}}
                                <div x-data="{open: false}" draggable="true" name="{{$indexTask}}" class="card" >

                                    <div  x-show="!open" class="bg-white mt-1 mb-1 items-center border-2 rounded-lg border-gray-600  p-2 ">
                                        <div class="flex space-x-4">
                                            <div class="flex-1 text-left">
                                                <div class=" font-medium break-all max-w-sm w-full h-fit text-gray-900 ">
                                                    {{$task['taskTitle']}}
                                                </div>
                                                <div class="break-all max-w-sm text-sm w-full h-fit  text-gray-600">
                                                    {{$task['taskOwnerName']}} {{$task['taskOwnerLastname']}}
                                                </div>
                                            </div>
                                            <div class="inline-flex items-center  ">
                                                <button wire:click="taskDelete({{$indexList}},{{$indexTask}})">
                                                    <div class="text-center font-bold text-sm text-sm hover:text-red-600 text-red-500">
                                                        &#10005;
                                                    </div>
                                                </button>
                                                <button  wire:click="taskComplete({{$indexList}},{{$indexTask}})">
                                                    <div class="ml-2.5 w-5 h-5 " >
                                                        <div class="text-center font-bold text-sm text-sm @if(!$task['taskCompleted']) hover:text-red-600 text-red-500 @else hover:text-green-600 text-green-500 @endif">
                                                            &#10003;
                                                        </div>
                                                    </div>
                                                </button>
                                                <button @click="open = true" >
                                                    <svg class="ml-2.5 w-5 h-5 "  xmlns="http://www.w3.org/2000/svg"><path fill="black" d="M5.293 7.293a1 1 0 011.414 0L10 10.586l3.293-3.293a1 1 0 111.414 1.414l-4 4a1 1 0 01-1.414 0l-4-4a1 1 0 010-1.414z" ></path></svg>
                                                </button>
                                            </div>
                                        </div>
                                    </div>
                                    {{--stop card--}}
                                    {{--start open card--}}
                                    <div x-show="open" class="mt-2 mb-1 items-center bg-white border-2  rounded-lg  p-2 border-gray-600 ">
                                        <div class="flex space-x-4">
                                            <div class="flex-1 text-left">
                                                <div class="mb-1 w-full h-fit ">
                                                    <label class="m-1 text-sm text-gray-400" >Tack title</label>
                                                    <input type="text" wire:model.lazy="taskBoard.lists.{{$indexList}}.tasks.{{$indexTask}}.taskTitle"  wire:keydown.enter="taskName({{$indexList}},{{$indexTask}})" class=" px-1 bg-blue-100 w-full h-8 rounded-lg "  placeholder="Tack title">
                                                </div>
                                                <div class="mb-1 w-full h-fit">
                                                    <label class="m-1 text-sm text-gray-400" >Owner name</label>
                                                    <select  wire:model.lazy="taskBoard.lists.{{$indexList}}.tasks.{{$indexTask}}.taskOwner"  wire:click="taskOwner({{$indexList}},{{$indexTask}})"  name="task_owner" class=" w-full px-1 bg-blue-100  w-full h-8 rounded-lg">
                                                        {{--list people wich invite--}}
                                                        <option value="null">Nobody</option>
                                                        @foreach($invitedPeople as $invite)
                                                        <option value="{{$invite['id']}}">{{$invite['name']}} {{$invite['lastname']}}</option>
                                                        @endforeach
                                                    </select>
                                                </div>
                                                <div class="mb-1 w-full h-fit">
                                                    <label class="m-1 text-sm text-gray-400" for="tack_name">Description</label>
                                                    <textarea  type="text" 	wire:model.defer="taskBoard.lists.{{$indexList}}.tasks.{{$indexTask}}.taskDescription" autofocus wire:keydown.enter="taskDescription({{$indexList}},{{$indexTask}})"  class=" px-1 bg-blue-100  w-full h-15 rounded-lg "  placeholder="Description"></textarea>
                                                </div>
                                            </div>
                                            <div class="inline-flex items-center ">
                                                <button @click="open = false">
                                                    <svg class="ml-2.5 w-5 h-5 rotate-180 "  xmlns="http://www.w3.org/2000/svg"><path fill="black" d="M5.293 7.293a1 1 0 011.414 0L10 10.586l3.293-3.293a1 1 0 111.414 1.414l-4 4a1 1 0 01-1.414 0l-4-4a1 1 0 010-1.414z" ></path></svg>
                                                </button>
                                            </div>
                                        </div>
                                    </div>
                                    {{--stop open card--}}
                                </div>
                                @endforeach
                            </div>
                            {{--buttom for add new task--}}
                            <div class="mt-3 items-center mb-1 ">
                                <button wire:click="addTask({{$indexList}})"  type="button" class=" shadow-md text-left text-white bg-green-500 hover:bg-green-600 font-bold p-2 h-fit w-full bg-white rounded-lg ">
                                    Add task
                                </button>
                            </div>
                        </div>
                    </div>
                    {{--end list--}}
                    @endforeach

                </div>
            </div>


   </div>

    {{--buttom for add new list--}}
    <div class="fixed justify-end  mt-96">
        <div class="flex flex-col mt-80 block min-h-full justify-end text-center items-center">
            <button  id="addList" wire:click="addList" class="relative mb-4 text-7xl w-24 h-24 text-white  bg-green-500 hover:bg-green-600  rounded-full shadow-md shadow-gray-400">
                +
            </button>
        </div>
    </div>

    {{--start drag and drop script--}}
    <script>
        {{--global variable--}}
        let dragCard = null;
        let dragMoveStart = false;
        let fakeCard = null;
        let elementForDrop = null;
        let oldList = null;
        let nextList = null;
        let cardBefore = -1;

        // if the list is empty, add the fake card, if not empty, remove the fake card if it exists
        const emptyList = () =>
        {
            let allList = document.querySelectorAll(".list");
            allList.forEach(list => {
                if(list.querySelector(".card:not(.fake)")){
                    // console.log('1')
                    let hiddenCard = list.querySelector(".fake");
                    if(hiddenCard){
                        hiddenCard.parentNode.removeChild(hiddenCard);
                    }
                }else{
                    if(!list.querySelector(".fake")){
                        let hiddenCard = document.createElement("div");
                        hiddenCard.classList.add("card");
                        hiddenCard.classList.add("fake");
                        hiddenCard.classList.add("h-10");
                        list.append(hiddenCard);
                    }
                }
            })

        }

        // add all drag events then start drag
        const dragStart = (event) => {
            dragCard = event.target;
            oldList = dragCard.parentNode.getAttribute('name');
            // console.log(oldList);
            dragCard.addEventListener('drag',drag);
            dragCard.addEventListener('dragend',dragEnd);
        }

        //executed on drag
        const drag = (event) =>{
            // event.preventDefault();
            // event.dataTransfer.setData('text', 'anything');
            //check if the drag has started and create a fake card
            if(!dragMoveStart){
                //hide the map that we start dragging
                dragCard.style.display = 'none';
                dragMoveStart = true;
                fakeCard = document.createElement("div");
                fakeCard.classList.add("h-10");
                fakeCard.classList.add("bg-slate-100");
                //resets the default behavior dragover to make the dragend work
                fakeCard.addEventListener('dragover',(event) =>{
                    event.preventDefault();
                });
                // fakeCard.addEventListener('drop',drop);
                dragCard.parentNode.insertBefore(fakeCard,dragCard);
            }


            //it is not work firefox but work in all browsers
            // let elementUnder = document.elementFromPoint(
            //     event.clientX, event.clientY
            // );
            // console.log(elementUnder);


            //check which element is under the card
            //it is work in forefox
            let elementUnder = document.elementFromPoint(
               X, Y
            );


            //check if the card is
            let cardUnder = elementUnder.closest(".card");

            //So that the system is not loaded, we check whether
            //the element has already been selected as the one where you can insert
            if(elementForDrop != cardUnder){
                elementForDrop = cardUnder;
                // console.log(elementForDrop);
                // check insert under or over elements
                if(elementForDrop){
                    if(!overlapElements(event,elementForDrop)){
                        elementForDrop.parentNode.insertBefore(
                          fakeCard,elementForDrop
                        );
                    }else{
                        elementForDrop.parentNode.insertBefore(
                            fakeCard,elementForDrop.nextElementSibling
                        );
                    }
                }


            }

        }

        //check how much one element overlaps another element
        const overlapElements = (event, underElement) => {
            let underCordinate = underElement.getBoundingClientRect();
            let underY = underCordinate.top + underCordinate.height/2;
            return Y < underY; //old event.clientY not work in firefox
        }

        //drag end
        const dragEnd = (event) =>{

            //insert element before fake card
            fakeCard.parentNode.insertBefore(dragCard,fakeCard);
            dragCard.style.display = 'block';

            //delete fake card
            fakeCard.parentNode.removeChild(fakeCard);
            // console.log(dragCard.parentNode.before(dragCard))
            nextList = dragCard.parentNode.getAttribute('name')

            //collecting data to send to the controller
            let allNextListElements = dragCard.parentNode.querySelectorAll('.card:not(.fake)')
            let oldElement = -1;
            allNextListElements.forEach(element =>{
                if(element.getAttribute('name') == dragCard.getAttribute("name")) {
                    cardBefore = oldElement;
                    return;
                }else{
                    oldElement++;
                }
            })

            //passing data to the controller
            Livewire.first().call('moveCard',[oldList,nextList,dragCard.getAttribute("name"),cardBefore])

            //nulling a variable
            dragCard = null;
            dragMoveStart = false;
            fakeCard = null;
            elementForDrop = null;
            oldList = null;
            nextList = null;
            cardBefore = -1;
            emptyList()
        }

        //start function
        function drugAndDrop(){
            emptyList();
            let allCard = document.querySelectorAll(".card:not(.fake)");
            allCard.forEach(card =>{
                card.addEventListener('dragstart',dragStart);
            })
        }

        // drugAndDrop();
        drugAndDrop();
        let X;
        let Y;

        // we get x and y cordinate
        window.addEventListener('dragover', (event) => {
            X = event.clientX;
            Y = event.clientY;
        });

        // after adding the list, update the script
        document.getElementById("addList").addEventListener("click",() =>{
                setTimeout(() => {
                    drugAndDrop();
                },500);
            }
        );

        // update script on mouse click
        document.addEventListener('mousedown',() =>{
            drugAndDrop();
        });


        // document.addEventListener('boardUpdate',  () => {
        //     drugAndDrop();
        // })

        document.addEventListener('mouseout',() =>{
            drugAndDrop();
        });


    </script>

</div>

</div>

