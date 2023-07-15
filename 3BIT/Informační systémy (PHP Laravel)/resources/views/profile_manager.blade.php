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
                <x-profile_elements.tab color="text-blue-700 border-b-blue-700" href="#">Správce města</x-profile_elements.tab>
                @if($is_repair)
                    <x-profile_elements.tab href="{{route('profile.technician')}}">Servisní technik</x-profile_elements.tab>
                @endif
                <x-profile_elements.tab href="{{route('profile.edit')}}">Změny profilu</x-profile_elements.tab>
            </x-profile_elements.tabs>


            <x-profile_elements.action>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('manager.tickets.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam nových hlášení</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Nově podáné hlášení o problémech ve městě</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('manager.problems.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam mnou vedených problemů</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card><S></S>Seznam problemů, které řešíte <br><br>
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('problem.createProb')}}">
                        <x-profile_elements.title_action_card>Vytvořit nový problém</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Tady vytvořite nový problem na řešení na základě hlášení</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('manager.problems.index.old')}}">
                        <x-profile_elements.title_action_card>Zobrazit archivované problémy</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card><S></S>Archiv problémů <br><br></x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>


                </x-profile_elements.action_list>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('manager.requirements.create')}}">
                        <x-profile_elements.title_action_card>Výtvořit nový technický požádavek</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Výtvoření a odesilání nového požadavku pro technika</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('manager.requirements.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam odeslaných technických požadavků</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Aktivní servisní požadavky</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('manager.requirements.index.old')}}">
                        <x-profile_elements.title_action_card>Zobrazit archivované technické požadavky</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Archív technických požadavků<br><br> </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('technician.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam techniků</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam aktualních techických pracovníků<br><br></x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('technician.index.new')}}">
                        <x-profile_elements.title_action_card>Zobrazit kandidáty na techického pracovníka</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam lidí, kteří se přihlásili <br>
                            na pozici technikého pracovníka
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>
            </x-profile_elements.action>

        </div>
    </x-profile_elements>
@endsection
