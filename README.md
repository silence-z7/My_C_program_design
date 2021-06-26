My_C_program_design

选题一：电话簿管理系统
一、系统功能
	电话簿管理系统要求实现一个电话簿系统的基本管理功能，包括添加、删除、查找和导入/导出等。电话簿记录项的格式即基本属性包括编号、姓名、联系电话、电子邮件地址等。系统目前仅考虑英文姓名数据输入，不支持中文。
	功能要求：
1.创建：创建电话簿，用逐条输入的方式；
2.显示：分屏显示电话簿中的所有记录；
3.插入：向电话簿中插入一条记录；
4.删除：删除一条已经存在的记录项；
5.排序：以编号为依据升序排列所有记录项；
6.查找：根据用户输入的属性值查找符合条件的记录项；
7.导入/导出：可以从文件读入已有的电话簿，也可将通讯录信息导出到文件；
8.反序：以编号为依据将按序排列的记录项反序排列；
9.删除相同记录。
 
	构建如图菜单系统，程序执行过程为：循环显示主菜单，用户在Give your choice:处输入选项，即按照功能列表输入0~10中的任意一个数字，按回车后，执行相应的功能。功能执行完毕，返回菜单。
	各菜单项功能如下：
	（1）Input Records（建立有序单向链表）
	从键盘上一次输入一条电话簿记录（编号、姓名、电话号码和电子邮件地址），以“编号”为序建立有序链表。插入一条记录后，显示提示信息：确认是否输入下一条记录，如确认，继续输入，否则，退出输入功能。
	（2）Display All Records（显示所有结点记录）
	按顺序显示链表中所有记录，每屏显示10条记录，按<Enter>键继续显示下一屏。
	（3）Insert a Record（插入一条结点记录）
	在以“编号”为序排列的链表中插入一条记录，插入后，链表仍有序。输出插入成功的信息。
	（4）Delete a Record（按“编号”查找，找到后删除该条结点记录）
	输入待删除记录的“编号”，显示提示信息，让用户再次确认是否要删除。确认后，将该“编号”的记录删除。
	（5） Sort（排序）
	以“编号”为升序排列链表中的记录。
	（6）Query（查找并显示一个结点记录）
	输入“编号”，查找该记录，找到后显示记录信息。
	（7）Add Records from a Text File（从文件中添加数据到链表中）
	用户可事前建立一个文件data.txt，存放多个待加入的记录。提示输入文件的文件名，然后从该文件中一次性加入多条电话簿记录。文件data.txt格式如下：
 
	注意：该文件中第一行的数字表示待添加的记录数，下面每行为电话薄记录。
	（8）Write to a Text File（将链表中记录写入文件）
	将电话簿中的全部记录写入文件records.txt，要求文件格式和文件data.txt相同。
	（9）Reverse List（将链表反序）
	将链表中的所有结点按“编号”反序存放。
	（10）Delete the Same Records（删除相同记录）
	删除姓名、电话、电子邮件地址均相同的记录。
	（0）Quit（退出电话簿管理系统程序）
	退出电话簿管理系统程序，并释放链表存储空间。
二、实现要求
	1.数据结构
	用单向链表实现电话薄的记录和管理，每一个结点存放一条记录。结点结构如下：
 ```c
    struct telebook
    {
    char num[NUM_SIZE];            //编号
    char name[NAME_SIZE];          //姓名
    char phonenum[PHONENUM_SIZE];      //电话号码
    char email[EMAIL_SIZE];         //电子邮件地址
    struct telebook *next;  //下一结点指针
    };
    typedef struct telebook TeleBook;
```

	2.各函数功能
	以下函数原型说明中出现的函数为本题的基本要求。请不要更改函数原型，以下序号为菜单序号。
	（1）建立有序链表
    TeleBook *Create();
    从键盘输入若干条记录，调用Insert函数建立以“编号”为序的单向链表，返回链表头指针。
	（2）输出链表数据
	void Display(TeleBook *head);
	显示所有电话簿记录，每10个暂停一下。
	（3）结点的有序插入
	TeleBook *Insert(TeleBook *head, TeleBook *s);
	按“编号”为序插入记录s，返回链表头指针。
	TeleBook *Insert_a_record(TeleBook *head);
	输入待插入的编号、姓名、联系电话、电子邮件地址等信息，调用Insert函数按“编号”做有序插入，输出插入成功信息，返回链表头指针。
	（4）结点删除
	TeleBook *Delete(TeleBook *head,char *num);
	删除“编号”为num的记录，返回链表头指针。
	TeleBook *Delete_a_record(TeleBook *head);
	输入待删除的“编号”，经确认后调用Delete函数删除该“编号记录”，输出删除成功与否的信息。返回链表头指针。
	（5）排序
	void Sort_by_num(TeleBook *head);
	以“编号”为升序排列链表中的记录。
	（6）结点数据查询
	TeleBook *Query(TeleBook *head,char *num);
	查找“编号”为num的记录，查找成功返回该结点地址；否则，返回空指针。
	Void Query_a_record(TeleBook *head);
	输入待查找的“编号”，调用Query函数查找该“编号”的记录，输出查找成功与否的信息和结点信息。
	（7）从文件中整批输入数据
	TeleBook *AddfromText(TeleBook *head,char *filename);
	从文件filename添加一批记录到链表中，调用Insert()函数作有序插入，返回链表头指针。
	（8）将链表结点记录写入到文件中
	void WritetoText(TeleBook *head, char *filename);
	将链表中的结点记录全部写入文件records.txt。
	（9）链表反序存放
	TeleBook *Reverse(TeleBook *head);
	按“编号”序反序存放链表，函数返回链表头指针。
	（9）删除雷同记录
	TeleBook *DeleteSame(TeleBook *head);
	删除链表中姓名、电话、电子邮件地址均相同的记录，函数返回链表头指针。
	（0）退出管理系统
	void Quit(TeleBook *head);
	退出系统时，释放动态存储空间。
	其他函数
	Void Display_Main_Menu();
	显示主菜单。
	实验过程中可以根据需要适当增加函数，以使程序算法更清晰明了。
四、程序运行界面
 

