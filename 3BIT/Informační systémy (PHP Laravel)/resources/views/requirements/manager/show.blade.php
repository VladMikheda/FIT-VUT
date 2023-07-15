@extends('layout.index')
@section('content')
    <x-ticket_elements>
        <div class="pb-6">
            <a href="{{route('profile.index')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Učet
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('profile.manager')}}" class="text-gray-500  hover:text-blue-500 font-bold w-auto  m-1">
                Správce města
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('manager.requirements.index')}}" class="text-gray-500   hover:text-blue-500 font-bold w-auto  m-1">
                Požadavky
            </a>
            <label class="w-4 h-4 text-gray-500" >/</label>
            <a href="{{route('manager.requirements.show', $requirement->id)}}" class="text-black  hover:text-blue-500 font-bold w-auto  m-1">
                Informace o požadavku
            </a>
            <label class="w-4 h-4 text-gray-500" >|</label>
            <a href="{{route('manager.requirements.index.old')}}" class="text-gray-500 hover:text-blue-500 font-bold w-auto  m-1">
                Archiv požadavků
            </a>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6">Název:</lavel>
        </div>
        <div class=" break-after-left mb-2 pl-10 text-3xl rounded-lg ">
            <p>{{$requirement->title}}</p>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6">Stav:</lavel>
        </div>
        <div class="@if($requirement->requirement_status_id == '1') text-red-600 @elseif($requirement->requirement_status_id == '2') text-yellow-500 @else text-green-600 @endif break-after-left mb-2 pl-10 text-3xl rounded-lg ">
            <p>{{$status->name}}</p>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6">Servisní technik:</lavel>
        </div>
        <div class=" break-after-left mb-2 pl-10 text-3xl rounded-lg ">
            <div>{{$names->name}} {{$names->lastname}}</div>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6">Adresa:</lavel>
        </div>
        <div class="mb-3 pl-10 text-3xl rounded-lg">
            <div>{{$requirement->address}}</div>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6">Popis:</lavel>
        </div>
        <div class="mb-3 pl-10 text-3xl rounded-lg">
            <div>{{$requirement->description}}</div>
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6 ">Předpokládané datum vyřízení:</lavel>
        </div>
        <div class="mb-2 pl-10 text-3xl rounded-lg ">
            @if(isset($requirement->estimated_time))
                <div>{{date('d-m-Y', strtotime($requirement->estimated_time))}}</div>
            @endif
        </div>

        <div class="mb-1">
            <lavel class="text-xl text-gray-600 pl-6 ">Cena:</lavel>
        </div>
        <div class="mb-5  break-after-left pl-10 text-3xl rounded-lg ">
            <div>{{$requirement->price}}</div>
        </div>

        <div class="flex items-start mb-6 pl-6">
            <a href="{{route('manager.requirements.edit', $requirement->id)}}" class="bg-blue-700 text-center text-white  hover:bg-blue-500 px-5 py-2.5 rounded-lg font-bold  items-center justify-center">
                Provést změny
            </a>
        </div>

        <div class="mb-3">
            <lavel class="text-xl text-gray-600 pl-6">Komentáře:</lavel>
        </div>
        <div class="pl-6">
            @foreach($comments as $comment)
                <div class="mr-auto my-3  w-fit p-6 bg-white border border-black rounded-lg">
                    <label class="w-fit break-all border-b border-black text-xl mb-2">@if($comment->user_id === \Illuminate\Support\Facades\Auth::id()) Vy @else Servisní technik @endif | {{$comment->created_at}}</label>
                    <div class="w-fit mt-2 text-xl">{{$comment->content}}</div>
                </div>
            @endforeach

            <div class="mt-1">
                {{$comments->withQuerystring()->links()}}
            </div>
        </div>

        <x-form_elements.form action="{{route('manager.requirements.comment', $requirement->id)}}">
            <div class="mx-5">
                <div class="mb-2">
                    <x-requirements.textarea name="content"></x-requirements.textarea>
                </div>
                <x-form_elements.buttom class="flex justify-end" >
                    Poslat
                </x-form_elements.buttom>
            </div>
        </x-form_elements.form>
    </x-ticket_elements>
@endsection
