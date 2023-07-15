<div>
    <label for="email"  class="m-1" >{{"Email".$slot}}</label>
    <input type="text" value="{{old('email')}}" name="email" class="< @error('email') border-2 border-red-500 @enderror  w-full p-2.5 rounded-lg shadow-inner focus:outline-blue-600 bg-gray-100 text-black" placeholder="@if(!empty($input)){{$input}}@else example@example.com @endif">
    @error('email')
    <div class="m-1 text-red-400 text-sm">{{$message}}</div>
    @enderror
</div>
