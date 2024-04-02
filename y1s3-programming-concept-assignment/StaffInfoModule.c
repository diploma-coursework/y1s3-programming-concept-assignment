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
	printf("1. Staff login menu\n");
	printf("2. Staff searching menu\n");
	printf("3. Staff account Registration Menu\n");
	printf("4. Staff Information Menu\n");
	printf("5. Account Modification Menu\n");
	printf("6. Account deletion menu \n");
	printf("\n");

	do {
	 printf("Enter a number (1,2,3,4,5,6) to enter a menu >");
	 scanf("%d", &choice);
	 printf("\n");
		switch (choice) {
		case 1:
			staffLogin();
			valid = 1;
			break;
		case 2:
			staffSearching();
			valid = 1;
			break;
		case 3:
			staffRegistration();
			valid = 1;
			break;
		case 4:
			staffInformation();
			valid = 1;
			break;
		case 5:
			staffModification();
			valid = 1;
			break;
		case 6:
			staffDeletion();
			valid = 1;
			break;
		default:
			printf("\n\033[1;31m        INVALID NUMBER ENTERED! \033[1;0m\n");
			printf("========================================\n");
			break;
		}
	} while (!valid);
}


staffLogin() {
	system("cls");
	printf("Test");
}


staffSearching() {
	system("cls");
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
		scanf("%s", &info.id);

		//Must include "PMD"
		if (strstr(&info.id, "PMD") != NULL) {
			break;
		}
		else {
			return 0;
			printf("\n\033[1;31mTHE STAFF ID MUST CONTAIN (PMD)\033[1;0m\n");
			printf("===============================\n");
			printf("\n");
		}

		//Must not exceed 7 digits length
		if (strlen(&info.id) > 7) {

			return 0;
			printf("\n\033[1;31mTHE MAXIMUM ID LENGTH CANNOT EXCEED 8!\033[1;0m\n");
			printf("======================================\n");
		}
	}

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

		if (length3 > 4) {
			break;
		}
		else {
			printf("\n\033[1;31mTHE PASSWORD LENGTH MUST EXCEED 4 DIGITS ABOVE\033[1;0m\n");
			printf("\n");
		}

	} while(length3 < 4);


	//
	fprintf(fp, "%s, %s, %s", info.id, info.name, info.pass);
	
	
	printf("\n");
	printf("\n\033[1;32mACCOUNT SUCCESSFULLY ADDED \033[1;0m\n");

	fclose(fp);

	// Enter another pages
	do {
	  printf("\nENTER 1 TO GO BACK THE MAIN STAFF PAGE, ENTER 2 TO GO TO LOGIN PAGE >");
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
		}
	} while (!valid2);

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


