{{--

    Project: Volunteer System

    File: login_form.blade.php
    Subject: ITU 2022

    @author: Vladisalav Mikheda xmikhe00
    the file was taken from the IIS project

--}}

@extends('layouts.app')
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
{{--            {{route('registration.create')}}--}}
        </x-form_elements.form>
    </x-form_elements.index>
@endsection
