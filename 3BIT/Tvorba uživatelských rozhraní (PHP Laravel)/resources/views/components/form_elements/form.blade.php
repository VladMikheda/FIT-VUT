{{--

    Project: Volunteer System

    File: form.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project
--}}
@props([
    'action' => '#',
    'enctype' => 'application/x-www-form-urlencoded',
    'method' => 'POST'
])
<form class="space-y-3 md:space-y-5" action="{{$action}}" method="{{$method}}" enctype="{{$enctype}}" >
    @csrf
    {{$slot}}
</form>
