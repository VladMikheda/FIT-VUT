@props([
    'name' => '#',
    'rows' => '8',
])

<div>
    <textarea rows="{{$rows}}" cols="40" name="{{$name}}" class=" @error($name) border-2 border-red-500 @enderror w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black">{{old($name)}}</textarea>
    @error($name)
    <div class="m-1 text-red-400 text-sm">{{$message}}</div>
    @enderror
</div>
