#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "Color.h"
#include "StaffDef.h"
#include "GeneralStructs.h"
#include "GeneralUtils.h"
#include "TrainSchedulingModule.h"
#include "GeneralUtils.h"

// staff main
void staffmain() {

	struct menu staffMain;
	
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
		printf(yellow"Enter a number (1,2,3) to enter a menu > ");
		if (scanf(" %d", &staffMain.choice) == 1) {
			printf("\n"reset);
			switch (staffMain.choice) {
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
			while (getchar() != '\n');
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}
	} while (!valid);
}

//register the staff account, only staff can register staff
int staffRegistration(const char* name) {
	int x;
	char id_check[30];
	valid = false;
	bool continue_adding = false;

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
			bool exist = false;
			printf(green"Enter staff Id with 'TRS' included >");
			scanf(" %15s", info.id);
			printf(reset"\n");

			while (getchar() != '\n');

			// Must not exceed 7 digits length and must include "TRS"
			if ((strlen(info.id) != 7) || (strstr(info.id, "TRS") == NULL)) {
				printf(red"\nTHE ID LENGTH MUST BE 7 AND MUST CONTAIN 'TRS' !\n"reset);
				printf("================================================\n");
				continue;
			}
			// The staff number cannot be the same
			rewind(fp);
			struct staff validate;

			while (fscanf(fp, " %[^,\n],\n",validate.id) != EOF) {
				if (strcmp(validate.id, info.id) == 0) {
					exist = true;
					break;
				}
			}

			if (exist) {
				printf(red"\nTHE ID ALREADY EXISTS. PLEASE CHOOSE ANOTHER ID!\n"reset);
				printf("==============================================\n");
			}
			else {
				break;
			}

		} while (1);

		// name validation check
		do {
			printf(green"Enter staff name >");
			scanf(" %30[^\n]", info.name); // Updated format specifier to allow spaces and hyphens
			printf(reset"\n");
			if (strlen(info.name) >= 40) {
				printf(red"\nYOUR NAME IS TOO LONG!\n"reset);
				printf("\n");
			}
			
			else {
				int isValid = 1;
				for (int i = 0; info.name[i] != '\0'; i++) {
					if (!isalpha(info.name[i]) && info.name[i] != ' ' && info.name[i] != '-') {
						isValid = 0;
						break;
					}
				}
				if (!isValid) {
					printf(red"\nTHE NAME CAN ONLY CONTAIN ALPHABETIC CHARACTERS, SPACES, AND HYPHENS!\n"reset);  
					printf("=====================================================================\n");
				}
				else {
					break;
				}
			}
		} while (1);

		//password validation check
		do {
			printf(green"Enter staff password >");
			scanf(" %40[^\n]", info.pass);
			printf(reset"\n");

			if (strlen(&info.pass) < 4) {
				printf(red "\nTHE PASSWORD LENGTH MUST BE AT LEAST 4 CHARACTERS!\n" reset);
				printf("===========================================\n");
			}
			else {
				break;
			}

		} while (1);

		do {
			printf(green"Enter staff position (0-9)\n");
			displayposition();
			int position;
			if (scanf(" %d"reset, &position) != 1 || position < 0 || position >= NUM_POSITIONS) {
				printf(red"\nInvalid input! Position must be a number between 0 and 9.\n"reset);
				printf("=========================================================\n");
			}
			else {
				printf("\n");
				info.position = (enum Position)position; 
				positionString(info.position);
				break;
			}
		} while (1);


		do {
			printf(green"Enter staff salary: ");
			scanf(" %d", &info.salary);
			if ( info.salary <= 0 || info.salary <= 1500) {
				printf(reset);
				printf(red"Invalid input! Salary must be a non-negative number and must not be lower than RM1500.\n"reset);
				printf("======================================================================================\n");
			}
			else {
				printf("\n");
				break;
			}
		} while (1);

		do {
			printf(green"Enter staff age: ");
			if (scanf(" %d", &info.age) != 1 || info.age < 18) {
				printf(reset);
				printf(red"Invalid input! Age must be a number greater than or equal to 18.\n"reset);
				printf("================================================================\n");
			}
			else {
				printf("\n");
				break; 
			}
		} while (1);

		do {
			printf(green"Enter staff phone number (Malaysia format, e.g., 0123456789): ");
			scanf(" %s", info.phone);

			if (isValidPhoneNumber(info.phone)) {
				printf("\n");
				break;
			}
			else {
				printf(red"Invalid phone number\n====================\n"reset);
			}
		} while (1);

		//Create a new line to the file
		if (ftell(fp) != 0) {
			fprintf(fp, "\n");
		}

		// print the information to text file
		fprintf(fp, "%s, %s, %s, %s, %d, %d, %s", info.id, info.name, info.pass, positionString(info.position), info.salary, info.age, info.phone);

		printf("\n");
		printf(green"ACCOUNT SUCCESSFULLY ADDED\n"reset);
		printf("===========================\n");

		fclose(fp);

		// Enter another pages
		do {
			printf(green"ENTER (1) TO GO TO BACK\nENTER (2) TO CONTINUE ADDING THE ACCOUNT\n\n>");
			if (scanf(" %d", &reg.choice) == 1) {
				printf(reset);
				switch (reg.choice) {
				case 1:
					staffloginmain(name);
					valid = true;
					break;
				case 2:
					continue_adding = true;
					valid = true;
					break;
				default:
					printf(red"INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n"reset);
					printf("=========================================\n");
					printf("\n");
				}
			}
			else {
				while (getchar() != '\n');
				printf(red"\nInvalid input! Please enter a valid number.\n"reset);
				printf("===========================================\n");
				continue;
			}
		} while (!valid);

	}while (continue_adding);
}

