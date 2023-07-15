@props([
    'href' => '#'
])

<a href="{{$href}}" class="bg-blue-500 text-center text-white  hover:bg-blue-700 px-5 py-2.5 rounded-lg font-bold w-auto flex items-center justify-center m-1">
    {{$slot}}
</a>
