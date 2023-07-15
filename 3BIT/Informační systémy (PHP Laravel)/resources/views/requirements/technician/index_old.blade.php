@extends('layout.index')
@section('content')

    <x-ticket_elements>
        <div>
            <a href="{{route('profile.index')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Učet
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('profile.technician')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Servisní technik
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('technician.requirements.index')}}" class="text-gray-500 hover:text-blue-500 font-bold w-auto  m-1">
                Požadavky
            </a>
            <label class="w-4 h-4 text-gray-500" >|</label>
            <a href="{{route('technician.requirements.index.old')}}" class="text-black hover:text-blue-500 font-bold w-auto  m-1">
                Archiv požadavků
            </a>
        </div>

        <form action="{{route('technician.requirements.index.old')}}">
            <div class="flex items-center justify-center p-6">
                <input type="search" id="title" name="title" placeholder="Zadejte jméno požadavku..."
                       class=" file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                <div class="flex items-center justify-center m-3">
                    <button class="text-white bg-blue-500 hover:bg-blue-700 font-bold rounded-lg sm:w-auto px-5 py-2.5 text-center " type="submit">
                        Hledat
                    </button>
                </div>
                <a href="{{route('technician.requirements.index.old')}}" class="bg-yellow-500 text-center text-white  hover:bg-green-500 px-5 py-2.5 rounded-lg font-bold w-auto flex items-center justify-center">
                    Obnovit
                </a>
            </div>
        </form>

        @foreach($reqs as $req)
            @if ($req->requirement_status_id == 3)
            <div class=" my-3 mx-5 min-w-3/4 p-6 bg-white border border-black rounded-lg @if($req->requirement_status_id == 1) bg-red-100 @elseif($req->requirement_status_id == 2) bg-yellow-100 @else bg-green-100  @endif">
                <div class="grid grequirement_commentsap-6 md:grid-cols-2">
                    <div>
                        <label class="w-fit break-all text-3xl mr-2">Nazev:  {{$req->title}}</label>
                        <div class="w-fit text-xl">Status: {{$req->name}}</div> {{--$ticket->name--}}
                    </div>
                    <div>
                        <div class="flex items-end justify-end">
                            <x-ticket_elements.buttom href="{{route('technician.requirements.show',$req->id)}}">Podívat se</x-ticket_elements.buttom>
                        </div>
                    </div>
                </div>
            </div>
            @endif
        @endforeach

        <div class="p-6">
            {{$reqs->withQuerystring()->links()}}
        </div>

    </x-ticket_elements>
@endsection

