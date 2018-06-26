
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "BaseUser.h"
#include "QQGroup.h"
#include <vector>
#include <map>
#include <string>
#include "something.h"

using namespace std;

int main()
{
    extern vector<BaseGroup *> GroupVec;
    extern vector<vector<BaseUser *> > UserVec;


/*

    const int arr[] = {1001, 1002, 1003, 1004, 1005, 1006};
    set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));

    const int arr2[] = {20000, 20001, 20002};
    set<int> mem(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));

    set<int> set1,emptySet;
    set1.insert(1000);
    emptySet.insert(10000);

    BaseGroup *A = new QQGroup("QQ Group", 1000, 10000, "Group 1000", mem,emptySet);
    BaseGroup *B = new BaseGroup("WeChat Group", 1001, 20000, "Group 1001", mem);
    BaseGroup *C = new BaseGroup("WeChat Group", 1002, 20000, "Group 1002", mem);
    BaseGroup *D = new BaseGroup("WeChat Group", 1003, 20000, "Group 1003", mem);
    BaseGroup *E = new BaseGroup("WeChat Group", 1004, 20000, "Group 1004", mem);
    BaseGroup *F = new BaseGroup("WeChat Group", 1005, 20000, "Group 1005", mem);
    BaseGroup *G = new BaseGroup("WeChat Group", 1006, 20000, "Group 1006", mem);

    GroupVec.push_back(A);
    GroupVec.push_back(B);
    GroupVec.push_back(C);
    GroupVec.push_back(D);
    GroupVec.push_back(E);
    GroupVec.push_back(F);
    GroupVec.push_back(G);


    map<int, string> emptyMap, QQ1, QQ2, We1, We2, We3;
    QQ1[10001] = "Myfriend";
    QQ2[10000] = "Myfriend";

    We1[20001] = "Ben20001";
    We1[20002] = "Kenny20002";

    We2[20000] = "Amy20000";
    We2[20002] = "Kenny20002";

    We3[20000] = "Amy20000";
    We3[20001] = "Ben20001";

    BaseUser *a = new BaseUser(1, "QQ", 10000, "123456", "Dick", 1999, 9, 9, "China", 2005, QQ1, set1);
    BaseUser *c = new BaseUser(1, "WeChat", 20000, "123456", "Amy", 1998, 9, 2, "China", 2008, We1, s);
    BaseUser *f = new BaseUser(1, "Weibo", 30000, "123456", "John", 1959, 2, 5, "Japan", 2007, emptyMap, set1);

    BaseUser *b = new BaseUser(2, "QQ", 10001, "123456", "John", 1959, 2, 5, "Japan", 2007, QQ2, set1);
    BaseUser *g = new BaseUser(2, "Weibo", 30001, "123456", "John", 1959, 2, 5, "Japan", 2007, emptyMap, set1);
    BaseUser *d = new BaseUser(2, "WeChat", 20001, "123456", "Ben", 1991, 4, 9, "Korea", 2004, We2, s);

    BaseUser *e = new BaseUser(3, "Weibo", 30002, "123456", "Kenny", 1988, 5, 4, "Australia", 2004, emptyMap, set1);
    BaseUser *i = new BaseUser(3, "QQ", 10002, "123456", "Kenny", 1988, 5, 4, "Australia", 2004, emptyMap, set1);
    BaseUser *h = new BaseUser(3, "WeChat", 20002, "123456", "Kenny", 1988, 5, 4, "Australia", 2004, We3, s);

    vector<BaseUser *> user1, user2, user3;

    user1.push_back(a);
    user1.push_back(c);
    user1.push_back(f);

    user2.push_back(d);
    user2.push_back(b);
    user2.push_back(g);

    user3.push_back(e);
    user3.push_back(i);
    user3.push_back(h);

    UserVec.push_back(user1);
    UserVec.push_back(user2);
    UserVec.push_back(user3);
*/



    Start();
    return 0;

}
