#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Staff_def.h"
#include "GeneralStructs.h"
#include "GeneralUtils.h"

// staff main
void staffmain() {

	struct menu staffmain;
	
	system("cls");

	valid = false;

	printf(blue);
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf("***                                                                           ***\n");
	printf("***                                STAFF MAIN                                 ***\n");
	printf("***                                                                           ***\n");
	printf("***                              POWERED BY LEE                               ***\n");
	printf("***                                                                           ***\n");
	printf("*********************************************************************************\n");
	printf("*********************************************************************************\n");
	printf(reset);
	
	printf("\n");
	printf(green"1. Staff login menu\n2. Exit\n\n"reset);

	do {
		printf(yellow"Enter a number (1,2) to enter a menu > ");
		if (scanf("%d", &staffmain.choice) == 1) {
			printf("\n"reset);
			switch (staffmain.choice) {
			case 1:
				staffLogin();
				valid = true;
				break;
			case 2:
				return 0;
			default:
				printf(red"     INVALID NUMBER ENTERED!\n"reset);
				printf("========================================\n");
				break;
			}
		}
		else { 
			clearInputBuffer();
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}
	} while (!valid);
}

//register the staff account, only staff can register staff
staffRegistration(const char* name) {

	int exist, x;
	char id_check[30];
	valid = false;

	struct menu reg;
	struct staff info;

	FILE* fp;

	if ((fp = fopen("staffInfo.txt", "a+")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	rewind(fp);

	do {
		system("cls");
	    printf(blue"ENTER THE STAFF INFORMATION TO CREATE ACCOUNT\n"reset);
	    printf("=============================================\n");

	    //Id validation check
		do {

			printf(green"Enter staff Id with 'TRS' included >");
			scanf("%10s", &info.id);
			printf(reset);

			//Must not exceed 7 digits length and must include "TRS"
			if ((strlen(info.id) != 7) || (strstr(&info.id, "TRS") == NULL)) {
				printf("\n");
				printf(red"\nTHE ID LENGHT MUST BE 7 AND MUST CONTAIN 'TRS' !\n"reset);
				printf("================================================\n");
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
		} while (exist);

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
		} while (1);

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

		} while (1);

		//Create a new line to the file
		if (ftell(fp) != 0) {
			fprintf(fp, "\n");
		}

		// print the information to text file
		fprintf(fp, "%s, %s, %s", info.id, info.name, info.pass);

		printf("\n");
		printf(green"ACCOUNT SUCCESSFULLY ADDED\n"reset);
		printf("===========================\n");

		fclose(fp);

		// Enter another pages
		do {
			printf(green"ENTER (1) TO GO BACK THE MAIN STAFF PAGE\nENTER (2) TO GO TO BACK\nENTER (3) TO CONTINUE ADDING THE ACCOUNT\nENTER (4) TO EXIT THE PROGRAM\n\n>");
			if (scanf("%d", &reg.choice) == 1) {
				printf(reset);
				switch (reg.choice) {
				case 1:
					staffmain();
					valid = true;
					break;
				case 2:
					staffloginmain(name);
					valid = true;
					break;
				case 3:
					valid = true;
					break;
				case 4:
					return 0;
					break;
				default:
					printf(red"INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n"reset);
					printf("=========================================\n");
					printf("\n");
				}
			}
			else {
				clearInputBuffer();
				printf(red"\nInvalid input! Please enter a valid number.\n"reset);
				printf("===========================================\n");
				continue;
			}
		} while (!valid);
	}while (reg.choice == 3);
}

// staff login
staffLogin() {
	system("cls");

	struct staff login;

	char id[8], pass[30];
	int attempts = 3;

	FILE* fpr = fopen("staffInfo.txt", "r");

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
			staffloginmain(login.name);
			return;
		 }
	  }
	  printf(red"\nLogin failed. Please check your ID and password.\n\n"reset);
	  attempts--;
    }
	printf(red"You have locked from login to this account!\n"reset);
	fclose(fpr);
}

staffloginmain(const char* name) {
	system("cls");

	valid = false;
	struct menu login;

	printf(blue"Welcome to staff menu %s!\n\n", name);
	printf(reset);
	printf(green"1. Staff registration\n2. Staff Modification\n3. Staff deletion\n4. Staff searching\n5. staff Information\n6. Exit to main page\n7. Exit the program\n\n"reset);
	do {
		printf(yellow"Enter a number (1, 2, 3, 4, 5, 6, 7) to enter a menu: ");
		if (scanf("%d", &login.choice) == 1) {
			printf("\n"reset);
			switch (login.choice) {
			case 1:
				staffRegistration(name);
				valid = true;
				break;
			case 2:
				staffModification(name);
				valid = true;
				break;
			case 3:
				staffDeletion(name);
				valid = true;
				break;
			case 4:
				staffsearching();
				valid = true;
				break;
			case 5:
				staffInformation();
				valid = true;
				break;
			case 6:
				staffmain();
				valid = true;
				break;
			case 7:
				return 0;
				break;
			default:
				printf("\n\033[1;31mInvalid number entered!\033[1;0m\n");
				printf("========================================\n");
				break;
			}
		}
		else {
			clearInputBuffer();
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}

	} while (!valid);
}

