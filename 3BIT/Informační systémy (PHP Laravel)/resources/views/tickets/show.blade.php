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
            <a href="{{route('user.tickets.show',$ticket->id)}}" class="text-black  hover:text-blue-500 font-bold w-auto  m-1">
                Informace o hlášení
            </a>
        </div>
        <h1 class="text-8xl mb-8 mt-4 ">Informace o hlášení </h1>


        <lavel class="text-xl text-gray-600">Nazev:</lavel>
        <div class=" break-after-left break-all mb-4 pl-4 text-4xl rounded-lg ">
            <p>{{$ticket->title}}</p>
        </div>


        <lavel class="text-xl text-gray-600">Stav:</lavel>
        <div class=" @if($ticket->ticket_status_id == '1') text-red-600 @elseif($ticket->ticket_status_id == '2') text-yellow-500 @else text-green-600 @endif break-after-left mb-4 pl-4 text-4xl rounded-lg ">
            <p>{{$status->name}}</p>
        </div>

        <lavel class="text-xl text-gray-600">Adresa:</lavel>
        <div class="mb-4 pl-4 break-all text-3xl rounded-lg ">
            <div>{{$ticket->address}}</div>
        </div>

        <lavel class="text-xl text-gray-600">Popis:</lavel>
        <div class="mb-4  break-all break-after-left pl-4 text-2xl rounded-lg ">
            <div>{{$ticket->description}}</div>
        </div>

        <label class="text-xl text-gray-600">Obrazky:</label>
        <div class="flex mb-4 pl-4 flex-row">

            @foreach($images as $image)
                    <a href="{{asset($image->path)}}">
            <img src="{{asset($image->path)}}" class="w-20 h-20 rounded-2xl mr-1" />
             </a>
            @endforeach
                <a href="{{route('user.tickets.show.images',$ticket->id)}}" class="bg-blue-500 text-center text-white w-20 h-20  hover:bg-blue-700 px-5 py-2.5 rounded-lg font-bold w-auto flex items-center justify-center ">
                    Vice
                </a>
        </div>

        @if($ticket->ticket_status_id != 3)
            <x-form_elements.form action="{{route('user.tickets.add.images',$ticket->id)}}" enctype="multipart/form-data">
                <div class="flex flex-row">
                    <div class="mb-6">
                    <label for="image" class="m-1 text-gray-600" >Nahrajte obrázky</label>
                        <div>
                        <input type="file"  id="image" name="image[]" multiple
                           class=" @error('image.*') border-2 border-red-500 @enderror file:border-0 file:border-r  w-fit p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                        @error('image.*')
                        <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                        @enderror
                        </div>
                    </div>

                    <x-form_elements.buttom class="flex justify-end h-fit ml-2 mt-6"  >
                        Poslat
                    </x-form_elements.buttom>

                </div>
            </x-form_elements.form>
        @endif

        <div class=" border-black border-b-2 ">
            <label class="text-xl text-gray-600">Komentare</label>
        </div>

        @foreach($comments as $comment)
            <div class="@if($comment->user_id === \Illuminate\Support\Facades\Auth::id()) ml-auto @else mr-auto @endif  my-3  w-fit p-6 bg-white border border-black rounded-lg">
            <label class="w-fit break-all border-b border-black text-xl mb-2">@if($comment->user_id === \Illuminate\Support\Facades\Auth::id()) Vy @else Moderator @endif | {{$comment->created_at}}</label>
            <div class="w-fit mt-2 text-xl">{{$comment->content}}</div>
            </div>
        @endforeach
        <div class="flex justify-end">
            <x-paginator :tickets="$comments" rout="{{route('user.tickets.show',$ticket->id)}}"></x-paginator>
        </div>
        @if($ticket->ticket_status_id != 3)
            <x-form_elements.form action="{{route('user.tickets.add.comment',$ticket->id)}}">
                <div class="mx-5">
                <x-form_elements.textarea name="content">Pridat komentar</x-form_elements.textarea>
                    <x-form_elements.buttom class="flex justify-end" >
                        Poslat
                    </x-form_elements.buttom>
                </div>

            </x-form_elements.form>
        @endif

    </x-ticket_elements>
@endsection
