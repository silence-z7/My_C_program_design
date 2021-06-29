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
TeleBook *Insert(TeleBook *head, TeleBook *s) //未检验正确性
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
TeleBook *Insert_a_record(TeleBook *head) //未检验正确性，未考虑出现相同编号的情况
{
    TeleBook *p;
    printf("Please input a data(number name phonenumber email):");
    while (1)
    {
        scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
        //进行输入数据检查，是否导致字符数组溢出，如果出现问题则重新输入该条数据
        if (Check(p->num, NUM_SIZE) == 0)
        {
            printf("Number enter error! Please retype the whole data and limit the number in %d size.\n", NUM_SIZE);
            continue;
        }
        if (Check(p->name, NAME_SIZE) == 0)
        {
            printf("Number enter error! Please retype the whole data and limit the name in %d size.\n", NAME_SIZE);
            continue;
        }
        if (Check(p->phonenum, PHONENUM_SIZE) == 0)
        {
            printf("Number enter error! Please retype the whole data and limit the phonenumber in %d size.\n", PHONENUM_SIZE);
            continue;
        }
        if (Check(p->email, EMAIL_SIZE) == 0)
        {
            printf("Number enter error! Please retype the whole data and limit the email in %d size.\n", EMAIL_SIZE);
            continue;
        }
        //如果上述情况都没出现，则成功输入，退出循环
        break;
    }
    if (Insert(head, p) != NULL)
        printf("Insert succeed!\n");
    return head;
}

//结点删除
//删除编号为num的记录
TeleBook *Delete(TeleBook *head, char *num)//未检验
{
    //循环指针
    TeleBook *data = head;
    while (data != NULL)
    {
        if (strcmp(data->num, num) == 0)
        {
            data = data->next;
			printf("Delete Succeed!");
            return head;
        }
    }
    printf("Cannot find the number you input. Delete fail.\n");
    return head;
}
//输入待删除编号，用Delet删除，输出是否删除成功
TeleBook *Delete_a_record(TeleBook *head)
{
    char num[NUM_SIZE];
    printf("Please input the number of the data you want to delete:");
    while (1)
    {
        scanf("%s", num);
        if(Check(num,NUM_SIZE)==1)
            break;
        printf("enter error! Please limit it in %d size.\n",NUM_SIZE);
    }
    Num_modi(num);
    head=Delete(head,num);
    return head;
}

//排序
//以编号为序升序排
void Sort_by_num(TeleBook *head);
{


}

//结点数据查询
//查找编号为num的记录，成功则返回地址，失败返回NULL
TeleBook *Query(TeleBook *head, char *num)
{
	TeleBook *data=head;
	while(data != NULL)
	{
		if(strcmp(data->num,num)==0)
			return data;
		data=data->next;
	}
	return(NULL);
}
//输入待查找编号，用Query查找，输出成功与否及结点信息
void Query_a_record(TeleBook *head)
{
    char num[NUM_SIZE];
    TeleBook *data;
	printf("Please input the number you want to search:");
	gets(num);
	Num_modi(num);
	Check(num,NUM_SIZE);
    data=Query(head,num);
    if(data != NULL)
    {   
        printf("Operation Success\n");
        printf("%s %s %s %s",data->num,data->name,data->phonenum,data->email);
    }
    else
        printf("Input error!\n");
}

//从文件中整批输入信息
//从文件filename添加一批记录到链表中，用Insert()有序插入
TeleBook *AddfromText(TeleBook *head, char *filename);

//将链表结点记录写入到文件中
//将链表中锋结点记录全部写入文件records.txt
void WritetoText(TeleBook *head, char *filename);

//链表反序存放
TeleBook *Reverse(TeleBook *head)
{
    //分别存放前一个数据地址和后一个数据地址
    TeleBook*fp1=NULL,*fp2;  
    while(head!=NULL)
    {
        fp2=head->next;
        head->next=fp1;
        fp1=head;
        head=fp2;
    }
    return fp1;
}

//删除雷同记录
//删除链表中姓名，电话，电子邮件地址均相同的记录
TeleBook *DeleteSame(TeleBook *head);
{   
    TeleBook *p1,*p2;
	int i=0;
    for(data=head;data!=NULL;data=data->next)
       for(p1=data,p2=data->next;p2!=NULL;p1=p2,p2=p2->next)
	        if (strcmp(data->name,p2->name) == 0 && strcmp(data->phonenum,p2->phonenum) == 0 && strcmp(data->email,p2->email) == 0)
	        {     
                i++;
                p1->next=p2->next;
                free(p2);
            }
            if(i>0)  printf("Delete Succeed\n"); 
            else      printf("No intems in common\n"); 
     return(head);
 
}

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