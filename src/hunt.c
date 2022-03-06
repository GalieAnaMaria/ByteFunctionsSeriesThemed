//Gâlie Ana-Maria 312CD

#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
    * The spell is 16 bits and they are in the memory exactly after 5
    * consecutive bits of 1:
    *
    *            high                                             low
    *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
    *                    |----16bits---|
    *                          Spell
    *
    * There is only 1 group of 5 consecutive bits of 1 and the other groups
    * have less than consecutive bits of 1
    * Steps:
    * - find 5 consecutive bits of 1
    * - the NEXT 16 bits == spell
    */

    uint16_t res = -1;
    
    int bit;
    int bitspell;
    long long int spell=0;
    long long int indexspell;
    int countspell=0;
    int contbit1=0;

    for(int i=0;i<64;i++){
    
        bit=memory%2;

        if(bit==1)contbit1++;
        else contbit1=0;

        if(contbit1==5){
            
            indexspell=memory>>1;
            
            for(int j=0;j<16;j++){

                bitspell=indexspell%2;
                
                if(bitspell==1){

                    spell=(1<<countspell)|spell;     
                }
                
            countspell++;
            indexspell=indexspell>>1;       
            }  
        
        }
        memory=memory>>1;
    }   
    res=(uint16_t)spell;
    
    
    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
    * The key is 16 bits and they are in the memory exactly before 3
    * consecutive bits of 1:
    *
    *                high                                           low
    *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
    *                                    |----16bits---|
    *                                           Key
    * Steps:
    * - find 3 consecutive bits of 1
    * - the PREVIOUS 16 bits == key
    */

    uint16_t res = -1;
    
    int bit;
    int bitspell;
    long long int spell=0;
    int countspell=0;
    int contbit=0;
    long long int keycopy;
    int pointerindex;

    keycopy=memory;

    for(int i=0;i<64;i++){

        bit=keycopy%2;

        if(bit==1)contbit++;
        else contbit=0;

        if(contbit==3){
            pointerindex=i;
            break;
        }
        keycopy=keycopy>>1;
    }

    memory=memory>>(pointerindex-18);

    for(int j=0;j<16;j++){

        bitspell=memory%2;

        if(bitspell==1){

            spell=(1<<countspell)|spell; 
        }
        countspell++;
        memory=memory>>1;
    }

    res=(uint16_t)spell;
    
    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
    * Find the spell knowing that
    * spell_encrypted = spell_plaintext ^ key
    */

    uint16_t res = -1;

    long long int decryptedspell;
    
    decryptedspell=spell^key;

    res=(uint16_t)decryptedspell;


    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
    * Help Geralt construct a sword that will give him an advantage in battle.
    * The steps we will follow:
    * - choose the corect sword
    * - brand the sword with the correct runes such that the equation
    * for that specific enemy type is true
    *
    * How does the sword look (Sword template):
    *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
    *  -------- --------------------- --------------------------------
    *     Type    Does not matter      The "Value" such that the equation
    *                               from 2 holds depending on the enemy type
    *    4 bits      12 bits                     16 bits
    *
    * 1. Type of the sword:
    * - 1001 - Silver Sword - for monsters
    * - 0110 - Steel Sword - for humans
    *
    *  If the number of active bits from variable "enemy" is even == Monster
    *  else == Human
    *
    * 2.
    * Monster Equation:
    *    Value ^ (Enemy & (1 - Enemy)) = 0
    *
    * Human Equation:
    *    Value + {Enemy} = 0
    */

    uint32_t res = -1;

    int bit;
    int ContorBitsActivi=0;
    uint16_t enemyclone;
    uint16_t value;

    enemyclone=enemy;

    for(int i=0;i<16;i++){
        bit=enemyclone%2;

        if(bit==1)ContorBitsActivi++;

        enemyclone=enemyclone>>1;
    }

    if(ContorBitsActivi%2==0){
        value=0^(enemy&(1-enemy));
        res=value|(9<<28);
    }
    else{
        value=-enemy;
        res=value|(6<<28);
    }


    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
    * To become a witcher one must survive a cocktail of different
    * herbs. The body should generate the correct antibodies to
    * neutralize the given cocktail.
    *
    *
    * The antibodies need to respect the following properties:
    *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
    *   antibodies_low & antibodies_high = 0
    *   antibodies_low | antibodies_high = cocktail
    *
    * Where:
    *  [][][]...[][][] | [][][]...[][][]
    *  ---------------   ---------------
    *  antibodies_high    antibodies_low
    *      16 bits           16 bits
    *      -------------------------
    *              antibodies
    */

    uint32_t res = -1;

    res=cocktail<<16;

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
    * For the next trail, the candidate is tied up and blindfolded.
    * They are also taken to a forest and they should return until
    * the next morning.
    *
    * The candidate knows that there are 4 possibilities for the forest:
    * Brokilon, Hindar, Wolven Glade and Caed Dhu.
    *
    * The candidate also knows those forests by heart, but first you
    * need to identify the forest.
    *
    * The characteristics for 3 of the forests are as follows:
    * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
    *   Ex: a group of 4 trees: "...00111100..."
    * - Hindar - has ONLY 2 trees in the MIDDLE
    * - Wolven Glade - FULL of trees
    *
    * The "map" variable encodes the following information:
    * - 1 tree
    * - 0 patch of grass
    *
    * You should put in the "res" variable the index for the identified
    * forrest.
    * - Brokilon - index 0
    * - Hindar - index 1
    * - Wolven Glade - index 2
    * - Caed Dhu - index 3
    */

    uint8_t res = -1;

    signed int index=-1; 
    int bittrees;
    int trees=0;
    int cont2trees=0;
    int contBrokilon=0;
    int bitBrokilon;
    unsigned long long int copymap,copymap2;

    copymap=map;
    copymap2=map;

    for(int i=0;i<64;i++){

        bittrees = copymap%2;

        if(bittrees==1)trees++;

        copymap=copymap>>1;
    }


    switch(trees)
    {
        case 0:
           index=0;
            break;

        case 2:
            copymap2=copymap2>>31;

            if(copymap2%2==1)cont2trees++;
            copymap2=copymap2>>1;
            
            if(copymap2%2==1)cont2trees++;

            if(cont2trees==2)index=1;
            break;

        case 64:
            index=2;
            break;

        default:
            //do nothing;
            break;
    }

    if(index==-1){
        for(int i=0;i<64;i++){

        bitBrokilon=map%2;

        if(bitBrokilon==1)contBrokilon++;
        else contBrokilon=0;

        if(contBrokilon==4)index=0;
        else if(contBrokilon==5){
            index=-1;
            break;
        }

        map=map>>1;
        }
    }
    if(index==-1)index=3;

    res=index;

    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
    * For this final trial, the candidates go into a trance and when
    * they woke up they would be a fully fledged witcher.
    *
    * For this task, you need to help the witcher find the number
    * of steps that would take the candidate from the dream realm to
    * the real world.
    *
    * The "map" variable would have only 2 bits of 1:
    * - candidate location
    * - portal location
    *
    * You should put in the "res" variable the distance from the
    * candidate position to the portal.
    *
    *  Ex:
    *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
    *
    *  res = 5
    */

    uint8_t res = -1;

    int bitToCandidate;
    int bitToPortal;
    int steps;

    for(int i=0;i<32;i++){
        bitToCandidate=map%2;

        if(bitToCandidate==1){

            for(int j=i;j<32;j++){

                bitToPortal=map%2;

                if(bitToPortal==1){
                    steps=j-i;
                    res=steps;
                }
                map=map>>1;
            }

        }
        map=map>>1;
    }

    return res;
}
