#include <stdio.h>
#include <string.h>


#include "STD_TYPES.h"
#include "linkedList.h"
#include "BankFunctions.h"



/* creating array of struct of system admins */
Admins adminsArray[NO_OF_ADMINS]={{"Hend","Hend123"},{"Mohsen","Mohsen123"},{"El-Hadidy","El-Hadidy123"}};

/* creating an object of linked list (bank accounts list)*/
extern List BankAccounts;


extern u32 account_number;		// keeping track of number of accounts in the system
extern u32 accountToCheck;
extern s32 pos, pos_found;
extern u8 ExitAdmin, ExitClient, ExitSystem, ExitAccount;




void main(void){
	ExitSystem = 0;
	CreateList(&BankAccounts);
	ListEntry CurrentAccount;
	ListEntry *pCurrentAccount = &CurrentAccount;
	u8 mode,choice, adminExist=0;
	u8 admin_username[50], admin_password[11];
	u32 client_bankAccountID;
	u32 client_password;
	while( ! ExitSystem ){
		printf("\n********************** Welcome to iTi Bank System **********************\n");
		printf("Admin			--> Enter 1\n"
			   "Client			--> Enter 2\n"
			   "Exit			--> Enter 3\n");
		
		printf("\nMode: ");
		scanf("%d", &mode);
		
		if(mode == ADMIN_MODE){
			printf("********************** Welcome Admin **********************\n");
			printf("Username: ");
			scanf("%s", &admin_username);
			printf("Password: ");
			scanf("%s", &admin_password);
			for(int i=0; i<3; i++){
				if(strcmp(admin_username, adminsArray[i].username) == 0 && strcmp(admin_password, adminsArray[i].password) == 0){
					adminExist = 1;
					break;
				}
			}
			if(adminExist){
				while( ! ExitAdmin ){
					admin_mainMenu();
				}
			}
			else{
				printf("Admin doesn't exist!\n");
			}
			
			
		}
		else if(mode == CLIENT_MODE){
			printf("********************** Welcome Client **********************\n");
			printf("Bank Account ID: ");
			scanf("%d", &client_bankAccountID);
			printf("Password: ");
			scanf("%d", &client_password);
			checkAccount(client_bankAccountID);
			if(pos == -1){
				printf("Account ID doesn't exist!!\n");
			}
			else{
				RetrieveList(&BankAccounts, pos, pCurrentAccount);
				if(pCurrentAccount->password != client_password){
					printf("Wrong password!");
				}
				else{
					printf("\n************************ Welcome %s ***********************\n", pCurrentAccount->fullName);
					while( ! ExitClient ){
						client_mainMenu(pCurrentAccount);
					}
				}
			}
			
		}
		else if(mode == EXIT_MODE){
			ExitSystem = 1;
			printf("Thank you for using iTi Bank System");
		}
		else{
			printf("Invalid Entery!");
		}
	}
}