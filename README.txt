Gâlie Ana-Maria 312CD

Part 1 -Bits & Pieces

Task 1 - Bit by Bit

->get_bit:
Folosim o masca ca sa obtinem bitul al i-lea. Verificam daca e active.

->flip_bit:
Folosim operatia XOR pe biti intre numar si 1 shiftat de i-ori.

->activate_bit:
Fol o variabila care ia valoarea lui nr shiftat de (i-1) ori. 
Verificam daca este active s-au nu. Daca nu il activam.
 Reversam shiftarea si o facem cu (i-1) la stanga si facem 
operatia OR pentru a crea numarul nou cu al i-lea bit activat. 
(daca bit-ul era deja 1 va trimite numarul original).

->clear_bit:
Folosim un numar intermediar reprezentat de 1 shiftat pana pe 
pozitia i si folosim operatia de negare pe intermediar 
(pentru ca 1 este elementrul neutru pentru AND logic). 
Aplicam AND logic ca sa transformam al i-lea bit in 0.

Task 2 - One Gate to Rule Them All

->and_gate/not_gate/or_gate/xor_gate:
Am folosit poarta NAND sa implementez portile cerute, 
luand pe rand fiecare nivel/ramura din circuite. 
Rezultatele portilor de inceput sunt conectate prin NAND-uri 
in continuare intre ele pana se ajunge la output-ul care 
ar fi fost oferit cu portile originale (AND,OR,NOT,XOR).

Task 3 - Just Carry the Bit
->full_adder:
Implementam full-adder-ul folosind gate-urile anterioare 
(care au fost implementate deja cu NAND) ca 
sa ofere output-ul droit (suma si carry). 
Pentru ca putem trimite doar o variabila prin functie am codat
 suma si carry intr-un numar int usor de decodificat in functia 
urmatoare (suma este pe a doua pozitie si carry este pe prima).

->ripple_carry_adder
Luam bitii pe rand ai fiecarui numar impreuna cu 
valoarea de default a lui carry (0) si folosim full_adder
 sa obtinem res care il decodam pentru a afla suma si carry.
 Verificam valorile lui carry si suma.
Carry o sa-l dam mai departe in noua apelare a functiei 
full_adder iar acesta va influenta si suma viitoare. 
Astfel contruim noul numar format prin suma pe biti.
Conditia de overflow va fi ca carry sa nu fie 1 cand ajungem la al 64-lea bit din numere

Part 2 – Shut up Morty!

Task 1 - The Beginning

Folosim in FIECARE functie un vector pentru alfabet pentru a avea un 
“database” util pentru codificare si decodificarea mesajelor.
(ne referim la pozitiile din vector al literelor -1)

->send_byte_message:
Cautam fiecare litera din mesaj in vectorul de alfabet si
 trimitem pozitia literelor -1 ca sa codam mesajul si trimitem fiecare caracter.

->recv_byte_message:
Folosim o variabila de “stocare” ca sa preluam mesajul codat si trimitem 
caracterul corespunzator cu pozitia (cod-1) din vectorul de alfabet

->comm_byte:
Primim caracterul si il trimitem de doua ori. Se repeta pasii.

Task 2 - Waiting for the Message
->send_message:
Trimitem lungimea codata shiftand-o 2 biti la stanga pentru a 
intra in zona de biti “important”
Encodam mesajul “hellothere” cum am facut si la task-urile anterioare

->recv_message:
Decodam lungimea shiftand-o 2 biti si fol &15 (de forma binara 1111) 
pentru a obtine doar primii 4 biti care ne intereseaza. 
Decodam mesajul ca in functiile anterioare.

->comm_message:
Decodam lungimea ca in functia recv_message.
Testam daca ultima litera primita prin mesaj este P si
 folosim un contor pe post de “semnalator”(1 pentru PICKLERICK 0 pentru VINDICATOR). 
