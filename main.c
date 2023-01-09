#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  IDLE, // represent idle state
  C25,  // represent state where the current amount of money is 25 cent.
  C50   // represent state where the current amount of money is 50 cent.
} State;

char DOLLAR = 'd';
char QUARTER = 'q';

int getQ1(State state)
{
  return (state >> 1) & 1;
}

int getQ0(State state)
{
  return state & 1;
}

int getQ1N(State state, int dollar, int quarter)
{
  return (!dollar && !quarter && getQ1(state)) ||
         (!dollar && quarter && getQ0(state)) ||
         (dollar && quarter && getQ1(state));
}

int getQ0N(State state, int dollar, int quarter)
{
  return (!dollar && !quarter && getQ0(state)) ||
         (dollar && quarter && getQ0(state)) ||
         (!dollar && quarter && !getQ1(state) && !getQ0(state));
}

int isCokeDispensed(State state, int dollar, int quarter)
{
  return (!dollar && quarter && getQ1(state)) || (dollar && !quarter);
}

int isChangeGiven(State state, int dollar, int quarter)
{
  return (dollar && !quarter);
}

void VENDING_IDLE()
{
  printf("    ___________\n");
  printf("   |           |\n");
  printf("   |   O   O   |\n");
  printf("   | _______  |\n");
  printf("   ||       || |\n");
  printf("   ||       || |\n");
  printf("   ||_______|| |\n");
  printf("   |           |\n");
  printf("   |___________|\n");
}

void VENDING_C25()
{
  printf("    ___________\n");
  printf("   |           |\n");
  printf("   |   O   O   |\n");
  printf("   | _______  |\n");
  printf("   ||  25C  || |\n");
  printf("   ||       || |\n");
  printf("   ||_______|| |\n");
  printf("   |           |\n");
  printf("   |___________|\n");
}

void VENDING_C50()
{
  printf("    ___________\n");
  printf("   |           |\n");
  printf("   |   O   O   |\n");
  printf("   | _______  |\n");
  printf("   ||  50C  || |\n");
  printf("   ||       || |\n");
  printf("   ||_______|| |\n");
  printf("   |           |\n");
  printf("   |___________|\n");
}


void VENDING_COKE_AND_CHANGE()
{
  printf("    ___________\n");
  printf("   |           |\n");
  printf("   |   O   O   |\n");
  printf("   | _______  |\n");
  printf("   ||       || |\n");
  printf("   ||       || |\n");
  printf("   ||_______|| |\n");
  printf("   |  ______  |\n");
  printf("   | /      \\ |\n");
  printf("   ||        ||\n");
  printf("   ||        ||\n");
  printf("   ||________||\n");
  printf("   |  ______  |\n");
  printf("   | / $$$$ \\ |\n");
  printf("   ||        ||\n");
  printf("   ||        ||\n");
  printf("   ||________||\n");
  printf("   |           |\n");
  printf("   |___________|\n");
}

void VENDING_COKE()
{
  printf("    ___________\n");
  printf("   |           |\n");
  printf("   |   O   O   |\n");
  printf("   | _______  |\n");
  printf("   ||       || |\n");
  printf("   ||       || |\n");
  printf("   ||_______|| |\n");
  printf("   |  ______  |\n");
  printf("   | /      \\ |\n");
  printf("   ||        ||\n");
  printf("   ||        ||\n");
  printf("   ||________||\n");
  printf("   |           |\n");
  printf("   |___________|\n");
}

State evaluate(State state, char money)
{
  int dollar, quarter;
  if (money == DOLLAR)
  {
    dollar = 1;
    quarter = 0;
  }

  if (money == QUARTER)
  {
    dollar = 0;
    quarter = 1;
  }

  int q1 = getQ1N(state, dollar, quarter) * 2;
  int q0 = getQ0N(state, dollar, quarter);

  int stateEnum = q1 + q0;

  if (stateEnum == IDLE)
  {
    printf("Vending machine is on IDLE mode\n");

    if (isCokeDispensed(state, dollar, quarter) && isChangeGiven(state, dollar, quarter))
    {
      system("clear");
      printf("Thank you for buying coke. Here is your coke and change!\n");
      VENDING_COKE_AND_CHANGE();
      printf("\nPress any key to continue!\n");
      getchar();
    }
    else if (isCokeDispensed(state, dollar, quarter))
    {
      system("clear");
      printf("Thank you for buying coke. Here is your coke!\n");
      VENDING_COKE();
      printf("\nPress any key to continue!\n");
      getchar();
    }

    return IDLE;
  }

  if (stateEnum == C25)
  {
    printf("You've inserted 25 cent, please insert 2 quarter more!\n");
    printf("\nPress any key to continue!\n");
    getchar();
    return C25;
  }

  if (stateEnum == C50)
  {
    printf("You've inserted 50 cent, please insert a quarter more!\n");
    printf("\nPress any key to continue!\n");
    getchar();
    return C50;
  }
}

void printVendingMachine(State state)
{
  if (state == IDLE)
  {
    VENDING_IDLE();
  }
  else if (state == C25)
  {
    VENDING_C25();
  }
  else if (state == C50)
  {
    VENDING_C50();
  }
}

int main()
{
  State currentState = IDLE;
  char money;
  while (1)
  {
    system("clear");
    printVendingMachine(currentState);
    printf("\nInsert dollar (d) or quarter (q): ");
    scanf("%c", &money);
    getchar();

    if (money != DOLLAR && money != QUARTER)
    {
      printf("Please input a proper value!\n");
    }
    else
    {
      currentState = evaluate(currentState, money);
    }
  }

  return 0;
}