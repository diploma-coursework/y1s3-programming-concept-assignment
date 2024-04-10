#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Staff_struct.h"

#define blue "\033[1;34m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
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
	 printf(yellow"Enter a number (1,2) to enter a menu >"reset);
	 scanf("%d", &choice);
	 printf("\n");
		switch (choice) {
		case 1:
			staffLogin();
			valid = 1;
			break;
		case 2:
			return 0;
			break;
		default:
			printf("\n\033[1;31m        INVALID NUMBER ENTERED! \033[1;0m\n");
			printf("========================================\n");
			break;
		}
	} while (!valid);
}

staffRegistration() {

	system("cls");

	int length, length2, length3;
	int choice, exist, valid = 0;
	char id_check[30];

	struct staff info;
	FILE* fp;


	if ((fp = fopen("StaffInfo.txt", "a+")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf("ENTER THE STAFF INFORMATION TO CREATE ACCOUNT\n");
	printf("=============================================\n");

	//Id validation check
	do {

		printf("Enter staff Id with PMD included >");
		scanf("%s", &info.id);

		//Must not exceed 7 digits length
		if (strlen(&info.id) > 7) {

			printf("\n\033[1;31mTHE MAXIMUM ID LENGTH CANNOT EXCEED 8!\033[1;0m\n");
			printf("======================================\n");
			continue;
		}

		//Must include "PMD"
		if (strstr(&info.id, "TRS") == NULL) {
			printf("\n");
			printf("\n\033[1;31mTHE STAFF ID MUST CONTAIN (PMD)\033[1;0m\n");
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
		printf("Enter staff name >");
		scanf("%s", &info.name);

		length2 = strlen(&info.name);

		if (length2 < 40) {
			break;
		}
		else {
			printf("\n\033[1;31mYOUR NAME IS TOO LONG\033[1;0m\n");
			printf("\n");
		}
	} while (length2 > 40);


	//password validation check
	do {
		printf("Enter staff password >");
		scanf("%s", &info.pass);

		length3 = strlen(&info.pass);

		if (length3 < 4) {
			printf("\n\033[1;31mTHE PASSWORD LENGTH MUST EXCEED OR EQUAL 4!\033[1;0m\n");
			printf("===========================================");
			continue;
		}
		else {
			break;
		}

	} while(length3 < 4);

	//Create a new line to the file
	if (ftell(fp) != 0) {
		fprintf(fp, "\n");
	}

	// print the information to text file
	fprintf(fp, "%s, %s, %s\n", info.id, info.name, info.pass);
	
	
	printf("\n");
	printf("\n\033[1;32mACCOUNT SUCCESSFULLY ADDED\033[1;0m\n");
	printf("===========================\n");

	fclose(fp);

	// Enter another pages
	do {
	  printf("ENTER (1) TO GO BACK THE MAIN STAFF PAGE\nENTER (2) TO GO TO LOGIN PAGE\nENTER (3) TO EXIT THE PROGRAM\n\n>");
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
		  return 0;
		  break;
	  default:
		  printf("INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n");
		  printf("=========================================\n");
		  printf("\n");
	  }
	} while (!valid);

}

// staff login
staffLogin() {
	system("cls");

	struct login info2;
	char id[8], pass[30];
	int choice, attempts = 3, valid = 0;
	FILE* fpr;

	fpr = fopen("StaffInfo.txt", "r");

	if (fpr == NULL) {
		printf("Error: Unable to open the file.\n");
		return;
	}

	printf("Login page\n\n");

	while (attempts > 0) {

		printf("IMPORTANT NOTES!\nyou only have %d attempts for login!\n\n", attempts);
	    printf("Staff id: "); 
	    scanf("%s", &id); 
	    printf("Staff password: ");
	    scanf("%s", &pass);

	  // Reading the file to retrieve the values
	  while (fscanf(fpr, "%[^,], %[^,], %s\n", &info2.id, &info2.name, &info2.pass) != EOF) {
		 if (strcmp(&id, &info2.id) == 0 && strcmp(&pass, &info2.pass) == 0) {
			fclose(fpr);
			system("cls");
			printf("Welcome to staff menu %s!\n\n", info2.name);
			printf("1. Staff registration\n2. Staff Modification\n3. Staff deletion\n4. Staff searching\n5. Exit to the main page\n\n");
			do {
				printf("Enter a number (1, 2, 3, 4, 5) to enter a menu: ");
				scanf("%d", &choice);
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
					staffSeacrhing();
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
	  printf("\n\033[1;31mLogin failed. Please check your ID and password.\033[1;0m\n\n");
	  attempts--;
    }
	printf("You have locked from login to this account!\n");
}

staffInformation() {
	system("cls");

}

staffModification() {
	system("cls");
}

staffDeletion() {
	system("cls");
}

staffSeacrhing() {
	system("cls");

	printf("Welcome");
}

