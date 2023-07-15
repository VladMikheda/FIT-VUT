@extends('layout.index')
@section('content')
    <x-form_elements.index>
        <x-form_elements.title>Přihláška do našeho týmu</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg p-1 w-auto">Zpráva: {{$message}}</div>
        @enderror
        @error('notError')
        <div class="text-xl text-white text-center bg-green-600 rounded-lg p-1 w-auto">Zpráva: {{$message}}</div>
        @enderror

        <x-form_elements.form action="{{route('join.store')}}">

            <select name='join' class=" @error('join') border-2 border-red-500 @enderror w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black">
                <option value="1">Administrátor</option>
                <option value="2">Správce města</option>
                <option value="3">Servisní technik</option>
            </select>
            @error('join')
            <div class="m-1 text-red-400 text-sm">{{$message}}</div>
            @enderror

            <div class="flex items-center justify-center">
                <x-form_elements.home href="{{route('profile.index')}}"></x-form_elements.home>
                <x-form_elements.buttom class="flex items-center justify-center m-3">
                    Poslat
                </x-form_elements.buttom>
            </div>

        </x-form_elements.form>
    </x-form_elements.index>
@endsection
