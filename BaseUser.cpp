//
// Created by ycfung on 5/19/18.
//

#include "BaseUser.h"
#include "BaseGroup.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <ncurses.h>

using namespace std;

//2D user info array
vector<vector<BaseUser *> > UserVec;

vector<BaseGroup *> GroupVec;


BaseUser::BaseUser() : Birthday(1970, 1, 1)
{
    Type = "N/A";
    ID = 0000;
    Nickname = "N/A";
    Location = "N/A";
    RegYear = 1970;
}

BaseUser::BaseUser(int pin, string type, int id, string PASSWD, string str, int y, int m, int d, string str2, int RegY,
                   map<int, string> map1, set<int> set1) : Birthday(y, m, d)
{
    PIN = pin;
    Type = std::move(type);
    ID = id;
    passwd = std::move(PASSWD);
    Nickname = std::move(str);
    Location = std::move(str2);
    RegYear = RegY;
    FriendMap = std::move(map1);
    GroupSet = std::move(set1);
}


int BaseUser::PrintFriendInfo(int id)
{
    for (auto p:UserVec)
    {
        for (auto ptr:p)
        {
            if (ptr->ID == id)
            {
                if (FriendMap.count(id) > 0)
                    cout << "Here's your friend " << FriendMap[id] << "'s profile:" << endl;

                cout << Type << "ID: " << ptr->ID << endl;
                cout << "Nickname: " << ptr->Nickname << endl;
                cout << "Birthday: " << ptr->Birthday.getYear() << '.' << ptr->Birthday.getMonth() << '.'
                     << ptr->Birthday.getDay() << endl;
                cout << "Location: " << ptr->Location << endl;
                cout << "Member since: " << ptr->RegYear << endl;
            }
            else
                continue;
        }
    }
}


int BaseUser::PrintUserInfo()
{

    cout << "Here's the profile:" << endl<<endl;
    cout << Type << " ID: " << ID << endl<<endl;
    cout << "Nickname: " << Nickname << endl<< endl;
    cout << "Birthday: " << Birthday.getYear() << '.' << Birthday.getMonth() << '.' << Birthday.getDay() << endl<< endl;
    cout << "Location: " << Location << endl<< endl;
    cout << "Member since: " << RegYear << endl<< endl;

}


int SaveUsersToFile(vector<vector<BaseUser *>> &vec)
{
    ofstream file;
    file.open("Users.txt");
    for (const auto &p:vec)
    {
        for (auto ptr:p)
        {
            file << (*ptr).PIN<< '\n';
            file << (*ptr).Type << '\n';
            file << (*ptr).ID << '\n';
            file << (*ptr).passwd << '\n';
            file << (*ptr).Nickname << '\n';
            file << (*ptr).RegYear << '\n';
            file << (*ptr).Birthday.getYear() << ' ' << (*ptr).Birthday.getMonth() << ' ' << (*ptr).Birthday.getDay()
                 << '\n';
            file << (*ptr).Location << '\n';

            for (const auto &pb :(*ptr).FriendMap)
                file << pb.first << ' ' << pb.second << ' ';
            file << '\n';

            for (const auto &pd :(*ptr).GroupSet)
                file << pd << ' ';
            file << '\n';

        }
    }
    file.close();
    for (auto ptr:vec)
        for (auto p:ptr)
            delete p;
    vec.clear();
}

//Bad codes below
int LoadUsersFromFile(vector<vector<BaseUser *> > &UserVec)
{
    vector<BaseUser *> vec;
    ifstream file;
    file.open("Users.txt");
    string TYPE, id, pin, NICKNAME, REGYEAR, birthday, Y, M, D, LOCATION, passwd;
    string tmp1, tmp2;
    //Read CurrentUser 1D vector from file
    while (file)
    {
        map<int, string> map1;
        set<int> set1;
        vector<string> vec1, vec2, birth;
        getline(file, pin);
        getline(file, TYPE);
        getline(file, id);
        getline(file, passwd);
        getline(file, NICKNAME);
        getline(file, REGYEAR);
        getline(file, birthday);
        getline(file, LOCATION);
        getline(file, tmp1);
        getline(file, tmp2);
        if (file.fail())
            break;
        boost::split(birth, birthday, boost::is_any_of(" "));
        birth.pop_back();
        boost::split(vec1, tmp1, boost::is_any_of(" "));
        vec1.pop_back();
        boost::split(vec2, tmp2, boost::is_any_of(" "));
        vec2.pop_back();
        Y = birth[0];
        M = birth[1];
        D = birth[2];
        for (int count = 0; count < vec1.size(); count += 2)
            map1[stoi(vec1[count])] = (vec1[count + 1]);
        for (const auto &ptr: vec2)
            set1.insert(stoi(ptr));
        BaseUser *a = new BaseUser(stoi(pin), TYPE, stoi(id), passwd, NICKNAME, stoi(Y), stoi(M), stoi(D), LOCATION,
                                   stoi(REGYEAR), map1, set1);
        vec.push_back(a);
    }

    //Divide into CurrentUser 2D vector according to the PIN
    int tPIN = 0;
    for (auto ptr:vec)
    {
        if (ptr->PIN == tPIN)
            UserVec.back().push_back(ptr);
        else
        {
            vector<BaseUser *> iVec;
            iVec.push_back(ptr);
            UserVec.push_back(iVec);
            tPIN = ptr->PIN;
        }
    }
    file.close();
    return 0;
}

