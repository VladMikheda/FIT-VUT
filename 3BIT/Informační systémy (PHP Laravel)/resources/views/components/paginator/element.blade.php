



<div class=" w-8 h-8 text-xl @if($number > $last) hidden @endif text-center @if($page == $number) bg-blue-500 @else bg-gray-400 @endif">
    <a href="{{$rout}}?page={{$number}}">{{$number}}</a>
</div>
