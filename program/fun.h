//预定义常量
//结构体声明
//函数声明

#define LEN sizeof(TeleBook)
#define CHOICE_SIZE 3
#define NUM_SIZE 4
#define NAME_SIZE 10
#define PHONENUM_SIZE 15
#define EMAIL_SIZE 20

#ifndef _FUN_H_
#define _FUN_H_

//结构体声明
struct telebook
{
    char num[NUM_SIZE];           //编号
    char name[NAME_SIZE];         //姓名
    char phonenum[PHONENUM_SIZE]; //电话号码
    char email[EMAIL_SIZE];       //电子邮件地址
    struct telebook *next;        //下一结点指针
};
typedef struct telebook TeleBook;

//建立有序链表
//从键盘输入若干条记录，调用Insert函数建立以“编号”为序的单向链表
TeleBook *Create();

//输出链表数据
void Display(TeleBook *head);

//结点的有序插入
//插入记录s，返回链表头指针
TeleBook *Insert(TeleBook *head, TeleBook *s);
//输入待插入的编号、姓名、联系电话、电子邮件地址等信息，
//调用Insert函数按“编号”做有序插入，输出插入成功信息，返回链表头指针。
TeleBook *Insert_a_record(TeleBook *head);

//结点删除
//删除编号为num的记录
TeleBook *Delete(TeleBook *head, char *num);
//输入待删除编号，用Delet删除，输出是否删除成功
TeleBook *Delete_a_record(TeleBook *head);

//排序
//以编号为序升序排
TeleBook *Sort_by_num(TeleBook *head);

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
void Quit(TeleBook *head);

//显示主菜单
void Display_Main_Menu();

//释放链表动态内存
void Free_all(TeleBook *head);

//其他函数

//字符串防溢出检查函数，返回值为1，0
//字符数组str大小为size，若字符串无内容或无终止符返回0，否则返回1
int Check(char *str, int size);

//字符转数字函数，若出现非数字字符返回-1，成功返回该数字
int Str_to_num(char *str);

//编号修正函数
//使得所有编号均为三位数的形式
//如1转化成001，12变成012
void Num_modi(char *num);

#endif