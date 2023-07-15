{{--
Project: Volunteer System

File: manage.blade.php
Subject: ITU 2022

@author: Denis Karev xkarev00
 --}}

<div>
    <div class="sticky top-0 ">
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="flex flex-row justify-between">
                    <p class="font-semibold text-2xl mx-7 my-3">Information about the task</p>
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
                                    </div>                                    </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        {{--            actions for the ticket--}}
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="bg-blue-100 flex flex-row flex-wrap mx-5 mb-1">
                    <button wire:click.prevent="save" class="w-20 h-8 m-2 text-white bg-green-400 hover:bg-green-600 font-bold rounded-xl shadow-md">
                        Save
                    </button>
                    <button wire:click.prevent="delete" class="w-20 h-8 m-2 text-white bg-red-400 hover:bg-red-600 font-bold rounded-xl shadow-md">
                        Delete
                    </button>
                    <button wire:click.prevent="openTakenPage" class="w-20 h-8 m-2 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md">
                        View
                    </button>
                    <button wire:click.prevent="openTicketPage" class="w-20 h-8 m-2 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md">
                        Public
                    </button>
                </div>
            </div>
        </div>
    </div>
{{--    <div class="sticky top-0">--}}
{{--        <div class="flex flex-row justify-center">--}}
{{--            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">--}}
{{--                <p class="font-semibold text-2xl mx-7 my-3">Ticket management</p>--}}
{{--                <div class="bg-blue-100 flex flex-row flex-wrap mx-5 mb-1">--}}
{{--                    <button wire:click.prevent="save" class="w-20 h-8 m-2 text-white bg-green-400 hover:bg-green-600 font-bold rounded-xl shadow-md">--}}
{{--                        Save--}}
{{--                    </button>--}}
{{--                    <button wire:click.prevent="delete" class="w-20 h-8 m-2 text-white bg-red-400 hover:bg-red-600 font-bold rounded-xl shadow-md">--}}
{{--                        Delete--}}
{{--                    </button>--}}
{{--                    <button wire:click.prevent="openTakenPage" class="w-20 h-8 m-2 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md">--}}
{{--                        View--}}
{{--                    </button>--}}
{{--                    <button wire:click.prevent="openTicketPage" class="w-20 h-8 m-2 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md">--}}
{{--                        Public--}}
{{--                    </button>--}}
{{--                </div>--}}
{{--            </div>--}}
{{--        </div>--}}
{{--    </div>--}}

    <x-background.index>
        <div class="flex flex-row justify-center h-screen space-x-8 mt-6" wire:poll>
            <div class="basis-1/2 flex flex-col h-full mb-8">
                <div class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">Ticket settings</div>
                <div class="flex flex-col space-y-4 h-full">
                    <div class="flex flex-col rounded-xl shadow-md bg-green-100 p-3">
                        <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">Title</p>
                        <textarea wire:model="title" class="rounded-lg w-full mr-4 px-2" type="text"></textarea>
                    </div>
                    <div class="flex flex-col rounded-xl shadow-md bg-green-100 p-3">
                        <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">Description</p>
                        <textarea wire:model="description" class="rounded-lg w-full mr-4 px-2" type="text" rows="5"></textarea>
                    </div>
                    <div class="flex flex-col rounded-xl shadow-md bg-green-100 p-3">
                        <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">Address</p>
                        <textarea wire:model="address" class="rounded-lg w-full mr-4 px-2" type="text"></textarea>
                    </div>
                </div>
            </div>
            <div class="basis-1/2 h-full">
                <div class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">Members</div>
                @foreach($invitations as $invitation)
                    <div class="flex flex-col rounded-xl shadow-md p-3.5 mb-2 @if($invitation->approved == 0) bg-amber-100 @else bg-green-100 @endif">
                        <div class="flex flex-row">
                            <p class="font-semibold text-lg">{{ $invitation->user->name }} {{ $invitation->user->lastname }}</p>

                            @if($invitation->approved == 0)
                                <button wire:click.prevent="approveInvitation({{ $invitation->id }})" class="w-20 h-8 ml-auto text-white font-semibold bg-green-400 hover:bg-green-600 rounded-xl shadow-md">
                                    Approve
                                </button>
                                <button wire:click.prevent="rejectInvitation({{ $invitation->id }})" class="w-20 h-8 ml-2 text-white bg-red-400 font-semibold hover:bg-red-600 rounded-xl shadow-md">
                                    Decline
                                </button>
                            @else
                                <button wire:click.prevent="rejectInvitation({{ $invitation->id }})" class="w-20 h-8 ml-auto text-white bg-red-400 font-semibold hover:bg-red-600 rounded-xl shadow-md">
                                    Remove
                                </button>
                            @endif
                        </div>
                        <p class="text-sm">{{ $invitation->content }}</p>
                    </div>
                @endforeach
            </div>
        </div>
    </x-background.index>
</div>
