@props([
    'href' => '#'
])
<li class="mt-5">
    <a href="{{$href}}" class="block max-w-sm p-6 bg-white border border-black rounded-lg  hover:text-white hover:bg-blue-500  ">
       {{$slot}}
    </a>
</li>
