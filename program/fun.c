//函数定义

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fun.h"

int main()
{
    //调试Display_Main_Menu()函数

    Display_Main_Menu();

    //调试Create()函数，Display()函数
    /*
    TeleBook *list;
    list = Create();
    Display(list);
    Free_all(list);
    */

    //list = Reverse(list);
    //Display(list);

    //调试从文件导入数据函数
    TeleBook *list = NULL;
    //list = Create(list);
    //WritetoText(list, "telephone_data.txt");
    list = AddfromText(list, "telephone.txt");
    Display(list);
    Free_all(list);
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
    TeleBook *head = NULL;
    TeleBook *p = (TeleBook *)malloc(LEN);
    char ch = '1';
    while (ch != '0')
    {
        printf("\tPlease input a data(number name phonenumber email):");
        while (1)
        {
            scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
            //进行输入数据检查，是否导致字符数组溢出，如果出现问题则重新输入该条数据
            if (Check(p->num, NUM_SIZE) == 0)
            {
                printf("\tNumber enter error! Please retype the whole data and limit the number in %d size.\n", NUM_SIZE);
                continue;
            }
            if (Check(p->name, NAME_SIZE) == 0)
            {
                printf("\tName enter error! Please retype the whole data and limit the name in %d size.\n", NAME_SIZE);
                continue;
            }
            if (Check(p->phonenum, PHONENUM_SIZE) == 0)
            {
                printf("\tPhonenumber enter error! Please retype the whole data and limit the phonenumber in %d size.\n", PHONENUM_SIZE);
                continue;
            }
            if (Check(p->email, EMAIL_SIZE) == 0)
            {
                printf("\tEmail enter error! Please retype the whole data and limit the email in %d size.\n", EMAIL_SIZE);
                continue;
            }
            //如果上述情况都没出现，则成功输入，退出循环
            //这个循环用于清楚缓冲区多余内容
            while (getchar() != '\n')
                ;
            break;
        }
        head = Insert(head, p);
        printf("\tAdd more data? Enter 1 or enter 0 to end:");
        while (1)
        {
            scanf("%c", &ch);
            while (ch == '\n')
                scanf("%c", &ch);
            if (ch == '1')
            {
                p = malloc(LEN);
                break;
            }
            else if (ch == '0')
            {
                p = NULL;
                return head;
            }
            else
                printf("\tEnter error! Please input 1 or 0.\n");
        }
    }

    return head;
}

//输出链表数据
//每十个暂停一下
void Display(TeleBook *head)
{
    int i;
    int page = 1;
    char choice, choice2;
    //此页首个数据
    TeleBook *page_head;
    TeleBook *data = head;
    while (data != NULL)
    {
        system("cls");
        page_head = data;
        printf("\t%-8s%-15s%-20s%s\n\n", "number", "name", "phonenumber", "email");
        for (i = 0; i < 10 && data != NULL; i++)
        {
            printf("\t%-8s", data->num);
            printf("%-15s", data->name);
            printf("%-20s", data->phonenum);
            printf("%s\n", data->email);
            data = data->next;
        }
        printf("\n\tpage%d\n", page);
        printf("\n\tpage up:1               page down:2               end:0\n");
        printf("\tPlease enter:");
        while (1)
        {
            scanf("%c", &choice);
            while (choice == '\n')
                scanf("%c", &choice);
            if (choice == '1')
            {
                //如果page=1表明这是第一页，无法往上翻
                if (page == 1)
                    printf("\tError! This is the first page. Please retype:");
                //通过反序链表让page_head向前回溯20个
                else
                {
                    page--;
                    head = Reverse(head);
                    for (i = 0; i < 10; i++)
                        page_head = page_head->next;
                    data = page_head;
                    //再把链表顺序调整回来，显示十个数据
                    head = Reverse(head);
                    break;
                }
            }
            else if (choice == '2')
            {
                if (data == NULL)
                    printf("\tError! This is the last page. Please retype:");
                else
                {
                    page++;
                    break;
                }
            }
            else if (choice == '0')
            {
                data = NULL;
                break;
            }
            else
                printf("\tEnter error! Please enter 1 or 2 to give your choice:");
        }
    }
}

