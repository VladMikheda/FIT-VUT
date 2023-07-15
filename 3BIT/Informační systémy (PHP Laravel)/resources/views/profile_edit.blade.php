@extends('layout.index')
@section('content')
    <x-profile_elements>
        <h1 class="text-8xl mt-8">Uživatelský účet</h1>
        <div class="px-10 mt-20">
            <x-profile_elements.header :user="$user"/>
            <x-profile_elements.tabs>
                <x-profile_elements.tab href="{{route('profile.index')}}">Uživatel</x-profile_elements.tab>
                @if($is_admin)
                    <x-profile_elements.tab href="#">Administrátor</x-profile_elements.tab>
                @endif

                @if($is_manager)
                    <x-profile_elements.tab href="{{route('profile.manager')}}">Správce města</x-profile_elements.tab>
                @endif

                @if($is_repair)
                    <x-profile_elements.tab href="{{route('profile.technician')}}">Servisní technik</x-profile_elements.tab>
                @endif
                <x-profile_elements.tab color="text-blue-700 border-b-blue-700" href="#">Změny profilu
                </x-profile_elements.tab>
            </x-profile_elements.tabs>
            <dev class="my-8">
            <x-form_elements.form action="{{route('profile.update')}}" enctype="multipart/form-data">
                <h1 class="text-xl mt-8">Změna uživatelských dat</h1>
                <div class=" grid gap-6 md:grid-cols-2">
                    <x-form_elements.universal name="name" input="{{$user->name}}" placeholder="Jan">Jmeno</x-form_elements.universal>

                    <x-form_elements.universal name="lastname" input="{{$user->lastname}}" placeholder="Novák">Příjmení</x-form_elements.universal>

                    <x-form_elements.email input="{{$user->email}}" ></x-form_elements.email>

                    <x-form_elements.universal input="{{$user->phone}}" name="phone" placeholder="787897543">Telefon</x-form_elements.universal>
                    <x-form_elements.universal input="{{$user->birthday}}" type="date"  name="birthday">Birthday</x-form_elements.universal>

                    <div>
                        <label for="image" class="m-1" >Nahrajte obrázky</label>
                        <input type="file"  id="image" name="image"
                               class=" @error('image') border-2 border-red-500 @enderror file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                        @error('image')
                        <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                        @enderror
                    </div>

                    <x-form_elements.buttom class="flex items-start justify-start ">
                        Změnit
                    </x-form_elements.buttom>
                </div>

            </x-form_elements.form>

                <x-form_elements.form  action="{{route('profile.update.password')}}">
                    <h1 class="text-xl mt-8">Změna hesla</h1>
                    <div class=" grid gap-6 md:grid-cols-2">
                        <x-form_elements.password>Staré heslo</x-form_elements.password>
                        <x-form_elements.password name="new_password">Nové heslo</x-form_elements.password>
                        <x-form_elements.buttom class="flex items-start justify-start ">
                            Změnit
                        </x-form_elements.buttom>
                    </div>

                </x-form_elements.form>

            </dev>


        </div>
    </x-profile_elements>
@endsection
