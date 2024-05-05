#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#include "GeneralUtils.h"

typedef struct
{
	char mName[50];
	char mUsername[50];
	char mIC[20];
	char mEmail[50];
	char mAddress[50];
	char mPassword[100];
	char mBackupPassword[100];
}Members;

int membermain();
int memloginpage();
int memregisterpage();
int clearScreen();
int verificationStatus(const char* username, const char* password);
int viewPage(const char* username, const char* password);
int viewProfile(const char* username, const char* password);
int findProfile(const char* currentUser);
int modifyProfile(const char* currentUser, const char* password);
int deleteProfile(const char* username, const char* password);
int clearInputBuffer();

//clear screen
int clearScreen()
{
	system("cls");
}

//clear excess input
int clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//main page of member/customer
int membermain()
{
	int option;

	do
	{
		clearScreen();
		// Display menu
		printf("\nWelcome to XXX Train Station Company\n");
		printf("1. Register\n");
		printf("2. Login\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			// Register new member
			clearScreen();
			if (memregisterpage() == 1)
			{
				printf("Registration successful!\n");
			}
			else
			{
				printf("Registration failed. Please try again.\n");
			}
			break;
		case 2:
			clearScreen();
			memloginpage();
			break;
		case 3:
			printf("Exiting program...\n");
			main();
			break;
		default:
			printf("Invalid option. Please try again.\n");
		}
	} while (option != 3);

	return 0;
}

//verify whether login information is correct
int verificationStatus(const char* username, const char* password)
{
	int success = 0;
	FILE* filePtr;
	Members member;

	// Open the file for reading
	filePtr = fopen("memberinfo.txt", "r");
	if (!filePtr) {
		printf("Error: Unable to open file for reading.\n");
		return -1; // Return an error code to indicate failure
	}

	// Read each line from the file
	while (fscanf(filePtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n",
		member.mName, member.mPassword, member.mUsername, member.mIC,
		member.mEmail, member.mAddress, member.mBackupPassword) == 7) {
		// Compare entered username and password with the stored credentials
		if (strcmp(member.mUsername, username) == 0 && strcmp(member.mPassword, password) == 0) {
			printf("Login successful. Welcome, %s!\n", member.mUsername);
			fclose(filePtr);
			return 1; // Return success
		}
	}

	// If no matching username and password found
	printf("Invalid username or password. Please try again.\n");

	// Close the file
	fclose(filePtr);

	return 0; // Return failure
}

//view options after login into member's main page
int viewPage(const char* username, const char* password)
{
	int option;
	const char* uname = username;
	const char* psw = password;

	printf("\nHello and Welcome to the XXX Train Ticketing Company %s", username);
	printf("\nWhat would you like to access?");
	printf("\n1)View Profile");
	printf("\n2)Modify Profile");
	printf("\n3)Delete Profile");
	printf("\n4)View Booking History");
	printf("\n5)Back to Homepage");
	printf("\n6)Exit");
	printf("\n------------------------------");
	printf("\nEnter your choice please:");
	scanf("%d", &option);
	clearInputBuffer();

	do
	{
		switch (option)
		{
		case 1:
			clearScreen();
			viewProfile(uname, psw);
			clearScreen();
			break;
		case 2:
			clearScreen();
			modifyProfile(uname, psw);
			clearScreen();
			break;
		case 3:
			clearScreen();
			deleteProfile(uname, psw);
			clearScreen();
			break;
		case 4:
			clearScreen();
			printf("Thanks for trying but this update will be here soon");
			//viewBookingPRofile();
			clearScreen();
			break;
		case 5:
			clearScreen();
			membermain();
			clearScreen();
		case 6:
			clearScreen();
			printf("Have a nice day\n");
			system("pause");
			main();
			break;
		}

	} while (option < 1 || option >6);
}

