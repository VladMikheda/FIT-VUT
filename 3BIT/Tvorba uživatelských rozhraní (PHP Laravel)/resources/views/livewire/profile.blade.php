{{--
Project: Volunteer System

File: manage.blade.php
Subject: ITU 2022

@author: Denis Karev xkarev00
--}}
<div class="h-fit">
    <div class="sticky top-0">
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="flex flex-row justify-between">
                    <p class="font-semibold text-2xl mx-7 my-3">Personal profile</p>
                    <div class="bg-blue-100 flex flex-row items-center justify-end flex-wrap mx-5 mb-1">
                        <div class="flex p-1 rounded-lg ">
                            <div class="py-2" x-data="{open: false}" @mouseover="open = true"
                                 @mouseleave="open = false">
                                <div
                                    class="relative flex rounded-lg items-center space-x-1 cursor-pointer text-sm font-medium">
                                    <x-heroicon-s-bars-3 class="h-8 w-8 text-blue-700  hover:text-blue-800"/>
                                    <div
                                        class="origin-top-right mt-3 absolute top-6 right-0 w-40 rounded-md shadow-lg bg-white ring-1 ring-black ring-opacity-5 focus:outline-none"
                                        x-show="open" x-cloak>
                                        <div class="py-1 rounded-t-md bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("profile")}}" class="text-white block px-4 py-2 text-sm">Profile</a>
                                        </div>
                                        <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("ticket.create")}}"
                                               class="text-white block px-4 py-2 text-sm">Create tasks</a>
                                        </div>
                                        <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("ticket.public")}}"
                                               class="text-white block px-4 py-2 text-sm">Available tasks</a>
                                        </div>
                                        <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("ticket.created")}}"
                                               class="text-white block px-4 py-2 text-sm">Created tasks</a>
                                        </div>
                                        <div class="py-1 bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("ticket.taken")}}"
                                               class="text-white block px-4 py-2 text-sm">Taken tasks</a>
                                        </div>

                                        <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("friends.index")}}"
                                               class="text-white block px-4 py-2 text-sm">Friends</a>
                                        </div>

                                        <div class="py-1 border-t-2 border-t-white bg-blue-400 hover:bg-blue-500">
                                            <a href="{{route("chats")}}" class="text-white block px-4 py-2 text-sm">Chats</a>
                                        </div>

                                        <div
                                            class="py-1 border-t-2 border-t-white rounded-b-md bg-red-400 hover:bg-red-500 ">
                                            <a href="{{route("authentication.exit")}}"
                                               class="text-white block px-4 py-2 text-sm">Sign Out</a>
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
    <x-background.index>
        <div class="flex flex-row justify-center h-fit space-x-8 mt-6">
            <div class="basis-1/2 flex flex-col h-full mb-8">
                <div class="flex flex-row mt-4">
                    <div
                        class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">
                        Your tickets
                    </div>
                </div>
                <div class="flex flex-col space-y-4 h-full" wire:poll>
                    @foreach($tickets as $ticket)
                        <div class="flex flex-col rounded-xl shadow-md p-3.5 bg-blue-100">
                            <div class="flex flex-row">
                                <div class="flex flex-col">
                                    <p class="font-semibold">{{ $ticket->title }} #{{ $ticket->id }}</p>
                                    <div class="flex">
                                        <p class="text-sm">Created
                                            at: {{ $ticket->created_at->format('d.m.Y H:i:s') }}</p>
                                    </div>
                                </div>
                                <div class="flex flex-row ml-auto my-auto">
                                    <a href="{{route('manage', $ticket->id)}}"
                                       class="w-10 h-8 text-white font-semibold bg-blue-400 hover:bg-blue-600 rounded-xl shadow-md text-center pt-1">
                                        <x-heroicon-s-pencil class="h-4 w-4 my-1 mx-auto"/>
                                    </a>
                                    <a wire:click.prevent="deleteTicket({{ $ticket->id }})" href="#"
                                       class="w-10 h-8 ml-1 text-white font-semibold bg-red-400 hover:bg-red-600 rounded-xl shadow-md text-center pt-1">
                                        <x-heroicon-s-trash class="h-4 w-4 my-1 mx-auto"/>
                                    </a>
                                </div>
                            </div>
                        </div>
                    @endforeach
                </div>
            </div>
            <div class="basis-1/2 flex flex-col h-full mb-8">
                <div class="flex flex-row mt-4">
                    <div
                        class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold text-lg mb-2 mr-4 ml-1">
                        Information
                    </div>
                    <button id="save"
                            class="w-20 h-8 m-1 text-white bg-green-400 hover:bg-green-600 font-bold rounded-xl shadow-md"
                            wire:click="save"
                            @if(!$formActive) style="display: none" @endif>
                        Save
                    </button>
                    <button id="cancel"
                            class="w-20 h-8 m-1 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md"
                            wire:click="deactivateForm"
                            @if(!$formActive) style="display: none" @endif>
                        Cancel
                    </button>
                    <button id="edit"
                            class="w-20 h-8 m-1 text-white bg-blue-400 hover:bg-blue-600 font-bold rounded-xl shadow-md"
                            wire:click="activateForm"
                            @if($formActive) style="display: none" @endif>
                        Edit
                    </button>
                </div>
                <div class="flex flex-col space-y-4 h-full">
                    <div class="flex flex-row">
                        <div class="flex flex-col">
                            <p class=" font-semibold text-md mb-1 mr-4 ml-1">Name</p>
                            <input id="name" type="text" class="h-7 px-1 @if(!$formActive) bg-slate-100 @endif editable"
                                   @if(!$formActive) disabled @endif wire:model="name">
                        </div>
                        <div class="flex flex-col ml-5">
                            <p class="font-semibold text-md mb-1 mr-4 ml-1">Email</p>
                            <input id="email" type="text"
                                   class="h-7 px-1 @if(!$formActive)  bg-slate-100 @endif editable"
                                   @if(!$formActive) disabled @endif wire:model="email">
                        </div>
                    </div>
                    <div class="flex flex-row">
                        <div class="flex flex-col">
                            <p class="font-semibold text-md mb-1 mr-4 ml-1">Registration date</p>
                            <input type="text" class="h-7 px-1 bg-slate-100" disabled
                                   wire:model="registrationDate">
                        </div>
                        <div class="flex flex-col ml-5">
                            <p class="font-semibold text-md mb-1 mr-4 ml-1">Tickets created</p>
                            <div class="flex flex-row">
                                <input type="text" class="h-7 px-1 bg-slate-100 flex flex-col" disabled
                                       wire:model="ticketsCreated">
                                <a href="{{route("ticket.created")}}" class="flex flex-col">
                                    <x-heroicon-s-eye class="h-6 w-6 text-blue-700 hover:text-blue-800"/>
                                </a>
                            </div>
                        </div>
                    </div>
                    <div class="flex flex-row">
                        <div class="flex flex-col">
                            <p class="font-semibold text-md mb-1 mr-4 ml-1">Friends</p>
                            <div class="flex flex-row">
                                <input type="text" class="h-7 px-1 bg-slate-100 flex flex-col" disabled
                                       wire:model="friends">
                                <a href="{{route("friends.index")}}" class="flex flex-col">
                                    <x-heroicon-s-eye class="h-6 w-6 text-blue-700 hover:text-blue-800"/>
                                </a>
                            </div>
                        </div>
                    </div>
                    <div class="flex flex-row">
                        <button id="save"
                                class="w-40 h-9 p-auto text-white bg-red-400 hover:bg-red-600 font-bold rounded-xl shadow-md" onclick="deleteAccount()">
                            Delete account
                        </button>
                    </div>
                </div>
            </div>
        </div>
    </x-background.index>
</div>

<script>
    function deleteAccount() {
        if (confirm('Are you sure you want to delete your account? You will not be able to restore it.')) {
            Livewire.emit('deleteAccount');
        }
    }
</script>
