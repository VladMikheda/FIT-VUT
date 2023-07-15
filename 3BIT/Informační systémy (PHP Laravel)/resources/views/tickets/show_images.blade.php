@extends('layout.index')
@section('content')
    <x-ticket_elements>
        <div>
            <a href="{{route('profile.index')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Profile
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('user.tickets.index')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Hlášení o problémech
            </a>
            <label class="w-4 h-4 text-gray-500" >|</label>
            <a href="{{route('user.tickets.index.old')}}" class="text-gray-500   hover:text-blue-500 font-bold w-auto  m-1">
                Archiv problémů
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('user.tickets.show',$ticket->id)}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Informace o hlášení
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('user.tickets.show.images',$ticket->id)}}" class="text-black  hover:text-blue-500 font-bold w-auto  m-1">
                Obrazky
            </a>
        </div>
        <h1 class="text-8xl mb-8 mt-4 ">Hlášení o problémech</h1>

{{--        <div class="flex mb-4 pl-4 flex-wrap">--}}
        <div class="grid gap-6 md:grid-cols-2">

            @foreach($images as $image)
                <a href="{{asset($image->path)}}">
                    <img src="{{asset($image->path)}}" class="w-50 h-45 rounded-2xl mr-1" />
                </a>
            @endforeach
        </div>

        <x-paginator :tickets="$images" rout="{{route('user.tickets.show.images',$ticket->id)}}"></x-paginator>

    </x-ticket_elements>
@endsection
