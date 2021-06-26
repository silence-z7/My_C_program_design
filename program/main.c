#include <stdio.h>
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
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 0:
            break;
        default:printf("enter error! Please retype your choice.\n");
            break;
        }
    }
    return 0;
}