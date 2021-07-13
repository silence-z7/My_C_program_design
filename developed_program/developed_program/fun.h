//Ԥ���峣��
//�ṹ������
//��������

#define LEN sizeof(TeleBook)
#define CHOICE_SIZE 3
#define NUM_SIZE 4
#define NAME_SIZE 10
#define PHONENUM_SIZE 15
#define EMAIL_SIZE 20

#ifndef _FUN_H_
#define _FUN_H_

//�ṹ������
struct telebook
{
    char num[NUM_SIZE];           //���
    char name[NAME_SIZE];         //����
    char phonenum[PHONENUM_SIZE]; //�绰����
    char email[EMAIL_SIZE];       //�����ʼ���ַ
    struct telebook* next;        //��һ���ָ��
};
typedef struct telebook TeleBook;

//������������
//�Ӽ���������������¼������Insert���������ԡ���š�Ϊ��ĵ�������
TeleBook* Create();

//�����������
void Display(TeleBook* head);

//�����������
//�����¼s����������ͷָ��
TeleBook* Insert(TeleBook* head, TeleBook* s);
//���������ı�š���������ϵ�绰�������ʼ���ַ����Ϣ��
//����Insert����������š���������룬�������ɹ���Ϣ����������ͷָ�롣
TeleBook* Insert_a_record(TeleBook* head);

//���ɾ��
//ɾ�����Ϊnum�ļ�¼
TeleBook* Delete(TeleBook* head, char* num);
//�����ɾ����ţ���Deletɾ��������Ƿ�ɾ���ɹ�
TeleBook* Delete_a_record(TeleBook* head);

//����
//�Ա��Ϊ��������
TeleBook* Sort_by_num(TeleBook* head);

//������ݲ�ѯ
//���ұ��Ϊnum�ļ�¼���ɹ��򷵻ص�ַ��ʧ�ܷ���NULL
TeleBook* Query(TeleBook* head, char* num);
//��������ұ�ţ���Query���ң�����ɹ���񼰽����Ϣ
void Query_a_record(TeleBook* head);

//���ļ�������������Ϣ
//���ļ�filename���һ����¼�������У���Insert()�������
TeleBook* AddfromText(TeleBook* head, char* filename);

//���������¼д�뵽�ļ���
//�������з����¼ȫ��д���ļ�records.txt
void WritetoText(TeleBook* head, char* filename);

//��������
TeleBook* Reverse(TeleBook* head);

//ɾ����ͬ��¼
//ɾ���������������绰�������ʼ���ַ����ͬ�ļ�¼
TeleBook* DeleteSame(TeleBook* head);

//�˳�����ϵͳ
void Quit(TeleBook* head);

//��ʾ���˵�
void Display_Main_Menu();

//�ͷ�����̬�ڴ�
void Free_all(TeleBook* head);

//��������

//�ַ����������麯��������ֵΪ1��0
//�ַ�����str��СΪsize�����ַ��������ݻ�����ֹ������0�����򷵻�1
int Check(char* str, int size);

//�ַ�ת���ֺ����������ַ������ַ�����-1���ɹ����ظ�����
int Str_to_num(char* str);

//�����������
//ʹ�����б�ž�Ϊ��λ������ʽ
//��1ת����001��12���012
void Num_modi(char* num);

//�޸����ݺ���//
//�޸������е�ĳ����//
TeleBook* Alter_list(TeleBook* head);

#endif
