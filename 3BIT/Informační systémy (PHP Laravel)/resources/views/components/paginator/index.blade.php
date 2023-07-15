
<div class="flex-row flex mt-8">
    <x-paginator.back page="{{$tickets->currentPage()}}" rout="{{$rout}}" />
    @if($tickets->currentPage() >= 5  && $tickets->currentPage() <=  $tickets->lastPage() - 4 )
        <div class="flex-row flex">
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()-4}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()-3}}"  rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()-2}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()-1}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()-0}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()+1}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()+2}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()+3}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->currentPage()+4}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
        </div>
    @elseif($tickets->currentPage() < 5 || $tickets->lastPage() - 8 < 1)
        <div class="flex-row flex">
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{1}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{2}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{3}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{4}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{5}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{6}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{7}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}" />
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{8}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{9}}" rout="{{$rout}}" last="{{$tickets->lastPage()}}"/>
        </div>
    @elseif($tickets->currentPage() >= $tickets->lastPage() -4 && $tickets->lastPage() - 8 >= 1)
        <div class="flex-row flex">
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-8}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-7}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-6}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-5}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-4}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-3}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-2}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-1}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
            <x-paginator.element page="{{$tickets->currentPage()}}" number="{{$tickets->lastPage()-0}}" rout="{{$rout}}"  last="{{$tickets->lastPage()}}"/>
        </div>
    @endif
    <x-paginator.next page="{{$tickets->currentPage()}}" last="{{$tickets->lastPage()}}" rout="{{$rout}}" />
</div>
