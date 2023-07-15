@extends('layout.index')
@section('content')
{{--        @php--}}
{{--            dump($requirement->id);--}}
{{--            dd($requirement);--}}
{{--        @endphp--}}
    <x-form_elements.index>
        <x-form_elements.title>Aktualizace servisního požadavku</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg w-auto">Zpráva: {{$message}}</div>
        @enderror
{{--        enctype="multipart/form-data"--}}
        <x-form_elements.form action="{{route('technician.requirements.update', $requirement->id)}} " enctype="multipart/form-data">
            <div class="mb-6">
                <x-form_elements.universal input="{{$requirement->estimated_time}}" type="date"  name="estimated_time">Předpokládané datum vyřízení</x-form_elements.universal>
            </div>

            <div class="mb-6">
                <label for="requirement_status_id" class="m-1" >Stav</label>
                <select id="requirement_status_id" name="requirement_status_id"
                        class=" @error('name') border-2 border-red-500 @enderror file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                                                <option disabled selected value>Zvolte si</option>
                        <option value="1">Přiřazen</option>
                        <option value="2">Vyřizuje se</option>
                        <option value="3">Vyřízeno</option>
                </select>
                @error('name')
                <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                @enderror
            </div>

            <div class="mb-6">
                <x-form_elements.universal name="price" type="text">Cena</x-form_elements.universal>
            </div>

            <div class="flex items-center justify-center">
                <a href="{{route('technician.requirements.show', $requirement->id)}}" class="bg-yellow-500 text-center text-white  hover:bg-red-600 px-5 py-2.5 rounded-lg font-bold w-auto flex items-center justify-center m-3">
                    Zrušit
                </a>
                <x-form_elements.buttom class="flex items-center justify-center m-3">
                    Uložit
                </x-form_elements.buttom>
            </div>
        </x-form_elements.form>
    </x-form_elements.index>
@endsection