//结点的有序插入
//按编号为序插入记录s，返回链表头指针
TeleBook *Insert(TeleBook *head, TeleBook *s)
{
    //这个指针用来做中间值
    TeleBook *fp;
    //这个指针作为循环变量
    TeleBook *data;
    //首先将新数据的编号转化成标准形式
    Num_modi(s->num);
    //如果链表中没有数据
    if (head == NULL)
    {
        s->next = NULL;
        head = s;
        return head;
    }
    //如果新插入的数据编号顺序在链表头的前面
    if (strcmp(s->num, head->num) < 0)
    {
        s->next = head;
        head = s;
        return head;
    }
    data = head;
    while (data != NULL && data->next != NULL)
    {
        if (strcmp(data->num, s->num) <= 0 && strcmp(s->num, data->next->num) < 0)
        {
            fp = data->next;
            data->next = s;
            s->next = fp;
            return head;
        }
        data = data->next;
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
TeleBook *Insert_a_record(TeleBook *head) //未检验正确性，未考虑出现相同编号的情况
{
    TeleBook *p = (TeleBook *)malloc(LEN);
    printf("\tPlease input a data(number name phonenumber email):");
    while (1)
    {
        scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
        //进行输入数据检查，是否导致字符数组溢出，如果出现问题则重新输入该条数据
        if (Check(p->num, NUM_SIZE) == 0)
        {
            printf("\tNumber enter error! Please retype the whole data and limit the number in %d size.\n", NUM_SIZE);
            continue;
        }
        if (Check(p->name, NAME_SIZE) == 0)
        {
            printf("\tName enter error! Please retype the whole data and limit the name in %d size.\n", NAME_SIZE);
            continue;
        }
        if (Check(p->phonenum, PHONENUM_SIZE) == 0)
        {
            printf("\tPhonenumber enter error! Please retype the whole data and limit the phonenumber in %d size.\n", PHONENUM_SIZE);
            continue;
        }
        if (Check(p->email, EMAIL_SIZE) == 0)
        {
            printf("\tEmail enter error! Please retype the whole data and limit the email in %d size.\n", EMAIL_SIZE);
            continue;
        }
        //如果上述情况都没出现，则成功输入，退出循环
        break;
    }
    if ((head = Insert(head, p)) != NULL)
        printf("\tInsert succeed!\n");
    return head;
}

//结点删除
//删除编号为num的记录
TeleBook *Delete(TeleBook *head, char *num) //未检验
{
    //循环指针
    TeleBook *data = head;
    //中间指针
    TeleBook *fp;
    char choice;
    if (strcmp(head->num, num) == 0)
    {
        printf("\tAre you sure to delete it?(y/n):");
        while (1)
        {
            scanf("%c", &choice);
            while (choice == '\n')
                scanf("%c", &choice);
            if (choice == 'y')
                break;
            else if (choice == 'n')
                return head;
            else
                printf("\tEnter error. Please enter y or n :");
        }
        fp = head;
        head = head->next;
        free(fp);
        printf("\tDelete Succeed!\n");
        return head;
    }
    while (data->next != NULL)
    {
        if (strcmp(data->next->num, num) == 0)
        {
            fp = data->next;
            data->next = data->next->next;
            free(fp);
            printf("\tDelete Succeed!\n");
            return head;
        }
    }
    printf("\tCannot find the number you input. Delete fail.\n");
    return head;
}
//输入待删除编号，用Delet删除，输出是否删除成功
TeleBook *Delete_a_record(TeleBook *head)
{
    char num[NUM_SIZE];
    //如果链表中无数据
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    printf("\tPlease input the number of the data you want to delete:");
    while (1)
    {
        scanf("%s", num);
        if (Check(num, NUM_SIZE) == 1)
            break;
        printf("\tEnter error! Please limit it in %d size.\n", NUM_SIZE);
    }
    Num_modi(num);
    head = Delete(head, num);
    return head;
}

//排序
//以编号为序升序排
TeleBook *Sort_by_num(TeleBook *head) //未检验
{
    //循环指针
    TeleBook *data1, *data2;
    //中间指针
    TeleBook *fp1, *fp2;
    //data2的前一个结点指针
    TeleBook *pre;
    int count = 0;
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //如果链表中只有一个结点，直接返回即可
    if (head->next == NULL)
        return head;
    //data1的循环只用作计数
    for (data1 = head; data1 != NULL; data1 = data1->next)
        count++;
    //冒泡排序
    for (; count > 1; count--)
    {
        //data2用作冒泡
        //由于head指针没有pre,故须单独讨论
        if (strcmp(head->num, head->next->num) > 0)
        {
            //进行相邻结点的交换
            fp1 = head->next;
            head->next = head->next->next;
            fp1->next = head;
            head = fp1;
        }
        pre = head;
        data2 = head->next;
        while (data2->next != NULL)
        {
            if (strcmp(data2->num, data2->next->num) > 0)
            {
                //相邻结点交换
                pre->next = data2->next;
                fp1 = data2->next->next;
                data2->next->next = data2;
                data2->next = fp1;
                pre = pre->next;
            }
            else
            {
                pre = data2;
                data2 = data2->next;
            }
        }
    }
    return head;
}

//结点数据查询
//查找编号为num的记录，成功则返回地址，失败返回NULL
TeleBook *Query(TeleBook *head, char *num)
{
    TeleBook *data = head;
    while (data != NULL)
    {
        if (strcmp(data->num, num) == 0)
            return data;
        data = data->next;
    }
    return (NULL);
}
//输入待查找编号，用Query查找，输出成功与否及结点信息
void Query_a_record(TeleBook *head)
{
    char num[NUM_SIZE];
    char choice;
    TeleBook *data;
    //如果链表不存在
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return;
    }
    while (1)
    {
        printf("\tPlease input the number you want to search:");
        scanf("%s", num);
        Num_modi(num);
        Check(num, NUM_SIZE);
        data = Query(head, num);
        if (data != NULL)
        {
            printf("\tOperation Success\n");
            printf("\t%-8s%-15s%-20s%s\n", data->num, data->name, data->phonenum, data->email);
        }
        else
            printf("\tCannot find this number!\n");
        printf("\tEnter 1 to continue to query or 0 to end.");
        while (1)
        {
            printf("\tPlease enter:");
            scanf("%c", &choice);
            while (choice == '\n')
                scanf("%c", &choice);
            if (choice == '1')
                break;
            else if (choice == '0')
                return;
            else
            {
                printf("\tEnter error. Please retype.\n");
            }
        }
    }
}

//从文件中整批输入信息
//从文件filename添加一批记录到链表中，用Insert()有序插入
TeleBook *AddfromText(TeleBook *head, char *filename)
{
    //记录条数变量
    int num;
    //循环指针
    TeleBook *data;
    FILE *in;
    //如果文件打开失败，打印打开错误，返回空指针
    if ((in = fopen(filename, "r")) == NULL)
    {
        printf("\tFile open error!\n");
        return NULL;
    }
    data = (TeleBook *)malloc(LEN);
    fscanf(in, "%d", &num);
    //如果文件指针不指向文件末尾，读入一条数据并插入链表
    while (!feof(in))
    {
        fscanf(in, "%s %s %s %s\n", data->num, data->name, data->phonenum, data->email);
        head = Insert(head, data);
        if (!feof(in))
            data = (TeleBook *)malloc(LEN);
    }
    if (num == 0)
        printf("\tFile has no contant.\n");
    else
        printf("\t%d data import succeed!\n", num);
    return head;
}

//将链表结点记录写入到文件中
//将链表中的结点记录全部写入文件records.txt
void WritetoText(TeleBook *head, char *filename)
{
    FILE *fp;
    TeleBook *data;
    //临时储存文件数据链表
    TeleBook *data0 = NULL;
    //中间数据指针
    TeleBook *p;
    int num = 0;
    //打开文件//
    //如果文件中有内容，即文件原先就存在，则先读取文件中数据记录条数，将文件数据储存在一个临时链表中，之后依次输入两个链表
    if ((fp = fopen(filename, "r+")) != NULL)
    {
        p = (TeleBook *)malloc(LEN);
        fscanf(fp, "%d", &num);
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s\n", p->num, p->name, p->phonenum, p->email);
            data0 = Insert(data0, p);
            if (!feof(fp))
                p = (TeleBook *)malloc(LEN);
        }
        for (data = head; data != NULL; data = data->next)
            num++;
        //返回文件标头
        rewind(fp);
        //输入计数
        fprintf(fp, "%d\n", num);
        //输入原数据
        p = data0;
        while (p != NULL)
        {
            fprintf(fp, "%s  %s  %s  %s\n", p->num, p->name, p->phonenum, p->email);
            p = p->next;
        }
        Free_all(data0);
        //输入新数据
        data = head;
        while (data != NULL)
        {
            fprintf(fp, "%s  %s  %s  %s\n", data->num, data->name, data->phonenum, data->email);
            data = data->next;
        }
    }
    else
    {
        if ((fp = fopen(filename, "w")) == NULL)
        {
            printf("\tFile write error.\n");
            return;
        }
        //进行计数
        for (data = head; data != NULL; data = data->next)
            num++;
        //输入计数
        fprintf(fp, "%d\n", num);
        //向文件输入数据
        data = head;
        while (data != NULL)
        {
            fprintf(fp, "%s  %s  %s  %s\n", data->num, data->name, data->phonenum, data->email);
            data = data->next;
        }
    }
    fclose(fp);
    printf("\tWrite Succeed!\n");
}

