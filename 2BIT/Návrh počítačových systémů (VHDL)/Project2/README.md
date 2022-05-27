V jazyku symbolických instrukcí procesorové architektury DLX
a s využitím simulátoru OpenDLX tohoto procesoru napište program
realizující lehce modifikovaný, zjednodušený algoritmus Vernamovy
šifry. Vernamova šifra patří do kategorie substitučních šifer
a její princip pro potřeby tohoto projektu bude spočívat
v nahrazování každého písmene zprávy jiným písmenem, které je
v abecedě posunuto o hodnotu danou příslušným písmenem šifrovacího
klíče. Uvažujte zprávu tvořenou výhradně malými písmeny anglické
abecedy a-z a číslicemi 0-9. Šifrovací klíč o pevné délce dvou
znaků bude tvořen písmeny anglické abecedy a-z, které se
periodicky opakují přes jednotlivé znaky zprávy. Znaky budou pro
potřeby šifrování reprezentovány svými ASCII kódy. Šifrování bude
probíhat tak, že je zpráva čtena znak po znaku zleva doprava,
první znak klíče posouvá přečtený znak vpřed, druhý znak klíče
posouvá znak vzad. Pokud je přečtena číslice, je šifrování
ukončeno a jako výsledek je vypsán zašifrovaný text. Posouvání
znaků je cyklické, tj. vychází-li posuv před písmeno ‘a’ nebo za
písmeno ‘z’, pokračuje se z opačného konce abecedy – vizte příklad
níže. Jiné znaky na vstupu pro jednoduchost neuvažujte (nemusíte
je vzlášť ošetřovat). Lze tak např. určit, že pokud má načtený
znak ASCII hodnotu menší než 97 (tj. je před písmenem ‘a’), jedná
se o číslici, protože jiné znaky se neočekávají (číslice jsou
v ASCII tabulce před písmeny). Váš program musí být schopen dle
výše uvedených pravidel korektně šifrovat řetězce sestávající
z libovolné kombinace malých písmen anglické abecedy a číslic.
