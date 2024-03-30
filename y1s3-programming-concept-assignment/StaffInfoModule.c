#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct staff{
	char id[7];
	char name[40];
	char pass[30];
	char passRec[30];
	char position[30];
};

void staffmain() {

	int choice, valid = 0;

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
	printf("1. Staff position menu\n");
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
			staffPosition();
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

staffPosition() {
	system("cls");
}

staffSearching() {
	system("cls");
}

staffRegistration() {

	system("cls");

	struct staff info;
	FILE* fp;


	system("cls");

	if ((fp = fopen("StaffInfo.txt", "w")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf("ENTER THE STAFF INFORMATION TO CREATE ACCOUNT\n");
	printf("=============================================\n");

	while(1) {

		printf("Enter staff Id >");
		scanf("%s", &info.id);

		if (strstr(&info.id, "PMD") != NULL) {
			break;
	    } else {
			printf("\n\033[1;31mTHE STAFF ID MUST CONTAIN (PMD)\033[1;0m\n");
			printf("===============================\n");
		}
	}

	/*
	do {	
		printf("\nEnter staff name >");
		scanf("%s", &info.name);
	}

	if (strlen(&info.name) > 0) {
		printf("\nEnter staff pass >");
		scanf("%s", &info.pass);
	}
	else
	*/
	

	printf("\n");
	printf("\n\033[1;32mACCOUNT SUCCESSFULLY ADDED \033[1;0m");

	fclose(fp);
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


