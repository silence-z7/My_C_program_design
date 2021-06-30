#include <stdio.h>
#include <stdlib.h>
#include "fun.h"
int main()
{
    TeleBook *list = NULL;
    char choice_ch[CHOICE_SIZE];
    int choice;
    char choice7;
    char outfile[20];
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
            printf ("\t Input Records \n");
            Create();
            system("pause");
            break;
        case 2:
            Display(list);
            system("pause");
            break;
        case 3:
            printf("\t Insert a record:\n");
		    list=Insert_a_record(list);
            system("pause");
            break;
        case 4:
            printf("\t Delete a record:\n");
            list=Delete_a_record(list);
            system("pause");
            break;
        case 5:
            printf("\t Sort:\n");
            Sort_by_num(list);
            system("pause");
            break;
        case 6:
            printf("\t Query:\n");
		    Query_a_record(list);
            system("pause");
            break;
        //从文件中导入数据到链表
        case 7:
            //如果链表中已存在数据，应先向用户确认储存下该数据还是放弃数据
            if (list != NULL)
            {
                printf("Data in the linked list is not stored. Do you want to stored them or abandon them?\n");
                printf("1.store them.\n");
                printf("2.abandon them.\n");
                printf("enter 1 or 2 to give your choice:");
                while (1)
                {
                    scanf("%c", &choice7);
                    if (choice7 == '1')
                    {
                        //此处补充储存数据代码
                        break;
                    }
                    if (choice7 == '2')
                        ;
                    //先释放空间
                    //读取文件数据并覆盖链表数据代码
                    else
                        printf("Enter error! Please give your choice in 1 or 2.\n");
                }
            }
            system("pause");
            break;
        case 8:
            printf("\t Write to a text file \n");
            WritetoText(list,outfile);
            system("pause");
            break;
        case 9:
            printf("\t Reverse List\n");
		    list=Reverse(list);
            system("pause");
            break;
        case 10:
            printf("\t Delete the same record:\n");
		    list=DeleteSame(list);
            system("pause");
            break;
        case 11:
            printf("Alter existing records");
            list=Alter_list(list);
            system("pause");
            break;
        case 0:
            printf("\t Quit\n");
		    Quit(list);
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