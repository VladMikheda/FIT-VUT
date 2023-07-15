@extends('layout.index')
@section('content')
    <x-profile_elements>
        <h1 class="text-8xl mt-8">Uživatelský účet</h1>
        <div class="px-10 mt-20">
            <x-profile_elements.header :user="$user"/>
            <x-profile_elements.tabs>
                <x-profile_elements.tab href="{{route('profile.index')}}">Uživatel
                </x-profile_elements.tab>
                <x-profile_elements.tab color="text-blue-700 border-b-blue-700" href="#">Administrátor</x-profile_elements.tab>
                @if($is_manager)
                <x-profile_elements.tab href="{{route('profile.manager')}}">Správce města</x-profile_elements.tab>
                @endif
                @if($is_repair)
                    <x-profile_elements.tab href="{{route('profile.technician')}}">Servisní technik</x-profile_elements.tab>
                @endif
                <x-profile_elements.tab href="{{route('profile.edit')}}">Změny profilu</x-profile_elements.tab>
            </x-profile_elements.tabs>


            <x-profile_elements.action>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('admin.allProblems')}}">
                        <x-profile_elements.title_action_card>Zobrazit seznam všech problemů</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card><S></S>Seznam vsech dosud neřešených problemů <br><br>

                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('admin.archProbs')}}">
                        <x-profile_elements.title_action_card>Zobrazit archivované problémy</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card><S></S>Archiv problémů <br><br></x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>


                </x-profile_elements.action_list>


                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('admin.users')}}">
                        <x-profile_elements.title_action_card>Zobrazit všechny uživatele</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam všech uživatelů. Můžete spravovat
                                                            jejich přístup do systému</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('admin.userAccept')}}">
                        <x-profile_elements.title_action_card>Zobrazit žádosti o registraci</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam uživatelů, kteří chtějí
                                                                    začit pracovat se systémem</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>


                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('admin.allManagers')}}">
                        <x-profile_elements.title_action_card>Zobrazit všechny správci města</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam správců města</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                    <x-profile_elements.action_card href="{{route('admin.managerApprove')}}">
                        <x-profile_elements.title_action_card>Zobrazit kandidáty na správce města</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam uživatelů, kteří chtějí
                                                                začit pracovat jako správce města</x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

            </x-profile_elements.action>


        </div>
    </x-profile_elements>
@endsection
