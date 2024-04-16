#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct
{
	char mName[50];
	char mUsername[50];
	char mIC[20];
	char mEmail[50];
	char mAddress[50];
	char mPassword[100];
}Members;

int member();
int memloginpage();
int memregisterpage();
int clearScreen();
int verificationStatus();
int viewProfile();
int modifyProfile();
int deleteProfile();
int clearInputBuffer();

int clearScreen()
{
	system("cls");
}

int clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int member()
{
	char answer;

	printf("Hello Welcome to the Members Page\n");
	system("pause");

	clearScreen();

	printf("Do you have an account?(Y/N):");
	scanf("%c", &answer);

	if (toupper(answer) == 'Y')
	{
		clearScreen();
		verificationStatus();
	}
	else
		if (toupper(answer) == 'N')
		{
			clearScreen();
			memregisterpage();
		}
		else
			printf("Error: No such options, please try again...");

}

int verificationStatus()
{
	char uname[30], psw[30];

	Members member;
	int success = 0;

	do
	{
		printf("Please enter your Username and password to login-----\n");
		printf("\nUsername:");
		scanf("%[^\n]", &uname);
		getchar();

		printf("\nPassword:");
		scanf("%[^\n]", &psw);
		getchar();

		if (strcmp(uname, member.mUsername) == 0 && strcmp(psw, member.mPassword) == 0)
		{
			success = 1;
		}
		else
		{
			printf("\nError no such Username or Password");

			printf("\nPlease try entering your Username and Password again...");
		}

	} while (!success);

	clearScreen();
	printf("\nLogin Successful...");
	clearScreen();

	memloginpage();
}

int viewProfile()
{

}

int modifyProfile()
{

}

int deleteProfile()
{

}

int memloginpage()
{
	int option;

	printf("\nHello and Welcome to the XXX Train Ticketing Company");
	printf("\nWhat would you like to access?");
	printf("\n1)View Profile");
	printf("\n2)Modify Profile");
	printf("\n3)Delete Profile");
	printf("\n4)View Booking History");
	printf("\n------------------------------");
	printf("Enter your choice please:");
	scanf("%d", &option);

	do
	{
		switch (option)
		{
		case 1:
			viewProfile();
			clearScreen();
			break;
		case 2:
			modifyProfile();
			clearScreen();
			break;
		case 3:
			deleteProfile();
			clearScreen();
			break;
		case 4:
			printf("Thanks for trying but this update will be here soon");
			//viewBookingPRofile();
			clearScreen();
			break;
		default:
			printf("Error no such options please try again");
			clearScreen();
			break;
		}
	} while (option < 1 || option > 4);
}

int memregisterpage()
{
	FILE* memptr;

	memptr = fopen("memberfile.txt", "a");

	if (!memptr)
	{
		printf("Error : file cannot be opened");
		exit(-1);
	}

	else
	{
		char mName[100], mUname[100], mIC[20], mEm[100], mAdrs[100], mPass[100];
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

		fprintf(memptr, "%s|%s|%s|%s|%s|%s", mUname, mPass, mName, mIC, mEm, mAdrs);


		fclose(memptr);
	}
}