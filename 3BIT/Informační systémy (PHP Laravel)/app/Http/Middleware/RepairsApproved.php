<?php

namespace App\Http\Middleware;


use App\Models\Repairs;
use Closure;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class RepairsApproved
{
    /**
     * Handle an incoming request.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \Closure(\Illuminate\Http\Request): (\Illuminate\Http\Response|\Illuminate\Http\RedirectResponse)  $next
     * @return \Illuminate\Http\Response|\Illuminate\Http\RedirectResponse
     */
    public function handle(Request $request, Closure $next)
    {
        $user_id = Auth::id();
        $is_repairs = !empty(Repairs::where('user_id',$user_id)->where('approved','1')->get()->toArray());

        if($is_repairs){
            return $next($request);
        }
        return redirect(route("profile.index"));
    }
}
