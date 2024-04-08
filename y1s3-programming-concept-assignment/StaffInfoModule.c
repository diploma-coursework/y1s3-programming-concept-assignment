#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Staff_struct.h"

// staff main
void staffmain() {

	int choice, valid = 0;

	system("cls");

	// main page
	printf("\033[1;34m*********************************************************************************\033[1;0m\n");
	printf("\033[1;34m*********************************************************************************\033[1;0m\n");
	printf("\033[1;34m***                                                                           ***\033[1;0m\n");
	printf("\033[1;34m***                                STAFF MENU                                 ***\033[1;0m\n");
	printf("\033[1;34m***                                                                           ***\033[1;0m\n");
	printf("\033[1;34m***                              POWERED BY LEE                               ***\033[1;0m\n");
	printf("\033[1;34m***                                                                           ***\033[1;0m\n");
	printf("\033[1;34m*********************************************************************************\033[1;0m\n");
	printf("\033[1;34m*********************************************************************************\033[1;0m\n");
	printf("\n"); 
	printf("1. Staff login menu\n");
	printf("2. Exit\n");
	printf("\n");

	do {
	 printf("Enter a number (1,2,3) to enter a menu >");
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
	int choice2, valid2 = 0;
	char id_check[30];

	struct staff info;
	FILE* fp, *fptr;


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
			continue;
		}
		
		
		//The staff number cannot be the same
		/*
		if ((fptr = fopen("StaffInfo.txt", "r")) == NULL) {
			printf("CAN'T OPEN FILE TO READ!");
		}

		int exist = 0;

		struct staff validate[10];


		for (int x = 0; x < 10; x++) {
		   (fscanf(fp, "%[^,], %[^,], %s\n", validate[x].id, validate[x].name, validate[x].pass) != 3) {

		   }
		   if (strcmp(validate[x].id, info.id) == 0) {
			   int exist = 1;
			   break;
		   }
		}
		*/
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
	  scanf("%d", &choice2);

	  switch (choice2) {
	  case 1:
		  staffmain();
		  valid2 = 1;
		  break;
	  case 2:
		  staffLogin();
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

// staff login
staffLogin() {

	system("cls");

	struct login info2;
	char id[8], pass[30];
	FILE* fpr;


	fpr = fopen("StaffInfo.txt", "r");

	if (fpr == NULL) {
		printf("Error: Unable to open the database file.\n");
		return 0; 
	}

	printf("Login page\n");
	printf("\n");

	printf("Staff id >");
	scanf("%s", &id);
	printf("staff password >");
	scanf("%s", &pass);

	//reading the file to retrieve the values
	while (fscanf(fpr, "%[^,] , %[^,] , %s", &info2.id, &info2.name, &info2.pass) != EOF) {
		if (strcmp(id, info2.id) == 0 && strcmp(pass, info2.pass) == 0) {
			fclose(fpr);
			printf("\n");
			printf("Successful login as %s !", info2.name);
			return;
		}
	}

	printf("\n");
	printf("Login failed. Please check your ID and password.\n");
	fclose(fpr);
		
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

