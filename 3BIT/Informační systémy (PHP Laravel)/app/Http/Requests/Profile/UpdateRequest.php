<?php

namespace App\Http\Requests\Profile;

use Illuminate\Foundation\Http\FormRequest;

class UpdateRequest extends FormRequest
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
            'name' => 'nullable|max:255|string',
            'lastname'  => 'nullable|max:255|string',
            'email' => 'nullable|max:255|email:rfc|unique:App\Models\User,email',
            'birthday'  => 'nullable|date|date_format:Y-m-d',
            'phone'  => 'nullable|digits_between:0,15|unique:App\Models\User,phone',
            'image'  => 'nullable|image|mimes:jpeg,jpg,png,bmp,gif,svg|max:20000',
        ];
    }
}
