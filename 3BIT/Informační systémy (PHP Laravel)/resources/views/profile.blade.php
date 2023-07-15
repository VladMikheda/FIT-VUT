@extends('layout.index')
@section('content')
    <x-profile_elements>
        <h1 class="text-8xl mt-8">Uživatelský účet</h1>
        <div class="px-10 mt-20">
            <x-profile_elements.header :user="$user"/>
            <x-profile_elements.tabs>
                <x-profile_elements.tab color="text-blue-700 border-b-blue-700" href="#">Uživatel
                </x-profile_elements.tab>
                @if($is_admin)
                    <x-profile_elements.tab href="{{route('profile.admin')}}">Administrátor</x-profile_elements.tab>
                @endif

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
                    <x-profile_elements.action_card href="{{route('user.tickets.create')}}">
                        <x-profile_elements.title_action_card>Hlásit problém</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Pokud ve městě vidíte problém - <br>dejte nám o tom vědět
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>


                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('user.tickets.index')}}">
                        <x-profile_elements.title_action_card>Zobrazit vaše hlášení o problémech</x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card><S></S>Seznam již nahlášených problémů
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>


                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('user.tickets.index.old')}}">
                        <x-profile_elements.title_action_card>Zobrazit již vyřešené problémy
                        </x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Seznam již vyřešených problémů
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

                <x-profile_elements.action_list class="mr-5">

                    <x-profile_elements.action_card href="{{route('join.create')}}">
                        <x-profile_elements.title_action_card>Přihláška do našeho týmu
                        </x-profile_elements.title_action_card>
                        <x-profile_elements.discription_action_card>Přidejte se k našemu týmu, zlepšme město!
                        </x-profile_elements.discription_action_card>
                    </x-profile_elements.action_card>

                </x-profile_elements.action_list>

            </x-profile_elements.action>


        </div>
    </x-profile_elements>
@endsection
