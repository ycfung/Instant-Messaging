//
// Created by ycfung on 5/30/18.
//

#ifndef IM_SOMETHING_H
#define IM_SOMETHING_H

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;


int StartPrivateChat(int from ,int to);


int StartGroupChat(int from, int groupID);


int LoginToServer(int PIN);


int LogoffFromServer(int PIN);

int getac();

string getpass(const char *prompt, bool show_asterisk);

int Start();

int getInt();

string getString();

char getCharWithoutEnter();

void UpdateAccount(int ID);

#endif //IM_SOMETHING_H
