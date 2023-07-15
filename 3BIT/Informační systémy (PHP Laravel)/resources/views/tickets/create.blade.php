@extends('layout.index')
@section('content')
    <x-form_elements.index>
        <x-form_elements.title>Formulář pro oznámení problému</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg w-auto">Zpráva: {{$message}}</div>
        @enderror
        <x-form_elements.form action="{{route('user.tickets.store')}}" enctype="multipart/form-data">
            <div class="grid gap-6 md:grid-cols-2">
                <div>
                    <div class="mb-6">
                        <x-form_elements.universal name="title" type="text">Nazev*</x-form_elements.universal>
                    </div>
                    <div class="mb-6">
                        <x-form_elements.universal name="address" type="text">Adresa*</x-form_elements.universal>
                    </div>

                    <div class="mb-6">
                        <label for="image" class="m-1" >Nahrajte obrázky</label>
                        <input type="file"  id="image" name="image[]" multiple
                                class=" @error('image.*') border-2 border-red-500 @enderror file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                        @error('image.*')
                        <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                        @enderror
                    </div>



                    {{--                    <div class="mb-6">--}}
                    {{--                        <span class=" hover:bg-green-600 hover:text-white overflow-hidden relative w-fit inline-flex items-center  @error('image') border-2 border-red-500 @enderror w-fit p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black" >--}}
                    {{--                            Nahrát obrázek--}}
                    {{--                            <input class=" opacity-0 absolute w-fit" type="file" multiple name="image">--}}
                    {{--                        </span>--}}
                    {{--                    </div>--}}

                </div>

                <x-form_elements.textarea name="description">Popis*</x-form_elements.textarea>
            </div>

            <div class="flex items-center justify-center">
                <x-form_elements.home href="{{route('profile.index')}}"></x-form_elements.home>
                <x-form_elements.buttom class="flex items-center justify-center m-3">
                    Poslat
                </x-form_elements.buttom>
            </div>


        </x-form_elements.form>
    </x-form_elements.index>

@endsection
