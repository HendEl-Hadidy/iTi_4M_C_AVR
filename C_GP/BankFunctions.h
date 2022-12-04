#ifndef BankSystem_h
#define BankSystem_h


#define NO_OF_ADMINS 3
#define ACCOUNT_ID_BASE 1000000000 	// 10 DIGITS

/* Modes */
#define ADMIN_MODE  1
#define CLIENT_MODE 2
#define EXIT_MODE 3

#define CREATE_ACCOUNT 1
#define OPEN_ACCOUNT   2
#define EXIT_SYSTEM    3

#define STATUS_ACTIVE     1
#define STATUS_RESTRICTED 2
#define STATUS_CLOSED     3

#define MAKE_TRANSACTION	1
#define CHANGE_STATUS		2
#define CHANGE_PASSWORD		2
#define GET_CASH			3
#define DEPOSIT				4
#define RETURN_MAIN_MENU	5


typedef struct admins{
	u8 username[20];
	u8 password[15];
}Admins;


/**************************** Functions Prototypes *************************/


void checkAccount(u32 Copy_currentAccountID);
void displayAccount(ListEntry *e);
u8 make_transaction(ListEntry *ptr_currentAccount);
u8 change_status(ListEntry *ptr_currentAccount);
u8 get_cash(ListEntry *ptr_currentAccount);
u8 deposite_in(ListEntry *ptr_currentAccount);
void open_account();
u8 create_account();
void admin_mainMenu();
void change_password(ListEntry *pCurrentAccount);
void client_mainMenu(ListEntry *pCurrentAccount);

#endif