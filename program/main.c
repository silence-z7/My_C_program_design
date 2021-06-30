#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun.h"
int main()
{
    TeleBook *list = NULL;
    char choice_ch[CHOICE_SIZE];
    int choice;
    char choice1, choice7;
    char outfile[20];
    char infile[20];
    while (1)
    {
        Display_Main_Menu();
        scanf("%s", choice_ch);
        if (Check(choice_ch, CHOICE_SIZE) == 0)
        {
            printf("\tenter error! Please retype your choice1.\n");
            system("pause");
            continue;
        }
        choice = Str_to_num(choice_ch);
        if (choice == -1)
        {
            printf("\tenter error! Please retype your choice.\n");
            system("pause");
            continue;
        }
        switch (choice)
        {
        case 1: //有序创建数据
            //如果链表已存在，提示是否储存或抛弃该数据
            if (list != NULL)
            {
                printf("\tList already exist.\n\tDo you want to store it first or abandon the data.\n");
                printf("\t1.store\t2.abandon\n");
                printf("\tPlease enter:");
                while (1)
                {
                    scanf("%c", &choice1);
                    while (choice1 == '\n')
                        scanf("%c", &choice1);
                    if (choice1 == '1')
                    {
                        printf("\tPlease input the name of the outfile:");
                        scanf("%s", outfile);
                        WritetoText(list, outfile);
                    }
                    else if (choice1 == '2')
                        ;
                    else
                    {
                        printf("\tEnter error. Please enter 1 or 2\n");
                        printf("\tPlease enter:");
                        continue;
                    }
                    Free_all(list);
                    list = NULL;
                    break;
                }
            }
            printf("\tInput Records \n");
            list = Create();
            system("pause");
            break;
        case 2: //分页显示数据
            //如果链表中没有数据
            if (list == NULL)
                printf("\tThere is no data.\n");
            else
                Display(list);
            system("pause");
            break;
        case 3: //插入一条数据
            printf("\tInsert a record:\n");
            list = Insert_a_record(list);
            system("pause");
            break;
        case 4: //删除一条数据
            printf("\tDelete a record:\n");
            list = Delete_a_record(list);
            system("pause");
            break;
        case 5: //排序
            printf("\tSort:\n");
            list = Sort_by_num(list);
            system("pause");
            break;
        case 6: //查找数据
            printf("\tQuery:\n");
            Query_a_record(list);
            system("pause");
            break;
        //从文件中导入数据到链表
        case 7: //从文件导入数据
            //如果链表中已存在数据，应先向用户确认储存下该数据还是放弃数据
            if (list != NULL)
            {
                printf("\tData in the linked list is not stored. Do you want to stored them or abandon them?\n");
                printf("\t1.store them.");
                printf("\t2.abandon them.\n");
                printf("\tenter 1 or 2 to give your choice:");
                while (1)
                {
                    scanf("%c", &choice7);
                    while (choice7 == '\n')
                        scanf("%c", &choice7);
                    if (choice7 == '1')
                    {
                        //此处补充储存数据代码
                        printf("\tPlease input the name of the outfile:");
                        scanf("%s", outfile);
                        WritetoText(list, outfile);
                        break;
                    }
                    if (choice7 == '2')
                        ;
                    else
                    {
                        printf("\tEnter error! Please give your choice in 1 or 2.\n");
                        continue;
                    }
                    //先释放空间
                    Free_all(list);
                    list = NULL;
                    //读取文件数据
                    printf("\tPlease input the name of the infile:");
                    scanf("%s", infile);
                    list = AddfromText(list, infile);
                    break;
                }
            }
            //如果链表中没有数据，则导入数据
            else
            {
                printf("\tPlease input the name of the infile:");
                scanf("%s", infile);
                list = AddfromText(list, infile);
            }
            system("pause");
            break;
        case 8: //向文件写入数据
            printf("\tWrite to a text file \n");
            printf("\tPlease input the name of the outfile:");
            scanf("%s", outfile);
            WritetoText(list, outfile);
            system("pause");
            break;
        case 9: //链表反序
            printf("\tReverse List\n");
            list = Reverse(list);
            system("pause");
            break;
        case 10: //删除相同数据
            printf("\tDelete the same record:\n");
            list = DeleteSame(list);
            system("pause");
            break;
        case 11: //修改一条数据
            printf("\tAlter existing records");
            list = Alter_list(list);
            system("pause");
            break;
        case 0: //退出
            printf("\tQuit\n");
            Quit(list);
            system("pause");
            break;
        default:
            printf("\tEnter error! Please retype your choice.\n");
            system("pause");
            break;
        }
    }
    return 0;
}