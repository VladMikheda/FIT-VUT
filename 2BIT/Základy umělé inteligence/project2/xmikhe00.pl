% Zadání č. 8:
% Napište program řešící úkol daný predikátem u8(LIN,VIN), kde LIN je vstupní
% číselný seznam s nejméně dvěma prvky a VIN je vstupní proměnná, jejíž
% hodnotou musí být kladné číslo. Predikát je pravdivý (má hodnotu true), pokud
% absolutní hodnoty rozdílů mezi všemi sousedními čísly v seznamu LIN jsou menší
% než číslo v proměnné VIN, jinak je predikát nepravdivý (má hodnotu false).

% Testovací predikáty:
u8_1:- u8([5,6.2,4,2.1,-1,1],4).                         %  true
u8_2:- u8([5,-6.2,4,2,-1,1],3).                          %  false
u8_3:- u8([5.1,6,4,2,-1,1.2],2).                         %  false
u8_r:- write('Zadej LIN: '),read(LIN),
       write('Zadej VIN: '),read(VIN),
       u8(LIN,VIN).

u8(LIN,VIN):- unew(LIN,VIN).
unew([H1,H2|T],VIN) :- unew([H2|T],VIN), N is H1 - H2, myabs(N,N1),N1 < VIN,!. 
unew([_],_) :- !.
myabs(X,N1) :- X < 0, N1 is -X,!. 
myabs(X,N1) :- X > 0, N1 is X,!.
myabs(0,0) :- !.