vector<BaseUser *>  FindUserVec(int id)
{
    for (auto pb:UserVec)
        for (auto pd:pb)
            if (pd->getID() == id)
                return pb;
}


BaseUser *FindUser(int id)
{
    for (auto pb:UserVec)
        for (auto pd:pb)
            if (pd->ID == id)
                return pd;
    return nullptr;
}

BaseGroup *FindGroup(int groupid)
{
    for (auto ptr: GroupVec)
        if (groupid == ptr->getID())
            return ptr;
    return nullptr;
}


int BaseUser::FriendsRecommend()
{
    //system("clear");
    cout << "Friend recommendation:" << endl;
    for (auto ptr:FindUserVec(ID))
    {
        if (ptr->Type == Type)
            continue;
        for (const auto &p1:ptr->FriendMap)
        {
            vector<BaseUser *> temp = FindUserVec(p1.first);
            BaseUser *tmp = nullptr;
            for (auto p2:temp)
                if (p2->Type == Type)
                    tmp = p2;
            if (tmp == nullptr)
                continue;
            //Make sure you don't have this friend
            for (auto p3:FriendMap)
                if (tmp->ID == p3.first)
                    continue;

            //Show the recommendation
            cout << "From " << tmp->Type << endl;
            PrintFriendInfo(tmp->ID);
        }
    }
}

bool BaseUser::DeleteFriend(int id)
{
    if (FriendMap.count(id) > 0)
    {
        FriendMap.erase(id);
        BaseUser *fd = FindUser(id);
        if (fd != nullptr)
            fd->FriendMap.erase(this->ID);
        cout << "Deleted." << endl;
        return true;
    }
    cout << "Not deleted." << endl;
    return false;
}

bool BaseUser::QuitAGroup(int id)
{
    BaseGroup *pd = FindGroup(id);

    if(pd == nullptr)
        return false;

    if (this->ID == pd->getCreator())
    {
        cout << "Please delete the group in management" << endl;
        getchar();
        return false;
    }
    cout << "breakpoint1" << endl;
    GroupSet.erase(id);
    cout << "breakpoint2" << endl;

    pd->deleteMember(this->ID);

    return true;

    cout << "End function" << endl;
    return true;
}

bool BaseUser::AddAFriend(int id, const string &remark)
{
    BaseUser *usr = FindUser(id);
    if (usr != nullptr)
    {
        this->FriendMap[id] = remark;
        usr->FriendMap[this->ID] = this->Nickname;
        return true;
    }
    else return false;
}

bool BaseUser::AddAFriend(int id)
{
    BaseUser *usr = FindUser(id);
    if (usr != nullptr)
    {
        this->FriendMap[id] = usr->Nickname;
        usr->FriendMap[this->ID] = this->Nickname;
        return true;
    }
    else return false;
}


bool BaseUser::ChangeRemark(int id, const string &newRemark)
{
    if (FriendMap.count(id) > 0)
    {
        FriendMap[id] = newRemark;
        return true;
    }
    return false;
}

