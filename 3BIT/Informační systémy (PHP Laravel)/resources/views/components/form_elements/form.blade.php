@props([
    'action' => '#',
    'enctype' => 'application/x-www-form-urlencoded',
    'method' => 'POST'
])
<form class="space-y-3 md:space-y-5" action="{{$action}}" method="{{$method}}" enctype="{{$enctype}}" >
    @csrf
    {{$slot}}
</form>
