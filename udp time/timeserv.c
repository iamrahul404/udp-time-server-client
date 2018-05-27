#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int main()
{
   int serverSocket,Bytes,byte,sizeOfMessage;
   time_t currentTime;
   time(&currentTime);
   char buffer[255];char message[100];
   unsigned int addr_size;
   struct sockaddr_in serverAddress,clientAddress;
   serverSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    memset(&serverAddress,0,sizeof(serverAddress));
   serverAddress.sin_family=AF_INET;
   serverAddress.sin_port=htons(9987);
   serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
   memset(buffer,'\0',255);
   memset(message,'\0',100);
   strcpy(message,"Server is connected...waiting for the client ");
   sizeOfMessage=strlen(message);
   write(0,message,sizeOfMessage);

   
   byte=strlen(ctime(&currentTime));

   if((bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)))<0)
       {
           memset(message,'\0',100);
           strcpy(message,"Error in bind");
           sizeOfMessage=strlen(message);
           write(0,message,sizeOfMessage);
       }

   addr_size=sizeof(clientAddress);   

   for(;;)
        {
           if((recvfrom(serverSocket,buffer,255,0,(struct sockaddr*)&clientAddress,&addr_size))<0)
                {
                 memset(message,'\0',100);
                 strcpy(message,"Error in receiving");   
                 sizeOfMessage=strlen(message);
                 write(0,message,sizeOfMessage);
                }
           
           Bytes=strlen(buffer);
           memset(message,'\0',100);
           strcpy(message,"Client is connected \n");
           sizeOfMessage=strlen(message);
           write(0,message,sizeOfMessage);
           write(0,buffer,Bytes);

           if((sendto(serverSocket,ctime(&currentTime),byte,0,(struct sockaddr*)&clientAddress,addr_size))<0)
              {
                  memset(message,'\0',100);
                 strcpy(message,"Error in sending");   
                 sizeOfMessage=strlen(message);
                 write(0,message,sizeOfMessage);
               }
        }
}