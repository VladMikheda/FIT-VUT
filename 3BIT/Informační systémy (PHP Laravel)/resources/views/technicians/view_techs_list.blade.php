@extends('layout.index')
@section('content')
    <x-ticket_elements>
        <div>
            <a href="{{route('profile.manager')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Správce města
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('technician.index')}}" class="@if(!isset($old))text-black @else text-gray-500  @endif  hover:text-blue-500 font-bold w-auto  m-1">
                Aktuální technici
            </a>
        </div>

        <div class="flex items-center justify-between">
            <h1 class="text-8xl mb-8 mt-4 ">Technici</h1>
            {{--<button class="block right-0 text-white bg-blue-700 hover:bg-red-500 font-bold rounded-lg h-10 ml-44 mt-10 px-5 py-2.5 text-center " type="submit">--}}
            <button class="text-white bg-blue-700 hover:bg-red-500, font-bold rounded-lg h-10 ml-44 mt-10 px-4 text-center" type="submit">
                <a href="{{route('technician.index.new')}}">Prohlednout seznam zájemců</a>
            </button>
        </div>

        <div class = "w-full h-16"> </div>

        @foreach($techs as $tech)
            {{--            @dd($tickets)--}}
            {{--            @dump($ticket)--}}
            <div class=" my-3 mx-5 min-w-3/4 p-6 bg-white border border-black rounded-l">
                <div class="grid gap-6 md:grid-cols-2">
                    <div>
                        <label class="w-fit break-all text-3xl mr-2">Jméno:  {{$tech->name}} {{$tech->lastname}}</label><br>
                        <label class="w-fit break-all text-2xl mr-2">Číslo:  {{$tech->phone}}</label><br>
                        <label class="w-fit break-all text-2xl mr-2">E-mail: {{$tech->email}}</label>
                    </div>
                    <div>
                        <div class="flex items-end justify-end mt-6">
                            <x-ticket_elements.buttom href="{{route('technician.fire',$tech->id)}}">Propustit</x-ticket_elements.buttom>
                        </div>
                    </div>
                </div>
            </div>

        @endforeach


        @php
            $rout = route('technician.index');
//            if(isset($old)){
//                $rout = route('user.tickets.index.old');
//            }
        @endphp

        <x-paginator  :tickets="$techs" rout='{{$rout}}' ></x-paginator>

    </x-ticket_elements>
@endsection
