#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "Staff_struct.h"

#define blue "\033[1;34m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define red "\033[1;31m"
#define reset "\033[0m"
#define bold "\033[1;0m"

// staff main
int staffmain() {

	int choice, valid = 0;

	system("cls");

	printf(blue);
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf("***                                                                           ***\n");
	printf("***                                STAFF MENU                                 ***\n");
	printf("***                                                                           ***\n");
	printf("***                              POWERED BY LEE                               ***\n");
	printf("***                                                                           ***\n");
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf(reset);
	
	printf("\n");
	printf(green"1. Staff login menu\n2. Exit\n\n"reset);

	do {
	 printf(yellow"Enter a number (1,2) to enter a menu >");
	 scanf("%d", &choice);
	 printf("\n"reset);
		switch (choice) {
		case 1:
			staffLogin();
			valid = 1;
			break;
		case 2:
			return 0;
			break;
		default:
			printf(red"        INVALID NUMBER ENTERED!"reset);
			printf("========================================\n");
			break;
		}
	} while (!valid);
}

//register the staff account, only staff can register staff
staffRegistration() {

	system("cls");

	int length, length2, length3;
	int choice, exist, valid = 0, x;
	char id_check[30];

	struct staff info;
	FILE* fp;

	if ((fp = fopen("staffInfo.txt", "a+")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf(blue"ENTER THE STAFF INFORMATION TO CREATE ACCOUNT\n"reset);
	printf("=============================================\n");

	//Id validation check
	do {

		printf(green"Enter staff Id with 'TRS' included >");
		scanf("%10s", &info.id);
		printf(reset);
		//Must not exceed 7 digits length
		if (strlen(&info.id) > 7) {

			printf(red"\nTHE MAXIMUM ID LENGTH CANNOT EXCEED 8!\n"reset);
			printf("======================================\n");
			continue;
		}

		//Must include "PMD"
		if (strstr(&info.id, "TRS") == NULL) {
			printf("\n");
			printf(red"\nTHE STAFF ID MUST CONTAIN (PMD)\n"reset);
			printf("===============================\n");
			continue;
		}

		//The staff number cannot be the same

		exist = 0;
		rewind(fp);
		struct staff validate;

		while (fscanf(fp, "%[^,], %[^,], %s", &validate.id, &validate.name, &validate.pass) != EOF) {
			if (strcmp(&validate.id, &info.id) == 0) {
				printf("\n\033[1;31mTHE ID ALREADY EXIST PLEASE CHOOSE ANOTHER ID!\033[1;0m\n==============================================\n");
				exist = 1;
				break;
			}
		}

	} while(exist);


	// name validation check
	do {
		printf(green"Enter staff name >");
		scanf("%39s", &info.name);
		printf(reset);

		if (strlen(&info.name) >= 40) {
			printf(red "\nYOUR NAME IS TOO LONG\n" reset);
			printf("\n");
		}
		else {
			break;
		}
	} while(1);


	//password validation check
	do {
		printf(green"Enter staff password >");
		scanf("%20s", &info.pass);
		printf(reset);

		if (strlen(&info.pass) < 4) {
			printf(red "\nTHE PASSWORD LENGTH MUST BE AT LEAST 4 CHARACTERS!\n" reset);
			printf("===========================================\n");
		}
		else {
			break;
		}

	} while(1);

	//Create a new line to the file
	if (ftell(fp) != 0) {
		fprintf(fp, "\n");
	}

	// print the information to text file
	fprintf(fp, "%s, %s, %s\n", info.id, info.name, info.pass);

	printf("\n");
	printf(green"ACCOUNT SUCCESSFULLY ADDED\n"reset);
	printf("===========================\n");
	
	fclose(fp);

	// Enter another pages
	do {
	  printf(green"ENTER (1) TO GO BACK THE MAIN STAFF PAGE\nENTER (2) TO GO TO LOGIN PAGE\nENTER (3) TO CONTINUE ADDING THE ACCOUNT\nENTER (4) TO EXIT THE PROGRAM\n\n>"reset);
	  scanf("%d", &choice);

	  switch (choice) {
	  case 1:
		  staffmain();
		  valid = 1;
		  break;
	  case 2:
		  staffLogin();
		  valid = 1;
		  break;
	  case 3:
		  valid = 1;
		  break;
	  case 4:
		  return 0;
		  break;
	  default:
		  printf(red"INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n"reset);
		  printf("=========================================\n");
		  printf("\n");
	  }
	} while (!valid);
}

// staff login
staffLogin() {
	system("cls");

	struct staff login;
	char id[8], pass[30];
	int choice, attempts = 3, valid = 0;
	FILE* fpr;

	fpr = fopen("staffInfo.txt", "r");

	if (fpr == NULL) {
		printf("Error: Unable to open the file.\n");
		return;
	}

	printf(blue"-------------------------------------\n");
	printf("|                                   |\n");
	printf("|            Login page             |\n");
	printf("|                                   |\n");
	printf("-------------------------------------\n\n"reset);

	while (attempts > 0) {

		printf(green"===================================\n");
		printf("          IMPORTANT NOTES!\n");
		printf("===================================\n"reset);
		printf(red"you only have %d attempts for login!\n\n\n", attempts);
		printf(reset);
		printf(yellow "Staff id: ");
	    scanf("%s", &id); 
	    printf("Staff password: ");
	    scanf("%s", &pass);
		printf(reset);

		//reset the reading of file
		rewind(fpr);

	  // Reading the file to retrieve the values
	  while (fscanf(fpr, "%[^,], %[^,], %s\n", &login.id, &login.name, &login.pass) != EOF) {
		 if (strcmp(&id, &login.id) == 0 && strcmp(&pass, &login.pass) == 0) {
			fclose(fpr);
			system("cls");
			printf(blue"Welcome to staff menu %s!\n\n", login.name);
			printf(reset);
			printf(green"1. Staff registration\n2. Staff Modification\n3. Staff deletion\n4. Staff searching\n5. Exit to the main page\n\n"reset);
			do {
				printf(yellow"Enter a number (1, 2, 3, 4, 5) to enter a menu: ");
				scanf("%d", &choice);
				printf(reset);
				switch (choice) {
				case 1:
					staffRegistration();
					valid = 1;
					break;
				case 2:
					staffModification();
					valid = 1;
					break;
				case 3:
					staffDeletion();
					valid = 1;
					break;
				case 4:
					staffsearching();
					valid = 1;
					break;
				case 5:
					staffmain();
					valid = 1;
					break;
				default:
					printf("\n\033[1;31mInvalid number entered!\033[1;0m\n");
					printf("========================================\n");
					break;
				}
			} while (!valid);
			return;
		 }
	  }
	  printf(red"\nLogin failed. Please check your ID and password.\n\n"reset);
	  attempts--;
    }
	printf(red"You have locked from login to this account!\n"reset);
	fclose(fpr);
}

//Delete the account of the staff, only staff can delete staff
staffDeletion() {
	system("cls");

	char id[10], line[100];
	struct staff deletion;

	SYSTEMTIME t;

	FILE* fptr, *fpr;

	if ((fptr = fopen("staffInfo.txt", "r")) == NULL || (fpr = fopen("temp.txt", "w")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf(blue"Staff deletion menu\n\n"reset);
	printf(green"Enter the staff id that you wanted to delete > ");
	scanf("%s", &id);
	printf("\n");
	printf(reset);

	while (fgets(line, sizeof(line), fptr) != NULL) {
		// Check if the line is empty or doesn't contain all three fields
		if (strlen(line) > 1 && sscanf(line, "%[^,], %[^,], %s", deletion.id, deletion.name, deletion.pass) == 3) {
			// Check if the ID matches the one to be deleted
			if (strcmp(deletion.id, id) != 0) {
				fprintf(fpr, "%s, %s, %s\n", deletion.id, deletion.name, deletion.pass);
			}
		}
	}

	rewind(fptr);

	fclose(fpr);
	fclose(fptr);

	remove("staffInfo.txt");
	rename("temp.txt", "staffInfo.txt");

	
	GetLocalTime(&t);

	printf(green"Staff record with ID %s has been deleted successfully on %d-%d-%d.\n"reset, id, t.wDay, t.wMonth, t.wYear);
}

staffsearching() {
	system("cls");

	printf("Welcome");
}

staffModification() {
	system("cls");
}

staffInformation() {
	system("cls");

	int choice;

	printf(blue"Staff Information menu\n\n"reset);
	printf(green"press (1) to add informations of staff\npress(2) to modify the informations of staff\n"reset);
	scanf("%d", &choice);

}

