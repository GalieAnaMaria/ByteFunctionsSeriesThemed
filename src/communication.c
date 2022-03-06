//Gâlie Ana-Maria 312CD

#include "communication.h"
#include "util_comm.h"

#include <stdio.h>

/* Task 1 - The Beginning */

void send_byte_message(void)
{
  char vcod[]={'A','B','C','D','E','F',
  'G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z'};
  char vmessage[]={'R','I','C','K'};
  
  for(int i=0;i<4;i++){
    for(int j=1;j<=26;j++){

      if(vmessage[i]==vcod[j-1]){
        send_squanch(j);
      }
    }
  }
  /* TODO
  * Send the encoding of the characters: R, I, C, K
  */
}


void recv_byte_message(void)
{
  char vcod[]={'A','B','C','D','E','F',
  'G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z'};
  
  int stocare;
  char caracter;

  for(int i=0;i<5;i++){
    stocare=recv_squanch();
    caracter=vcod[stocare-1];
     
    fprintf(stdout,"%c",caracter);
  }

  /* TODO
  * Receive 5 encoded characters, decode them and print
  * them to the standard output (as characters)
  *
  * ATTENTION!: Use fprintf(stdout, ...)
  */
}


void comm_byte(void)
{   
  
  int stocare;

  for(int i=0;i<10;i++){ 

    stocare=recv_squanch();

    send_squanch(stocare);
    send_squanch(stocare);
  
  }
  /* TODO
  * Receive 10 encoded characters and send each character (the character is
  * still encoded) 2 times
  */
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{   
  char vcod[]={'A','B','C','D','E','F',
  'G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z'};
  int len;
  char vmess[]={'H','E','L','L','O','T','H','E','R','E'};

  len  = sizeof(vmess);
  
  int lenn;
  lenn = len<<2;
  send_squanch(lenn);
  
  for(int i=0;i<len;i++){
    for(int j=1;j<=26;j++){

      if(vmess[i]==vcod[j-1]){
        send_squanch(j);
      }
    }
      
  }

  /* TODO
  * Send the message: HELLOTHERE
  * - send the encoded length
  * - send each character encoded
  */
}


void recv_message(void)
{
  char vcod[]={'A','B','C','D','E','F',
  'G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z'};
  int encodedlenght;
  int lenght;
  int finallenght;
  char decode;
  int encode;
  
  encodedlenght = recv_squanch();
  lenght= encodedlenght>>2;
  finallenght= lenght&15;
    
  fprintf(stdout,"%d",finallenght);

  for(int i=0;i<finallenght;i++){
    encode =  recv_squanch();
    
    for(int j=1;j<=26;j++){
      if(encode==j-1)decode=vcod[j-2];
    }

    fprintf(stdout,"%c",decode);
  }
  /* TODO
  * Receive a message:
  * - the first value is the encoded length
  * - length x encoded characters
  * - print each decoded character
  * 
  * ATTENTION!: Use fprintf(stdout, ...)
  */
}


void comm_message(void)
{  
  char vcod[]={'A','B','C','D','E','F',
  'G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z'};
  
  int encodedlenght,lenght,finallenght;

  encodedlenght =  recv_squanch();
  lenght= encodedlenght>>2;
  finallenght= lenght&15;

  int cont=0,decode,testP;
  
  for(int i=0;i<finallenght;i++){
    decode =  recv_squanch();
    if(i==(finallenght-1))testP=decode;
  }

  if(testP==16)cont=1;

  char P[]={'P','I','C','K','L','E','R','I','C','K'};
  int  lenP;
  lenP  = sizeof(P);

  char VIN[]={'V','I','N','D','I','C','A','T','O','R','S'};
  int lenVIN;
  lenVIN  = sizeof(VIN);

  int lenEnchoP;
  int lenEnchoVIN;
  lenEnchoP = (1<<5)|(1<<3); //8
  lenEnchoVIN = lenEnchoP|(1<<2);

  if(cont==1)
  {
    send_squanch(lenEnchoP);
    for(int i=0;i<lenP;i++){
      for(int j=1;j<=25;j++){

        if(P[i]==vcod[j-1])send_squanch(j);  
      }
    }
  }
  else
  {
    send_squanch(lenEnchoVIN);
    for(int i=0;i<lenVIN;i++){
      for(int j=1;j<=25;j++){

      if(VIN[i]==vcod[j-1])send_squanch(j);
      }     
    }         
  }
   
  /* TODO
  * Receive a message from Rick and do one of the following depending on the
  * last character from the message:
  * - 'P' - send back PICKLERICK
  * - anything else - send back VINDICATORS
  * You need to send the messages as you did at the previous tasks:
  * - encode the length and send it
  * - encode each character and send them
  */
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{ 
  int maskc1,interc1,bitc1;
  int maskc2,interc2,bitc2;
  int byte=0;
  int cont=0;

  for(int i=0;i<4;i++){
    
    maskc2 =  1 << i;
    interc2 = c2 & maskc2;
    bitc2 = interc2 >> i;

    maskc1 =  1 << i;
    interc1 = c1 & maskc1;
    bitc1 = interc1 >> i;

    if((bitc2==0)&&(bitc1==0)){
      cont=cont+2;
    }
    else if((bitc2==0)&&(bitc1==1)){
      cont=cont+1;
      byte=(1<<cont)|byte;
      cont=cont+1;
    }
    else if((bitc2==1)&&(bitc1==0)){
      byte=(1<<cont)|byte;
      cont=cont+2;
    }
    else if((bitc2==1)&&(bitc1==1)){
      byte=(3<<cont)|byte;
      cont=cont+2;
    }
  }
  send_squanch(byte);
  
  /* TODO
  * Steps:
  * - "merge" the character encoded in c1 and the character encoded in c2
  * - use send_squanch to send the newly formed byte
  */
}


uint8_t decode_squanch2(uint8_t c)
{
  /*
  * Decode the given byte:
  * - split the two characters as in the image from ocw.cs.pub.ro
  */

  uint8_t res = -1;

  int c1=0,c2=0;
  int maskc1,interc1,bitc1;
  int maskc2,interc2,bitc2;
  int contc1=0,contc2=0;

  for(int i=0;i<8;i+=2){

    maskc2 =  1 << i;
    interc2 = c & maskc2;
    bitc2 = interc2 >> i;

    if(bitc2==0)contc2++;
    if(bitc2==1){
      c2=(1<<contc2)|c2;
      contc2++;
    }
  }

  for(int i=1;i<9;i+=2){

    maskc1 =  1 << i;
    interc1 = c & maskc1;
    bitc1 = interc1 >> i;

    if(bitc1==0)contc1++;
    if(bitc1==1){
      c1=(1<<contc1)|c1;
      contc1++;
  }
  }
  c1=c1<<4;
  res=c1|c2;

  return res;
}
