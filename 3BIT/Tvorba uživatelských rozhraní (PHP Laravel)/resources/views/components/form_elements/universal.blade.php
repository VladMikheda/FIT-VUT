{{--

    Project: Volunteer System

    File: universal.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project

--}}
@props([
    'name' => '#',
    'placeholder' => '',
    'type' => 'text',
    'input' => ''
])

<div>
    <label for="{{$name}}" class="m-1">{{$slot}}</label>
    <input type="{{$type}}" value="{{old($name)}}" name="{{$name}}"
           class=" @error($name) border-2 border-red-500 @enderror w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black"
           placeholder="@if(!empty($input)){{$input}}@else {{$placeholder}} @endif">
    @error($name)
    <div class="m-1 text-red-400 text-sm">{{$message}}</div>
    @enderror
</div>
