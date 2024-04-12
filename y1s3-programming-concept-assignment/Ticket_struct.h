#pragma once

// Struct for Member
struct Member {
	char id[20];
	char name[20];
	char pass[10];
	int age;
	char ticket_number[20];
};

// Struct for Train
struct Train {
	char train_number[20];
	char origin[50];
	char destination[50];
	char departure_time[10];
	char arrival_time[10];
};


