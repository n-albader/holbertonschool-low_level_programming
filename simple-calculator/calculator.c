#include <stdio.h>


int read_user_choice(void) 
{
  int input;
  
  while(1) 
  {
    printf("Choice: ");
    if(scanf("%d", &input)!=1) 
    {
      printf("Invalid choice\n");
      scanf("%*s");
    } else 
    {
      return (input);
    }
  }
}

int read_user_number(char name) 
{
  int input;

  while(1) 
  {
    printf("%c: ", name);

    if(scanf("%d", &input)!=1) 
    {
      printf("Invalid number\n");
      scanf("%*s");
    }
    else 
    {
      return (input);
    }
  }
}
int main(void)
 {
  int choice = -1;
  int a, b, result;

  printf("Simple Calculator\n");

	while (choice !=0)
	{
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\n");
		printf("Choice: ");

    choice = read_user_choice();
		
		if (choice ==0)
    {
			printf("Bye!\n");
      break;
	  }
    else if (choice < 0 || choice > 4)
    {
      printf("Invalid choice\n");
      continue;
    }

    a = read_user_number('A');
    b = read_user_number('B'); 

    if (choice == 1)
    {
      result = a + b;
      printf("Result: %d\n", result);
    }
    else if (choice == 2)
    {
      result = a - b ;
      printf("Result: %d\n", result);
    }
    else if (choice == 3)
    {
      result = a * b ;
      printf("Result: %d\n", result);
    }
    else if (choice == 4)
    {
      if (b == 0)
      {
        printf("Error: division by zero\n");
      }
      else
      {
        printf("result %.1f\n", (double)a / b);
      }
    }
  }
	return (0);
}
