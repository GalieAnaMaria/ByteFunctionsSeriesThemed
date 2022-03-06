//Gâlie Ana-Maria 312CD

#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;
    int active;
    int NriBit;

    NriBit = 1<<(i-1);
    active = nr & NriBit;
    active = active>>(i-1);

    if(active%2==0)res=0;
    else res=1;

    /* TODO
    *
    * "res" should be 1 if the bit is active, else 0
    */

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    //unsigned long Nribit;
    //unsigned long NrBitFlipped;
    
    nr=nr^(1<<i);
    res = nr; 

    /* TODO
    *
    * Return the "nr" with the ith bit flipped
    */

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;
    
    int NrCopie;
    int NrCutToi;
    int NrIntermediar;

    NrCopie = nr;

    NrCutToi = nr>>(i-1);

    if(NrCutToi%2==0)NrCutToi = NrCutToi+1;
    
    NrIntermediar = NrCutToi<<(i-1);
    
    res =  NrCopie|NrIntermediar;

    /* TODO
    *
    * Return the "nr" with the ith bit "1"
    */

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    int NrNou;
    int NrIntermediar;

    NrIntermediar = 1<<i;

    NrNou= nr &~(NrIntermediar);
    
    res =  NrNou;

    /* TODO
    *
    * Return the "nr" with the ith bit "0"
    */

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    int Ramura1,RamuraFinal;

    Ramura1 = nand_gate(a,b);
    RamuraFinal = nand_gate(Ramura1,Ramura1);

    res = RamuraFinal;

    /* TODO - Use the nand gate to implement the and gate */

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    int Ramura1;

    Ramura1= nand_gate(a,a);
    
    res = Ramura1;

    /* TODO - Use the nand gate to implement the not gate */

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;
    int RamuraNotA,RamuraNotB,RamuraFinal;

    RamuraNotA = nand_gate(a,a);
    RamuraNotB = nand_gate(b,b);
    RamuraFinal = nand_gate(RamuraNotA,RamuraNotB);
    res = RamuraFinal;

    /* TODO - Use the previously defined gates to implement the or gate */

    return res;
}

uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;
    int RamuraNotA,RamuraNotB,Ramura1,Ramura2,RamuraFinal;

    RamuraNotA = nand_gate(a,a);
    RamuraNotB = nand_gate(b,b);

    Ramura1= nand_gate(a,RamuraNotB);
    Ramura2= nand_gate(RamuraNotA,b);

    RamuraFinal = nand_gate(Ramura1,Ramura2);

    res = RamuraFinal;

    /* TODO - Use the previously defined gates to implement the xor gate */

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;
     
    int sum;
    int xor1,xor2,And1,And2;
    int Carry;
    
    xor1 = xor_gate(a,c);
    And1 = and_gate(a,c);

    xor2 = xor_gate(xor1,b);
    And2 = and_gate(xor1,b);

    sum = xor2;
    Carry = or_gate(And2,And1);

    if((sum==0)&&(Carry==0)) res=100;
    else if((sum==1)&&(Carry==1))res=111;
    else if((sum==1)&&(Carry==0)) res=110;
    else if((sum==0)&&(Carry==1))res=101;

    /* TODO - implement the full_adder using the previous gates
    * Since the full_adder needs to provide 2 results, you should
    * encode the sum bit and the carry bit in one byte - you can encode
    * it in whatever way you like
    */

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;
   
    uint8_t bitA , bitB;
    int index;
    int decoder=0;
    uint8_t carry=0;
    int suma=0;
    uint64_t sumafinala=0;

    for(int i=0;i<64;i++){

        bitA = a%2;

        a=a>>1;

        bitB = b%2;

        b=b>>1;

        decoder = full_adder(bitA,bitB,carry);

        if(decoder%10==0)carry=0;
        else carry=1;

        decoder= decoder/10;

        if(decoder%10==0)suma=0;
        else {
            suma=1;
            index=i;
        }

        if((index==63)&&(carry==1)){
            res=0;
            return res;
        }

        sumafinala=sumafinala|(suma<<i);
    }

    res=sumafinala;

    return res;

    /* TODO
    * Use the full_adder to implement the ripple carry adder
    * If there is ANY overflow while adding "a" and "b" then the
    * result should be 0
    */

}