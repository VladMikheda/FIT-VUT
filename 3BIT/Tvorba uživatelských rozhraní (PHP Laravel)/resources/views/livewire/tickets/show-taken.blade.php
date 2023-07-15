{{--
    Project: Volunteer System

    File: show-taken.blade.php
    Subject: ITU 2022

    @author: Vladisalav Khrisanov(xkhris00)
--}}
<div>
{{--    main menu and the header--}}
    <div class="sticky @if(!$deleteHidden or !$changeHidden or !$hidden) hidden @endif top-0 ">
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="flex flex-row justify-between">
                    <p class="font-semibold text-2xl mx-7 my-3">Information about the taken task</p>
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
                                    </div>                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
{{--        list of actions with the tickets--}}
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="bg-blue-100 flex flex-row flex-wrap mx-5 mb-1">
                    {{--                    buttons--}}
                    @if($my_id != $ticket->user_id)
                    <button wire:click.prevent="giveUpRequest({{$ticket->id}})" class="w-20 h-8 m-2 text-white bg-red-500 hover:bg-red-600 font-bold rounded-xl shadow-md">
                        Give Up
                    </button>
                    @endif
                    <div wire:click="taskList({{$ticket->id}})" class="w-20 h-8 m-2 text-white bg-green-500 hover:bg-green-600 font-bold rounded-xl shadow-md grid place-content-center">
                        <div class="self-center">
                            Task list
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

{{--    give up ticket window--}}
    <div>
        <div class="fixed inset-0 @if($hidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
            <div  class="flex block justify-center text-center items-center h-full">
                <div class="flex flex-col justify-center relative bg-white rounded-lg w-1/3">
                    {{--text--}}
                    <div class="flex justify-center my-5 mx-10">
                        <h3 class="font-semibold text-lg leading-6 text-gray-900">Do you want to give up this task?</h3>
                    </div>
                    {{--button area--}}
                    <div class="flex flex-row justify-center space-x-4 mb-5">
                        <button wire:click="cancelGiveUp" class="py-1 px-2 w-20 h-12 text-xl text-white bg-green-500 hover:bg-green-600 font-bold rounded-lg shadow-md" type="submit">
                            No
                        </button>
                        <button wire:click="giveUp" class="py-1 px-2 w-20 h-12 text-xl text-white bg-red-500 hover:bg-red-600 font-bold rounded-lg shadow-md" type="submit">
                            Yes
                        </button>
                    </div>
                </div>
            </div>
        </div>
    </div>

{{--    delete message window--}}
    <div>
        <div>
            <div class="fixed inset-0 @if($deleteHidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
                <div  class="flex block justify-center text-center items-center h-full">
                    <div class="flex flex-col justify-center relative bg-white rounded-lg w-1/3">
                        {{--                        text--}}
                        <div class="flex justify-center my-5 mx-10">
                            <h3 class="font-semibold text-lg leading-6 text-gray-900">Do you want to delete this message?</h3>
                        </div>
                        {{--                        button area--}}
                        <div class="flex flex-row justify-center space-x-4 mb-5">
                            <button wire:click="cancelDelete" class="py-1 px-2 w-20 h-12 text-xl text-white bg-green-500 hover:bg-green-600 font-bold rounded-lg shadow-md" type="submit">
                                No
                            </button>
                            <button wire:click="deleteMessage" class="py-1 px-2 w-20 h-12 text-xl text-white bg-red-500 hover:bg-red-600 font-bold rounded-lg shadow-md" type="submit">
                                Yes
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        </div>

