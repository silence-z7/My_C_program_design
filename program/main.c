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
        //显示主菜单
        Display_Main_Menu();
        //输入作为选择的字符串
        scanf("%s", choice_ch);
        //如果字符串长度超过规定，提示错误
        if (Check(choice_ch, CHOICE_SIZE) == 0)
        {
            printf("\tenter error! Please retype your choice1.\n");
            system("pause");
            continue;
        }
        //未超出则将其转为对应数字，不可转则返回-1
        choice = Str_to_num(choice_ch);
        //如果不可转，也提示错误
        if (choice == -1)
        {
            printf("\tenter error! Please retype your choice.\n");
            system("pause");
            continue;
        }
        //清屏
        system("cls");
        //开始匹配你的选择
        switch (choice)
        {
        case 1: //有序创建数据
            //如果链表已存在，提示是否储存或抛弃该数据
            if (list != NULL)
            {
                printf("\tList already exist.\n\tDo you want to store it first or abandon the data.\n");
                printf("\t1.store\t2.abandon\t3.quit\n");
                printf("\tPlease enter:");
                while (1)
                {
                    scanf("%c", &choice1);
                    //这种循环都是为了清除缓冲区的换行符，避免读取字符读到换行符，之后出现不予赘述
                    while (choice1 == '\n')
                        scanf("%c", &choice1);
                    //如果输1.则先将链表写入一个文件，再创建链表
                    if (choice1 == '1')
                    {
                        printf("\tPlease input the name of the outfile:");
                        scanf("%s", outfile);
                        WritetoText(list, outfile);
                    }
                    //如果是2，直接创建链表并覆盖原数据
                    else if (choice1 == '2')
                        ;
                    //输2表示取消
                    else if (choice1 == '3')
                        break;
                    //其他内容的输入则提示输入错误
                    else
                    {
                        printf("\tEnter error. Please enter 1 or 2\n");
                        printf("\tPlease enter:");
                        continue;
                    }
                    //释放原链表全部内存并创建新链表
                    Free_all(list);
                    list = NULL;
                    break;
                }
            }
            //如果选的是3 取消，则不执行这一语块
            if (choice1 != '3')
            {
                printf("\tInput Records \n");
                list = Create();
            }
            system("pause");
            break;
        case 2: //分页显示数据
            //如果链表中没有数据，提示无数据
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
            if (list != NULL)
                printf("\tSort succeed.\n");
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
                printf("\t2.abandon them.");
                printf("\t3.quit\n");
                printf("\tPlease enter:");
                while (1)
                {
                    scanf("%c", &choice7);
                    while (choice7 == '\n')
                        scanf("%c", &choice7);
                    //如果输1，将链表中数据先储存在一个文件中
                    if (choice7 == '1')
                    {
                        printf("\tPlease input the name of the outfile:");
                        scanf("%s", outfile);
                        WritetoText(list, outfile);
                    }
                    //输2直接读取文件
                    else if (choice7 == '2')
                        ;
                    //取消
                    else if (choice7 == '3')
                        break;
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
            printf("\tAlter existing records\n");
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
