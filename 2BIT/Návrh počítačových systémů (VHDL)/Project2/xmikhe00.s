; Vernamova sifra na architekture DLX
; jmeno prijmeni login

        .data 0x04          ; zacatek data segmentu v pameti
login:  .asciiz "xmikhe00"  ; <-- nahradte vasim loginem
cipher: .space 9 ; sem ukladejte sifrovane znaky (za posledni nezapomente dat 0)

        .align 2            ; dale zarovnavej na ctverice (2^2) bajtu
laddr:  .word login         ; 4B adresa vstupniho textu (pro vypis)
caddr:  .word cipher        ; 4B adresa sifrovaneho retezce (pro vypis)

        .text 0x40          ; adresa zacatku programu v pameti
        .global main        ; 

main:   ; sem doplnte reseni Vernamovy sifry dle specifikace v zadani

	addi r5, r0, 13		; r5 <- m (13)angl abceda
	addi r6, r0, 9  	; r6 <- i (9) angl abceda 	
;nop
  	sub r6,r0,r6  		; r6 <- 0 - r6 protoze musime odcitat proto budeme pricitat zaporne cilo
  	add r26,r0,r0 		; r26 <- 0
  	add r22,r0,r0 		; r22 <- 0
  	add r27,r0,r0 		;
  	j do
	nop
	nop

m96:
  	subi r27,r26,96         ; r27 <- r26 - 96 odecteme od hodnoty 96 protoze je mensi
  	addi r26,r27,122  	; pridame k rozdilu 122 rozdil je zaporny
  	j zp
	nop
	nop
 
b122:
  	subi r27,r26,122	; odecteme od hodnoty 122 protoze je vetsi
  	addi  r26,r27,96     	; 96 je "a" pridame rozdil  
  	j zp    
	nop
	nop

do:
  	lb r26, login(r22)      ; r26 <- login[0]
  	addi r27,r0,97    	; r27 <-97 nejmensi hodnota ktera muzebyt 
  	sgt r27,r27,r26         ; if(r27 > r26) r27 <- 1 else r27 <-0
  	bnez r27,enddo          ; kdyz r26 je mensi 97 skoc na enddo (neni pismeno)
	nop
	nop
  	add r26,r26,r5          ; r26 <-  r26 + r5 pismeno + klic
  	sgti r27 ,r26,122       ; if(r26 > 122) r26 <- 1 else r26 <-0
  	bnez r27,b122           ; kdyz hodnota vetsi 122 skoc na b122 protoze 122 je maximalni hodnota
	nop
	nop
  	slei r27, r26,96
  	bnez r27,m96        	; kdyz hodnota je mensi nez 96 skoc na m96
	nop
	nop

zp:
  	sb cipher(r22),r26   	; vlozime hodnotu v retezec
  	addi r22,r22,1  	; zvetsime slider o 1
  	add r27,r0,r5   	; zmena hodnot registru
  	add r5,r0,r6    	; r5 <- r6
  	add r6,r0,r27    	; r6 <- r5 pro stridani
  	j do
	nop
	nop

enddo:
  	add r6,r0,r0
  	sb cipher(r22),r6 	; nahrame \0 konec retezcu

end:    addi r14, r0, caddr ; <-- pro vypis sifry nahradte laddr adresou caddr
        trap 5  ; vypis textoveho retezce (jeho adresa se ocekava v r14)
        trap 0  ; ukonceni simulace
