<div class="flex flex-row">
    <div class="border-2  border-black rounded-full w-56 h-56">
        <img src="{{asset($user->photo)}}" class="w-56 h-56 rounded-full">
    </div>
    <div class="ml-8 mt-6">
        <div class="text-6xl">{{$user->name." ".$user->lastname}}</div>
        <div class="grid gap-2 md:grid-cols-2 ml-10 mt-6 text-gray-500 text-xl">
            <div>Email: {{$user->email}}</div>
            @if($user->phone)
                <div>Telefon: {{$user->phone}}</div>
            @endif
            @if($user->birthday)
                <div>Narozeni: {{date('d-m-Y', strtotime($user->birthday))}}</div>
            @endif
        </div>
    </div>
    <div class="justify-self-end">
        <button class="text-white bg-blue-700 hover:bg-red-500 font-bold rounded-lg h-10 ml-44 mt-10 px-5 py-2.5 text-center " type="submit">
            <a href="{{route(('authentication.exit'))}}">Odhlásit se</a>
        </button>
    </div>
</div>
