<?php

namespace App\Services\Tickets;


use App\Models\Images;
use App\Models\Ticket;
use App\Models\TicketComments;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class Service
{

    public function index($user,$data)
    {
//        return $user->tickets()->leftJoin('ticket_statuses','tickets.ticket_status_id','ticket_statuses.id')->select('tickets.id','name','title','ticket_status_id')->where('ticket_status_id','!=',3)->paginate(10);

        if(isset($data['title'])){
            return $user->tickets()
                ->leftJoin('ticket_statuses','tickets.ticket_status_id','ticket_statuses.id')
                ->select('tickets.id','name','title','ticket_status_id')
                ->where('ticket_status_id','!=',3)
                ->where("title","like","%{$data['title']}%")
                ->paginate(10);
        }

        return $user->tickets()
            ->leftJoin('ticket_statuses','tickets.ticket_status_id','ticket_statuses.id')
            ->select('tickets.id','name','title','ticket_status_id')
            ->where('ticket_status_id','!=',3)
            ->paginate(10);

    }

    public function viewAll()
    {
        return Ticket::paginate(10);
    }

    public function viewNewUnsolved()
    {
        return Ticket::where('ticket_status_id','!=', 3)->orderBy('created_at', 'asc')->paginate(10);
    }

    public function indexOld($user,$data)
    {
        if(isset($data['title'])){
            return $user->tickets()
                ->leftJoin('ticket_statuses','tickets.ticket_status_id','ticket_statuses.id')
                ->select('tickets.id','name','title','ticket_status_id')
                ->where('ticket_status_id','=',3)
                ->where("title","like","%{$data['title']}%")
                ->paginate(10);
        }

        return $user->tickets()
            ->leftJoin('ticket_statuses','tickets.ticket_status_id','ticket_statuses.id')
            ->select('tickets.id','name','title','ticket_status_id')
            ->where('ticket_status_id','=',3)
            ->paginate(10);
//        ->where('ticket_status_id','!=',3)
    }


    public function store($data)
    {
        $images=null;
        if(isset($data['image'])){
            $images = $data['image'];
            unset($data['image']);
        }
        $data['user_id'] = Auth::id();
        $data['ticket_status_id'] = 1;

        $ticket = Ticket::create($data);

        if(!$ticket){
            return "Formulář se nepodařilo uložit";
        }

        if($images) {
            foreach ($images as $image) {
                $path = $image->store('public/images/tickets');
                $path = str_replace('public/','storage/',$path);
                $newImage = Images::create(['path' => $path, 'ticket_id' => $ticket->id]);
                if (!$newImage) {
                    return "Obrázek se nepodařilo uložit";
                }
            }
        }


        return null;

    }

    public function addComment($data,$ticket): ?string
    {
        $data['user_id'] = Auth::id();
        $data['ticket_id'] = $ticket->id;

        $message = null;

        $comment = TicketComments::create($data);
        if(!$comment){
            $message = 'Komentář se nepodařilo přidat';
        }

        return $message;


    }


    public function addImage($data,$ticket){


        $images=null;
        if(isset($data['image'])){
            $images = $data['image'];
            unset($data['image']);
        }

        $data['user_id'] = Auth::id();
        $data['ticket_id'] = $ticket->id;
        $message = null;

        if($images){
            foreach ($images as $image) {
                $path = $image->store('public/images/tickets');
                $path = str_replace('public/','storage/',$path);
                $newImage = Images::create(['path' => $path, 'ticket_id' => $ticket->id]);
                if (!$newImage) {
                    $message = "Obrázek se nepodařilo uložit";
                }
            }
        }



        return $message;
    }

}
