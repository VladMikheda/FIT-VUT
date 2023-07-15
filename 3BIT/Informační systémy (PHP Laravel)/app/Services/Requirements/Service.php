<?php

namespace App\Services\Requirements;

use App\Models\Problems;
use App\Models\Repairs;
use App\Models\RequirementComments;
use App\Models\Requirements;
use App\Models\RequirementStatuses;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class Service
{
    public function index($repair)
    {
        return $repair->requirements()->paginate(10);
    }

    public function addComment($data,$requirement): ?string
    {
        $data['user_id'] = Auth::id();
        $data['requirement_id'] = $requirement->id;

        $message = null;

        $comment = RequirementComments::create($data);
        if(!$comment){
            $message = 'Komentář se nepodařilo přidat';
        }

        return $message;

    }

    public function store($data)
    {
        $data['requirement_status_id'] = 1;
        $problemInfo = Problems::find($data['problem_id']);
        $data['description'] = $problemInfo->description;
        $data['title'] = $problemInfo->title;
        $data['address'] = $problemInfo->address;

        $requirement = Requirements::create($data);

        if(!$requirement){
            return "Formulář se nepodařilo uložit";
        }

        return null;
    }

    public function updateManager($data, $id)
    {
        $requirement = Requirements::find($id);

        if(isset($data['title'])){
            $requirement->title = $data['title'];
        }
        if(isset($data['description'])){
            $requirement->description = $data['description'];
        }
        if(isset($data['address'])){
            $requirement->address = $data['address'];
        }
        if(isset($data['problem_id'])){
            $requirement->problem_id = $data['problem_id'];
        }
        if(isset($data['repair_id'])){
            $requirement->repair_id = $data['repair_id'];
        }
        if(isset($data['requirement_status_id'])){
            $requirement->requirement_status_id = $data['requirement_status_id'];
        }

        $requirement->save();

        return null;
    }

    public function updateTechnician($data, $id)
    {
        $requirement = Requirements::find($id);

        if(isset($data['estimated_time'])){
            $requirement->estimated_time = $data['estimated_time'];
        }
        if(isset($data['price'])){
            $requirement->price = $data['price'];
        }
        if(isset($data['requirement_status_id'])){
            $requirement->requirement_status_id = $data['requirement_status_id'];
        }

        $requirement->save();

        return null;
    }

}