{{--        change message window--}}
        <div>
            <div class="fixed inset-0 @if($changeHidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
                <div  class="flex block justify-center text-center items-center h-full">
                    <div class="flex flex-col relative bg-white rounded-lg w-1/3 h-1/2">
                        {{--                    text--}}
                        <div class="flex justify-center my-5 mx-10">
                            <h3 class="font-semibold text-lg leading-6 text-gray-900">Change message</h3>
                        </div>

                        {{--                    content--}}
                        <div class="w-full h-full bg-white px-4">
                            <textarea class="w-full h-full resize-none bg-slate-100 rounded-2xl pt-3 px-3 shadow-md" wire:model.defer="contentToChange">{{$contentToChange}}</textarea>
                        </div>

                        {{--                    button area--}}
                        <div class="flex flex-row justify-center space-x-4 m-6">
                            <button wire:click="hidePanel" class="py-1 px-2 w-24 h-12 text-xl text-white bg-red-500 hover:bg-red-600 font-bold rounded-lg shadow-md" type="submit">
                                Close
                            </button>
                            <button wire:click="updateMessage" class="py-1 px-2 w-24 h-12 text-xl text-white bg-green-500 hover:bg-green-600 font-bold rounded-lg shadow-md" type="submit">
                                Change
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        </div>


        <x-background.index>
{{--            ticket info--}}
            <div class="flex flex-row justify-center h-screen space-x-8 mt-6" wire:poll>
                <div class="basis-1/2 flex flex-col h-full space-y-4 mb-8">
                    <div class="flex flex-col space-y-4 h-full overflow-scroll">
                        <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                            <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Title</p>
                            <p class="text-lg">{{$ticket->title}}</p>
                        </div>
                        <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                            <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Description</p>
                            <p class="text-lg">{{$ticket->description}}</p>
                        </div>
                        <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                            <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Address</p>
                            <p class="text-lg">{{$ticket->address}}</p>
                        </div>
                        @if(isset($ticket->price))
                            <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                                <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Reward</p>
                                <p class="text-lg">{{$ticket->price}}</p>
                            </div>
                        @endif
                    </div>
                </div>
{{--                messages window--}}
                <div class="basis-1/2 h-full">
                    <div class="flex flex-col h-full">
                        <p class="bg-white font-semibold text-lg p-2 rounded-t-xl  shadow-md">Chat with the group</p>
                        <div id="chatWindow" class="bg-blue-100 basis-8/12 overflow-scroll overscroll-contain shadow-md">
                            {{--messages--}}
                            <div class="flex flex-col space-y-2 p-2 w-full">
                                @foreach($ticket->groupMessages as $message)
                                    <div class="flex w-3/4 @if($message->user_id != $my_id) self-start justify-start @else self-end justify-end @endif">
                                        <div class="@if($message->user_id != $my_id) bg-green-100 @else bg-amber-100 @endif w-fit p-2 rounded-xl">

                                            <div x-data="{ open: false }" @mouseleave="open = false">

                                                @if($message->user_id != $my_id)
                                                    <div class="flex flex-col">
                                                        <p class = "text-sm underline decoration-2 decoration-blue-300 underline-offset-4">{{$message->fromUser->name}} {{$message->fromUser->name}}</p>
                                                        <div>{{$message->content}}</div>

                                                    </div>
                                                @else
                                                    <div class="flex flex-row">
                                                        <div x-show="open" class="flex flex-row px-2 space-x-2" style="display:none">
                                                            <x-heroicon-s-trash wire:click.prevent="deleteVerify({{$message->id}})" class="h-6 w-6 text-red-400 hover:text-red-700" />
                                                            <x-heroicon-s-pencil wire:click="changeWindow({{$message->id}})" class="h-6 w-6 text-blue-400 hover:text-blue-700" />
                                                        </div>
                                                        <div @mouseover="open = true" class="">
                                                            {{$message->content}}
                                                        </div>
                                                    </div>
                                                @endif
                                            </div>
                                        </div>

                                    </div>
                                @endforeach
                            </div>
                            {{--messages--}}
                        </div>
                        <div class="bg-white rounded-b-xl shadow-md">
                            <form wire:submit.prevent="sendMessage" action="#">
                                <div class="flex flex-row space-x-2 p-2">
                                    <div class="basis-4/5 flex flex-col">
                                        <textarea wire:model.defer="messageContent" class="resize-y bg-slate-100 rounded-2xl pt-3 px-3" placeholder="Write a comment.."></textarea>
                                    </div>
                                    <div class="basis-1/5 flex flex-col">
                                        <button class="bg-blue-400 hover:bg-blue-500 rounded-2xl font-bold text-white h-10" type="submit">Send it</button>
                                    </div>
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
        </x-background.index>
    </div>
{{--chat scroll down--}}
    <script>
        let container = document.querySelector('#chatWindow');
        window.addEventListener('DOMContentLoaded', () => {
            container.scrollTop = container.scrollHeight;
        });
        window.addEventListener('chatToBottom', () => {
            Livewire.hook('message.processed', () => {
                if (container.scrollTop + container.clientHeight + 100 < container.scrollHeight) {
                    return;
                }
                container.scrollTop = container.scrollHeight;
            });
            container.scrollTop = container.scrollHeight;
        });
    </script>
