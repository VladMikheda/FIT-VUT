{{--
    Project: Volunteer System

    File: app.blade.php
    Subject: ITU 2022

    @author: Vladisalav Khrisanov(xkhris00)
--}}

{{--    layout setup and import--}}
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    @vite(['resources/css/app.css', 'resources/js/app.js'])
    <script defer src="https://unpkg.com/@alpinejs/intersect@3.x.x/dist/cdn.min.js"></script>

    <script defer src="https://unpkg.com/alpinejs@3.x.x/dist/cdn.min.js"></script>

    @livewireStyles
</head>
<body class="overscroll-none">
    @yield('content')
    @livewireScripts
</body>
</html>
