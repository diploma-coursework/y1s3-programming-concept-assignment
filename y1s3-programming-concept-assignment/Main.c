#include <stdio.h>
#include <stdlib.h>

#include "Color.h"
#include "StaffInfoModule.h"
#include "MemberInfoModule.h"


int main() {
	char mainmenuSelection;

	while (1) {
		system("cls");
		printf(
			yellow"+---------------------------------------------+\n"
			"|                                             |\n"
			"|  Welcome to the Train Ticketing System:     |\n"
			"|                                             |\n"
			"+---------------------------------------------+\n\n"reset
			blue"1"reset" - Member\n"
			blue"2"reset" - Staff\n"
			blue"0"reset" - Exit\n\n"
			"Enter your account type selection: "green
		);
		scanf(" %c", &mainmenuSelection);

		switch (mainmenuSelection) {
			case '1':
				membermain();
				break;
			case '2':
				staffmain();
				break;
			case '0':
				system("cls");
				printf(yellow"Thank you for using the train ticketing system. Wishing you a pleasant journey and hope to serve you again soon!\n"reset);
				return 0;
			default:
				printf(red"Invalid selection, please try again.\n"reset);
				system("pause");
		}
	}

	

}