//view personal information of customer
int viewProfile(const char* username, const char* password)
{
	FILE* filePtr;
	Members member;

	// Open the file for reading
	filePtr = fopen("memberinfo.txt", "r");
	if (!filePtr) {
		printf("Error: Unable to open file for reading.\n");
		return -1; // Return an error code to indicate failure
	}

	printf("Hello %s these are your profile information\n", username);
	// Search for the profile corresponding to the provided username and password
	while (fscanf(filePtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n",
		member.mName, member.mPassword, member.mUsername, member.mIC,
		member.mEmail, member.mAddress, member.mBackupPassword) == 7) {
		if (strcmp(member.mUsername, username) == 0 && strcmp(member.mPassword, password) == 0) {
			// Print the profile information
			printf("Name: %s\n", member.mName);
			printf("Username: %s\n", member.mUsername);
			printf("IC: %s\n", member.mIC);
			printf("Email: %s\n", member.mEmail);
			printf("Address: %s\n", member.mAddress);

			// Close the file and return success
			fclose(filePtr);
			system("pause");
		}
	}

	// If no matching username and password found
	if (feof(filePtr)) {
		printf("Error: Profile not found.\n");
	}

	// Close the file
	fclose(filePtr);

	clearScreen();
	viewPage(username, password);
}

//search for customer profile
int findProfile(const char* currentUser) {
	FILE* filePtr;
	Members member;
	int found = 0;

	// Open the file for reading
	filePtr = fopen("memberinfo.txt", "r");
	if (!filePtr) {
		printf("Error: Unable to open file for reading.\n");
		return -1; // Return an error code to indicate failure
	}

	// Display profile information for the specified user type
	printf("Current Profile Information for %s:\n", currentUser);
	while (fscanf(filePtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n",
		member.mName, member.mPassword, member.mUsername, member.mIC,
		member.mEmail, member.mAddress, member.mBackupPassword) == 7) {
		if (strcmp(member.mName, currentUser) == 0) {
			printf("User %s: \nName: %s, \nUsername: %s\n", currentUser, member.mName, member.mUsername);
			fclose(filePtr);
			system("pause");
			return 1; // Return success
		}
	}

	printf("No profiles found for %s.\n", currentUser);
	fclose(filePtr);
	return 0; // Return failure
}

//modify the information of customer profile
int modifyProfile(const char* currentUser, const char* password) {
	Members member;

	// Check if the profile exists
	if (!findProfile(currentUser)) {
		return 0; // Return failure if profile not found
	}

	clearScreen();
	printf("\nHello, welcome to profile modify.\n");
	printf("Enter the number corresponding to the field you want to modify:\n");
	printf("1. Name(Must)\n");
	printf("2. Username\n");
	printf("3. IC\n");
	printf("4. Email\n");
	printf("5. Address\n");
	printf("6. Password(Must)\n");
	printf("7. Backup Password\n");
	printf("8. Save Changes and Exit\n");

	int choice;
	do {
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		clearInputBuffer(); // Clear the input buffer to prevent issues with subsequent input

		switch (choice) {
		case 1:
			printf("Enter new name: ");
			scanf("%s", member.mName);
			break;
		case 2:
			printf("Enter new username: ");
			scanf("%s", member.mUsername);
			break;
		case 3:
			printf("Enter new IC: ");
			scanf("%s", member.mIC);
			break;
		case 4:
			printf("Enter new email: ");
			scanf("%s", member.mEmail);
			break;
		case 5:
			printf("Enter new address: ");
			scanf("%s", member.mAddress);
			break;
		case 6:
			printf("Enter new password: ");
			scanf("%s", member.mPassword);
			break;
		case 7:
			printf("Enter new backup password: ");
			scanf("%s", member.mBackupPassword);
			break;
		case 8:
			// Save changes and exit the loop
			break;
		default:
			printf("Invalid choice. Please enter a number between 1 and 8.\n");
			break;
		}
	} while (choice != 8);

	system("pause");
	clearScreen();

	// Modify the profile in the file
	FILE* originalFile = fopen("memberinfo.txt", "r");
	FILE* tempFile = fopen("tempefile.txt", "w");

	if (originalFile == NULL || tempFile == NULL) {
		printf("Error: Unable to open files for modification.\n");
		return -1;
	}

	while (fscanf(originalFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n",
		member.mName, member.mPassword, member.mUsername, member.mIC,
		member.mEmail, member.mAddress, member.mBackupPassword) == 7) {
		if (strcmp(member.mUsername, currentUser) != 0 && strcmp(member.mPassword, password) != 0) {
			// Write modified profile data to the temporary file
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s\n", member.mName, member.mPassword, member.mUsername, member.mIC,
				member.mEmail, member.mAddress, member.mBackupPassword);
		}
		else {
			// Write profile data as it is to the temporary file
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s\n", member.mName, member.mPassword, member.mUsername, member.mIC,
				member.mEmail, member.mAddress, member.mBackupPassword);
		}
	}

	fclose(originalFile);
	fclose(tempFile);

	// Remove the original file
	remove("memberinfo.txt");

	// Rename the temporary file to the original file name
	rename("tempfile.txt", "memberinfo.txt");

	printf("\nChanges saved successfully.\n");
	system("pause");
	return 1; // Return success

	memloginpage();
}

