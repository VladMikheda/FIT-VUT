{{--

    Project: Volunteer System

    File: index.blade.php
    Subject: ITU 2022

    @author: Vladislav Mikheda xmikhe00

--}}
<div>
{{--start top menu--}}
<div class="sticky  top-0 ">
    <div class="flex flex-row justify-center">
        <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
            <div class="flex flex-row justify-between">
                <p class="font-semibold text-2xl mx-7 my-3">Friends</p>
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
{{--end top menu--}}
<x-background.index>
{{--Start body--}}
{{--Start search and sort buttom--}}
        <div class="flex justify-center mx-2 mt-2 mb-1 h-12">
                <input type="text" wire:model.debounce.350ms="search" placeholder="Type a name " name="search" class="basis-5/6 bg-blue-100 rounded-xl px-3 shadow-md">
        </div>
        <div class="flex mb-12 justify-center mt-7" role="group">
            <button type="button" wire:click="switchSearchFriend" class="w-40 h-fit p-3 border-r-2 rounded-l-xl text-white bg-yellow-500 hover:bg-yellow-600 font-bold  shadow-md">
                Find a friend
            </button>
            <button type="button" wire:click="switchNewFriend" class="w-40 h-fit p-3 text-white bg-yellow-500 hover:bg-yellow-600 font-bold  shadow-md">
                Friend requests
            </button>
            <button type="button" wire:click="switchMyRequest" class="w-40 h-fit p-3 border-l-2 text-white bg-yellow-500 hover:bg-yellow-600 font-bold  shadow-md">
                My requests
            </button>
            <button type="button" wire:click="switchMyFriend" class="w-40 h-fit p-3  border-l-2 rounded-r-xl text-white bg-yellow-500 hover:bg-yellow-600 font-bold shadow-md">
                My friends
            </button>
        </div>
{{--End search and sort buttom--}}

{{--Dynamic implementation displaying a list of friends--}}
    <div class="h-screen overflow-auto">
        <div  wire:poll.5000ms class="flex justify-center flex-wrap">
        @foreach($allPeople as $person)
                <div class="max-w-xs w-72 p-3 h-fit mx-2 my-3 bg-white border border-gray-200 rounded-lg shadow-md">
                    <div class="flex flex-col items-center">
                        <div class="inline-flex justify-center items-center w-24 h-24 mb-2 bg-gray-100 rounded-full">
                            <span class="font-bold text-xl text-gray-600">{{$person->name[0]}}{{$person->lastname[0]}}</span>
                        </div>
                        <div class="mb-1 text-xl font-medium"> {{$person->name}}  {{$person->lastname}}</div>
                        <div class="flex mt-2 space-x-3">
                            <button type="button" wire:click="{{$chosenFunction}}({{$person->id}})" class="w-fit p-2 h-fit m-2 text-white @if($myFriends || $myRequest) bg-red-500 hover:bg-red-600 @else bg-green-500 hover:bg-green-600 @endif font-bold rounded-xl shadow-md">
                                @if($myFriends || $myRequest)
                                    Delete
                                @else
                                    Add a friend
                                @endif
                            </button>
                            <button wire:click.prevent="startChat({{$person->id}})" type="button" class="w-fit p-2 h-fit m-2 text-white bg-yellow-500 hover:bg-yellow-600 font-bold rounded-xl shadow-md">Message</button>
                        </div>
                    </div>
                </div>
        @endforeach
        </div>
        {{$allPeople->links()}}
    </div>
{{--End body--}}
</x-background.index>
</div>