int BaseUser::PrintGroupContacts()
{
    label:
    system("clear");
    cout << "┌──────────────────────────────────────────────────────────────────────┐" << endl;
    cout << setw(12) << setiosflags(ios::left) << "│ID " << setfill(' ') << "│";
    cout << setw(24) << setiosflags(ios::left) << "Group name " << setfill(' ') << "│";
    cout << setw(9) << setiosflags(ios::left) << "Members " << setfill(' ') << "│";
    cout << setw(13) << setiosflags(ios::left) << "Owner " << setfill(' ') << "│";
    cout << setw(18) << setiosflags(ios::left) << "Owner ID   │" << setfill(' ') << endl;
    for (auto ptr: this->GroupSet)
    {
        if (FindGroup(ptr) == nullptr)
            continue;
        cout << "│";
        cout << setw(9) << setiosflags(ios::left) << ptr << setfill(' ') << "│";
        cout << setw(24) << setiosflags(ios::left) << FindGroup(ptr)->getName() << setfill(' ') << "│";
        cout << setw(9) << setiosflags(ios::left) << FindGroup(ptr)->getNumOfMem() << setfill(' ') << "│";
        cout << setw(13) << setiosflags(ios::left) << FindUser((FindGroup(ptr)->getCreator()))->getNickname()
             << setfill(' ') << "│";
        cout << setw(11) << setiosflags(ios::left) << FindGroup(ptr)->getCreator() << setfill(' ') << "│" << endl;
    }
    cout << "└──────────────────────────────────────────────────────────────────────┘" << endl;

    cout << "1.Select a group  2.Go back" << endl;
    char navi = getCharWithoutEnter();
    if (navi == '2')
        return 0;
    else if (navi != '1')
    {
        cout << "Wrong input, try again." << endl;
        goto label;
    }
    else if (navi == '1')  //NOLINT
    {
        BaseGroup *obj;
        int tempID;
        cout << "Enter the ID:" << endl;
        while (true)
        {

            tempID = getInt();
            obj = FindGroup(tempID);
            if (obj == nullptr)
                cout << "Not found, try again." << endl;
            else break;
        }


        int IDToInvite;
        string tempStr;
        while (true)
        {
            cout << endl
                 << "1.Show the details\n2.Invite someone\n3.Manage the group\n4.Quit the group\n5.Start group chat\n6.Go back"
                 << endl;
            label3:while (true)
            {
                navi = getCharWithoutEnter();
                if (navi > '0' && navi < '7')
                    break;
                else continue;
            }
            switch (navi)
            {
                default:
                    break;
                case '1':
                    obj->PrintGroupDetail();
                    goto label3;
                case '2':
                    cout << "Enter the ID of user you want to invite." << endl;
                    IDToInvite = getInt();
                    InviteToGroup(tempID, IDToInvite);
                    cout << "Done!" << endl;
                    getchar();
                    goto label;
                case '3':
                    ManageAGroup(tempID);
                    cout << "Done!" << endl;
                    getchar();
                    goto label;
                case '4':
                    QuitAGroup(tempID);
                    cout << "Done!" << endl;
                    getchar();
                    goto label;
                case '5':
                    StartGroupChat(this->getID(), obj->getID());
                    goto label;
                case '6':
                    goto label;
            }
        }
    }
    return 0;
}

int BaseUser::PrintUserContact()
{
    remove("OnlineList.txt");
    system("wget -b http://127.0.0.1:6666/OnlineList.txt");
    remove("wget-log");

    manage:
    system("clear");
    cout << "┌──────────────────────────────────────────────────────────────────────┐" << endl;
    cout << setw(14) << setiosflags(ios::left) << "│ID  " << setfill(' ') << "│";
    cout << setw(24) << setiosflags(ios::left) << "Nickname  " << setfill(' ') << "│";
    cout << setw(24) << setiosflags(ios::left) << "Remark  " << setfill(' ') << "│";
    cout << setw(9) << setiosflags(ios::left) << "Status  │" << setfill(' ') << endl;
    for (const auto &ptr : FriendMap)
    {
        BaseUser &fd = *FindUser(ptr.first);
        cout << "│";
        cout << setw(11) << setiosflags(ios::left) << ptr.first << setfill(' ') << "│";
        cout << setw(24) << setiosflags(ios::left) << FindUser(ptr.first)->Nickname << setfill(' ') << "│";
        cout << setw(24) << setiosflags(ios::left) << ptr.second << setfill(' ') << "│";
        cout << setw(8) << setiosflags(ios::left) << CheckIfOnline(fd.PIN) << setfill(' ') << "│" << endl;

    }
    cout << "└──────────────────────────────────────────────────────────────────────┘" << endl;
    label:
    cout << "1.Manage friends  2.Go back" << endl;
    char navi = getCharWithoutEnter();
    if (navi == '2')
        return 0;
    else if (navi != '1')
    {
        cout << "Invalid input." << endl;
        getchar();
        goto label;
    }
    else
    {

        int tempID;
        BaseUser *obj;
        string tempStr;
        while (true)
        {
            while (true)
            {
                cout << "Enter your friend's ID:" << endl;
                tempID = getInt();
                getchar();
                obj = FindUser(tempID);
                bool flag = false;
                for (auto ptr:this->FriendMap)
                    if (ptr.first == tempID)
                        flag = true;
                if (obj != nullptr && flag)
                    break;
                else
                {
                    cout << "Not found." << endl;
                    getchar();
                    goto manage;
                }
            }
            cout << "1.Delete the friend  2.Change remark  3.Start a chat  4.Go back" << endl;
            while (true)
            {
                navi = getCharWithoutEnter();
                if (navi > '0' && navi < '5')
                    break;
                else continue;
            }
            switch (navi)
            {
                default:
                    break;
                case '1':
                    DeleteFriend(tempID);
                    cout << "Done!" << endl << endl;
                    getchar();
                    goto manage;
                case '2':
                    cout << "Enter a new reamrk" << endl;
                    tempStr = getString();
                    ChangeRemark(tempID, tempStr);
                    cout << "Done!" << endl;
                    getchar();
                    goto manage;
                case '3':
                    StartPrivateChat(this->getID(), tempID);
                    goto manage;
                case '4':
                    return 0;
            }
        }
    }
}

