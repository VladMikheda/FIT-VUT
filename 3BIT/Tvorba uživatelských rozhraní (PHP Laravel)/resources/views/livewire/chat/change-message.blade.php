{{--
    Project: Volunteer System

    File: app.blade.php
    Subject: ITU 2022

    @author: Vladisalav Khrisanov(xkhris00)
--}}
{{--change message window--}}
<div>
    <div class="fixed inset-0 @if($hidden) hidden @endif bg-gray-600 bg-opacity-60 h-screen">
        <div  class="flex block justify-center text-center items-center h-full">
            <div class="flex flex-col relative bg-white rounded-lg w-1/3 h-1/2">
                {{--header--}}
                <div class="flex justify-center my-5 mx-10">
                    <h3 class="font-semibold text-lg leading-6 text-gray-900">Change message</h3>
                </div>

                {{--content--}}
                <div class="w-full h-full bg-white px-4">
                    <textarea class="w-full h-full resize-none bg-slate-100 rounded-2xl pt-3 px-3 shadow-md" wire:model.defer="contentToChange">{{$contentToChange}}</textarea>
                </div>

                {{--button area--}}
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

