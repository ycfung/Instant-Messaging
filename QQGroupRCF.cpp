//
// Created by ycfung on 6/20/18.
//

#include "QQGroupRCF.h"
#include "BaseUserRCF.h"
#include <utility>
#include <ncurses.h>

QQGroup::QQGroup(string TYPE, int ID, int CREATOR, string NAME, set<int> mem, set<int> ADMINS) : BaseGroup(
        std::move(TYPE), ID, CREATOR, std::move(NAME), std::move(mem))
{
    admins = std::move(ADMINS);
}

bool QQGroup::RequestToJoin(int id)
{
    if (Verify(id))
    {
        this->addMember(id);
        return true;
    }
    return false;
}

bool QQGroup::Verify(int id)
{
    //Send CurrentUser request to admins
    return true;
}

int QQGroup::PrintGroupDetail()
{
    initscr();
    box(stdscr, ACS_VLINE, ACS_HLINE);
    move(LINES / 7, (COLS / 2) - 6);
    waddstr(stdscr, this->getName().c_str());
    move(LINES - 18, (COLS - 70));
    waddstr(stdscr, "Type:");
    move(LINES - 16, (COLS - 70));
    waddstr(stdscr, this->getType().c_str());
    move(LINES - 14, (COLS - 70));
    waddstr(stdscr, "ID:");
    move(LINES - 12, (COLS - 70));
    char a[8];
    sprintf(a, "%d", this->getID());
    waddstr(stdscr, a);

    move(LINES - 10, (COLS - 70));
    waddstr(stdscr, "Admins & ID");
    move(LINES - 8, (COLS - 70));
    string b = FindUser(this->getCreator())->getNickname() + "   " + to_string(this->getCreator());
    auto *bb = const_cast<char *>(b.c_str());
    waddstr(stdscr, bb);
    int j = 7;
    for (auto ptr:this->admins)
    {
        move(LINES - j, (COLS - 33));
        j--;
        if (FindUser(ptr) == nullptr)
            cout << "nullptr" << endl;
        string d = to_string(ptr) + "  " + (FindUser(ptr)->getNickname());
        waddstr(stdscr, const_cast<char *>(d.c_str()));
    }
    string c = "Members: " + to_string(this->getNumOfMem());
    move(LINES - 18, (COLS - 33));
    waddstr(stdscr, const_cast<char *>(c.c_str()));
    int i = 16;
    for (auto ptr:this->getMemberIDs())
    {
        move(LINES - i, (COLS - 33));
        i--;
        if (FindUser(ptr) == nullptr)
            cout << "nullptr" << endl;
        string d = to_string(ptr) + "  " + (FindUser(ptr)->getNickname());
        waddstr(stdscr, const_cast<char *>(d.c_str()));
    }


    refresh();
    getch();
    erase();
    endwin();

    return 0;
}

