// Header file for server to generate public and private keys so that client can encrypt

// these functions assumes that p and q have been filtered to be prime
int GetKeyE(int p, int q)
{
  int exp;
  int phi;
  int tmp;
  int d;
  int n;
  int i;
  int e;
  unsigned int c;
  unsigned int m;
  int data;
  
  exp = 2;
  
  n = p * q;
  phi = (q - 1) * (p - 1);
 
  // compute the value of e
  while (exp < phi)
  {
    if (gcd(exp, phi) == 1)
    {
      break;
    }
    else
    {
      exp++;
    }
  }
  
  // compute the value of d
  i = 1;
  while(1)
  {
    tmp = (phi * i) + 1;
    if((tmp % exp) == 0)
    {
      d = tmp / exp;
      break;
    }
    i++;
  }
  
  return exp;
}


int GetKeyD(int p, int q)
{
  int exp;
  int phi;
  int tmp;
  int d;
  int n;
  int i;
  int e;
  unsigned int c;
  unsigned int m;
  int data;
  
  exp = 2;
  
 n = p * q;
  phi = (13 - 1) * (11 - 1);
 
  // compute the value of e
  while (exp < phi)
  {
    if (gcd(exp, phi) == 1)
    {
      break;
    }
    else
    {
      exp++;
    }
  }
  
  // compute the value of d
  i = 1;
  while(1)
  {
    tmp = (phi * i) + 1;
    if((tmp % exp) == 0)
    {
      d = tmp / exp;
      break;
    }
    i++;
  }
  
  return d;
}

int GetKeyN(int p, int q)
{
  int exp;
  int phi;
  int tmp;
  int d;
  int n;
  int i;
  int e;
  unsigned int c;
  unsigned int m;
  int data;
  
  exp = 2;
  
  n = p * q;
  phi = (13 - 1) * (11 - 1);
 
  // compute the value of e
  while (exp < phi)
  {
    if (gcd(exp, phi) == 1)
    {
      break;
    }
    else
    {
      exp++;
    }
  }
  
  // compute the value of d
  i = 1;
  while(1)
  {
    tmp = (phi * i) + 1;
    if((tmp % exp) == 0)
    {
      d = tmp / exp;
      break;
    }
    i++;
  }
  
  return n;
}

int gcd(int a, int b)
{
  int tmp;
  while(1)
  {
    tmp = a % b;
    if (tmp == 0)
    {
      return b;
    }
    a = b;
    b = tmp;
  }
  return 1;
}