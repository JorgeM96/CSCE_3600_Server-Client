// Header File for Changing CLient to Server
struct ServerInfo
{
  char ip_address[20];
  int port_number;
};

void ChangeToServer(struct ServerInfo serverinfo, int clientPort, int n, int test)
{
 
  int client_fd = 0;
  struct sockaddr_in server_ip_address;
  struct sockaddr_in client_ip_address;
  struct in_addr ip_address;
  char server_buffer[2000];
  int on = 1;
  int s_read;
  
  int client_size;
  
  //create client socket
  if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Socket Error: ");
    exit(0);
  }
  memset(&server_ip_address, '0', sizeof(server_ip_address));
  memset(server_buffer, '0', sizeof(server_buffer));
  
  setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  
  server_ip_address.sin_family = AF_INET;
  server_ip_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_ip_address.sin_port = htons(clientPort);
  
  if(bind(client_fd, (struct sockaddr *) &server_ip_address, sizeof(server_ip_address)) == -1)
  {
    perror("Server Bind Error: ");
    exit(1);
  }
  
  if(listen(client_fd, 1) < 0)
  {
    perror("Server Listen Error: ");
    exit(1);
  }
  
  client_size = sizeof(client_ip_address);
  
  if((client_fd = accept(client_fd, (struct sockaddr *)&client_ip_address, &client_size)) == -1)
  {
    perror("Client Accept Error: ");
    exit(1);
  }
  printf("[Client_Server]: Other Client has connected.\n");
  
  struct Encrypt encrypt;
  encrypt = GenerateEncryptedString(n);
  
  bzero(server_buffer,2000);
  strcpy(server_buffer,encrypt.encrypted_str);
  send(client_fd,server_buffer,strlen(server_buffer),0);
  
  printf("\nDisconnecting from other client...\n");
  
}

void ConnectToServer(struct ServerInfo serverinfo, char *ip, int clientPort, int n, int d, int test2)
{
  int server_fd = 0;
  char client_buffer[2000];
  int c_read;
  struct in_addr ip_address;
  struct sockaddr_in server_ip_address;
  struct hostent *server;
  
  memset(client_buffer, '0', sizeof(client_buffer));
  
  //create server socket
  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Socket Error: ");
    exit(0);
  }

  if(!inet_aton(ip, &ip_address))
  {
    errx(1, "Unable to parse IP address %s", ip);
    exit(0);
  }
  
  if((server = gethostbyaddr((const void *)&ip_address, sizeof(ip_address), AF_INET)) == NULL)
  {
    errx(1, "Cannot find host by that ip address %s", ip);
    exit(0);
  }
  
  bzero((char *) &server_ip_address, sizeof(server_ip_address));
  server_ip_address.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_ip_address.sin_addr.s_addr, server->h_length);
  server_ip_address.sin_port = htons(clientPort);

  if(connect(server_fd, (struct sockaddr *)&server_ip_address, sizeof(server_ip_address)) < 0)
  {
    perror("Connect Error: ");
    exit(0);
  }
  printf("\nConnected to other client\n");
  bzero(client_buffer, 2000);
  
    sleep(1);
    c_read = recv(server_fd,client_buffer,sizeof(client_buffer),0);
  if(c_read < 1)
  {
    perror("Receive error!\n");
    close(server_fd);
    exit(0);
  }
  
  struct Encrypt encrypt;
  char test[2000];
  strcpy(test, client_buffer);
  strcpy(encrypt.encrypted_str, test);
  GenerateDecryptedString(encrypt, n, d);
  bzero(client_buffer, 2000);
  printf("\nDisconnecting from other client...\n");
  if(test2== 2)
  {
    exit(0); 
  }
  
}