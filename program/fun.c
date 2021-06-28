//函数定义

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fun.h"

int main()
{
    TeleBook *list;

    Display_Main_Menu();
    list = Create();
    Display(list);

    //调试Num_modi()函数
    /*
    char num[4]="1";
    Num_modi(num);
    printf("%s",num);
    */
    return 0;
}

//建立有序链表
//从键盘输入若干条记录，调用Insert函数建立以“编号”为序的单向链表
TeleBook *Create()
{
    TeleBook *head = (TeleBook *)malloc(LEN);
    TeleBook *p = head;
    int n;
    printf("Please input the number of data:");
    scanf("%d", &n);
    while (n-- != 0)
    {
        printf("Please input a data(number name phonenumber email):");
        scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
        if (n != 0)
            p->next = malloc(LEN);
        else
            p->next = NULL;
        p = p->next;
    }

    return head;
}

//输出链表数据
//每十个暂停一下
void Display(TeleBook *head)
{
    int i;
    while (head != NULL)
    {
        for (i = 0; i < 10 && head != NULL; i++)
        {
            printf("%-4s", head->num);
            printf("%-15s", head->name);
            printf("%s     ", head->phonenum);
            printf("%s\n", head->email);
            head = head->next;
        }
        system("pause");
        system("cls");
    }
}

//结点的有序插入
//按编号为序插入记录s，返回链表头指针
TeleBook *Insert(TeleBook *head, TeleBook *s) //未检验正确性，未考虑出现相同编号的情况
{
    //这个指针用来做中间值
    TeleBook *fp;
    //这个指针作为循环变量
    TeleBook *data;
    //首先将新数据的编号转化成标准形式
    Num_modi(s->num);
    //如果新插入的数据编号顺序在链表头的前面
    if (strcmp(s->num, head->num) < 0)
    {
        fp = head->next;
        head = s;
        s->next = fp;
        return head;
    }
    data = head;
    while (data != NULL && data->next != NULL)
    {
        if (strcmp(data->num, s->num) < 0 && strcmp(s->num, data->next->num) > 0)
        {
            fp = data->next;
            data->next = s;
            s->next = fp;
            return head;
        }
    }
    //如果新插入数据编号顺序在链表末尾的后面
    if (data->next == NULL)
    {
        data->next = s;
        s->next = NULL;
        return head;
    }
}
//输入待插入的编号、姓名、联系电话、电子邮件地址等信息，
//调用Insert函数按“编号”做有序插入，输出插入成功信息，返回链表头指针。
TeleBook *Insert_a_record(TeleBook *head)
{
    TeleBook *p;
    printf("Please input a data(number name phonenumber email):");
    scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
    if (Insert(head, p) != NULL)
        printf("Insert succeed!\n");
    return head;
}

//结点删除
//删除编号为num的记录
TeleBook *Delete(TeleBook *head, char *num);
//输入待删除编号，用Delet删除，输出是否删除成功
TeleBook *Delete_a_record(TeleBook *head);

//排序
//以编号为序升序排
void Sort_by_num(TeleBook *head);

//结点数据查询
//查找编号为num的记录，成功则返回地址，失败返回NULL
TeleBook *Query(TeleBook *head, char *num);
//输入带查找编号，用Query查找，输出成功与否及结点信息
void Query_a_record(TeleBook *head);

//从文件中整批输入信息
//从文件filename添加一批记录到链表中，用Insert()有序插入
TeleBook *AddfromText(TeleBook *head, char *filename);

//将链表结点记录写入到文件中
//将链表中锋结点记录全部写入文件records.txt
void WritetoText(TeleBook *head, char *filename);

//链表反序存放
TeleBook *Reverse(TeleBook *head);

//删除雷同记录
//删除链表中姓名，电话，电子邮件地址均相同的记录
TeleBook *DeleteSame(TeleBook *head);

//退出管理系统
void Quit(TeleBook *head)
{
    char ch;
    printf("Are you sure you want to exit?\n");
    printf("    1.Yes   0.NO\n");
    while (1)
    {
        if ((ch = getchar()) == '1')
        {
            Free_all(head);
            exit(0);
        }
        else if (ch == '0')
            break;
        printf("enter error!\n");
        printf("    1.Yes   0.NO\n");
        getchar();
    }
}

//显示主菜单
void Display_Main_Menu()
{
    printf("\n");
    printf("       The telephone Management System       \n");
    printf("---------------------------------------------\n");
    printf("|                   Menu                    |\n");
    printf("|-------------------------------------------|\n");
    printf("|     1.Input Record                        |\n");
    printf("|     2 Display All Records                 |\n");
    printf("|     3 Insert a Record                     |\n");
    printf("|     4 Delete a Record                     |\n");
    printf("|     5 Sort                                |\n");
    printf("|     6 Query                               |\n");
    printf("|     7 Add Records from a Text File        |\n");
    printf("|     8 Write to a Text File                |\n");
    printf("|     9 Reverse List                        |\n");
    printf("|     10 Delete the Same Records            |\n");
    printf("|     0 Quit                                |\n");
    printf("---------------------------------------------\n");
    printf("      Please enter your choice(0-10):");
}

//释放链表动态内存
void Free_all(TeleBook *head)
{
    TeleBook *fp;

    while (head != NULL)
    {
        fp = head;
        head = head->next;
        free(fp);
    }
}

//字符串防溢出检查函数，返回值为1，0
int Check(char *str, int size)
{
    int i;

    if (*str == '\0')
        return 0;
    for (i = 1; i < size; i++)
    {
        if (*(str + i) == '\0')
            return 1;
    }
    return 0;
}

//字符转数字函数，若出现非数字字符返回-1，成功返回该数字
int Str_to_num(char *str)
{
    int sum = 0;
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return -1;
        sum = sum * 10 + *str - '0';
    }
    return sum;
}

//编号修正函数
//使得所有编号均为三位数的形式
//如1转化成001，12变成012
void Num_modi(char *num)
{
    int n;
    int i;
    for (n = strlen(num); n < 3; n++)
    {
        //每次循环让字符串整体后移一个位置，并且在最开头添上'0'
        for (i = n; i > 0; i--)
            num[i] = num[i - 1];
        num[0] = '0';
    }
}