#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *MSSV = "20205006";
typedef struct Linked_List
{
	char userName[30];
	char passWord[30];
	int status;
	int error;
	int login;
	struct Linked_List *next;
} node;

node *head = NULL;
node *loginNode = NULL;

node *MakeNode(char *userName, char *passWord, int status)
{
	node *temp = (node *)malloc(sizeof(node));
	strcpy(temp->userName, userName);
	strcpy(temp->passWord, passWord);
	temp->status = status;
	temp->error = 0;
	temp->login = 0;
	temp->next = NULL;
	return temp;
}

node *AddNode(char *userName, char *passWord, int status, node *h)
{
	if (h == NULL)
	{
		h = MakeNode(userName, passWord, status);
		return h;
	}
	int c = strcmp(userName, h->userName);
	if (c > 0)
	{
		h->next = AddNode(userName, passWord, status, h->next);
		return h;
	}
	else if (c == 0)
		return h;
	else if (c < 0)
	{
		node *tmp = MakeNode(userName, passWord, status);
		tmp->next = h;
		return tmp;
	}
}

node *Search(char *userName)
{
	for (node *h = head; h != NULL; h = h->next)
	{
		if (strcmp(userName, h->userName) == 0)
			return h;
	}
	return NULL;
}

void UpdateFile()
{
	FILE *fp = fopen("nguoidung.txt", "w");
	for (node *h = head; h != NULL; h = h->next)
	{
		fprintf(fp, "%s %s %d\n", h->userName, h->passWord, h->status);
	}
	fclose(fp);
}
void Register()
{
	char userName[30];
	char passWord[30];
	printf("Username: ");
	scanf("%s", userName);
	node *find = Search(userName);
	if (find != NULL)
	{
		printf("Account existed\n");
		return;
	}
	printf("Password: ");
	scanf("%s", passWord);
	head = AddNode(userName, passWord, 2, head);
	printf("Successful registration. Activation required.\n");
}
void Active()
{
	char activeCode[30];
	strcpy(activeCode, MSSV);
	char userName[30];
	char passWord[30];
	char code[30];
	printf("Username: ");
	scanf("%s", userName);
	node *find = Search(userName);

	if (find == NULL)
	{
		printf("Cannot find account\n");
		return;
	}

	printf("Password: ");
	scanf("%s", passWord);
	int c = strcmp(passWord, find->passWord);
	if (c != 0)
	{
		printf("Password is incorrect\n");
		return;
	}

	printf("Code: ");
	scanf("%s", code);

	c = strcmp(code, activeCode);

	int status = find->status;
	if (status == 1 && c == 0)
	{
		printf("Account is activated\n");
		return;
	}
	else if (status == 0 && c == 0)
	{
		printf("Account is blocked\n");
		return;
	}
	else if (status == 2 && c == 0)
	{
		find->status = 1;
		find->error = 0;
		printf("Account is activated\n");
		return;
	}
	else
	{
		find->error++;
		if (find->error >= 5)
		{
			printf("Activation code is incorrect\n");
			find->status = 0;
			printf("Account is blocked\n");
		}
		else
			printf("Activation code is incorrect\n");
		return;
	}
}
void SignIn()
{
	char userName[30];
	char passWord[30];
	printf("Username: ");
	scanf("%s", userName);
	node *find = Search(userName);
	if (find == NULL)
	{
		printf("Cannot find account\n");
		return;
	}
	if (find->status == 0)
	{
		printf("Account is blocked\n");
		return;
	}
	printf("Password: ");
	scanf("%s", passWord);
	int c = strcmp(passWord, find->passWord);
	if (c != 0)
	{
		find->login++;
		if (find->login <= 3)
		{
			printf("Password is incorrect\n");
			return;
		}
		else
		{
			find->status = 0;
			printf("Password is incorrect. Account is blocked\n");
			UpdateFile();
			return;
		}
	}
	else
	{
		if (find->status == 0)
		{
			printf("Account is blocked\n");
			return;
		}
		else
		{
			loginNode = find;
			loginNode->login = 0;
			printf("Hello %s\n", userName);
			return;
		}
	}
}

void ChangePassword()
{
	char oldPassWord[30];
	char newPassWord[30];
	printf("Username: %s\n", loginNode->userName);
	printf("Password: ");
	scanf("%s", oldPassWord);
	printf("NewPassword: ");
	scanf("%s", newPassWord);
	int c = strcmp(oldPassWord, loginNode->passWord);
	if (c != 0)
	{
		printf("Current password is incorrect. Please try again\n");
		return;
	}
	else
	{
		strcpy(loginNode->passWord, newPassWord);
		printf("Password is changed\n");
		return;
	}
}
void SignOut()
{
	char userName[30];
	printf("Username: ");
	scanf("%s", userName);
	node *find = Search(userName);
	if (find == NULL)
	{
		printf("Cannot find account\n");
		return;
	}
	int c = strcmp(userName, loginNode->userName);
	if (c != 0)
	{
		printf("Username is incorrect\n");
		return;
	}
	else
	{
		loginNode = NULL;
		printf("Goodbye %s\n", userName);
	}
}

void ReadData()
{
	char userName[30];
	char passWord[30];
	int status;
	FILE *fp = fopen("nguoidung.txt", "r");
	while (fscanf(fp, "%s %s %d", userName, passWord, &status) == 3)
	{
		// printf("%s %s %d\n", userName, passWord, status);
		head = AddNode(userName, passWord, status, head);
	}
	fclose(fp);
}

int main()
{
	ReadData();
	char cmd[10];
	while (1)
	{
		printf("\n\n\nUSER MANAGEMENT PROGRAM\n");
		printf("-----------------------------------\n");
		printf("1. Register\n");
		printf("2. Activate\n");
		printf("3. Sign in\n");
		printf("4. Search\n");
		printf("5. Change password\n");
		printf("6. Sign out\n");
		printf("Your choice (1-6, other to quit): ");
		scanf("%s", cmd);
		if (strcmp(cmd, "1") == 0)
		{
			Register();
			UpdateFile();
		}
		else if (strcmp(cmd, "2") == 0)
		{
			Active();
			UpdateFile();
		}
		else if (strcmp(cmd, "3") == 0)
		{
			if (loginNode != NULL)
			{
				printf("Please signout %s\n", loginNode->userName);
				continue;
			}
			SignIn();
			// UpdateFile();
		}
		else if (strcmp(cmd, "4") == 0)
		{
			if (loginNode == NULL)
			{
				printf("Account is not sign in\n");
				continue;
			}
			char userName[30];
			printf("Username: ");
			scanf("%s", userName);
			node *find = Search(userName);
			if (find == NULL)
			{
				printf("Cannot find account\n");
				continue;
			}
			else
			{
				int status = find->status;
				if (status == 0)
					printf("Account is blocked\n");
				else if (status == 1)
					printf("Account is active\n");
				else if (status == 2)
					printf("Account is idle\n");
			}
		}
		else if (strcmp(cmd, "5") == 0)
		{
			if (loginNode == NULL)
			{
				printf("Account is not sign in\n");
				continue;
			}
			ChangePassword();
			UpdateFile();
		}
		else if (strcmp(cmd, "6") == 0)
		{
			if (loginNode == NULL)
			{
				printf("Account is not sign in\n");
				continue;
			}
			SignOut();
		}
		else
			break;
	}
	return 0;
}