//Delete the account of the staff, only staff can delete staff
staffDeletion(const char* name) {
	system("cls");

	char id[10], line[100];
	valid = false;

	struct staff deletion;
	struct menu delete;

	struct Date currentDate = getCurrentDate();
	struct Time currentTime = getCurrentTime();

	FILE* fptr, *fpr, *fdel;

	if ((fptr = fopen("staffInfo.txt", "r")) == NULL || (fpr = fopen("temp.txt", "w")) == NULL || (fdel = fopen("records.txt", "a")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return 1;
	}

	printf(blue"Welcome to Staff deletion menu %s\n\n", name);
	printf(reset);
	do {
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
				else {
					fprintf(fdel, "Staff record with ID %s was deleted by %s on %d-%02d-%02d at %02d:%02d\n", deletion.id, name, currentDate.day, currentDate.month, currentDate.year, currentTime.hour, currentTime.minute);
				}
			}
		}

		rewind(fptr);

		fclose(fpr);
		fclose(fptr);
		fclose(fdel);

		remove("staffInfo.txt");
		rename("temp.txt", "staffInfo.txt");

		printf(green"Staff record with ID %s has been deleted by %s successfully!\nDate: %d/%d/%d\nTime: %02d:%02d\n"reset, id, name, currentDate.day, currentDate.month, currentDate.year, currentTime.hour, currentTime.minute);

		do {
			printf(yellow"\nEnter a number (1) to continue delete, Enter (2) to go back: ");
			scanf("%d", &delete.choice);
			printf(reset);
			switch (delete.choice) {
			case 1:
				valid = true;
				break;
			case 2:
				staffloginmain(name);
				valid = true;
				break;
			default:
				printf("\n\033[1;31mInvalid number entered!\033[1;0m\n");
				printf("========================================\n");
				break;
			}
		} while (!valid);
	} while (delete.choice == 1);
}

// Modify the staff name and password, **id cannot be modify
staffModification(const char* name) {
	system("cls");

	struct menu mod;
	struct staff modi;
	FILE* fpr, * fp;
	char id[10];
	found = false;

	if ((fpr = fopen("staffInfo.txt", "r")) == NULL || (fp = fopen("temp.txt", "w")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return;
	}

	printf(blue"Staff modification menu\n\n"reset);
	printf(green"Enter the staff ID you want to modify: ");
	scanf("%s", id);
	printf(reset);

	while (fscanf(fpr, "%[^,], %[^,], %[^\n]", modi.id, modi.name, modi.pass) != EOF) {
		printf(green"Read ID: %s and %s\n", modi.id, id);
		if (strcmp(modi.id, id) == 0) {
			found = true;
			// Modify the information
			printf("Enter new name: ");
			scanf("%s", modi.name);
			printf("Enter new phone number: ");
			scanf("%s" reset, modi.pass);
			break;
		}
		fprintf(fp, "%s, %s, %s\n", modi.id, modi.name, modi.pass);
		if (found == true) {
			break;
		}
	}


	fclose(fpr);
	fclose(fp);

	printf("ID searched for: %s\n", id);

	if (found == true) {
		// Remove the old file and rename the temp file
		remove("staffInfo.txt");
		rename("temp.txt", "staffInfo.txt");
		printf(green"Staff information modified successfully!\n"reset);
	}
	else {
		printf(red"\n");
		printf("Staff ID is not found!\n"reset);
	}

	do {
		printf(yellow"\nEnter a number (1) to continue modification, Enter (2) to go back: ");
		scanf("%d", &mod.choice);
		printf(reset);
		switch (mod.choice) {
		case 1:
			valid = true;
			break;
		case 2:
			staffloginmain(name);
			valid = true;
			break;
		default:
			printf("\n\033[1;31mInvalid number entered!\033[1;0m\n");
			printf("========================================\n");
			break;
		}
	} while (!valid);

}

staffInformation() {
	system("cls");

	struct menu info;

	printf(blue"Staff Information menu\n\n"reset);
	printf(green"press (1) to add informations of staff\npress(2) to modify the informations of staff\n"reset);
	scanf("%d", &info.choice);

}

staffsearching() {
	system("cls");

	printf("Welcome");
}

