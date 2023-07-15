<?php

namespace App\Http\Controllers\Requirements\Manager;

use App\Http\Controllers\Controller;
use App\Http\Requests\Requirements\AddCommentRequest;
use App\Http\Requests\Requirements\FilterRequest;
use App\Http\Requests\Requirements\UpdateRequestManager;
use App\Models\Problems;
use App\Models\Repairs;
use App\Models\Managers;
use App\Models\Requirements;
use App\Models\RequirementStatuses;
use App\Models\User;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;
use App\Http\Requests\Requirements\StoreRequest;

class RequirementController extends BaseController
{
    public function index(FilterRequest $request)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $reqs = DB::table('requirements')
            ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
            ->select('requirements.id', 'name', 'title', 'requirement_status_id')
            ->where('requirement_status_id', '!=', 3)
            ->paginate(10);

        if (isset($data['title'])) {
            $reqs = DB::table('requirements')
                ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
                ->select('requirements.id', 'name', 'title', 'requirement_status_id')
                ->where('title', 'like', "%{$data['title']}%")
                ->where('requirement_status_id', '!=', 3)
                ->paginate(10);
        }

        return view('requirements.manager.index', compact('reqs'));
    }

    public function indexOld(FilterRequest $request)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $reqs = DB::table('requirements')
            ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
            ->select('requirements.id', 'name', 'title', 'requirement_status_id')
            ->where('requirement_status_id', '=', 3)
            ->paginate(10);

        if (isset($data['title'])) {
            $reqs = DB::table('requirements')
                ->leftJoin('requirement_statuses', 'requirements.requirement_status_id', 'requirement_statuses.id')
                ->select('requirements.id', 'name', 'title', 'requirement_status_id')
                ->where('title', 'like', "%{$data['title']}%")
                ->where('requirement_status_id', '=', 3)
                ->paginate(10);
        }

        $old = true;
        return view('requirements.manager.index', compact('reqs', 'old'));
    }

    public function create()
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $problems = Problems::all();
        $technicians = DB::table('repairs')
            ->join('users', 'user_id', '=', 'users.id')
            ->select('repairs.id', 'users.name', 'users.lastname')
            ->get();

        return view('requirements.manager.create', compact('technicians', 'problems'));
    }

    public function store(StoreRequest $request)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $message = $this->service->store($data);

        if ($message) {
            return redirect(route('manager.requirements.create'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect((route('profile.manager')));
    }

    public function show($id)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $requirement = Requirements::find($id);
        if (!$requirement) {
            return redirect(route('profile.index'));
        }

        $comments = $requirement->requirementComment()->paginate(10);

        $status = RequirementStatuses::find($requirement->requirement_status_id);

        $technician = Repairs::find($requirement->repair_id);
        $names = User::find($technician->user_id);

        return view('requirements.manager.show', compact('requirement', 'status', 'comments', 'names'));
    }

    public function addComment(AddCommentRequest $request, Requirements $requirement)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $data = $request->validated();

        $message = $this->service->addComment($data, $requirement);

        if (!$message) {
            return redirect(route('manager.requirements.show', $requirement->id))->withErrors([
                'content' => $message,
            ]);
        }

        return redirect(route('manager.requirements.show', $requirement->id));
    }

    public function edit($id)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $requirement = Requirements::find($id);
        if (!$requirement) {
            return redirect(route('profile.index'));
        }

        $technicians = DB::table('repairs')
            ->join('users', 'user_id', '=', 'users.id')
            ->select('repairs.id', 'users.name', 'users.lastname')
            ->get();

        return view('requirements.manager.edit', compact('requirement', 'technicians'));
    }

    public function update(UpdateRequestManager $request, Requirements $requirement)
    {
        $manager = DB::table('managers')->where('user_id', '=', Auth::id())->first();

        if(!$manager) {
            return redirect(route('profile.index'));
        }

        $data = $request->validated();
        $message = $this->service->updateManager($data, $requirement->id);

        if ($message) {
            return redirect(route('manager.requirements.create'))->withErrors([
                'formError' => $message,
            ]);
        }

        return redirect((route('manager.requirements.show', $requirement->id)));
    }
}


