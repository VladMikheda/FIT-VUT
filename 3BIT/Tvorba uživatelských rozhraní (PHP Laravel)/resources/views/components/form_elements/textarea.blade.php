{{--

    Project: Volunteer System

    File: textarea.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project
--}}
@props([
    'name' => '#',
    'rows' => '8',
])

<div>
    <label for="{{$name}}"  class="m-1" >{{$slot}}</label>
    <textarea rows="{{$rows}}" cols="40" name="{{$name}}" class=" @error($name) border-2 border-red-500 @enderror w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black">{{old($name)}}</textarea>
    @error($name)
    <div class="m-1 text-red-400 text-sm">{{$message}}</div>
    @enderror
</div>
