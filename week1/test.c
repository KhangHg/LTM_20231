#include <stdio.h>

typedef struct
{
    char username[20];
    char password[20];
    int status;
    struct account *next;
} account;

account listAcc[20];

void doRegister()
{
    char username[20];
    char password[20];
}

void activate() {}

void signIn() {}

void search() {}

void changePassword() {}

void signOut() {}

void run()
{
    printf("\nUSER MANAGEMENT PROGRAM\n");
    printf("-------------------------------------\n");
    printf("1. Register\n");
    printf("2. Activate\n");
    printf("3. Sign in\n");
    printf("4. Search\n");
    printf("5. Change password\n");
    printf("6. Sign out\n");
    printf("Your choice (1-6, other to quit): ");
    int x;
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        doRegister();
        run();
        break;
    case 2:
        activate();
        run();
        break;
    case 3:
        signIn();
        run();
        break;
    case 4:
        search();
        run();
        break;
    case 5:
        changePassword();
        run();
        break;
    case 6:
        signOut();
        run();
        break;
    default:
        break;
    }
}

int main()
{
    run();
    return 0;
}
