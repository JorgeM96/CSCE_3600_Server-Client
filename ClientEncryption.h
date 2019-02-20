// header file that allows the the client to encrypt and decrypt a string

struct Encrypt
{
  char encrypted_str[2000];
};

// function that generate encrypted string
struct Encrypt GenerateEncryptedString(int n)
{
  int e = 0;
  int d = 0;
  int i = 0;
  unsigned int c = 0;
  unsigned int m = 0;
  char temp;
  
  struct Encrypt a;
  
  // encryption process
  char str[2000];
  bzero(str, 2000);
  
 //fflush(stdin);
 printf("\nEnter a message to encrypt and send to other client: ");
 scanf("%c",&temp); // temp statement to clear buffer 
 scanf("%[^\n]s", str);
  
  int y = 0;
  int z = 0;
  int int_counter = 0;
  int str_counter = 0;
  char encrypted_str[2000];
  char encrypted_buffer[2000];
  
  bzero(encrypted_str, 2000);
  bzero(encrypted_buffer, 2000);
  
  for(y = 0; y < sizeof(str); y++)
  {
    m = (int) str[y];
    c = m;
    for(z = 0; z < (e - 1); z++)
    {
      c = (c * m) % n;
    }
    sprintf(encrypted_buffer, "%d ", c);
    strcat(encrypted_str, encrypted_buffer);
  }
  
  // print encrypted string
  printf("\nSending Message Encrypted as: ");
  for(i = 0; i < sizeof(encrypted_str); i++)
  {
    if(encrypted_str[i] == '0' && encrypted_str[i - 1] == ' ')
    {
      continue;
    }
    else
    {
      if(encrypted_str[i] == '\0')
      {
        break;
      }
      else
      { 
        if(encrypted_str[i] != ' ' && encrypted_str[i - 1] == ' ' && encrypted_str[i + 1] == ' ')
        {
          printf( "%c ", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ' && encrypted_str[i + 1] == ' ')
        {
          printf("%c ", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ' && encrypted_str[i - 1] == ' ')
        {
          printf("%c", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ')
        {
          printf("%c", encrypted_str[i]);
        }
      }
    }
  }
  printf("\n\n");
  
  strcpy(a.encrypted_str,encrypted_str);
  
  return a;  
}

void GenerateDecryptedString(struct Encrypt a, int n, int d)
{
  // decryption process
  char encrypted_str[2000];
  char encrypted_buffer[2000];
  char decrypted_str[2000];
  bzero(decrypted_str, 2000);
  bzero(encrypted_buffer,2000);
  bzero(encrypted_str, 2000);
  int int_val = 0;
  int i;
  int j;
  unsigned int c = 0;
  unsigned int m = 0;
  d = 0;
  
  strcpy(encrypted_str, a.encrypted_str);
  
  //////////////////////////////////////////
  printf("\nReceieved Encrypted Message from other client: ");
  for(i = 0; i < sizeof(encrypted_str); i++)
  {
    if(encrypted_str[i] == '0' && encrypted_str[i - 1] == ' ')
    {
      continue;
    }
    else
    {
      if(encrypted_str[i] == '\0')
      {
        break;
      }
      else
      { 
        if(encrypted_str[i] != ' ' && encrypted_str[i - 1] == ' ' && encrypted_str[i + 1] == ' ')
        {
          printf( "%c ", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ' && encrypted_str[i + 1] == ' ')
        {
          printf("%c ", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ' && encrypted_str[i - 1] == ' ')
        {
          printf("%c", encrypted_str[i]);
        }
        else if(encrypted_str[i] != ' ')
        {
          printf("%c", encrypted_str[i]);
        }
      }
    }
  }
  printf("\n");
  /////////////////////////////////////////
  
  printf("\nDecrypted Message from other client is: ");
  for(i = 0; i < sizeof(encrypted_str) - 1; i++)
  {
    if(encrypted_str[i] == '0' && encrypted_str[i - 1] == ' ')
    {
      continue;
    }
    else
    {
      if(encrypted_str[i] == '\0')
      {
        break;
      }
      else
      {
        if(encrypted_str[i] == '0' && encrypted_str[i + 1] == ' ')
        {
          continue;
        }
        else if(encrypted_str[i] == ' ' && encrypted_str[i + 1] == '0')
        {
          continue;
        }
        else
        {
          while(encrypted_str[i] != ' ')
          {
            encrypted_buffer[int_val] = encrypted_str[i];
            int_val++;
            i++;
          }
          int_val = 0;
          c = atoi(encrypted_buffer);
          m = c;
          bzero(encrypted_buffer,2000);
          for(j = 0; j < (d - 1); j++)
          {
            m = (m * c) % n;
          }
          printf("%c", (char) m);
        }
      }
    }
  }
  printf("\n\n");
}
