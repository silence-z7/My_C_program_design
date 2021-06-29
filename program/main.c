#include <stdio.h>
#include <stdlib.h>
#include "fun.h"
int main()
{
    TeleBook *list;
    char choice_ch[CHOICE_SIZE];
    int choice;

    while (1)
    {
        Display_Main_Menu();
        gets(choice_ch);
        if (Check(choice_ch, CHOICE_SIZE) == 0)
        {
            printf("enter error! Please retype your choice.\n");
            continue;
        }
        choice = Str_to_num(choice_ch);
        if (choice == -1)
        {
            printf("enter error! Please retype your choice.\n");
            continue;
        }
        switch (choice)
        {
        case 1:
            system("pause");
            break;
        case 2:
            system("pause");
            break;
        case 3:
            system("pause");
            break;
        case 4:
            system("pause");
            break;
        case 5:
            system("pause");
            break;
        case 6:
            system("pause");
            break;
        case 7:
            system("pause");
            break;
        case 8:
            system("pause");
            break;
        case 9:
            system("pause");
            break;
        case 10:
            system("pause");
            break;
        case 0:
            system("pause");
            break;
        default:
            printf("enter error! Please retype your choice.\n");
            system("pause");
            break;
        }
    }
    return 0;
}