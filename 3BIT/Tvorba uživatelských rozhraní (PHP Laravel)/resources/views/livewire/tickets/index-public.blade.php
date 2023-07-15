{{--
    Project: Volunteer System

    File: index-public.blade.php
    Subject: ITU 2022

    @author: Vladisalav Khrisanov(xkhris00)
--}}
{{--  index of the public tickets--}}
<div>
    <div class="fixed inset-0 @if($changeHidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
        <div  class="flex block justify-center text-center items-center h-full">
            @if($invitationExists == false)
            <div class="flex flex-col relative bg-white rounded-lg w-1/3 h-1/2">
                {{--text--}}
                <div class="flex justify-center my-5 mx-10">
                    <h3 class="font-semibold text-lg leading-6 text-gray-900">Do you want to take this task?</h3>
                </div>
                {{--content--}}
                <div class="w-full h-full bg-white px-4">
                    <textarea placeholder="Write a few words to the author and your application will be considered." class="w-full h-full resize-none bg-slate-100 rounded-2xl pt-3 px-3 shadow-md" wire:model.defer="invitationMessage"></textarea>
                </div>
                {{--button area--}}
                <div class="flex flex-row justify-center space-x-4 m-6">
                    <button wire:click="cancelInvitation" class="py-1 px-2 w-24 h-12 text-xl text-white bg-red-500 hover:bg-red-600 font-bold rounded-lg shadow-md" type="submit">
                        Cancel
                    </button>
                    <button wire:click="createInvitation" class="py-1 px-2 w-24 h-12 text-xl text-white bg-green-500 hover:bg-green-600 font-bold rounded-lg shadow-md" type="submit">
                        Send
                    </button>
                </div>
            </div>
            @else
                <div class="flex flex-col justify-center relative bg-white rounded-lg w-1/3 h-1/12">
                {{--text--}}
                <div class="flex justify-center my-5 mx-10 ">
                    <h3 class="font-semibold text-lg leading-6 text-gray-900">You've already sent an invitation.</h3>
                </div>
                {{--button area--}}
                <div class="flex flex-row justify-center space-x-4 m-6">
                    <button wire:click="cancelInvitation" class="py-1 px-2 w-24 h-12 text-xl text-white bg-red-500 hover:bg-red-600 font-bold rounded-lg shadow-md" type="submit">
                        Hide
                    </button>
                </div>
                </div>
            @endif
        </div>
    </div>
{{--tickets preview--}}
    <div class="fixed inset-0 @if($previewHidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
        <div  class="flex block justify-center text-center items-center h-full">
            <div class="flex flex-col relative bg-white rounded-lg w-1/3 h-1/2">
                {{--text--}}
                <div class="flex justify-center my-5 mx-10">
                    <h3 class="font-semibold text-lg leading-6 text-gray-900">Preview of the task</h3>
                </div>
                {{--content--}}
                <div class="w-full h-full bg-white px-4 overflow-scroll">
{{--                    <textarea placeholder="Write a few words to the author and your application will be considered." class="w-full h-full resize-none bg-slate-100 rounded-2xl pt-3 px-3 shadow-md" wire:model.defer="invitationMessage"></textarea>--}}
                    <div class="flex flex-col space-y-2 text-start">
                        @if(isset($ticketToPreview))
                            <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                                <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Title</p>
                                <p class="text-lg">{{$ticketToPreview->title}}</p>
                            </div>
                            <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                                <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Description</p>
                                <p class="text-lg">{{$ticketToPreview->description}}</p>
                            </div>
                            <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                                <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Address</p>
                                <p class="text-lg">{{$ticketToPreview->address}}</p>
                            </div>
                            @if(isset($ticketToPreview->price))
                                <div class="flex flex-col  rounded-xl shadow-md p-2 bg-green-100">
                                    <p class="underline decoration-2 decoration-blue-300 underline-offset-4 font-semibold mb-1">Reward</p>
                                    <p class="text-lg">{{$ticketToPreview->price}}</p>
                                </div>
                            @endif
                        @endif
                    </div>
                </div>
                {{--button area--}}
                <div class="flex flex-row justify-center space-x-4 m-6">
                    <button wire:click="hidePreview" class="py-1 px-2 w-24 h-12 text-xl text-white bg-yellow-500 hover:bg-yellow-600 font-bold rounded-lg shadow-md" type="submit">
                        Hide
                    </button>
                </div>
            </div>
        </div>
    </div>
{{--main menu and the header--}}
        <div class="sticky top-0 @if(!$previewHidden or !$changeHidden) hidden @endif">
            <div class="flex flex-row justify-center">
                <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                    <div class="flex flex-row justify-between">
                        <p class="font-semibold text-2xl mx-7 my-3">Available tasks</p>
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
        </div>
    <x-background.index >
        <div class="flex justify-center mx-2 mt-2 mb-10 h-12">
            <form action="#" class="flex space-x-4 justify-center flex-row w-7/12 max-w-4xl h-full" >
                <input wire:model="search" type="text" placeholder="Type something that interests you.." name="search" class="w-full bg-blue-100 rounded-xl px-3 shadow-md">
            </form>
        </div>
        @livewire('tickets.index-filter')
{{--        ticket list--}}
        <div class="md:mx-10 sm:mx-0 flex flex-col justify-center space-y-6">
            @foreach($tickets as $ticket)
                @if($ticket->user->id != $my_id)
                <div class="flex flex-row justify-between bg-blue-300 rounded-xl shadow-xl">
                    <div class="basis-3/5 flex flex-col bg-green-100 px-10 py-4 rounded-l-xl">
                        <div class="text-2xl">
                            {{$ticket->title}}
                        </div>
                        <div>
                            Address: {{$ticket->address}}
                        </div>
                    </div>
                    <div class="basis-2/5 flex flex-row justify-center flex-wrap bg-blue-100 p-4 rounded-r-xl">
                        <button wire:click.prevent="invitationForm({{$ticket->id}})" class="w-20 h-12 m-2 text-white bg-green-500 hover:bg-green-600 font-bold rounded-xl shadow-md">
                            Take
                        </button>
                        <a href="{{route('public.show', $ticket->id)}}" class="w-20 h-12 m-2 text-white bg-blue-500 hover:bg-blue-600 font-bold rounded-xl shadow-md grid place-content-center">
                            <div class="self-center">
                                Show
                            </div>
                        </a>
                        <button wire:click.prevent="showPreview({{$ticket->id}})" class="w-20 h-12 m-2 text-white bg-yellow-500 hover:bg-yellow-600 font-bold rounded-xl shadow-md">
                            Preview
                        </button>
                    </div>
                </div>
                @endif
            @endforeach
        </div>
    </x-background.index>
</div>


