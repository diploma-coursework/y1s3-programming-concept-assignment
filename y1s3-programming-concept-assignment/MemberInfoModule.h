#pragma once
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