//链表反序存放
TeleBook *Reverse(TeleBook *head)
{
    //分别存放前一个数据地址和后一个数据地址
    TeleBook *fp1 = NULL, *fp2;
    while (head != NULL)
    {
        fp2 = head->next;
        head->next = fp1;
        fp1 = head;
        head = fp2;
    }
    return fp1;
}

//删除雷同记录
//删除链表中姓名，电话，电子邮件地址均相同的记录
TeleBook *DeleteSame(TeleBook *head)
{
    TeleBook *data;
    TeleBook *p1, *p2;
    //用于记录p1的前一个指针
    TeleBook *pre;
    int i = 0;
    //如果链表中没有数据
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //如果链表中只有一个数据，则不可能有相同的
    if (head->next == NULL)
    {
        printf("\tThere is no same data.\n");
        return head;
    }
    for (data = head; data != NULL && data->next != NULL; data = data->next)
    {
        p1 = data->next;
        pre = data;
        while (p1 != NULL)
        {
            if (strcmp(data->name, p1->name) == 0 && strcmp(data->phonenum, p1->phonenum) == 0 && strcmp(data->email, p1->email) == 0)
            {
                i++;
                pre->next = p1->next;
                free(p1);
                p1 = pre->next;
            }
            else
            {
                pre = p1;
                p1 = p1->next;
            }
        }
    }
    if (i > 0)
        printf("\t%d Delete Succeed\n", i);
    else
        printf("\tThere is no same data.\n");
    return head;
}

