# Tvorba uživatelských rozhraní

## Autoři 
Vladislav Khrisanov xkhris00  
Denis Karev xkarev00  
Vladislav Mikhed xmikhe00   

# Instalace
Musí být nainstalováno PHP a Composer a MySql.
Do souboru env přidejte své přihlašovací jméno, heslo z databáze a jméno databáze.

Vytvořte nový projekt larovel
```bash
composer create-project laravel/laravel example-app
```
Zkopírujte odevzdane soubory do vytvořeného projektu  

Spustit příkaz k instalaci modulů
```bash
npm install
```
Vytváří tabulky v databázi
```bash
php artisan migrate
```

Pak spusťte následující příkazy pro instalaci knihoven
```bash
composer require livewire/livewire
```
```bash
composer require blade-ui-kit/blade-icons
```
```bash
composer require blade-ui-kit/blade-heroicons
```
```bash
npm install -D tailwindcss
```
```bash
npx tailwindcss init
```

## Spuštění projektu

```bash
npm run dev
```

```bash
php artisan serve
```

## Přihlášení do aplikace
Můžete použít následující email a heslo   
email: 1@user.cz  
password: 123    
  
email: 2@user.cz   
password: 123  
  
email: 3@user.cz  
password: 123  
