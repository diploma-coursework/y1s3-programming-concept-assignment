#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct staff{
	char name[40];
	char pass[30];
	char passRec[30];
	char position[30];
};

void staffmain() {
  
	/*
	struct staff info;
	FILE* fp;

	scan();

	if ((fp = fopen("Staffinfo.txt", "wb")) == NULL) {
		printf("UNABLE TO ACCESS THE FILE");
		return 1;
	}

	fwrite(&info.name, sizeof(10), 1, fp);
	printf("\n");
	printf("ACCOUNT SUCCESSFULLY CREATED\n");

	fclose(fp);
	*/

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
	printf("1. Main Menu\n");
	printf("2. Login Menu\n");
	printf("3. Account Registration Menu\n");
	printf("\n");

	do {
	 printf("Enter a number (1,2,3) to enter a menu >");
	 scanf("%d", &choice);
	 printf("\n");

		switch (choice) {
		case 1:
			staffmainMenu();
			valid = 1;
			break;
		case 2:
			staffloginMenu();
			valid = 1;
			break;
		case 3:
			staffCreateStaffAccMenu();
			valid = 1;
			break;
		default:
			printf("       INVALID NUMBER ENTERED!\n");
			printf("========================================\n");
			break;
		}
	} while (!valid);
}

staffmainMenu() {
	printf("Hi1");
}

staffloginMenu() {
	printf("Hi2");
}

staffCreateStaffAccMenu() {
	printf("Hi3");
}


/*
void scan() {
	struct staff info;

	printf("Enter Staff info\n\n");

	printf("Name");
	scanf("%s", &info.name);

}
*/

