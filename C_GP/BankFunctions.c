#include <stdio.h>
#include <string.h>


#include "STD_TYPES.h"
#include "linkedList.h"
#include "BankFunctions.h"


/* creating array of struct of system admins */
//Admins adminsArray[NO_OF_ADMINS]={{"Hend","Hend123"},{"Mohsen","Mohsen123"},{"El-Hadidy","El-Hadidy123"}};

/* creating an object of linked list (bank accounts list)*/
List BankAccounts;


u32 account_number = 1;		// keeping track of number of accounts in the system
u32 accountToCheck;
s32 pos, pos_found;
u8 ExitAdmin, ExitClient, ExitSystem, ExitAccount;



static void checkAccountID(ListEntry *e){
	pos_found++;
	if(e->accountID == accountToCheck){
		pos = pos_found;
	}
}

void checkAccount(u32 Copy_currentAccountID){
	pos = pos_found = -1;
	accountToCheck = Copy_currentAccountID;
	TraverseList(&BankAccounts, &checkAccountID);
}

void displayAccount(ListEntry *e){
	printf("Full Name: %s\n", e->fullName);
	printf("Full Address: %s\n", e->fullAddress);
	printf("Age: %d\n", e->age);
	if(e->age < 21){
		printf("Guardian Name: %s\n", e->guardianName);
		printf("Guardian National ID: %s\n", e->guardianNationalID);
	}
	printf("National ID: %s\n", e->nationalID);
	printf("Balance: %.4f\n", e->balance);
	printf("Account ID: %d\n", e->accountID);
	printf("Password:   %d\n", e->password);
	printf("Account Status: %s\n\n\n", e->accountStatus == STATUS_ACTIVE? "Active" : e->accountStatus == STATUS_RESTRICTED? "Restricted" : "Closed");
}






u8 make_transaction(ListEntry *ptr_currentAccount){
	printf("\n****************** Making Transaction ******************\n");
	u32 account_transferedTo; 
	ListEntry Account_transferedTo;
	ListEntry *pAccount_transferedTo = &Account_transferedTo;
	f64 money_amount;
	if(ptr_currentAccount->accountStatus != STATUS_ACTIVE){
		printf("Account is not active!\n"
			   "Transaction can not be completed\n");
	}
	else{
		printf("Enter Account ID to transfer money to: ");
		scanf("%d", &account_transferedTo);
		checkAccount(account_transferedTo);
		if(pos == -1){
			printf("Account doesn't exist!!\n"
				   "Transaction can not be completed\n");
		}
		else{
			RetrieveList(&BankAccounts, pos, pAccount_transferedTo);
			if(pAccount_transferedTo->accountStatus != STATUS_ACTIVE){
				printf("Account is not active!\n"
					   "Transaction can not be completed\n");
			}
			else{
				printf("Enter amount of money to transfer: ");
				scanf("%d", &money_amount);
				if(ptr_currentAccount->balance < money_amount){
					printf("Balance is less than the money wanted to be transfered!\n"
						   "Transaction can not be completed\n");
				}
				else{
					ptr_currentAccount->balance -= money_amount;
					pAccount_transferedTo->balance +=money_amount;
					printf("Transaction succeeded\n");
					printf("\nCurrent Balance = %0.4lf\n", ptr_currentAccount->balance); 
			  
				}
			}
		}
	}
	return 0;
}



u8 change_status(ListEntry *ptr_currentAccount){
	printf("\n****************** Changing Status ******************\n");
	u8 choice;
	printf("Set Account to Active State				--> Enter 1\n"
		   "Set Account to Restricted State				--> Enter 2\n"
		   "Set Account to Closed					--> Enter 3\n");
	printf("Choice: ");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			ptr_currentAccount->accountStatus = STATUS_ACTIVE;
			printf("Account status changed to Active successfully\n");
			break;
		case 2:
			ptr_currentAccount->accountStatus = STATUS_RESTRICTED;
			printf("Account status changed to Restricted successfully\n");
			break;
		case 3:
			ptr_currentAccount->accountStatus = STATUS_CLOSED;
			printf("Account status changed to Closed successfully\n");
			break;
		default:
			printf("Invalid Entry!");
	}	
	
}


u8 get_cash(ListEntry *ptr_currentAccount){
	printf("\n****************** Getting Cash ******************\n");
	f64 cashAmount;
	printf("Enter the cash amount: ");
	scanf("%lf", &cashAmount);
	if(ptr_currentAccount->balance < cashAmount){
		printf("Balance is less than the cash wanted!\n"
			   "Transaction can not be completed\n");
	}
	else{
		ptr_currentAccount->balance -= cashAmount;
		printf("Transaction succeeded\n"
			   "Please wait for the cash\n");
		printf("\nCurrent Balance = %0.4lf\n", ptr_currentAccount->balance); 
	}
	return 0;
}

u8 deposite_in(ListEntry *ptr_currentAccount){
	printf("\n****************** Deposite ******************\n");
	u32 cashAmount;
	printf("Enter the cash amount: ");
	scanf("%d", &cashAmount);
	ptr_currentAccount-> balance += cashAmount;
	printf("Operation Succeeded\n");
	printf("Current Balance = %.4lf\n", ptr_currentAccount->balance);
}

