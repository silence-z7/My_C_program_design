#define _CRT_SECURE_NO_WARNINGS

//��������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fun.h"

//������������
//�Ӽ���������������¼������Insert���������ԡ���š�Ϊ��ĵ�������
TeleBook* Create()
{
    TeleBook* head = NULL;
    TeleBook* p = (TeleBook*)malloc(LEN); //����һ����Ÿýṹ��Ŀռ䣬ʹpָ��ÿռ�
    char ch = '1';
    while (ch != '0')
    {
        printf("\tPlease input a data(number name phonenumber email):");
        while (1)
        {
            scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
            //�����������ݼ�飬�Ƿ����ַ��������������������������������������
            if (Check(p->num, NUM_SIZE) == 0)
            {
                printf("\tNumber enter error! Please retype the whole data and limit the number in %d size.\n", NUM_SIZE - 1);
                continue;
            }
            if (Check(p->name, NAME_SIZE) == 0)
            {
                printf("\tName enter error! Please retype the whole data and limit the name in %d size.\n", NAME_SIZE - 1);
                continue;
            }
            if (Check(p->phonenum, PHONENUM_SIZE) == 0)
            {
                printf("\tPhonenumber enter error! Please retype the whole data and limit the phonenumber in %d size.\n", PHONENUM_SIZE - 1);
                continue;
            }
            if (Check(p->email, EMAIL_SIZE) == 0)
            {
                printf("\tEmail enter error! Please retype the whole data and limit the email in %d size.\n", EMAIL_SIZE - 1);
                continue;
            }
            //������������û���֣���ɹ����룬�˳�ѭ��
            //���ѭ�����������������������
            while (getchar() != '\n')
                ;
            break;
        }
        //��p��������head,�������ص��µ�����ָ�븳��head
        head = Insert(head, p);
        //ѯ���Ƿ��������
        printf("\tAdd more data? Enter 1 to continue or enter 0 to end:");
        while (1)
        {
            scanf("%c", &ch);
            while (ch == '\n')
                scanf("%c", &ch);
            if (ch == '1')
            {
                p = (TeleBook*)malloc(LEN);
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

//�����������
//ÿʮ����ͣһ��
void Display(TeleBook* head)
{
    int i;
    int page = 1;
    char choice, choice2;
    //��ҳ�׸�����
    TeleBook* page_head;
    //ѭ��ָ��
    TeleBook* data = head;
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
                //���page=1�������ǵ�һҳ���޷����Ϸ�
                if (page == 1)
                    printf("\tError! This is the first page. Please retype:");
                //ͨ������������page_head��ǰ����10��
                else
                {
                    page--;
                    head = Reverse(head);
                    for (i = 0; i < 10; i++)
                        page_head = page_head->next;
                    data = page_head;
                    //�ٰ�����˳�������������ʾʮ������
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
                printf("\tEnter error! Please enter 1 or 2 or 3 to give your choice:");
        }
    }
}

//�����������
//�����Ϊ������¼s����������ͷָ��
TeleBook* Insert(TeleBook* head, TeleBook* s)
{
    //���ָ���������м�ֵ
    TeleBook* fp;
    //���ָ����Ϊѭ������
    TeleBook* data;
    //���Ƚ������ݵı��ת���ɱ�׼��ʽ
    Num_modi(s->num);
    //���������û������
    if (head == NULL)
    {
        s->next = NULL;
        head = s;
        return head;
    }
    //����²�������ݱ��˳��������ͷ��ǰ��
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
    //����²������ݱ��˳��������ĩβ�ĺ���
    if (data->next == NULL)
    {
        data->next = s;
        s->next = NULL;
        return head;
    }
}

//���������ı�š���������ϵ�绰�������ʼ���ַ����Ϣ��
//����Insert����������š���������룬�������ɹ���Ϣ����������ͷָ�롣
TeleBook* Insert_a_record(TeleBook* head)
{
    TeleBook* p = (TeleBook*)malloc(LEN);
    printf("\tPlease input a data(number name phonenumber email):");
    while (1)
    {
        scanf("%s %s %s %s", p->num, p->name, p->phonenum, p->email);
        //�����������ݼ�飬�Ƿ����ַ��������������������������������������
        if (Check(p->num, NUM_SIZE) == 0)
        {
            printf("\tNumber enter error! Please retype the whole data and limit the number in %d size.\n", NUM_SIZE - 1);
            continue;
        }
        if (Check(p->name, NAME_SIZE) == 0)
        {
            printf("\tName enter error! Please retype the whole data and limit the name in %d size.\n", NAME_SIZE - 1);
            continue;
        }
        if (Check(p->phonenum, PHONENUM_SIZE) == 0)
        {
            printf("\tPhonenumber enter error! Please retype the whole data and limit the phonenumber in %d size.\n", PHONENUM_SIZE - 1);
            continue;
        }
        if (Check(p->email, EMAIL_SIZE) == 0)
        {
            printf("\tEmail enter error! Please retype the whole data and limit the email in %d size.\n", EMAIL_SIZE - 1);
            continue;
        }
        //������������û���֣���ɹ����룬�˳�ѭ��
        break;
    }
    if ((head = Insert(head, p)) != NULL)
        printf("\tInsert succeed!\n");
    return head;
}

//���ɾ��
//ɾ�����Ϊnum�ļ�¼
TeleBook* Delete(TeleBook* head, char* num)
{
    //ѭ��ָ��
    TeleBook* data = head;
    //�м�ָ��
    TeleBook* fp;
    char choice;
    if (strcmp(head->num, num) == 0) //����һ�����Ϊ��ɾ������
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
        head = head->next; //ʹ�ڶ�������Ϊ�����ͷ
        free(fp);
        printf("\tDelete Succeed!\n");
        return head;
    }
    while (data->next != NULL)
    {
        if (strcmp(data->next->num, num) == 0)
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
            fp = data->next;
            data->next = data->next->next; //ʹdataֱ��ָ��data->next->next
            free(fp);
            printf("\tDelete Succeed!\n");
            return head;
        }
        data = data->next;
    }
    printf("\tCannot find the number you input. Delete fail.\n");
    return head;
}
//�����ɾ����ţ���Deletɾ��������Ƿ�ɾ���ɹ�
TeleBook* Delete_a_record(TeleBook* head)
{
    char num[NUM_SIZE];
    //���������������
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

//����
//�Ա��Ϊ��������
TeleBook* Sort_by_num(TeleBook* head)
{
    //ѭ��ָ��
    TeleBook* data1, * data2;
    //�м�ָ��
    TeleBook* fp1, * fp2;
    //data2��ǰһ�����ָ��
    TeleBook* pre;
    int count = 0;
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //���������ֻ��һ����㣬ֱ�ӷ��ؼ���
    if (head->next == NULL)
        return head;
    //data1��ѭ��ֻ��������
    for (data1 = head; data1 != NULL; data1 = data1->next)
        count++;
    //ð������
    for (; count > 1; count--)
    {
        //data2����ð��
        //����headָ��û��pre,���뵥������
        if (strcmp(head->num, head->next->num) > 0)
        {
            //�������ڽ��Ľ���
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
                //���ڽ�㽻��
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

//������ݲ�ѯ
//���ұ��Ϊnum�ļ�¼���ɹ��򷵻ص�ַ��ʧ�ܷ���NULL
TeleBook* Query(TeleBook* head, char* num)
{
    TeleBook* data = head;
    while (data != NULL)
    {
        if (strcmp(data->num, num) == 0)
            return data;
        data = data->next;
    }
    return (NULL);
}
//��������ұ�ţ���Query���ң�����ɹ���񼰽����Ϣ
void Query_a_record(TeleBook* head)
{
    char num[NUM_SIZE];
    char choice;
    TeleBook* data;
    //�����������
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return;
    }
    while (1)
    {
        printf("\tPlease input the number you want to search:");
        scanf("%s", num);

        if (Check(num, NUM_SIZE) == 0)
        {
            printf("\tEnter error. Please limit it in %d size.\n", NUM_SIZE - 1);
            continue;
        }
        Num_modi(num);
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

//���ļ�������������Ϣ
//���ļ�filename���һ����¼�������У���Insert()�������
TeleBook* AddfromText(TeleBook* head, char* filename)
{
    //��¼��������
    int num;
    //ѭ��ָ��
    TeleBook* data;
    FILE* in;
    //����ļ���ʧ�ܣ���ӡ�򿪴��󣬷��ؿ�ָ��
    if ((in = fopen(filename, "r")) == NULL)
    {
        printf("\tFile open error!\n");
        return NULL;
    }
    data = (TeleBook*)malloc(LEN);
    fscanf(in, "%d", &num); //�ȶ�ȡ�ļ�ǰ���������
    //����ļ�ָ�벻ָ���ļ�ĩβ������һ�����ݲ���������
    while (!feof(in))
    {
        fscanf(in, "%s %s %s %s\n", data->num, data->name, data->phonenum, data->email); //�ٶ�ȡ������
        head = Insert(head, data);
        if (!feof(in))
            data = (TeleBook*)malloc(LEN);
    }
    if (num == 0)
        printf("\tFile has no contant.\n");
    else
        printf("\t%d data import succeed!\n", num);
    return head;
}

//���������¼д�뵽�ļ���
//�������еĽ���¼ȫ��д���ļ�records.txt
void WritetoText(TeleBook* head, char* filename)
{
    FILE* fp;
    TeleBook* data;
    //��ʱ�����ļ���������
    TeleBook* data0 = NULL;
    //�м�����ָ��
    TeleBook* p;
    int num = 0;
    //���ļ�//
    //����ļ��������ݣ����ļ�ԭ�Ⱦʹ��ڣ����ȶ�ȡ�ļ������ݼ�¼���������ļ����ݴ�����һ����ʱ�����У�֮������������������
    if ((fp = fopen(filename, "r+")) != NULL)
    {
        p = (TeleBook*)malloc(LEN);
        fscanf(fp, "%d", &num);
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s\n", p->num, p->name, p->phonenum, p->email);
            data0 = Insert(data0, p);
            if (!feof(fp))
                p = (TeleBook*)malloc(LEN);
        }
        for (data = head; data != NULL; data = data->next)
            num++;
        //�����ļ���ͷ
        rewind(fp);
        //�������
        fprintf(fp, "%d\n", num);
        //����ԭ����
        p = data0;
        while (p != NULL)
        {
            fprintf(fp, "%s  %s  %s  %s\n", p->num, p->name, p->phonenum, p->email);
            p = p->next;
        }
        Free_all(data0);
        //����������
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
        //���м���
        for (data = head; data != NULL; data = data->next)
            num++;
        //�������
        fprintf(fp, "%d\n", num);
        //���ļ���������
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

//��������
TeleBook* Reverse(TeleBook* head)
{
    //�ֱ���ǰһ�����ݵ�ַ�ͺ�һ�����ݵ�ַ
    TeleBook* fp1 = NULL, * fp2;
    while (head != NULL)
    {
        fp2 = head->next; //fp2ָ��ǰ����һ�����
        head->next = fp1; //ʹhead����һ����NULL
        fp1 = head;       //��fp1��Ϊ��һ������ָ���ǰһ��
        head = fp2;       //��ͷ��Ϊ��ǰ����һ��
    }
    return fp1;
}

//ɾ����ͬ��¼
//ɾ���������������绰�������ʼ���ַ����ͬ�ļ�¼
TeleBook* DeleteSame(TeleBook* head)
{
    TeleBook* data;
    TeleBook* p1, * p2;
    //���ڼ�¼p1��ǰһ��ָ��
    TeleBook* pre;
    int i = 0;
    //���������û������
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //���������ֻ��һ�����ݣ��򲻿�������ͬ��
    if (head->next == NULL)
    {
        printf("\tThere is no same data.\n");
        return head;
    }
    for (data = head; data != NULL && data->next != NULL; data = data->next)
    {
        p1 = data->next; //��ͬ�Ĳ�����ǰ��
        pre = data;      //pre��p1��ǰһ�����
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

//�˳�����ϵͳ
void Quit(TeleBook* head)
{
    char ch;
    printf("\tAre you sure you want to exit?\n");
    printf("\t1.Yes\t0.NO\n");
    while (1)
    {
        while ((ch = getchar()) == '\n') //ȥ���������Ļ��з� ��������з�ʱ�˳�ѭ��
            ;
        if (ch == '1') //�ͷ����ж�̬�ڴ�
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

//��ʾ���˵�
void Display_Main_Menu()
{
    system("cls");
    printf("\n");
    printf("       The telephone Management System       \n");
    printf("---------------------------------------------\n");
    printf("|                   Menu                    |\n");
    printf("|-------------------------------------------|\n");
    printf("|       1 Input Record                      |\n");
    printf("|       2 Display All Records               |\n");
    printf("|       3 Insert a Record                   |\n");
    printf("|       4 Delete a Record                   |\n");
    printf("|       5 Sort                              |\n");
    printf("|       6 Query                             |\n");
    printf("|       7 Add Records from a Text File      |\n");
    printf("|       8 Write to a Text File              |\n");
    printf("|       9 Reverse List                      |\n");
    printf("|       10 Delete the Same Records          |\n");
    printf("|       11 Alter a Record                   |\n");
    printf("|       0 Quit                              |\n");
    printf("---------------------------------------------\n");
    printf("        Please enter your choice(0-11):");
}

//�ͷ�����̬�ڴ�
void Free_all(TeleBook* head)
{
    TeleBook* fp;

    while (head != NULL)
    {
        fp = head;
        head = head->next;
        free(fp);
    }
}

//�ַ����������麯��������ֵΪ1��0
int Check(char* str, int size)
{
    int i;
    //����ַ������һ�����ǿ��ַ����������ݣ�����0
    if (*str == '\0')
        return 0;
    //������ַ�����ķ���λ�ռ����ҵ��˿��ַ�������ֹ��������1
    for (i = 1; i < size; i++)
    {
        if (*(str + i) == '\0')
            return 1;
    }
    //����ַ�������δ���ֿ��ַ�������0
    return 0;
}

//�ַ�ת���ֺ����������ַ������ַ�����-1���ɹ����ظ�����
int Str_to_num(char* str)
{
    int sum = 0;
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9') //���������ĸ����-1
            return -1;
        sum = sum * 10 + *str - '0'; //���ַ�������ת��Ϊ����
        str++;
    }
    return sum;
}

//�����������
//ʹ�����б�ž�Ϊ��λ������ʽ
//��1ת����001��12���012
void Num_modi(char* num)
{
    int n;
    int i;
    for (n = strlen(num); n < 3; n++)
    {
        //ÿ��ѭ�����ַ����������һ��λ�ã��������ͷ����'0'
        for (i = n; i > 0; i--)
            num[i] = num[i - 1];
        num[0] = '0';
    }
}

//�޸����ݺ���
//�޸������е�ĳ����
TeleBook* Alter_list(TeleBook* head)
{
    char s[20];
    char choice;
    TeleBook* data = head;
    if (head == NULL)
    {
        printf("\tThere is no data.\n");
        return head;
    }
    //�ҵ���Ҫ�޸ĵĽṹ��
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
    //ѡ����Ҫ�޸ĵ�����
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