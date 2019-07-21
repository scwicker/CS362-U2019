#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
char inputChar()
{
    int random_int, random_range, ascii_min, ascii_max;
    ascii_min = 32;
    ascii_max = 126; // don't need DEL or ~
    // range of ascii characters that we want to generate
    random_range = ascii_max - ascii_min;
    // get a random int that will correspond to a char
    random_int = (rand() % (random_range)) + ascii_min;
    // cast random_int into a char
    char random_char = (char) random_int;
    
    return random_char;
}


char *inputString()
{
    char random_string[6], *return_string;
    char reasonable_letter_pool[10] = "restabcdef";
    int i, random_position;
    // grab 5 random letters from our letter pool
    for(i = 0; i < 5; i++){
         random_position = (rand() % (10));
         random_string[i] = reasonable_letter_pool[random_position];
    }
    // append string with newline 
    random_string[5] = '\0';
    // return char* random string
    return_string = random_string;
return return_string;
}


void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
