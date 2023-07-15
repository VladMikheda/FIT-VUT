@props([
    'href' => '#',
    'color' => 'hover:text-black hover:border-b-black'
])
<li>
    <a href="{{$href}}" class="inline-block px-4 border-b-2 border-transparent {{$color}}">{{$slot}}</a>
</li>
