//
// Created by ycfung on 5/17/18.
//

#include "BaseGroup.h"
#include "BaseUser.h"
#include "QQGroup.h"
#include <ncurses.h>
#include <cstdlib>

extern vector<BaseGroup *> GroupVec;
extern vector<QQGroup *> QQGroupVec;





int SaveGroupsToFile(vector<BaseGroup *> &vec) //the argument is a vector that stores pointers to object
{
    ofstream file;
    file.open("Groups.txt");
    for (auto ptr:vec)
    {
        ostream_iterator<int> output_iterator(file, " ");
        file << (*ptr).getType() << '\n';
        file << (*ptr).getID() << '\n';
        file << (*ptr).getCreator() << '\n';
        file << (*ptr).getName() << '\n';
        if((*ptr).Type == "QQ Group")
        {
            QQGroup * p =dynamic_cast<QQGroup*>(ptr); //NOLINT
            for(auto pd:(*p).getAdmins())
                file<<pd<<' ';
        }
        file<<'\n';
        for (auto pd:(*ptr).getMemberIDs())
            file << pd << ' ';
        file << '\n';
    }
    //Don't forget to free the memory allocated before
    for (auto ptr:vec)
        delete ptr;
    vec.clear();
    file.close();

}

int LoadGroupsFromFile(vector<BaseGroup *> &vec)
{
    ifstream file;
    file.open("Groups.txt");
    string ID, OWNER, NAME, s, TYPE,adminSet;
    while (file)
    {
        vector<string> memberList,adminList;
        set<int> vi,vi2;
        getline(file, TYPE);
        getline(file, ID);
        getline(file, OWNER);
        getline(file, NAME);
        getline(file,adminSet);
        getline(file, s);
        if (file.fail())
            break;

        boost::split(adminList, adminSet, boost::is_any_of(" "));
        adminList.pop_back(); //delete the '\0'
        for (const auto &ptr:adminList)
        {
            int i = stoi(ptr);
            vi2.insert(i);
        }


        boost::split(memberList, s, boost::is_any_of(" "));
        memberList.pop_back(); //delete the '\0'
        for (const auto &ptr:memberList)
        {
            int i = stoi(ptr);
            vi.insert(i);
        }
        if(TYPE != "QQ Group")
        {
            BaseGroup *a = new BaseGroup(TYPE, stoi(ID), stoi(OWNER), NAME, vi);
            vec.push_back(a);

        }
        else
        {
            QQGroup *b = new QQGroup(TYPE, stoi(ID), stoi(OWNER), NAME, vi, vi2);
            vec.push_back(b);
        }
    }
    file.close();
    return 0;
}

bool BaseGroup::RequestToJoin(int id)
{
    this->getMemberIDs().insert(id);
    return true;
}

int BaseGroup::PrintGroupDetail()
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
    waddstr(stdscr, "Owner & ID");
    move(LINES - 8, (COLS - 70));
    string b = FindUser(this->getCreator())->getNickname() + "   " + to_string(this->getCreator());
    auto *bb = const_cast<char *>(b.c_str());
    waddstr(stdscr, bb);
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

void BaseGroup::deleteMember(int id)
{
    this->memberSet.erase(id);
}