void open_account(){
	ExitAccount = 0;
	u32 currentAccountID;
	ListEntry CurrentAccount;
	ListEntry *pCurrentAccount = &CurrentAccount;

	u8 choice;
	printf("\n************ Opening Account ************\n");
	printf("Enter Bank Account ID: ");
	fflush(stdin);
	scanf("%d", &currentAccountID);
	fflush(stdin);
	checkAccount(currentAccountID);
	if(pos == -1){
		printf("Account doesn't exist!!\n");
	}		
	else{
		RetrieveList(&BankAccounts, pos, pCurrentAccount);
		while( ! ExitAccount ){
			printf("\n************************ Welcome %s ***********************\n", pCurrentAccount->fullName);
			printf("\nMake Transaction		Enter --> 1\n"
				   "Change Status			Enter --> 2\n"
				   "Get Cash			Enter --> 3\n"
				   "Deposite			Enter --> 4\n"
				   "Return to main menu		Enter --> 5\n");
				   
			printf("\nChoice: ");
			scanf("%d", &choice);
			switch(choice){
				case MAKE_TRANSACTION: 	make_transaction(pCurrentAccount); 	break;
				case CHANGE_STATUS:	 	change_status(pCurrentAccount); 	break;	
				case GET_CASH:		 	get_cash(pCurrentAccount); 			break;
				case DEPOSIT:			deposite_in(pCurrentAccount);	    break;
				case RETURN_MAIN_MENU: 	ExitAccount = 1; 					break;
				default: printf("Invalid Entery!");
			}
		}
		ReplaceList(&BankAccounts, pos, *pCurrentAccount);
	}
}


u8 create_account(){
	printf("\n************ Creating New Account************\n");
	ListEntry newAccount;
	ListEntry *pAccount = &newAccount;
	
	printf("Full Name: ");
	fflush(stdin);
	//gets(pAccount->fullName);
	scanf("%[^\n]%*c", pAccount->fullName);
	fflush(stdin);
	
	printf("Full Address: ");
	//gets(pAccount->fullAddress);
	scanf("%[^\n]%*c", pAccount->fullAddress);
	fflush(stdin);
	
	printf("Age: ");
	scanf("%d", &pAccount->age);
	
	printf("National ID: ");
	scanf("%s", pAccount->nationalID);
	
	if(pAccount-> age < 21){		
		printf("Guardian Name: ");
		fflush(stdin);
		scanf("%[^\n]%*c", pAccount->guardianName);
		fflush(stdin);
		printf("Guardian National ID: ");
		fflush(stdin);
		scanf("%s", pAccount->guardianNationalID);
	}
	
	printf("Balance: ");
	scanf("%lf", &pAccount->balance);
	
	pAccount->accountID = ACCOUNT_ID_BASE + account_number;
	pAccount->password  = ACCOUNT_ID_BASE + account_number; //generate rand
	pAccount->accountStatus = STATUS_ACTIVE;
	
	AppendList(&BankAccounts, *pAccount);
	account_number++;
	printf("\n******************************************\n");
	printf("***** Account created successfully! ******\n");
	printf("******************************************\n");

	displayAccount(pAccount);
	
	return 0;
}





void admin_mainMenu(){
	ExitAdmin = 0;
	u8 choice;
	printf("\n\n****************** Main Menu *******************\n");
	printf("Create new account			--> Enter 1\n"
		   "Open existing account			--> Enter 2\n"
		   "Exit System				--> Enter 3\n");
	printf("\nChoice: ");
	fflush(stdin);
	scanf("%d" , &choice);
	switch(choice){
		case CREATE_ACCOUNT: create_account(); break;
		case OPEN_ACCOUNT  : open_account(); break;
		case EXIT_SYSTEM   : ExitAdmin = 1;  break;
		default : printf("Invalid Entry\n");
	}
}


void change_password(ListEntry *pCurrentAccount){
	u32 oldPassword, newPassword;
	printf("Old Password: ");
	scanf("%d", &oldPassword);
	if(oldPassword != pCurrentAccount->password){
		printf("Wrong Password!");
	}
	else{
		printf("New Password: ");
		scanf("%d", &newPassword);
		pCurrentAccount->password = newPassword;
		printf("Password changed successfully");
	}
}

void client_mainMenu(ListEntry *pCurrentAccount){
	ExitClient = 0;
	u8 choice;
	printf("\n****************** Main Menu *******************\n");
	printf("Make Transaction		Enter --> 1\n"
		   "Change Password			Enter --> 2\n"
		   "Get Cash			Enter --> 3\n"
		   "Deposite			Enter --> 4\n"
		   "Return to main menu		Enter --> 5\n");
			   
		printf("Choice: ");
		scanf("%d", &choice);
		switch(choice){
			case MAKE_TRANSACTION: 	make_transaction(pCurrentAccount); 	break;
			case CHANGE_PASSWORD:	change_password(pCurrentAccount); 	break;	
			case GET_CASH:		 	get_cash(pCurrentAccount); 			break;
			case DEPOSIT:			deposite_in(pCurrentAccount); 		break;
			case RETURN_MAIN_MENU: 	ExitClient = 1;						break;
			default: printf("Invalid Entery!");
		}
		ReplaceList(&BankAccounts, pos, *pCurrentAccount);

		
	
}

