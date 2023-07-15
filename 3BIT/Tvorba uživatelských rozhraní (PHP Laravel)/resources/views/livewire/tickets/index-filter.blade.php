{{--
    Project: Volunteer System

    File: index-filter.blade.php
    Subject: ITU 2022

    @author: Vladisalav Khrisanov(xkhris00)
--}}
{{--filters for index--}}
<div>
    <div class="flex justify-center mb-10 w-full">
        <div class="flex flex-row justify-center w-3/4 space-x-4">
            <select wire:model="category" wire:change="filter" class="w-1/5 bg-blue-100 rounded-xl px-3 shadow-md h-10">
                <option value="0">Category</option>
                @foreach($categories as $category)
                    <option value="{{$category->id}}">{{$category->name}}</option>
                @endforeach
            </select>
            <select wire:model="dateOrder" wire:change="filter" class="w-1/5 bg-blue-100 rounded-xl px-3 shadow-md h-10">
                <option value="''">Date</option>
                    <option value="newest">Newest</option>
                    <option value="oldest">Oldest</option>
            </select>
            <select wire:model="reward" wire:change="filter" class="w-1/5 bg-blue-100 rounded-xl px-3 shadow-md h-10">
                <option value="''">Reward</option>
                <option value="highest">Highest</option>
                <option value="lowest">Lowest</option>
            </select>
        </div>
    </div>
</div>
