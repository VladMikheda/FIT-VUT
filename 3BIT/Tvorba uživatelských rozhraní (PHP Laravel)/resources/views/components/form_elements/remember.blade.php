{{--

    Project: Volunteer System

    File: remember.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project
--}}
<div>
    <input type="hidden" value='0' name="remember" >
    <input type="checkbox" value='1' name="remember" class=" ml-2.5 focus:outline-blue-600 bg-gray-100" >
    <label for="remember"  class="m-1" >{{$slot}}</label>
</div>