Encodam lungimile mesajelor PICKLERICK si VINDICATORS (10 si 12) folosind operatii pe biti. 
In functie de valoarea lui cont trimitem mesajul codat ca in functiile anterioare

Task 3 - In the Zone

->send_squanch2:
Folosim masti ca sa aflam bitii de pe pozitiile care ne intereseaza fara sa 
distrugem numarul original. In functie de valoare bitilor folosim un contor in asa fel 
incat sa tinem evidenta la modifcarile care sa le facem in timpul “merge” ului bitilor

->decode_squanch2:
Facem procesul invers celui de la send_squanch2. C1 il mutam cu 4 biti 
la stanga si il concatenam cu C2 prim OR si cream noul numar 

Part 3 – Toss a coin to your witcher

Task 1 – Axii

->find_spell:
Luam memory de la stanga la dreapta si analizam bit cu bit. 
Tinem evidenta cu un contor aparitiile lui 1. Daca urmatorul bit 
este 0 dupa o secventa mai mica de 5 de 1 contorul se reseteaza si analiza reincepe.
In momentul cand contorul se face 5 incepe crearea “spell”-ului format din urmatorii 16 biti.

->find_key:
Analizam memory in momentul in care gasim o secventa de 
3 de 1 memoram indexul unde se termina secventa. Shiftam memory cu index-18 ori 
(cele 16 biti din cheie plus 2 biti din secventa). 
Dupa shiftare luam bit cu bit de la prima pozitie si construim spell-ul

->decrypt_spell:
In operatia pe biti XOR operatorii din ecuatie pot fi schimbati 
in orice directive pentru ca a^b=c si c^a=b si c^b=a

Task 2 - Sword Play
->choose_sword:
Verificam daca numarul de biti activi sunt pari sau impari si 
determinam ce tip de enemy avem. (luam bit cu bit si folosim un contor). 
Pentru fiecare inamic folosim formula data si folosim SAU cu sabia 
potrivita dusa pe ultimele 4 biti (ignorand bitii din mijloc)


Task 3 - The Witcher Trials

->trial_of_the_grasses

Rezolvam ecuatiile date.

(antibodies_high&cocktail)^0=(antibodies_low|cocktail)

Pentru ca antibodies_low&antibodies_high=0: 

antibodies_low= (negat de)antibodies_high sau antibodies_low=0 sau antibodies_high=0

antibodies_low|antibodies_high=cocktail (inlocuim in prima formula)

(antibodies_high&(antibodies_low|antibodies_high))^0=antibodies_low(antibodies_low|antibodies_high)

Si pentru antibodies_low=(negat de) antibodies_high sau antibodies_low=0 

ajungem la ->> cocktail^0=antibodies_high =>
 antibodies_high nu poate sa fie 0 pentru ca (antibodies_high&cocktail)=0 => 
0^0=(antibodies_low|cocktail) (eroare)

Doar antibodies_low poate sa fie 0 ca antibodies_low|antibodies_high=cocktail (ADEVARAT)

Concluzia putem shifta pur si simplua cocktail cu 16 biti la stanga pentru ca antibodse_high=cocktail

->trial_of_forrest_eyes
Numaram cantitatea de biti 1 (copaci).
Ne ocupam de cazurile Brokilon, Hindar si Wolven Glade
Pentru Hindar verificam daca sunt 2 copaci consecutive (care tot timpul o sa fie in mijlocul la cei 64 biti)
Verificam Brokilon acum pentru grupuri de 4 copaci consecutive izolati.
Cu un contor verficam adiacenta copacilor. Cand gasim 4 copaci consecutive index-ul 
se schimba dar daca contorul creste din nou la 5 copaci consecutive se reseteaza si 
incepe cautarea secventei in continuare.
Daca index =-1 avem padurea Caed Dhu

->trial_of_the_dreams
Gasesc prima aparitie a lui 1 si incep numaratoare folosind j cand gasesc al
 doilea 1 (portalul) distanta va fi j-i (lungimea lui i si j incepe de la 0,j>i)