// staff login
int staffLogin() {
	system("cls");

	struct staff login;

	char loginid[10], loginpass[30];
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
	    scanf(" %15s", loginid);
	    printf("Staff password: ");
	    scanf(" %40s", loginpass);
		printf(reset);

		//reset the reading of file
		rewind(fpr);

	  // Reading the file to retrieve the values
		while (fscanf(fpr, "%[^,], %[^,], %[^,\n], %[^,], %[^d,], %[^d,], %[^\n]\n", login.id, login.name, login.pass, &login.position, &login.salary, &login.age, login.phone) != EOF) {
			if (strcmp(loginid, login.id) == 0 && strcmp(loginpass, login.pass) == 0) {
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

//staff menu
int staffloginmain(const char* name) {
	system("cls");

	valid = false;
	struct menu login;

	printf(blue"Welcome to staff menu %s!\n\n", name);
	printf(reset);
	printf(green"1. Staff registration\n2. Staff Modification\n3. Staff deletion\n4. Staff searching\n5. staff Display\n6. Train Scheduling\n7. Sign out\n8. Exit the program\n\n"reset);
	do {
		printf(yellow"Enter a number (1, 2, 3, 4, 5, 6, 7, 8) to enter a menu: ");
		if (scanf(" %d", &login.choice) == 1) {
			printf("\n"reset);
			switch (login.choice) {
			case 1: staffRegistration(name); valid = true; break;
			case 2: staffModification(name); valid = true; break;
			case 3: staffDeletion(name); valid = true;break;
			case 4: staffsearching(name); valid = true; break;
			case 5: staffDisplay(name); valid = true; break;
			case 6: staffScheduling(name); valid = true; break;
			case 7: staffmain(); valid = true; break;
			case 8: return -1; break;
			default: printf("\n\033[1;31mInvalid number entered!\033[1;0m\n========================================\n"); break;
			}
		}
		else {
			while (getchar() != '\n');
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}

	} while (!valid);
}

//Delete the account of the staff, only staff can delete staff
int staffDeletion(const char* name) {
	char deletionid[15], line[2000], positionDel[100];
	bool valid = false;
	int found = 0;



	struct staff deletion;
	struct menu delete;

	struct Date currentDate = getCurrentDate();
	struct Time currentTime = getCurrentTime();

	FILE* fptr = fopen("staffInfo.txt", "r");
	FILE* fdel = fopen("records.txt", "a");
	FILE* ftemp = fopen("temp.txt", "w");

	if (fptr == NULL || fdel == NULL || ftemp == NULL) {
		printf("AN ERROR OCCURRED. PLEASE TRY AGAIN!\n");
		return 1;
	}

	do {
		system("cls");
		printf(blue"Welcome to Staff deletion menu %s\n\n"reset, name);

		printf(green"Enter the staff id that you want to delete > ");
		scanf(" %14s", deletionid); // Limit input to 14 characters to avoid buffer overflow
		printf(reset"\n");

		while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %d, %d, %[^\n]\n", deletion.id, deletion.name, deletion.pass, positionDel, &deletion.salary, &deletion.age, deletion.phone) != EOF) {
			if (strcmp(deletionid, deletion.id) == 0) {
				deletion.position = INVALID_POSITION; // Mark position as Invalid
				found = 1;
			}
			else {
				deletion.position = getPositionEnum(positionDel);
				if (deletion.position == INVALID_POSITION) {
					// If position is not recognized, mark it as Invalid
					printf("Invalid position found: %s\n", positionDel);
					deletion.position = INVALID_POSITION;
				}
			}
			if (strcmp(deletionid, deletion.id) != 0) {
				// Write the record to the temporary file only if it's not the record to delete
				fprintf(ftemp, "%s, %s, %s, %s, %d, %d, %s\n", deletion.id, deletion.name, deletion.pass, positionString(deletion.position), deletion.salary, deletion.age, deletion.phone);
			}
		}

		fclose(fptr);
		fclose(ftemp);
		

		remove("staffInfo.txt");
		rename("temp.txt", "staffInfo.txt");

		if (found) {
			printf(green"Staff entry with ID %s deleted successfully.\n", deletionid);
		}
		else {
			printf("Staff entry with ID %s not found.\n"reset, deletionid);
		}
	

		printf(green"\nStaff record with ID %s has been deleted by %s successfully!\n", deletionid, name);
		printf("Date: %d/%d/%d\n", currentDate.day, currentDate.month, currentDate.year);
		printf("Time: %02d:%02d\n"reset, currentTime.hour, currentTime.minute);

		fprintf(fdel, "Staff record with ID %s was Modified by %s on %d-%02d-%02d at %02d:%02d\n", deletionid, name, currentDate.day, currentDate.month, currentDate.year, currentTime.hour, currentTime.minute);

		fclose(fdel);
		do {
			printf(yellow"\nEnter a number (1) to continue delete, Enter (2) to go back: ");
			if (scanf(" %d"reset, &delete.choice) == 1) {
				switch (delete.choice) {
				case 1:
					valid = true;
					break;
				case 2:
					staffloginmain(name);
					valid = true;
					break;
				default:
					printf("\nInvalid number entered!\n");
					printf("========================================\n");
					break;
				}
			}
			else {
				while (getchar() != '\n');
				printf("\nInvalid input! Please enter a valid number.\n");
				printf("===========================================\n");
				continue;
			}
		} while (!valid);
	} while (delete.choice == 1);
}

// Modify the staff name and password, **id cannot be modify
int staffModification(const char* name) {

	struct menu mod;
	struct staff modi;
	struct Date currentDate = getCurrentDate();
	struct Time currentTime = getCurrentTime();
	FILE* fpr, * fp, *fmod;
	char Modiid[10], ModiPosition[100], orig_name[50], orig_pass[50];
	found = false;

	if ((fpr = fopen("staffInfo.txt", "r")) == NULL || (fp = fopen("temp.txt", "w")) == NULL || (fmod = fopen("records.txt", "a")) == NULL) {
		printf("AN ERROR OCCUR PLEASE TRY AGAIN!");
		return;
	}
	do {
		system("cls");

		printf(blue"Staff modification menu\n\n"reset);
		printf(green"NOTE! If you don't want to modify the certain data field please press (ENTER) to skip\n\n"reset);
		printf(green"Enter the staff ID you want to modify: ");
		scanf(" %s", Modiid);
		printf("\n"reset);
		getchar();
		
		while (fscanf(fpr, "%[^,], %[^,], %[^,], %[^,], %d, %d, %[^\n]\n", modi.id, modi.name, modi.pass, ModiPosition, &modi.salary, &modi.age, modi.phone) != EOF) {
			if (strcmp(modi.id, Modiid) == 0) {
				found = true;

				char orig_name[50], orig_pass[50], orig_phone[50];
				enum Position orig_position = modi.position;
				int orig_salary = modi.salary;
				int orig_age = modi.age;
				strcpy(orig_phone, modi.phone);
				strcpy(orig_name, modi.name);
				strcpy(orig_pass, modi.pass);

				// Modify the information
				printf(green"Enter new name (Press Enter to skip): ");
				fgets(modi.name, sizeof(modi.name), stdin);
				modi.name[strcspn(modi.name, "\n")] = '\0'; // Remove newline character
				if (modi.name[0] == '\0') {
					// If the input string is empty, skip modifying the name
					strcpy(modi.name, orig_name);
					printf("\n");
				}
				else if (strlen(modi.name) >= 40) {
					printf(red "\nYOUR NAME IS TOO LONG\n" reset);
					continue;
				}
				printf("Enter new pass (Press Enter to skip): ");
				fgets(modi.pass, sizeof(modi.pass), stdin);
				modi.pass[strcspn(modi.pass, "\n")] = '\0'; // Remove newline character
				if (modi.pass[0] == '\0') {
					// If the input string is empty, skip modifying the password
					strcpy(modi.pass, orig_pass);
					printf("\n");
				}
				else if (strlen(modi.pass) < 4) {
					printf(red "\nTHE PASSWORD LENGTH MUST BE AT LEAST 4 CHARACTERS!\n===========================================\n" reset);
					continue;
				}

				printf(green"Enter new position (0-9) (Press Enter to skip)\n\n");
				displayposition();
				char input[100];
				fgets(input, sizeof(input), stdin);
				if (input[0] == '\n') {
					// If the input string is empty (user pressed Enter), skip modifying the position
					modi.position = orig_position;
					printf("\n");
				}
				else {
					int newPosition;
					if (sscanf(input, " %d", &newPosition) != 1 || newPosition < 0 || newPosition >= NUM_POSITIONS) {
						printf(red"Invalid input! Position must be a number between 0 and 9.\n"reset);
						printf("\n");
						continue;
					}
					else {
						modi.position = (enum Position)newPosition;
						positionString(modi.position);
						printf("\n");
					}
				}

				printf(green"Enter new salary (Press Enter to skip): ");
				fgets(input, sizeof(input), stdin);
				if (input[0] == '\n') {
					// If the input string is empty (user pressed Enter), skip modifying the salary
					modi.salary = orig_salary;
					printf("\n");
				}
				else {
					if (sscanf(input, " %d", &modi.salary) != 1 || modi.salary < 0) {
						printf(red"Invalid input! Salary must be a non-negative number.\n"reset);
						printf("\n");
						continue;
					}
				}
				printf("\n");
				printf(green"Enter new age (Press Enter to skip): ");
				fgets(input, sizeof(input), stdin);
				if (input[0] == '\n') {
					// If the input string is empty (user pressed Enter), skip modifying the age
					printf("\n");
					modi.age = orig_age;
				}
				else {
					if (sscanf(input, " %d", &modi.age) != 1 || modi.age < 18) {
						printf(red"Invalid input! Age must be a number greater than or equal to 18.\n"reset);
						printf("\n");
						continue;
					}
				}

				printf(green"Enter new phone number (Malaysia format, e.g., 0123456789) (Press Enter to skip): ");
				fgets(modi.phone, sizeof(modi.phone), stdin);
				modi.phone[strcspn(modi.phone, "\n")] = '\0'; // Remove newline character
				if (modi.phone[0] == '\0') {
					// If the input string is empty (user pressed Enter), skip modifying the phone number
					strcpy(modi.phone, orig_phone);
					printf("\n");
				}
				else {
					if (!isValidPhoneNumber(modi.phone)) {
						printf(red"Invalid phone number\n"reset);
						continue;
					}
				}
			}
			fprintf(fp, "%s, %s, %s, %s, %d, %d, %s\n", modi.id, strcmp(modi.name, "-") != 0 ? modi.name : "-", strcmp(modi.pass, "-") != 0 ? modi.pass : "-", strcmp(ModiPosition, "-") != 0 ? ModiPosition : "-", modi.salary, modi.age, strcmp(modi.phone, "-") != 0 ? modi.phone : "-");
			fprintf(fmod, "Staff record with ID %s was Modified by %s on %d-%02d-%02d at %02d:%02d\n", Modiid, name, currentDate.day, currentDate.month, currentDate.year, currentTime.hour, currentTime.minute);
		}
		fclose(fpr);
		fclose(fp);
		fclose(fmod);

		if (found) {
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
			if (scanf(" %d", &mod.choice) == 1) {
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
			}
			else {
				while (getchar() != '\n');
				printf(red"\nInvalid input! Please enter a valid number.\n"reset);
				printf("===========================================\n");
				continue;
			}
		} while (!valid);
	} while (mod.choice == 1);
}

//display staff report
int staffDisplay(const char* name) {

	int display, count = 0;
	char positionstr[100];
	struct staff dis;
	struct menu displayed;

	FILE* fpr = fopen("staffInfo.txt", "r");

	if (fpr == NULL) {
		printf("ERROR OCCUR WHILE ACCESSING THE FILE!");
		return 1;
	}

	system("cls");
	printf(blue"Welcome to staff display report %S!\n"reset, name);
	printf(green"\n\nEnter (1) to display all the staff informations >");
	scanf("%d"reset, &display);

	if (display == 1) {
		printf("\nStaff Information:\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("ID\t     Name\t\tPosition\t\t           Salary\t\tAge\t\tPhone\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");

		// Read and display staff information from the file
		while (fscanf(fpr, " %[^,], %[^,], %[^,], %[^,], %d, %d, %[^\n]\n", dis.id, dis.name, dis.pass, positionstr, &dis.salary, &dis.age, dis.phone) != EOF) {
			count++;
			dis.position = getPositionEnum(positionstr);
			printf("%7s\t%15s\t\t%18s\t\t%10d\t%10d\t%15s\n\n", dis.id, dis.name, positionString(dis.position), dis.salary, dis.age, dis.phone);
		}
	}
	else {
		printf("Invalid choice!\n");
	}

	fclose(fpr);

	printf("---------------------------------------------------------------------------------------------------------------\n\n");
	printf("Total of %d staff informations diaplayed\n", count);

	do {
		printf(green"\nENTER (1) TO GO TO BACK\nENTER (2) TO EXIT THE PROGRAM\n\n>");
		if (scanf(" %d", &displayed.choice) == 1) {
			printf(reset);
			switch (displayed.choice) {
			case 1:
				staffloginmain(name);
				valid = true;
				break;
			case 2:
				return 0;
				break;
			default:
				printf(red"INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n"reset);
				printf("=========================================\n");
				printf("\n");
			}
		}
		else {
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}
	} while (!valid);

}

//search for staff
int staffsearching(const char* name) {
	
	char searchid[10];
	struct staff search;
	struct menu searchstaff;
	bool found = false;
	bool continue_searching = true;
	char position_String[100];


	FILE* fpr = fopen("staffInfo.txt", "r");

	if (fpr == NULL) {
		printf("ERROR OCCUR WHILE ACCESSING THE FILE!");
		return 1;
	}

	do {
		system("cls"); 

		printf(blue"Welcome to Staff searching %s!\n"reset, name);
		printf(green"\nEnter the staff Id to search for it's informations >");
		scanf(" %s"reset, searchid);

		while (fscanf(fpr, " %[^,], %[^,], %[^,], %[^,], %d, %d, %[^\n]\n", search.id, search.name, search.pass, position_String, &search.salary, &search.age, search.phone) != EOF) {
			if (strcmp(searchid, search.id) == 0) {
				search.position = getPositionEnum(position_String);
				printf("\nThe ID you searched for (%s) is found!\n\n", searchid);
				printf("Staff ID          : %s\nStaff Name        : %s\nStaff Password    : %s\nStaff Position    : %s\nStaff Salary      : RM%d\nStaff Age         : %d\nStaff Phone Number: %s\n", search.id, search.name, search.pass, positionString(search.position), search.salary, search.age, search.phone);
				found = 1;
				break;
			}
		}
		if (!found) {
			printf(red"RESULT FOR THE %s IS NOT FOUND, PLEASE TRY AGAIN!\n"reset, searchid);
		}
		fclose(fpr);

		do {
			printf(green"\nENTER (1) TO GO TO BACK\nENTER (2) TO CONTINUE SEARCHING FOR THE INFORMATION\nENTER (3) TO EXIT THE PROGRAM\n\n>");
			if (scanf(" %d", &searchstaff.choice) == 1) {
				printf(reset);
				switch (searchstaff.choice) {
				case 1:
					staffloginmain(name);
					valid = true;
					break;
				case 2:
					continue_searching = false;
					valid = true;
					break;
				case 3:
					return 0;
					break;
				default:
					printf(red"INVALID NUMBER ENTERED, PLEASE TRY AGAIN!\n"reset);
					printf("=========================================\n");
					printf("\n");
				}
			}
			else {
				while (getchar() != '\n');
				printf(red"\nInvalid input! Please enter a valid number.\n"reset);
				printf("===========================================\n");
				continue;
			}
		} while (!valid);

	} while (continue_searching);
}

// train schedule
int staffScheduling(const char* name) {

	struct menu schedule;

	system("cls");

	printf(blue"Welcome to train scheduling menu %s !\n\n"reset, name);

	printf(green"Enter (1) to schedule Train\nEnter (2) to paginate Train schedule records\nEnter (3) to remove Train Schedule Records\nEnter (4) to go back\n\n"reset);
	do {
		printf(yellow"Enter a number (1, 2, 3, 4, 5, 6, 7, 8) to enter a menu: ");
		if (scanf(" %d", &schedule.choice) == 1) {
			printf("\n"reset);
			switch (schedule.choice) {
			case 1: scheduleTrainMenu(); valid = true; break;
			case 2: paginateAllTrainScheduleRecordsMenu(); valid = true; break;
			case 3: removeTrainScheduleRecordMenu(); valid = true; break;
			case 4: staffloginmain(name); valid = true; break;
			case 5: return 0; break;
			default: printf("\n\033[1;31mInvalid number entered!\033[1;0m\n========================================\n"); break;
			}
		}
		else {
			while (getchar() != '\n');
			printf(red"\nInvalid input! Please enter a valid number.\n"reset);
			printf("===========================================\n");
			continue;
		}

	} while (!valid);
}