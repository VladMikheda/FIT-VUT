@props([
    'name' => 'password'
])

<div>
    <label for="{{$name}}"  class="m-1" >{{$slot}}</label>
    <input type='password' name="{{$name}}" class=" @error('password') border-2 border-red-500 @enderror  w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black" placeholder="&#9679;&#9679;&#9679;&#9679;&#9679;&#9679;" >
    @error('password')
    <div class="m-1 text-red-400 text-sm">{{$message}}</div>
    @enderror
</div>
