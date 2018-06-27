//
// Created by ycfung on 5/19/18.
//

#ifndef IM_BASEUSER_H
#define IM_BASEUSER_H

#include "DateRCF.h"
#include "BaseGroupRCF.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include "somethingRCF.h"

using namespace std;

class BaseUser
{
protected:

    int PIN;

    string Type;

    int ID;

    string Nickname;

    int RegYear;

    Date Birthday;

    string Location;

    string passwd;

    map<int, string> FriendMap; //map: id:remark

    set<int> GroupSet;

public:

    bool ManageAGroup(int id);

    bool JoinAGroup(int id);

    friend BaseGroup * FindGroup(int groupid);

    friend BaseUser * FindUser(int ID);

    bool QuitAGroup(int id);

    friend void UpdateAccount(int ID);

    bool AddAFriend(int id, const string &remark);

    bool ChangeRemark(int id, const string &newRemark);

    bool DeleteFriend(int id);

    string getPassword()
    { return passwd; }

    string getNickname()
    { return Nickname; }

    string getType()
    {return Type;}

    int getID()
    { return ID; }

    int getPIN()
    { return PIN; }

    set<int> getGroupSet()
    { return GroupSet; }

    map<int, string> getFriendMap()
    { return FriendMap; }

    friend void UpdateAccount(int ID);

    friend int SaveUsersToFile(vector<vector<BaseUser *>> &vec); //Use CurrentUser 2D vector to store user info

    friend int LoadUsersFromFile(vector<vector<BaseUser *>> &UserVec);

    friend vector<BaseUser *> FindUserVec(int id);

    friend BaseUser *FindUser(int ID);

    BaseUser();

    BaseUser(int pin, string type, int id, string passwd, string str, int y, int m, int d, string str2, int RegY,
             map<int, string> map1, set<int> set1);

    BaseUser(BaseUser & a):Birthday(a.Birthday.getYear(),a.Birthday.getMonth(),a.Birthday.getDay())
    {
        PIN = a.PIN;
        Type = a.Type;
        ID = a.ID;
        passwd = a.passwd;
        Nickname = a.Nickname;
        Location = a.Location;
        RegYear = a.RegYear;
    }

    int PrintFriendInfo(int id);

    int PrintGroupContacts();

    int PrintUserInfo();

    int FriendsRecommend();

    bool AddAFriend(int id);

    int PrintUserContact();

    bool InviteToGroup(int groupid, int user1id);

};

int SaveUsersToFile(vector<vector<BaseUser *>> &vec); //Use CurrentUser 2D vector to store user info

int LoadUsersFromFile(vector<vector<BaseUser *>> &UserVec);

string CheckIfOnline(int PIN);
BaseUser *FindUser(int ID);
vector<BaseUser *> FindUserVec(int id);
#endif //IM_BASEUSER_H
