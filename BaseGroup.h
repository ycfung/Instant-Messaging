//
// Created by ycfung on 5/17/18.
//

#ifndef IM_BASEGROUP_H
#define IM_BASEGROUP_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <set>

using namespace std;



class BaseGroup //NOLINT
{
private:

    string Type;

    int id;

    int Creator;

    string name;

    set<int> memberSet;

public:
    BaseGroup() = default;

    BaseGroup(string TYPE, int ID, int CREATOR, string NAME, set<int> mem)
    {
        Type = std::move(TYPE);
        id = ID;
        Creator = CREATOR;
        name = std::move(NAME);
        memberSet = std::move(mem);
    }

    friend int SaveGroupsToFile(vector<BaseGroup *> &vec);

    friend int LoadGroupsFromFile(vector<BaseGroup *> &vec);

    virtual bool RequestToJoin(int id);

    string getType()
    { return Type;}

    string getName()
    { return name; }

    int getID()
    { return id; };

    int getCreator()
    { return Creator; }

    unsigned long getNumOfMem()
    { return memberSet.size(); };

    set<int> & getMemberIDs()
    { return memberSet; }

    void addMember(int id)
    { memberSet.insert(id); }

    void deleteMember(int id);

    void ChangeName(string str)
    {name = std::move(str);}

    virtual int PrintGroupDetail();

};

BaseGroup * FindGroup(int id);


int SaveGroupsToFile(vector<BaseGroup *> &vec);

int LoadGroupsFromFile(vector<BaseGroup *> &vec);

#endif //IM_BASEGROUP_H
