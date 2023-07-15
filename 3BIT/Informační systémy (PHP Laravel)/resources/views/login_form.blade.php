@extends('layout.index')
@section('content')
    <x-form_elements.index>
        <x-form_elements.title>Přihlásit se</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg p-1 w-auto">Zpráva: {{$message}}</div>
        @enderror
        @error('notError')
        <div class="text-xl text-white text-center bg-green-600 rounded-lg p-1 w-auto">Zpráva: {{$message}}</div>
        @enderror

        <x-form_elements.form action="{{route('authentication.check')}}">

            <x-form_elements.email></x-form_elements.email>

            <x-form_elements.password>Heslo</x-form_elements.password>

            <x-form_elements.remember>Zůstat přihlášen(a)</x-form_elements.remember>

            <x-form_elements.buttom class='flex items-center justify-center'>
                Přihlásit se
            </x-form_elements.buttom>
            <div class="flex items-center justify-center">Nemám účet.<a href="{{route('registration.create')}}"
                                                                        class="text-blue-600 p-1"> Registrace</a></div>
        </x-form_elements.form>
    </x-form_elements.index>
@endsection
