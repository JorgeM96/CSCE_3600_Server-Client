/*
CSCE 3600 Major 2 Client File

Author 1: Jorge Moreno Email: JorgeMoreno3@my.unt.edu EUID: JM1066
Author 2: Tate Mosier Email: tatemosier@my.unt.edu EUDI: TCM0106
Author 3: Justin Paul Email: JustinPaul2@my.unt.edu EUID: JKP0126
Author 4: Hector Tamez Email: HectorTamez@my.unt.edu EUID: HT0158
*/
#include <sys/socket.h>
#include <netdb.h>
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
#include "ClientEncryption.h"
#include "ServerChange.h"

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    printf("Usage: %s [hostname] [server port] [client 2 ipaddress] [client port]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  int serverPort = atoi(argv[2]);
  int clientPort = atoi(argv[4]);
  int sockfd = 0;  //socket file descriptor
  char buffer[2000];  //buffer array to communicate
  int clientReady;
  int cRead;
  int clientHandle;
  int numConnections;
  unsigned int p;   //prime integer received
  unsigned int q;   //prime integer received
  unsigned int n = 0;
  unsigned int d = 0;
  unsigned int e = 0;
  int prime_check = -1;
  int p_temp,q_temp;
  int temp_var;
  int checkp = 0;
  
  pthread_t threadID;  //thread id for client 1 or 2
  
  struct ServerInfo serverinfo;
  strcpy(serverinfo.ip_address, argv[3]);
  serverinfo.port_number = clientPort;
  
  int z;
  int int_val = 0;
  char cli_buffer[10];
  int temp_arr[2];
  int arr_num = 0;
  
  memset(buffer, '0', strlen(buffer));
  if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) //create socket
  {
    printf("Client socket error!\n");
    exit(EXIT_FAILURE);
  }
  server = gethostbyname(argv[1]);
  if(server == NULL)
  {
    printf("Hostname error!\n");
    exit(EXIT_FAILURE);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(serverPort);
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  
  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
  {
    printf("Connect error!\n");
    exit(EXIT_FAILURE);
  }
  bzero(buffer,2000);  //clear buffer
  printf("Server message: ");
  sleep(1);
  cRead = recv(sockfd,buffer,sizeof(buffer)+10,0);
  if(cRead < 1)
  {
    perror("Receive error!\n");
    close(sockfd);
    exit(0);
  }
  if(strcmp(buffer,"MAX") == 0) //if server sent msg that max clients connected
  {
    printf("Max clients server can have has been reached (2)\n");
    exit(1);
  }
  else
  {
    printf("%s\n",buffer);
    bzero(buffer,2000);  //clear buffer
    strcpy(buffer,"I have connected.\n");
    send(sockfd,buffer,sizeof(buffer)+10,0);
    sleep(1);
    cRead = recv(sockfd,buffer,sizeof(buffer)+10,0);
    if(cRead < 1)
    {
      perror("Receive error!\n");
      close(sockfd);
      exit(0);
    }
    clientHandle = atoi(buffer);
  }
  printf("\n=====================================\n");
  cRead = recv(sockfd,buffer,sizeof(buffer)+10,0);
  {
    if(cRead < 1)
    {
      perror("Receive error!\n");
      close(sockfd);
      exit(0);
    }
  
  numConnections = atoi(buffer);
  if(numConnections == 2)
  {
    while(prime_check == -1)
    {
      printf("Enter CLIENT %d Data (p and q prime, where p * q > 128) (Enter 0 0 to disconnect): \n",clientHandle);
      scanf("%d %d",&p, &q);
      p_temp = p;
      q_temp = q;
      for(temp_var = 2; temp_var <= p_temp/2; temp_var++)
      {
       if((p_temp % temp_var) == 0)
       {
          checkp == 1;
        }
      }
      for(temp_var = 2; temp_var <= q_temp/2; temp_var++)
      {
        if((q_temp % temp_var) == 0)
        {
          checkp == 1;
        }
      }
      if(checkp == 1 || p*q < 128)
      {
       /* bzero(buffer,2000);
        strcpy(buffer,"INVALID");
        send(sockfd,buffer,sizeof(buffer)+10,0); */
        printf("Numbers are not valid for the server please try again!\n");
        prime_check = -1;
      }
      else
      {
       /* bzero(buffer,2000);
        strcpy(buffer,"READY");
        send(sockfd,buffer,sizeof(buffer)+10,0);*/
        prime_check = 0;
        break;
      }
    }
    
    if(p == 0)
    {
      printf("Client %d disconnecting...\n",clientHandle);
      bzero(buffer,2000);
      strcpy(buffer,"CLOSE");
      send(sockfd,buffer,sizeof(buffer)+10,0);
      exit(0);
    }
    else
    {
      bzero(buffer, 2000);
      sprintf(buffer,"%d %d",p, q);
      printf("\nBuffer = %s\nSending Now\n", buffer);
      send(sockfd,buffer,sizeof(buffer)+10,0);
 
       sleep(1);
       cRead = recv(sockfd,buffer,strlen(buffer)+10,0);
       if(cRead < 1)
       {
        perror("Receive error!\n");
        close(sockfd);
        exit(0);
        }
     /*   if(strcmp(buffer, "INVALID") == 0)
        {
           printf("The numbers entered were not primed or their products was not greater than 128.\n");
           printf("Please try again.\n");
        }*/
        if(buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0 && clientHandle == 1)
        {
          if(buffer[0] != 'K' && buffer[1] != 'E' && buffer[2] != 'Y')
          {
            printf("\nPrivate Key Recieved.\n");
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
          e = temp_arr[0];
          n = temp_arr[1];
         
          //struct Encrypt encrypt;
          //encrypt = GenerateEncryptedString(n);
          // now disconnection from main server to become server for other client
          //close(sockfd);
          /////////////////////////////////// 
         // struct ServerInfo serverinfo;
          //strcpy(serverinfo.ip_address, argv[3]);
          //serverinfo.port_number = clientPort;
          ChangeToServer(serverinfo, clientPort, n, 0);
          sleep(1);
          cRead = recv(sockfd,buffer,strlen(buffer)+10,0);
           if(cRead < 1)
           {
            perror("Receive error!\n");
            close(sockfd);
            exit(0);
            }
            
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            printf("\nPublic Key Recieved.\n");
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
          d = temp_arr[0];
          n = temp_arr[1];
          int temp_e; // for storing private key later
             sleep(2);
             //close(sockfd);
           ConnectToServer(serverinfo, argv[3], clientPort, n, d, 2);
            printf("\n\nprogram done exiting...\n");
            close(sockfd);
            exit(0);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
          /////////////////////////////////// 
            
          }
          else if(buffer[0] == 'K' && buffer[1] == 'E' && buffer[2] == 'Y')// recieved public key from server so we can decrypt messages
          {
            printf("\nPublic Key Recieved.\n");
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
          d = temp_arr[0];
          n = temp_arr[1];
          printf("\nd = %d\nn = %d", d, n);
         // sleep(1);
          }
        }
   }
 
  // second client key information
  if(buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0 && clientHandle == 2)
    {
      if(buffer[0] != 'K' && buffer[1] != 'E' && buffer[2] != 'Y')
      {
        printf("\nPrivate Key Recieved.\n");
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
      e = temp_arr[0];
      n = temp_arr[1];
      struct Encrypt encrypt;
      encrypt = GenerateEncryptedString(n);
      }
      else if(buffer[0] == 'K' && buffer[1] == 'E' && buffer[2] == 'Y')// recieved public key from server so we can decrypt messages
      {
        printf("\nPublic Key Recieved.\n");
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
      d = temp_arr[0];
      n = temp_arr[1];
      int temp_e; // for storing private key later
         sleep(1);
         //close(sockfd);
       ConnectToServer(serverinfo, argv[3], clientPort, n, d, 1);
        int choice = 0;
       printf("\nWould you like to send an encrypted message to the other client? (1 for yes, 2 for no): ");
        scanf("%d", &choice);
        if(choice == 1)
        {
          bzero(buffer, 2000);
          printf("\nEnter CLIENT %d Data (p and q prime, where p * q > 128) (Enter 0 0 to disconnect): \n",clientHandle);
          scanf("%d %d",&p, &q);
          
          sprintf(buffer, "KEY %d %d", p, q);
          send(sockfd,buffer,sizeof(buffer)+10,0);
          bzero(buffer, 2000);
          sleep(1);
          cRead = recv(sockfd,buffer,strlen(buffer)+10,0);
           if(cRead < 1)
           {
            perror("Receive error!\n");
            close(sockfd);
            exit(0);
            }
          
          
          ///////////////////////////////////////////////////////////////////////////////////////
          if(buffer[0] == 'K' && buffer[1] == 'E' && buffer[2] == 'Y')
          {
            printf("\nPrivate Key Recieved.\n");
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
          e = temp_arr[0];
          n = temp_arr[1];
         
          //struct Encrypt encrypt;
          //encrypt = GenerateEncryptedString(n);
          // now disconnection from main server to become server for other client
          //close(sockfd);
          /////////////////////////////////// 
         // struct ServerInfo serverinfo;
          //strcpy(serverinfo.ip_address, argv[3]);
          //serverinfo.port_number = clientPort;
          ChangeToServer(serverinfo, clientPort, n, 1);
          sleep(1);
          
          exit(0);
          /////////////////////////////////// 
            
          }
          ///////////////////////////////////////////////////////////////////////////////////////
          
        }
        else if(choice == 2)
        {
          printf("\nClosing all connection and exiting the program...\n");
          close(sockfd);
          exit(0);
        }
      }
    }
  
  while(1)
  {
    printf("\nput other code here\n");
    break;
  }
  
  
  
  return 0;
}