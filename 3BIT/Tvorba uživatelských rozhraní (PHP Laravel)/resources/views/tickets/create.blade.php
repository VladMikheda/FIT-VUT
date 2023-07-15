{{--

    Project: Volunteer System

    File: create.blade.php
    Subject: ITU 2022

    @author: Vladislav Mikheda xmikhe00

--}}

<div class="h-screen overflow-auto">
{{-- start top-bar --}}
    <div class="sticky  top-0 ">
        <div class="flex flex-row justify-center">
            <div class="bg-blue-100 w-3/4 max-w-7xl shadow-md">
                <div class="flex flex-row justify-between">
                <p class="font-semibold text-2xl mx-7 my-3">Create task </p>
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
{{--End top bar--}}
<x-background.index-create>
{{--Body--}}
        <div class="mx-2 mt-2 mb-12 h-12">
            {{--Start form--}}
            <form wire:submit.prevent="saveTicket">
                <div>
                <div class="flex flex-row justify-center mt-2 ">
                    <div class=" w-5/12 max-w-4xl h-full">
                        <div>
                            <div class="flex space-y-2 justify-center flex-col mt-2  max-w-4xl h-20">
                                <label for="title">Title</label>
                                <input type="text" placeholder="Title" wire:model="title" id="title" name="title" class="@error('title') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 shadow-md">
                            </div>
                            @error('title')
                            <div class="text-red-600">
                                {{$message}}
                            </div>
                            @enderror
                        </div>
                        <div>
                            <div class="flex space-y-2 justify-center mt-2 flex-col  max-w-4xl h-20">
                                <label for="address"  >Address</label>
                                <input type="text" placeholder="Street 10" wire:model="address" name="address" class="@error('address') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 shadow-md">
                            </div>
                            @error('address')
                            <div class="text-red-600">
                                {{$message}}
                            </div>
                            @enderror
                        </div>

                        <div>
                            <div class="flex space-y-2 justify-center flex-col mt-2  max-w-4xl h-20">
                                <label for="Category">Category</label>
                                <select wire:model="category" id="category" name="category" class="@error('category') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 shadow-md">
                                    <option value=""></option>
                                    @foreach($allCategories as $category)
                                    <option value="{{$category['id']}}">{{$category['name']}}</option>
                                    @endforeach
                                </select>
                            </div>
                            @error('category')
                            <div class="text-red-600">
                                {{$message}}
                            </div>
                            @enderror
                        </div>

                        <div class="flex flex-row mt-2">
                            <div class="w-1/2">
                                <div class="flex w-full flex-col h-20 pr-4">
                                    <label for="number">Number of people</label>
                                    <input type="text" placeholder="10" wire:model="number" name="number" class="@error('number') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 shadow-md">
                                </div>
                                    @error('number')
                                    <div class="text-red-600">
                                        {{$message}}
                                    </div>
                                    @enderror
                            </div>
                            <div class="w-1/2">
                                <div class="flex w-full flex-col h-20">
                                    <label for="price"  >Price $</label>
                                    <input type="text" placeholder="100" wire:model="price" name="price" class="@error('price') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 shadow-md">
                                </div>
                                    @error('price')
                                    <div class="text-red-600">
                                        {{$message}}
                                    </div>
                                    @enderror
                            </div>
                        </div>

                        <div class="flex  space-y-2 justify-center mt-2 flex-col  max-w-4xl h-fit">
                            <div class="flex flex-row mt-2 ">
                            <label>Invite people</label>
                            <button   wire:click="doShow" type="button"  class="ml-3 flex justify-center text-white bg-green-500 hover:bg-green-600 font-bold rounded-lg  shadow-md w-10 h-6">Add</button>
                            </div>
                            {{--Start list with invite people--}}
                            <div class="bg-blue-100 overflow-auto h-fit max-h-28 w-full rounded-xl px-3 shadow-md">
                                @foreach($invitePeople as $index => $invite)
                                    <div class="m-2 w-96 p-1 rounded-xl">
                                        <div class="flex space-x-4">
                                            <div class="inline-flex justify-center items-center ml-1 w-10 h-10 bg-gray-100 rounded-full">
                                                <span class="font-bold text-gray-600">{{$invite['name'][0]}}{{$invite['lastname'][0]}}</span>
                                            </div>
                                            <div class="flex-1 text-left">
                                                <div class=" font-medium text-gray-900 truncate">
                                                    {{$invite['name']}}
                                                </div>
                                                <div class="text truncate text-gray-900">
                                                    {{$invite['lastname']}}
                                                </div>
                                            </div>
                                            <div class="inline-flex ml-2 items-center">
                                                <button  wire:click="del({{$index}})" type="button"  class="text-white bg-red-500 hover:bg-red-600 font-bold shadow-md  rounded-lg flex justify-center  w-14 h-6">Delete</button>
                                            </div>
                                        </div>
                                    </div>

                                @endforeach

                            </div>
                        {{--End list invite people--}}
                        </div>

                    </div>

                    <div class="flex space-y-2 justify-center mt-2 ml-4 flex-col w-1/2 max-w-4xl">
                        <label for="description">Description</label>
                        <textarea type="text" wire:model="description" name="description" class="@error('description') border-2 border-red-500 @enderror bg-blue-100 h-full w-full rounded-xl px-3 py-3 shadow-md"></textarea>
                        @error('description')
                        <div class="text-red-600">
                            {{$message}}
                        </div>
                        @enderror

                    </div>
                </div>
                    <div class="flex justify-end mt-2 flex-row h-20">
                        <button  wire:click="saveTicket" type="button" class=" mt-2 mr-10 w-1/5  shadow-md px-2 text-white bg-green-500 hover:bg-green-600 font-bold rounded-xl shadow-md" >
                            Create
                        </button>
                    </div>
                </div>
            </form>
        </div>


