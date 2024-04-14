#pragma once

#ifndef staff_def
#define staff_def

struct staff {
	char id[10];
	char name[30];
	char pass[40];
};

struct menu {
	int choice;
	int valid;
};

#define blue "\033[1;34m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define red "\033[1;31m"
#define reset "\033[0m"
#define bold "\033[1;0m"

bool valid;

char buffer[100];

#endif