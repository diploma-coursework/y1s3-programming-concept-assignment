#include <stdio.h>
#include <stdlib.h>
#include "StaffInfoModule.h"


int main() {
	char mainmenuSelection;

	while (1) {
		system("cls");
		printf(
			"+---------------------------------------------+\n"
			"|                                             |\n"
			"|  Welcome to the Train Ticketing System:     |\n"
			"|                                             |\n"
			"+---------------------------------------------+\n\n"
			"1 - Member\n"
			"2 - Staff\n"
			"0 - Exit\n\n"
			"Enter your account type selection: "
		);
		scanf(" %c", &mainmenuSelection);

		switch (mainmenuSelection) {
			case '1':
				// member main
				break;
			case '2':
				staffmain();
				break;
			case '0':
				system("cls");
				printf("Thank you for using the train ticketing system. Wishing you a pleasant journey and hope to serve you again soon!\n");
				return 0;
			default:
				printf("Invalid selection, please try again.\n");
				system("pause");
		}
	}

	

}