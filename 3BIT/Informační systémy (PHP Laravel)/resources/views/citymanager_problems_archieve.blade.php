@extends('layout.index')
@section('content')
    <x-ticket_elements>
        <div>
            <a href="{{route('profile.manager')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Správce města
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('manager.problems.index')}}" class="text-gray-500 hover:text-blue-500 font-bold w-auto  m-1">
                Aktuální problémy
            </a>
            <label class="w-4 h-4 text-gray-500" >|</label>
            <a href="{{route('manager.problems.index.old')}}" class="@if(isset($old))text-black @else text-gray-500  @endif  hover:text-blue-500 font-bold w-auto  m-1">
                Archivované problémy
            </a>
        </div>

        <div class="flex items-center justify-between">
            <h1 class="text-8xl mb-8 mt-4 ">Archiv problémů</h1>
        </div>

        <div class = "w-full h-16"> </div>

        @foreach($problems as $problem)
            {{--            @dd($tickets)--}}
            {{--            @dump($ticket)--}}
            <div class=" my-3 mx-5 min-w-3/4 p-6 bg-white border border-black rounded-lg bg-green-100">
                <div class="grid gap-6 md:grid-cols-2">
                    <div>
                        <label class="w-fit break-all text-3xl mr-2">Nazev:  {{$problem->title}}</label>
                            <div class="w-fit text-xl">Status: Vyřešen</div>
                    </div>
                    <div>
                        <div class="flex items-end justify-end">
                            <x-ticket_elements.buttom href="{{route('problem.unsolveProb',$problem->id)}}">Zahajit znovu</x-ticket_elements.buttom>
                        </div>
                    </div>
                </div>
            </div>
        @endforeach


        @php
            $rout = route('manager.problems.index.old');
        @endphp

        <x-paginator :tickets="$problems" rout='{{$rout}}' ></x-paginator>

    </x-ticket_elements>
@endsection
