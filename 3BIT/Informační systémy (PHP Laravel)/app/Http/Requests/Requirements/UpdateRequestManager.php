<?php

namespace App\Http\Requests\Requirements;

use Illuminate\Foundation\Http\FormRequest;

class UpdateRequestManager extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     *
     * @return bool
     */
    public function authorize()
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array<string, mixed>
     */
    public function rules()
    {
        return [
            'title' => 'nullable|max:255|string',
            'description' => 'nullable|max:10000',
            'address'  => 'nullable|max:255|string',
            'repair_id' => 'nullable|integer',
            'requirement_status_id' => 'nullable|integer',
        ];
    }
}
