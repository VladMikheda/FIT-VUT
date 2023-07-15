@extends('layout.index')
@section('content')
    <x-form_elements.index>
        <x-form_elements.title>Vytvoření servisního požadavku</x-form_elements.title>
        @error('formError')
        <div class="text-xl text-white text-center bg-red-600 rounded-lg w-auto">Zpráva: {{$message}}</div>
        @enderror
        <x-form_elements.form action="{{route('manager.requirements.store')}}" enctype="multipart/form-data">

            <div class="mb-6">
                <label for="repair_id" class="m-1" >Servisní technik</label>
                <select id="repair_id" name="repair_id"
                        class=" @error('name') border-2 border-red-500 @enderror file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">
                    @foreach($technicians as $technician)
                        <option value="{{$technician->id}}">{{$technician->name}} {{$technician->lastname}}</option>
                    @endforeach
                </select>
                @error('name')
                <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                @enderror
            </div>

            <div class="mb-6">
                <label for="problem_id" class="m-1" >Problém</label>
                <select id="problem_id" name="problem_id"
                        class=" @error('name') border-2 border-red-500 @enderror file:border-0 file:border-r  w-full p-2.5 rounded-lg shadow-inner value:text-white bg-gray-100">

                    @foreach($problems as $problem)
                        <option value="{{$problem->id}}">{{$problem->title}}</option>
                    @endforeach
                </select>
                @error('name')
                <div class="m-1 text-red-400 text-sm">{{$message}}</div>
                @enderror
            </div>

            <div class="flex items-center justify-center">
                <a href="{{route('profile.manager')}}" class="bg-yellow-500 text-center text-white  hover:bg-red-600 px-5 py-2.5 rounded-lg font-bold w-auto flex items-center justify-center m-3">
                    Zrušit
                </a>
                <x-form_elements.buttom class="flex items-center justify-center m-3">
                    Uložit
                </x-form_elements.buttom>
            </div>

        </x-form_elements.form>
    </x-form_elements.index>

@endsection
