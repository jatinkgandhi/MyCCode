
/* Buffered version */
#include <stdio.h> 
#include <string.h> 
 
void dump_hex(unsigned char *p,int len) 
{ 
        int i;  
        static unsigned char Buffer[1024]; 
        static unsigned char Char[5]; 
         
        memset(Buffer,'\0',sizeof(Buffer)); 
        snprintf(Buffer,1024,"\n"); 
        for(i = 0; i < len; i++) 
        {        
                Char[0] = '\0'; 
                snprintf(Char,1024,"%s",(i != 0 && i % 16 == 0)? "\n" : "") ; 
                snprintf(Char,1024,"%s",( i != 0 &&  i % 4 == 0 && i % 16 != 0) ? " " : ""); 
                snprintf(Char,1024,"0x%02X ",p[i]) ; 
                strncat(Buffer,Char,1024); 
         
        }   
         
        printf("Buff: %s\n",Buffer); 
} 
 
int main(int argc, char **argv) 
{ 
        dump_hex("abcdefghi",9); 
        return 0; 
} 
