#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct staff{
	char id[8];
	char name[40];
	char pass[30];
};

void staffmain() {

	int choice, valid = 0;

	system("cls");

	// main page
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf("***                                                                           ***\n");
	printf("***                                STAFF MENU                                 ***\n");
	printf("***                                                                           ***\n");
	printf("***                              POWERED BY LEE                               ***\n");
	printf("***                                                                           ***\n");
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf("\n");
	printf("1. Staff account Registration Menu\n"); 
	printf("2. Staff login menu\n"); 
	/*
	printf("3. Staff searching menu\n"); 
	printf("4. Staff Information Menu\n");
	printf("5. Account Modification Menu\n");
	printf("6. Account deletion menu \n");
	*/
	printf("\n");

	do {
	 printf("Enter a number (1,2) to enter a menu >");
	 scanf("%d", &choice);
	 printf("\n");
		switch (choice) {
		case 1:
			staffRegistration();
			valid = 1;
			break;
		case 2:
			staffLogin();
			valid = 1;
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
	int choice2, valid2 = 0;

	struct staff info;
	FILE* fp;

	if ((fp = fopen("StaffInfo.txt", "a")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf("ENTER THE STAFF INFORMATION TO CREATE ACCOUNT\n");
	printf("=============================================\n");

	//Id validation check
	while (1) {
		printf("Enter staff Id with PMD included >");
		scanf("%19s", &info.id);

		//Must not exceed 7 digits length
		if (strlen(&info.id) > 7) {

			printf("\n\033[1;31mTHE MAXIMUM ID LENGTH CANNOT EXCEED 8!\033[1;0m\n");
			printf("======================================\n");
			continue;
		}

		//Must include "PMD"
		if (strstr(&info.id, "PMD") != NULL) {
			break;
		}
		else {
			printf("\n");
			printf("\n\033[1;31mTHE STAFF ID MUST CONTAIN (PMD)\033[1;0m\n");
			printf("===============================\n");
		}

	}

	// name validation check
	do {
		printf("Enter staff name >");
		scanf("%40s", &info.name);

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
		scanf("%40s", &info.pass);

		length3 = strlen(&info.pass);

		if (length3 > 4) {
			break;
		}
		else {
			printf("\n\033[1;31mTHE PASSWORD LENGTH MUST EXCEED 4 DIGITS ABOVE\033[1;0m\n");
			printf("\n");
		}

	} while(length3 < 4);


	// print the information to text file
	fprintf(fp, "%s, %s, %s\n", info.id, info.name, info.pass);
	
	
	printf("\n");
	printf("\n\033[1;32mACCOUNT SUCCESSFULLY ADDED \033[1;0m\n");

	fclose(fp);

	// Enter another pages
	do {
	  printf("ENTER (1) TO GO BACK THE MAIN STAFF PAGE\nENTER (2) TO GO TO LOGIN PAGE\nENTER (3) TO EXIT THE PROGRAM\n\n>");
	  scanf("%d", &choice2);

	  switch (choice2) {
	  case 1:
		  staffmain();
		  valid2 = 1;
		  break;
	  case 2:
		  staffmain();
		  valid2 = 1;
		  break;
	  case 3:
		  return 0;
		  break;
	  default:
		  printf("INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n");
		  printf("=========================================\n");
		  printf("\n");
	  }
	} while (!valid2);

}

staffLogin() {

	system("cls");

	struct staff info2;
	FILE* fpr;

	fpr = fopen("StaffInfo.txt", "r");

	printf("Login page\n");
	printf("\n");
	printf("Staff id >");
	scanf("%s", info2.id);
	printf("staff password >");
	scanf("%s", info2.pass);

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

staffSearching() {
	system("cls");
}

