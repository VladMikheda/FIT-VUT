@extends('layout.index')
@section('content')
    <x-ticket_elements>
        <div>
            <a href="{{route('profile.admin')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Administrátor
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="#" class="@if(!isset($old))text-black @else text-gray-500  @endif  hover:text-blue-500 font-bold w-auto  m-1">
               Všichni správce města
            </a>
        </div>

        <div class="flex items-center justify-between">
            <h1 class="text-8xl mb-8 mt-4 ">Správce města</h1>
        </div>

        <div class = "w-full h-16"> </div>

        @foreach($managers as $manager)
            {{--            @dd($tickets)--}}
            {{--            @dump($ticket)--}}
            <div class=" my-3 mx-5 min-w-3/4 p-6 bg-white border border-black rounded-lgs">
                <div class="grid gap-6 md:grid-cols-2">
                    <div>
                        <label class="w-fit break-all text-3xl mr-2">Jméno: {{$manager->name}} {{$manager->lastname}}</label>
                            <div class="w-fit text-xl">Datum narození: {{$manager->birthday}}</div>
                            <div class="w-fit text-xl">Číslo:  {{$manager->phone}}</div>
                            <div class="w-fit text-xl">E-mail: {{$manager->email}}</div>
                    </div>
                    <div class="grid grid-cols-1 gap-2">
                        <div class="justify-end flex">
                            <button class="text-white bg-red-500 hover:bg-red-400 w-fit font-bold rounded-lg h-10 ml-44 mt-10 px-5 text-center" type="submit">
                                <a href="{{route('admin.managerFire', $manager)}}">Propustit</a>
                            </button>
                        </div>
                    </div>
                </div>
            </div>

        @endforeach


        @php
            $rout = route('admin.users');
        @endphp

        <x-paginator :tickets="$managers" rout='{{$rout}}' ></x-paginator>

    </x-ticket_elements>
@endsection
