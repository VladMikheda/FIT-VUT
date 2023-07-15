<?php

namespace App\Http\Controllers\Requirements\Technician;

use App\Http\Controllers\Controller;
use App\Http\Requests\Requirements\AddCommentRequest;
use App\Http\Requests\Requirements\FilterRequest;
use App\Http\Requests\Requirements\UpdateRequestTechnician;
use App\Models\Requirements;
use App\Models\RequirementStatuses;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;
use App\Models\Repairs;


class RequirementController extends BaseController
{
    public function index(FilterRequest $request)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $reqs = Repairs::find($technician->id)
                 ->requirements()
                 ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
                 ->select('requirements.id', 'name', 'title', 'requirement_status_id')
                 ->paginate(10);

        if (isset($data['title'])) {
            $reqs = Repairs::find($technician->id)
                ->requirements()
                ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
                ->select('requirements.id', 'name', 'title', 'requirement_status_id')
                ->where('title', 'like', "%{$data['title']}%")
                ->paginate(10);
        }

        return view('requirements.technician.index', compact('reqs'));
    }

    public function indexOld(FilterRequest $request)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $reqs = Repairs::find($technician->id)
            ->requirements()
            ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
            ->select('requirements.id', 'name', 'title', 'requirement_status_id')
            ->paginate(10);

        if (isset($data['title'])) {
            $reqs = Repairs::find($technician->id)
                ->requirements()
                ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
                ->select('requirements.id', 'name', 'title', 'requirement_status_id')
                ->where('title', 'like', "%{$data['title']}%")
                ->paginate(10);
        }

        return view('requirements.technician.index_old', compact('reqs'));
    }

    public function show($id)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $requirement = Requirements::find($id);

        if(!$requirement) {
            return redirect(route('profile.index'));
        }

        if($requirement->repair_id != $technician->id){
            return redirect(route('profile.index'));
        }

        $comments = $requirement->requirementComment()->paginate(5);

        $status = RequirementStatuses::find($requirement->requirement_status_id);

        return view('requirements.technician.show',compact('requirement','status','comments'));
    }

    public function addComment(AddCommentRequest $request, Requirements $requirement)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $message = $this->service->addComment($data,$requirement);

        if(!$message){
            return redirect(route('technician.requirements.show',$requirement->id))->withErrors([
                'content' => $message,
            ]);
        }

        return redirect(route('technician.requirements.show',$requirement->id));
    }

    public function edit($id)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $requirement = Requirements::find($id);

        if(!$requirement) {
            return redirect(route('profile.index'));
        }

        if($requirement->repair_id != $technician->id){
            return redirect(route('profile.index'));
        }

        return view('requirements.technician.edit',compact('requirement'));
    }

    public function update(UpdateRequestTechnician $request, Requirements $requirement)
    {
        $technician = DB::table('repairs')->where('user_id', '=', Auth::id())->first();

        if(!$technician){
            return redirect(route('profile.index'));
        }

        $data = $request->validated();
        $message = $this->service->updateTechnician($data, $requirement->id);

        if ($message) {
            return redirect(route('requirements.technician.create'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect((route('technician.requirements.show', $requirement->id)));
    }
}
