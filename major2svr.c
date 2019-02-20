/*
CSCE 3600 Major 2 Server File

Author 1: Jorge Moreno Email: JorgeMoreno3@my.unt.edu EUID: JM1066
Author 2: Tate Mosier Email: tatemosier@my.unt.edu EUDI: TCM0106
Author 3: Justin Paul Email: JustinPaul2@my.unt.edu EUID: JKP0126
Author 4: Hector Tamez Email: HectorTamez@my.unt.edu EUID: HT0158
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include "ServerEncryption.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("Usage: %s [port number].\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  struct sockaddr_in serv_addr, cli_addr;
  int port = atoi(argv[1]);  //convert the port to an int
  int serverfd = 0;    //File descriptor for server side socket
  int clientfd1 = 0;   //File descriptor for client 1 socket
  int clientfd2 = 0;   //File descriptor for client 2 socket
  int clientReady;  //When a client file descriptor is ready
  int serverRead;   //Holds return of recv()
  int maxfd;   //descriptors up to maxfd-1 polled
  socklen_t clientSize;   //length of client address
  char buffer[2000];   //buffer for sending messages
  int numConnections = 0;  //number of client connected
  unsigned int p = 0;   //prime integer received
  unsigned int q = 0;   //prime integer received
  unsigned int n = 0;
  unsigned int d = 0;
  unsigned int e = 0;
	int count =0;
	int count2 = 0;
  int on =1;
  int i = 0;
   int checkp;
  int temp_var;
  int p_temp ;
  int q_temp;
  fd_set fds;   //set of file descriptors to poll
  int prime_check = -1;
  
  int z;
  int int_val = 0;
  char cli_buffer[10];
  int temp_arr[2];
  int arr_num = 0;

  if((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1) //create server socket
  {
    perror("Error creating Socket!\n");
    exit(EXIT_FAILURE);
  }
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(buffer, '0', sizeof(buffer));
  //This line is used for unlinking the port
  setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  //set up server socket type, hostname, port
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);
  //bind server socket
  if(bind(serverfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
  {
    perror("Server bind error!\n");
    exit(EXIT_FAILURE);
  }
  if(listen(serverfd,2) < 0)  //listen for 5 connections
  {
    perror("Server listen error!\n");
    exit(EXIT_FAILURE);
  }
  printf("Waiting for incoming connections...\n");
  //clientSize = sizeof(cli_addr);
	
  while(1)
  {
    clientSize = sizeof(cli_addr);
    //accept connection for client 1
    if((clientfd1 = accept(serverfd,(struct sockaddr*)&cli_addr,&clientSize)) == -1)
    {
      printf("Accept error for client 1!\n");
      exit(EXIT_FAILURE);
    }
    numConnections++;
    if(numConnections > 2)
    {
      bzero(buffer,2000);
      strcpy(buffer,"MAX");
      send(clientfd1,buffer,strlen(buffer)+10,0);
      numConnections--;
    }
    else
    {
      printf("[SERVER X]: Client 1 has connected.\n");
      bzero(buffer,2000);
      strcpy(buffer,"You connected");
      send(clientfd1,buffer,strlen(buffer)+10,0);
      sleep(1);
      serverRead = recv(clientfd1,buffer,strlen(buffer)+10,0);
      if(serverRead < 1)
      {
				close(clientfd1);
				exit(0);
      }
      printf("[Client 1]: %s\n",buffer);
			bzero(buffer,2000);
			strcpy(buffer,"1");  //client handler
			send(clientfd1,buffer,strlen(buffer)+10,0);
    }
    if((clientfd2 = accept(serverfd,(struct sockaddr*)&cli_addr,&clientSize)) == -1)
    {
      printf("Accept error for client 2!\n");
      exit(EXIT_FAILURE);
    }
    numConnections++;
    if(numConnections > 2)
    {
      bzero(buffer,2000);
      strcpy(buffer,"MAX");
      send(clientfd2,buffer,strlen(buffer)+10,0);
      numConnections--;
    }
    else
    {
     printf("[SERVER X]: Client 2 has connected\n");
     bzero(buffer,2000);
     strcpy(buffer,"You connected");
     send(clientfd2,buffer,strlen(buffer)+10,0);
     sleep(1);
     serverRead = recv(clientfd2,buffer,strlen(buffer)+10,0);
     if(serverRead < 1)
     {
      close(clientfd2);
      exit(0);
     }
     printf("[Client 2]: %s\n",buffer);
		 bzero(buffer,2000);
		 strcpy(buffer,"2");  //client handler
		 send(clientfd2,buffer,strlen(buffer)+10,0);
    }
    if(numConnections == 2)
    {
			bzero(buffer,2000);
			strcpy(buffer,"2");
			send(clientfd1,buffer,strlen(buffer)+10,0);
			maxfd = (clientfd1 > clientfd2 ? clientfd1 : clientfd2) + 1;  //find max file descriptor
			while(1)
			{
     		FD_ZERO(&fds);  //setting up polling using select()
     		FD_SET(clientfd1,&fds);
     		FD_SET(clientfd2,&fds);
      
      	clientReady = select(maxfd, &fds, (fd_set *) 0, (fd_set *) 0,(struct timeval *) 0);
				
      	if(FD_ISSET(clientfd1, &fds))  //if client 1 is ready to send data
		  	{
					if(count == 0)
					{
						printf("[SERVER X]: Waiting on Client 1 to send two prime integers.\n");
						count++;
					}    
          sleep(1);
          serverRead = recv(clientfd1,buffer,strlen(buffer)+10,0);
          if(serverRead < 1)
          {
            close(clientfd1);
            exit(0);
          } 
          if(buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0)
          {
              if(strcmp(buffer,"CLOSE") == 0)
					    {
						    printf("[SERVER X]: Client 1 has disconnected waiting for a connection.");
						    numConnections--;
						    count = 0;
						    close(clientfd1);
						    break;
				  	  }
              else 
              {
               int z;
               int int_val = 0;
               char cli_buffer[10];
               int temp_arr[2];
               int arr_num = 0;

              for(z = 0; z < sizeof(buffer); z++)
              {
                if(buffer[z] == 0)
                {
                  break;
                } 
                else
                {
                  while(buffer[z] != ' ')
                  {
                  cli_buffer[int_val] = buffer[z];
                  int_val++;
                  z++;
                }
                int_val = 0;
                temp_arr[arr_num] = atoi(cli_buffer);
                bzero(cli_buffer, 10);
                arr_num++;
                if(arr_num == 2)
                {
                  break;
                }
              }
            }
            p = temp_arr[0];
            q = temp_arr[1];
            if(p != 0 && q != 0)
            {
              checkp = 0;
              temp_var = 0;
              p_temp = p;
              q_temp = q;
          
              printf("[SERVER X]: Received 2 Prime numbers %d and %d from Client 1\n",p,q);
            }
                
            printf("\nGenerating Encryption Keys\n");
            // generating encryption keys
            d = GetKeyD(p, q);
            e = GetKeyE(p, q);
            n = GetKeyN(p, q);
            // for testing only
            if(d > 0 && e > 0 && n > 0)
            {
              printf("\nPublic Key: (%d,%d)\n", d, n);
              printf("Private Key: (%d,%d)\n", e, n);
              printf("\nSending Keys to clients\n");
              sprintf(buffer, "%d %d", e, n);
              send(clientfd1,buffer,strlen(buffer)+10,0);
              //printf("\nJust sent data to Client 1.\n");
              bzero(buffer, 2000);
              sprintf(buffer, "KEY %d %d", d, n);
              send(clientfd2,buffer,strlen(buffer)+10,0);
              //printf("\nJust sent data to Client 2.\n");
            }
          }
            
          }
				}
      	if(FD_ISSET(clientfd2, &fds))  //if client 2 is ready to send data
		  	{
					bzero(buffer, 2000);
          serverRead = recv(clientfd2,buffer,strlen(buffer)+10,0);
          if(serverRead < 1)
          {
            close(clientfd2);
            exit(0);
          }
          //if(buffer[0] == 'K' && buffer[1] == 'E' && buffer[2] == 'Y')
          if(buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0)
          {
            printf("\nGenerating Encryption Keys\n");
            ////////////////////////////////////////////////////
            for(z = 4; z < sizeof(buffer); z++)
            {
              if(buffer[z] == 0)
              {
                break;
              } 
              else
              {
                while(buffer[z] != ' ')
                {
                  cli_buffer[int_val] = buffer[z];
                  int_val++;
                  z++;
                }
              int_val = 0;
              temp_arr[arr_num] = atoi(cli_buffer);
              bzero(cli_buffer, 10);
              arr_num++;
              if(arr_num == 2)
              {
                break;
              }
            }
          }
            p = temp_arr[0];
            q = temp_arr[1];
          ///////////////////////////////////////////////////  
             // generating encryption keys
            d = GetKeyD(p, q);
            e = GetKeyE(p, q);
            n = GetKeyN(p, q);
            // for testing only
            if(d > 0 && e > 0 && n > 0)
            {
              printf("\nPublic Key: (%d,%d)\n", d, n);
              printf("Private Key: (%d,%d)\n", e, n);
              printf("\nSending Keys to clients\n");
              sprintf(buffer, "%d %d", e, n);
              send(clientfd1,buffer,strlen(buffer)+10,0);
              //printf("\nJust sent data to Client 1.\n");
              bzero(buffer, 2000);
              sprintf(buffer, "KEY %d %d", d, n);
              send(clientfd2,buffer,strlen(buffer)+10,0);
              //printf("\nJust sent data to Client 2.\n");
            }
          ///////////////////////////////////////////////////
          }
          
      	}
    
    	}
			
		}
  }

  return 0;
}