{{--Invite people--}}
    <div class="fixed inset-0 @if($hidden) hidden @endif bg-gray-600 bg-opacity-60">
        <div  class="flex block min-h-full justify-center text-center items-center">
            <div class="relative bg-white rounded-lg">
                <div class="m-6 text-left">
                    <h3 class="text-2xl mt-5 font-medium leading-6 text-gray-900">Send invite</h3>
                </div>
                @if(empty($allFriend))
                    <div class="m-3 w-96 p-3  rounded-xl">
                        <div class="flex-1 text-left">
                            <div class=" font-medium text-gray-900 truncate">
                                <h3>You have no one else to add!</h3>
                            </div>
                        </div>
                    </div>
                @endif
                {{--Start friend list--}}
                <div class=" overflow-auto w-full overflow-x-hidden  max-h-72">
                @foreach($allFriend as $friend)
                    <div class="m-3 w-96 p-3 border-black border-2 rounded-xl">
                        <div class="flex space-x-4">
                            <div class="inline-flex justify-center items-center w-10 h-10 bg-gray-100 rounded-full">
                                <span class="font-bold text-gray-600">{{$friend['name'][0]}}{{$friend['lastname'][0]}}</span>
                            </div>
                            <div class="flex-1 text-left">
                                <div class=" font-medium text-gray-900 truncate">
                                    {{$friend['name']}}
                                </div>
                                <div class="text truncate text-gray-900">
                                    {{$friend['lastname']}}
                                </div>
                            </div>
                            <div class="inline-flex items-center ">
                                <div>
                                    <input type="checkbox"  wire:click="inviteFriends({{$friend['id']}})"  name="invite-friend{{$friend['id']}}" class=" ml-2.5 w-5 h-5 checked:accent-green-500 text-green-500 rounded-xl border border-gray-600 focus:outline-green-600 bg-gray-100" >
                                </div>
                            </div>
                        </div>
                    </div>
                @endforeach
                </div>
                {{--Stop friend list--}}
                <div class="p-6">
                    <button wire:click="doHidden" value="1" class=" text-white bg-yellow-500 hover:bg-yellow-600 font-bold rounded-xl shadow-md mt-2 mr-10 py-2 text-xl  w-full  px-2" type="submit">
                        Close
                    </button>
                </div>
            </div>
        </div>
    </div>
</x-background.index-create>

</div>
