@extends('layout.index')
@section('content')
    <x-profile_elements>
        <h1 class="text-8xl mt-8">Uživatelský účet</h1>
        <div class="px-10 mt-20">
            <x-profile_elements.header :user="$user"/>
            <x-profile_elements.tabs>
                <x-profile_elements.tab href="{{route('profile.index')}}">Uživatel
                </x-profile_elements.tab>
                @if($is_admin)
                    <x-profile_elements.tab href="{{route('profile.admin')}}">Administrátor</x-profile_elements.tab>
                @endif
                @if($is_manager)
                    <x-profile_elements.tab href="{{route('profile.manager')}}" >Správce města</x-profile_elements.tab>
                @endif
                    <x-profile_elements.tab color="text-blue-700 border-b-blue-700" href="{{route('profile.technician')}}">Servisní technik</x-profile_elements.tab>
                <x-profile_elements.tab href="{{route('profile.edit')}}">Změny profilu</x-profile_elements.tab>
            </x-profile_elements.tabs>


            <x-profile_elements.action>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('technician.requirements.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam přiřazených servisních požadavků</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Moje aktivní servisní požadavky</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('technician.requirements.index.old')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam vyřízených servisních požadavků</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Moje vyřízené servisní požadavky</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

            </x-profile_elements.action>

        </div>
    </x-profile_elements>
@endsection