string CheckIfOnline(int PIN)
{
    string PINinfile;
    ifstream file("OnlineLists.txt");
    while (file)
    {
        getline(file, PINinfile);
        if (file.fail())
            break;
        if (stoi(PINinfile) == PIN)
            return "Online";
        else continue;
    }
    return "Offline";
}

bool BaseUser::JoinAGroup(int groupid)
{
    BaseGroup *pd = FindGroup(groupid);
    if (pd == nullptr)
    {
        cout << "Not found." << endl;
        return false;
    }
    if (Type == "WeChat" || pd->getType() == "WeChat Group")
    {
        cout << "Cannot join a group by searching." << endl;
        return true;
    }
    else
        pd->RequestToJoin(this->getID());
    return false;
}

bool BaseUser::InviteToGroup(int groupid, int user1id)
{
    //check the parameters
    if (FindUser(user1id) == nullptr)
        if (FindGroup(groupid) == nullptr)
            return false;
    //Check the current user if in group chat
    int tmp;
    for (auto ptr:this->GroupSet)
    {
        tmp = ptr;
        if (tmp == this->ID)
        {
            BaseUser *user = FindUser(user1id);
            user->GroupSet.insert(groupid);
            BaseGroup *group = FindGroup(groupid);
            group->addMember(user1id);
            break;
        }
        else continue;
    }

    return true;
}

bool BaseUser::ManageAGroup(int id)
{
    BaseGroup *obj = FindGroup(id);
    if (this->getID() != FindGroup(id)->getCreator())
    {
        initscr();
        box(stdscr, ACS_VLINE, ACS_HLINE);
        move(LINES / 4, (COLS / 2) - 5);
        waddstr(stdscr, "FORBIDDEN!!");
        move(LINES / 1.8, (COLS / 2) - 20);
        waddstr(stdscr, "You are not authorized to manage this group");
        move(1, 1);
        refresh();
        getch();
        erase();
        endwin();
        return 0;
        return false;
    }
    else
    {

        char navi;
        int memToKick;
        string newName;
        while (true)
        {
            system("clear");
            cout << "1.Kick someone out" << endl << endl << "2.Change the name" << endl << endl << "3.Delete the group"
                 << endl << endl << "4.Go Back" << endl << endl;
            navi = getCharWithoutEnter();
            if (navi > '0' && navi < '5')
            {
                switch (navi)
                {
                    default:
                        break;
                    case '1':
                        cout << "Enter the ID you wanna kick:" << endl;
                        memToKick = getInt();
                        if (FindUser(memToKick) == nullptr)
                        {
                            cout << "Not found." << endl;
                            break;
                        }
                        obj->deleteMember(memToKick);
                        cout << "Done!" << endl;
                        getchar();
                        break;
                    case '2':
                        cout << "Enter a new name:" << endl;
                        obj->ChangeName(getString());
                        cout << "Done!" << endl;
                        getchar();
                        break;
                    case '3':
                        for (auto ptr:obj->getMemberIDs())
                            obj->deleteMember(ptr);
                        cout << "Done!" << endl;
                        getchar();
                        break;
                    case '4':
                        return true;
                }
                break;
            }
            else continue;
        }
    }
}
