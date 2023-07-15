@extends('layout.index')
@section('content')
    <x-form_elements.index>
        <x-form_elements.title>Formulář pro vytvoření problému</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg w-auto">Zpráva: {{$message}}</div>
        @enderror
        <x-form_elements.form action="{{route('problem.storeProb')}}" enctype="multipart/form-data">
            <div class="grid gap-6 md:grid-cols-2">
                <div>
                    <div class="mb-6">
                        <x-form_elements.universal name="title" type="text">Nazev*</x-form_elements.universal>
                    </div>
                    <div class="mb-6">
                        <x-form_elements.universal name="address" type="text">Adresa*</x-form_elements.universal>
                    </div>

                </div>

                <x-form_elements.textarea name="description">Popis*</x-form_elements.textarea>
            </div>

            <div class="flex items-center justify-center">
                <x-form_elements.home href="{{route('manager.problems.index')}}"></x-form_elements.home>
                <x-form_elements.buttom class="flex items-center justify-center m-3">
                    Vytvořit
                </x-form_elements.buttom>
            </div>


        </x-form_elements.form>
    </x-form_elements.index>

@endsection
