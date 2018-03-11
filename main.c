#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Prototypedesfontions.h"

#define TRUE 1
#define FALSE 0

int main()
{
    int exit = FALSE;
    while (exit == FALSE)
    {
        system("cls");
        int choice = afficherMainMenu();
        switch(choice)
        {
            case 1:
                launchGame(FALSE);
                break;
            case 2:
                launchGame(TRUE);
                break;
            case 3:
                afficherAboutMenu();
                break;
            case 4:
                Color(3,0);
                printf("\n     BYE BYE\n");
                Color(3,0);
                exit = TRUE;
        }
    }
    return 0;
}
