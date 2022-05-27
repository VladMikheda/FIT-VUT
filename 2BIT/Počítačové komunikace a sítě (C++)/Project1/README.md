#IPK project

## Popis
Podle zadání byl udělán Http server který poskytuje informace o zařízení na kterém běží: název, název procesoru,
zátěž procesoru.

Projekt je implementován v jazyce C++ a byl vyzkoušen objektově orientovaný přístup,

Server je spuštěn na zadaném portu a běží v nekonečném cyklu, čeká na request a v závislosti od vyžádání odpoví.



## Překlad
Pro překlad spustíte make filé příkazem:
``
make
``
## Spuštění
```
$ ./hinfosvc 
```
**Port** je nutným argumentem a může být v rozhraní od 1 do 65535

## Využité
Pro komunikace s serverem je možné využít prohlížeč nebo konsolní aplikace pro zazílaní Get požadávku, například
- wget
- curl

Server podporuje **GET** a **HEAD** požadávky. Pro přijímání dát z serveru je nutno zaslat **GET** požadávek na url adres.

### Příklady vyžití
Pro příklady bude využít nástroj curl, IP adresem je local host a port je nastaven na 12345

#### Získání jména serveru
```
$ curl http://localhost:12345/hosname 
```
#### Získání modelu cpu serveru
```
$ curl http://localhost:12345/cpu-name
```
#### Získání zatíženi CPU
```
$ curl http://localhost:12345/load 
```