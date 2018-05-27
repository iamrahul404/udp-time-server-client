
#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc,char* argv[])
{
  int ClientSocket,Bytes;
  char buffer[255];
  char *servIP = "127.0.0.1";
  struct sockaddr_in serverAddress;
  unsigned int addrSize;

  if((ClientSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
    printf("Error at socket creation\n");

  memset(&serverAddress,0,sizeof(serverAddress));

  serverAddress.sin_family=AF_INET;
  serverAddress.sin_port=htons(9987);
  serverAddress.sin_addr.s_addr=inet_addr(servIP);
  memset(buffer,0,255);

  addrSize=sizeof(serverAddress);

 for(;;){
  printf("Enter the string : ");
  scanf("%s",buffer);
  Bytes=strlen(buffer);
  if((sendto(ClientSocket,buffer,Bytes,0,(struct sockaddr*)&serverAddress,addrSize))<0)
       {
          printf("Error in sending ");
       }
  
  recvfrom(ClientSocket,buffer,255,0,(struct sockaddr*)&serverAddress,&addrSize);
  printf("Time is %s\n",buffer);
 }
}