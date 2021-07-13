#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include "fun.h"
int main()
{
    TeleBook* list = NULL;
    char choice_ch[CHOICE_SIZE];
    int choice;
    char choice1, choice7;
    char outfile[20];
    char infile[20];
    while (1)
    {
        //��ʾ���˵�
        Display_Main_Menu();
        //������Ϊѡ����ַ���
        scanf("%s", choice_ch);
        //����ַ������ȳ����涨����ʾ����
        if (Check(choice_ch, CHOICE_SIZE) == 0)
        {
            printf("\tenter error! Please retype your choice and limit it in %d size.\n", CHOICE_SIZE - 1);
            system("pause");
            continue;
        }
        //δ��������תΪ��Ӧ���֣�����ת�򷵻�-1
        choice = Str_to_num(choice_ch);
        //�������ת��Ҳ��ʾ����
        if (choice == -1)
        {
            printf("\tenter error! Please retype your choice.\n");
            system("pause");
            continue;
        }
        //����
        system("cls");
        //��ʼƥ�����ѡ��
        switch (choice)
        {
        case 1: //���򴴽�����
            //��������Ѵ��ڣ���ʾ�Ƿ񴢴������������
            if (list != NULL)
            {
                printf("\tList already exist.\n\tDo you want to store it first or abandon the data.\n");
                printf("\t1.store\t2.abandon\t3.quit\n");
                printf("\tPlease enter:");
                while (1)
                {
                    scanf("%c", &choice1);
                    //����ѭ������Ϊ������������Ļ��з��������ȡ�ַ��������з���֮����ֲ���׸��
                    while (choice1 == '\n')
                        scanf("%c", &choice1);
                    //�����1.���Ƚ�����д��һ���ļ����ٴ�������
                    if (choice1 == '1')
                    {
                        printf("\tPlease input the name of the outfile:");
                        scanf("%s", outfile);
                        WritetoText(list, outfile);
                    }
                    //�����2��ֱ�Ӵ�����������ԭ����
                    else if (choice1 == '2')
                        ;
                    //��3��ʾȡ��
                    else if (choice1 == '3')
                        break;
                    //�������ݵ���������ʾ�������
                    else
                    {
                        printf("\tEnter error. Please enter 1 or 2\n");
                        printf("\tPlease enter:");
                        continue;
                    }
                    //�ͷ�ԭ����ȫ���ڴ沢����������
                    Free_all(list);
                    list = NULL; //������������ʱ����ͷָ���ʼ��Ϊ��ָ��
                    break;
                }
            }
            //���ѡ����3 ȡ������ִ����һ���
            if (choice1 != '3')
            {
                printf("\tInput Records \n");
                list = Create();
            }
            system("pause");
            break;
        case 2: //��ҳ��ʾ����
            //���������û�����ݣ���ʾ������
            if (list == NULL)
                printf("\tThere is no data.\n");
            else
                Display(list);
            system("pause");
            break;
        case 3: //����һ������
            printf("\tInsert a record:\n");
            list = Insert_a_record(list);
            system("pause");
            break;
        case 4: //ɾ��һ������
            printf("\tDelete a record:\n");
            list = Delete_a_record(list);
            system("pause");
            break;
        case 5: //����
            printf("\tSort:\n");
            list = Sort_by_num(list);
            if (list != NULL)
                printf("\tSort succeed.\n");
            system("pause");
            break;
        case 6: //��������
            printf("\tQuery:\n");
            Query_a_record(list);
            system("pause");
            break;
            //���ļ��е������ݵ�����
        case 7: //���ļ���������
            printf("\tPlease input the name of the infile:");
            scanf("%s", infile);
            list = AddfromText(list, infile);
            system("pause");
            break;
        case 8: //���ļ�д������
            printf("\tWrite to a text file \n");
            printf("\tPlease input the name of the outfile:");
            scanf("%s", outfile);
            WritetoText(list, outfile);
            system("pause");
            break;
        case 9: //������
            printf("\tReverse List\n");
            list = Reverse(list);
            system("pause");
            break;
        case 10: //ɾ����ͬ����
            printf("\tDelete the same record:\n");
            list = DeleteSame(list);
            system("pause");
            break;
        case 11: //�޸�һ������
            printf("\tAlter existing records\n");
            list = Alter_list(list);
            system("pause");
            break;
        case 0: //�˳�
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