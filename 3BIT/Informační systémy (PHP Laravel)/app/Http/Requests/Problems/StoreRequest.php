<?php

namespace App\Http\Requests\Problems;

use Illuminate\Foundation\Http\FormRequest;

class StoreRequest extends FormRequest
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
            'title' => 'required|max:255|string',
            'address'  => 'required|max:255|string',
            'description' => 'required|max:10000',
            'manager_id' => 'required|int',
            'image.*'  => 'nullable|image|mimes:jpeg,jpg,png,bmp,gif,svg|max:20000',
        ];
    }
}
