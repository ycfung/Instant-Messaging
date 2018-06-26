//
// Created by ycfung on 6/20/18.
//

#ifndef UNLIMITED_CLIENT_QQGROUP_H
#define UNLIMITED_CLIENT_QQGROUP_H


#include "BaseGroup.h"

class QQGroup:public BaseGroup
{
public:
    QQGroup(string TYPE, int ID, int CREATOR, string NAME, set<int> mem, set<int> ADMINS);

    set<int> getAdmins()
    { return admins;}

    bool RequestToJoin(int id) override;

    bool Verify(int id);

    int PrintGroupDetail() override;

private:
    set<int> admins;

};


#endif //UNLIMITED_CLIENT_QQGROUP_H