//delete customer profile
int deleteProfile(const char* username, const char* password)
{
	FILE* filePtr;
	FILE* tempFile;
	Members member;
	int found = 0;

	// Open the original file for reading
	filePtr = fopen("memberinfo.txt", "r");
	if (!filePtr) {
		printf("Error: Unable to open file for reading.\n");
		return -1; // Return an error code to indicate failure
	}

	// Create a temporary file
	tempFile = fopen("tempfile.txt", "w");
	if (!tempFile) {
		printf("Error: Unable to open temporary file for writing.\n");
		fclose(filePtr);
		return -1; // Return an error code to indicate failure
	}

	system("pause");
	clearScreen();
	printf("Hello welcome to profile delete.\n");
	// Copy contents of original file to temporary file, excluding the profile to delete
	while (fscanf(filePtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n",
		member.mName, member.mPassword, member.mUsername, member.mIC,
		member.mEmail, member.mAddress, member.mBackupPassword) == 7) {
		if (strcmp(member.mUsername, username) != 0 && strcmp(member.mPassword, password) != 0) {
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s\n", member.mName, member.mPassword, member.mUsername, member.mIC,
				member.mEmail, member.mAddress, member.mBackupPassword);
		}
		else {
			found = 1; // Indicate that the profile was found and deleted
		}
	}

	fclose(filePtr);
	fclose(tempFile);

	// Remove the original file
	remove("memberinfo.txt");

	// Rename the temporary file to the original file
	rename("tempfile.txt", "memberinfo.txt");

	if (found) {
		printf("Profile for %s deleted successfully.\n", username);
		return 1; // Return success
	}
	else {
		printf("Invalid username or password.\n");
		return 0; // Return failure
	}

	system("pause");

	main();
}

//login page for customer
int memloginpage()
{
	char uname[30], psw[30];

	int verified = 0;

	// Verification loop
	do {
		printf("Please enter your Username and password to verify:\n");
		printf("\nUsername: ");
		scanf("%s", uname);
		printf("\nPassword: ");
		scanf("%s", psw);

		verified = verificationStatus(uname, psw);

	} while (!verified);

	clearScreen();

	viewPage(uname, psw);
}

//register page for customer
int memregisterpage()
{
	FILE* memptr;

	memptr = fopen("memberinfo.txt", "a");

	if (memptr == NULL)
	{
		printf("Error : file cannot be opened");
		exit(-1);
	}

	else
	{
		char mName[100], mUname[100], mIC[20], mEm[100], mAdrs[100], mPass[100], mBpass[100];
		int i;

		printf("Greetings New User Welcome to the XXX Train Station Company\n");
		printf("Please fill out the neccessary details to join us as a member\n");
		printf("\nFull Name:");
		clearInputBuffer();
		scanf("%[^\n]", mName);

		printf("\nUsername:");
		clearInputBuffer();
		scanf("%[^\n]", mUname);

		printf("\nIC:");
		clearInputBuffer();
		scanf("%[^\n]", mIC);

		printf("\nEmail:");
		clearInputBuffer();
		scanf("%[^\n]", mEm);

		printf("\nHousing Address:");
		clearInputBuffer();
		scanf("%[^\n]", mAdrs);

		printf("\nPassword:");
		clearInputBuffer();
		scanf("%[^\n]", mPass);

		printf("\nBackup Password:");
		clearInputBuffer();
		scanf("%[^\n]", mBpass);

		fprintf(memptr, "%s|%s|%s|%s|%s|%s|%s\n", mName, mPass, mUname, mIC, mEm, mAdrs, mBpass);


		fclose(memptr);
	}

	clearScreen();

	return 1;
}