{{--

    Project: Volunteer System

    File: buttom.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project
--}}

<div {{$attributes->class('')}}>
    <button class="text-white bg-blue-700 hover:bg-blue-500 font-bold rounded-lg sm:w-auto px-5 py-2.5 text-center " type="submit">{{$slot}}</button>
</div>
