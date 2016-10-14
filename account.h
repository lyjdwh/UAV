#ifndef _ACCOUNT_H_
#define _ACCOUNT_H

#define USERFILE "account\\account.txt"
#define TUSERFILE "account\\taccount.txt"

#define FORMAT "%20s%20s%20s"
#define MAXLEN 20

typedef struct {
	char user_name[MAXLEN];
	char password[MAXLEN];
	char email[MAXLEN];
	int message;	//��ʼ��Ϊ0����������ȷ��1���Ҳ����û�Ϊ2���������Ϊ3,�û����ظ�Ϊ4
}Account;


int ProcessMessage(int message,int x,int y);
void Encrypt(Account *);
void SearchAccount(Account * p);
void AddAccount(Account p);
int SearchName(Account *p);
void ChangePassword(Account p);
void ReadCurrentAccount(Account *p);
void Encrypt(Account *p);
#endif