//退出管理系统
void Quit(TeleBook *head)
{
    char ch;
    printf("\tAre you sure you want to exit?\n");
    printf("\t1.Yes\t0.NO\n");
    while (1)
    {
        while ((ch = getchar()) == '\n')
            ;
        if (ch == '1')
        {
            Free_all(head);
            exit(0);
        }
        else if (ch == '0')
            break;
        printf("\tEnter error!\n");
        printf("\t1.Yes\t0.NO\n");
    }
}

//显示主菜单
void Display_Main_Menu()
{
    system("cls");
    printf("\n");
    printf("       The telephone Management System       \n");
    printf("---------------------------------------------\n");
    printf("|                   Menu                    |\n");
    printf("|-------------------------------------------|\n");
    printf("|       1.Input Record                      |\n");
    printf("|       2 Display All Records               |\n");
    printf("|       3 Insert a Record                   |\n");
    printf("|       4 Delete a Record                   |\n");
    printf("|       5 Sort                              |\n");
    printf("|       6 Query                             |\n");
    printf("|       7 Add Records from a Text File      |\n");
    printf("|       8 Write to a Text File              |\n");
    printf("|       9 Reverse List                      |\n");
    printf("|       10 Delete the Same Records          |\n");
    printf("|       11 Quit                             |\n");
    printf("|       0 Quit                              |\n");
    printf("---------------------------------------------\n");
    printf("        Please enter your choice(0-10):");
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
    //如果字符数组第一个就是空字符，即无内容，返回0
    if (*str == '\0')
        return 0;
    //如果在字符数组的非首位空间中找到了空字符，即终止符，返回1
    for (i = 1; i < size; i++)
    {
        if (*(str + i) == '\0')
            return 1;
    }
    //如果字符数组中未出现空字符，返回0
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
        str++;
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

//修改数据函数//
//修改链表中的某数据//
TeleBook *Alter_list(TeleBook *head) //待修改！！！
{
    char s[20];
    char choice;
    TeleBook *data = head;
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //找到想要修改的结构体//
    printf("\tPlease input the name of the data you want to alter:");
    scanf("%s", s);
    while (strcmp(s, data->name) != 0)
    {
        data = data->next;
        if (data == NULL)
        {
            printf("\tNot Found!\n");
            return head;
        }
    }
    printf("\tFound Succeed\n");
    printf("\tName: ");
    puts(data->name);
    printf("\tNumber: ");
    puts(data->num);
    printf("\tPhonenumber: ");
    puts(data->phonenum);
    printf("\tE-mail: ");
    puts(data->email);
    putchar('\n');
    //选择想要修改的数据//
    while (1)
    {
        printf("\tAlter(1.Name 2.Number 3.Phonenumber 4.E-mail 5 Quit)\n");
        printf("\tPlease enter:");
        scanf("%c", &choice);
        while (choice == '\n')
            scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            printf("\tPlease input new name:");
            scanf("%s", data->name);
            break;
        case '2':

            printf("\tPlease input new number:");
            scanf("%s", data->num);
            break;
        case '3':
            printf("\tPlease input new phonenumber:");
            scanf("%s", data->phonenum);
            break;
        case '4':
            printf("\tPlease input new E-mail:");
            scanf("%s", data->email);
            break;
        case '5':
            return head;
            break;
        default:
            printf("\tEnter error! Please retype:");
        }
        printf("\tDo you want to alter any more?\n");
    }
}