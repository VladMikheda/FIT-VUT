<?php

namespace App\Http\Requests\Registration;

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
            'name' => 'required|max:255|string',
            'lastname'  => 'required|max:255|string',
            'email' => 'required|max:255|email:rfc|unique:App\Models\User,email',
            'password' => 'required|max:255|confirmed',
            'birthday'  => 'nullable|date|date_format:Y-m-d',
            'phone'  => 'nullable|digits_between:0,15|unique:App\Models\User,phone'
        ];
    }
}
