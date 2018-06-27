//
// Created by ycfung on 6/22/18.
//

#include "somethingRCF.h"
#include "BaseUserRCF.h"
#include "BaseGroupRCF.h"
#include <ncurses.h>

extern vector<vector<BaseUser *> > UserVec;

extern vector<BaseGroup *> GroupVec;

BaseUser *CurrentUser = nullptr;

int StartPrivateChat(int from, int to)
{
    system("clear");
    string command = "python3 privateclient.py " + to_string(from) + " " + to_string(to);
    system(command.c_str());
}

int StartGroupChat(int from, int groupID)
{
    system("clear");
    string command = "python3 groupclient.py " + to_string(from) + " " + to_string(groupID);
    system(command.c_str());
}

int LoginToServer(int PIN)
{
    string command = "python3 loginclient.py " + to_string(PIN) + " Online";
    system(command.c_str());
}

int LogoffFromServer(int PIN)
{
    string command = "python3 loginclient.py " + to_string(PIN) + " Offline";
    system(command.c_str());
}


int getchh()
{
    int ch;
    struct termios t_old, t_new; //NOLINT

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO); //NOLINT
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}


int VerifyPasswd(const char *prompt, const string &passwd)
{
    cin.clear();
    cin.ignore();
    cout << prompt << endl;
    again:
    const char BACKSPACE = 127;
    const char RETURN = 10;

    string password;
    unsigned char ch = 0;


    while ((ch = static_cast<unsigned char>(getchh())) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }

    if (password != passwd)
    {
        cout << endl << "Wrong password, try again." << endl;
        goto again;
    }
    cout << endl;

    return 0;

}

char getCharWithoutEnter()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON; //NOLINT
    old.c_lflag &= ~ECHO; //NOLINT
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

int getInt()
{
    int c;
    cin >> c;
    while (true)
    {
        if (cin.fail())
        {
            cout << "Invalid input, try again." << endl;
            cin.clear();
            cin.ignore();
            cin >> c;
        }
        else break;
    }
    return c;
}

string getString()
{
    string c;
    cin >> c;
    while (true)
    {
        if (cin.fail())
        {
            cout << "Invalid input, try again." << endl;
            cin.clear();
            cin.ignore();
            cin >> c;
        }
        else break;
    }
    return c;
}


void UpdateAccount(int ID)
{
    CurrentUser = FindUser(ID);
    vector<BaseUser *> Vec = FindUserVec(CurrentUser->getID());
    bool we = false, qq = false, wei = false;
    BaseUser *pQQ = nullptr, *pWeChat = nullptr, *pWeibo = nullptr;
    for (auto ptr:Vec)
    {
        if (ptr->getType() == "QQ")
            pQQ = ptr;
        else if (ptr->getType() == "Weibo")
            pWeibo = ptr;
        else if (ptr->getType() == "WeChat")
            pWeChat = ptr;
    }
    initscr();
    box(stdscr, ACS_VLINE, ACS_HLINE);
    move(LINES / 7, (COLS / 2) - 8);
    waddstr(stdscr, "Services status");
    move(LINES - 18, COLS - 65);
    waddstr(stdscr, "WeChat");
    move(LINES - 16, COLS - 65);
    waddstr(stdscr, "QQ");
    move(LINES - 14, COLS - 65);
    waddstr(stdscr, "Weibo");
    move(LINES - 18, COLS - 30);
    if (pWeChat != nullptr)
        waddstr(stdscr, "Active");
    else
        waddstr(stdscr, "Inactive");
    move(LINES - 16, COLS - 30);
    if (pQQ != nullptr)
        waddstr(stdscr, "Active");
    else
        waddstr(stdscr, "Inactive");
    move(LINES - 14, COLS - 30);
    if (pWeibo != nullptr)
        waddstr(stdscr, "Active");
    else
        waddstr(stdscr, "Inactive");
    move(LINES - 10, COLS - 70);
    waddstr(stdscr, "Press 1 to register WeChat, 2 for QQ, 3 for Weibo, else to exit");
    refresh();
    char navi = getCharWithoutEnter();
    if (navi == '1' && pWeChat == nullptr)
    {
        auto *tmp = new BaseUser(*CurrentUser);
        tmp->Type = "WeChat";
        FindUserVec(CurrentUser->getID()).push_back(tmp);

    }
    if (navi == '2' && pQQ == nullptr)
    {
        auto *tmp = new BaseUser(*CurrentUser);
        tmp->Type = "QQ";
        FindUserVec(CurrentUser->getID()).push_back(tmp);
    }
    if (navi == '3' && pWeibo == nullptr)
    {
        auto *tmp = new BaseUser(*CurrentUser);
        tmp->Type = "Weibo";
        if (CurrentUser->Type != "Weibo")
            tmp->ID += 20000;
        FindUserVec(CurrentUser->getID()).push_back(tmp);
    }
    else
    {
        erase();
        endwin();
        return;
    }
    refresh();
    erase();
    endwin();
    initscr();
    box(stdscr, ACS_VLINE, ACS_HLINE);
    move(LINES / 2, (COLS / 2) - 4);
    waddstr(stdscr, "Success!");
    getch();
    refresh();
    erase();
    endwin();
}


int SearchUser()
{
    system("clear");
    cout << "Please enter the ID:" << endl;
    int t = getInt();
    BaseUser *A = FindUser(t);
    char x;
    if (A == nullptr || A->getType() != CurrentUser->getType())
    {
        cout << "User does not exist." << endl;
        getchar();
        return -1;
    }
    cout << endl;
    A->PrintUserInfo();
    bool flag = false;
    for (auto ptr:CurrentUser->getFriendMap())
        if (ptr.first == A->getID())
            flag = true;
    while (flag) //NOLINT
    {
        cout << "1. Delete this friend." << endl << endl << "2. Go back." << endl << endl;
        x = getCharWithoutEnter();
        if (x == '1')
        {
            CurrentUser->getFriendMap().erase(A->getID());
            A->getFriendMap().erase(CurrentUser->getID());
            cout << '\b' << "Done!" << endl;
            break;
        }
        else if (x == '2')
            break;
        else
        {
            cout << '\b';
            break;
        }
    }

    while (!flag)
    {
        cout << endl << "1. Add this user as friend." << endl << endl << "2. Go back." << endl << endl;
        x = getCharWithoutEnter();
        if (x == '1')
        {
            if (CurrentUser->getID() == A->getID())
            {
                cout << "You can't add yourself." << endl;
                return 0;
            }
            else
            {
                //system("clear");
                cout << "Need a remark? (y/n)" << endl << endl;
                int xx = getCharWithoutEnter();
                if (xx == 'n')
                    CurrentUser->getFriendMap()[A->getID()] = CurrentUser->getNickname();
                else if (xx == 'y')
                {
                    cout << "Enter the remark:" << endl;
                    CurrentUser->getFriendMap()[A->getID()] = getString();
                }
                A->getFriendMap()[CurrentUser->getID()] = CurrentUser->getNickname();
            }
        }
        else if (x == '2')
            break;
        else
        {
            cout << '\b';
            break;
        }
    }
    return 0;
}

int SearchGroup()
{
    system("clear");
    if (CurrentUser->getType() == "WeChat")
    {

        initscr();
        box(stdscr, ACS_VLINE, ACS_HLINE);
        move(LINES / 4, (COLS / 2) - 5);
        waddstr(stdscr, "FORBIDDEN!!");
        move(LINES / 1.8, (COLS / 2) - 24);
        waddstr(stdscr, "WeChat user can join a group by invitation ONLY");
        move(1, 1);
        refresh();
        getch();
        erase();
        endwin();
        return 0;
    }
    cout << "Please enter the group number: (enter 0 to exit)" << endl;
    while (true)
    {
        int num = getInt();
        if (num == 0)
            break;
        BaseGroup *G = FindGroup(num);
        if (G == nullptr || G->getType() != CurrentUser->getType() || G->getType() != CurrentUser->getType())
        {
            cout << "Not found. Try again?" << endl;
            continue;
        }
        else
        {
            G->PrintGroupDetail();
            cout << "1. Request to join" << endl << "2.Go back" << endl;
            while (true)
            {
                int b = getCharWithoutEnter();
                if (b == '1')
                {
                    CurrentUser->JoinAGroup(num);
                    break;
                }
                if (b == '2')
                    break;
                else continue;
            }
        }

    }

}

int Start()
{
    LoadGroupsFromFile(GroupVec);
    LoadUsersFromFile(UserVec);
    system("clear");
    int type, id;
    char navi;
    string password;
    cout << "Please login: (Ctrl + C to exit anytime)" << endl << endl;
    cout << "Account type: 1.WeChat 2.QQ 3.Weibo" << endl << endl;
    while (true)
    {
        type = getCharWithoutEnter();
        if (type == '1' || type == '2' || type == '3')
            break;
        else
            cout << "\b";
    }
    cout << "Please enter your ID: " << endl;
    while (true)
    {
        id = getInt();
        if (FindUser(id) == nullptr)
        {
            cout << "User does not exist, try again." << endl;
            continue;
        }
        else break;
    }
    cout << endl;
    VerifyPasswd("Please enter the password: ", FindUser(id)->getPassword());
    CurrentUser = FindUser(id);
    LoginToServer(CurrentUser->getPIN());
    while (true)
    {
        system("clear");
        initscr();
        box(stdscr, ACS_VLINE, ACS_HLINE);
        move(LINES / 7, (COLS / 2) - 6);
        waddstr(stdscr, "Main Menu");
        move(LINES - 18, (COLS - 70));
        waddstr(stdscr, "1. Show contacts");
        move(LINES - 15, (COLS - 70));
        waddstr(stdscr, "2. Show group chats");
        move(LINES - 12, (COLS - 70));
        waddstr(stdscr, "3. Search a user");
        move(LINES - 9, (COLS - 70));
        waddstr(stdscr, "4. Search a group");
        move(LINES - 18, (COLS - 33));
        waddstr(stdscr, "5. Friend recommendation");
        move(LINES - 15, (COLS - 33));
        waddstr(stdscr, "6. Profile");
        move(LINES - 12, (COLS - 33));
        waddstr(stdscr, "7. Platform services");
        move(LINES - 9, (COLS - 33));
        waddstr(stdscr, "8. Exit");
        refresh();
        while (true)
        {
            navi = getCharWithoutEnter();
            if (navi > '0' && navi < '9')
                break;
            else continue;
        }
        erase();
        endwin();

        switch (navi)
        {
            default:
                break;
            case '1':
                CurrentUser->PrintUserContact();
                break;
            case '2':
                CurrentUser->PrintGroupContacts();
                break;
            case '3':
                SearchUser();
                getchar();
                break;
            case '4':
                SearchGroup();
                break;
            case '5':
                CurrentUser->FriendsRecommend();
                getchar();
                break;
            case '6':
                CurrentUser->PrintUserInfo();
                getchar();
                break;
            case '7':
                UpdateAccount(CurrentUser->getID());
                break;
            case '8':
                LogoffFromServer(CurrentUser->getPIN());
                SaveGroupsToFile(GroupVec);
                SaveUsersToFile(UserVec);
                initscr();
                box(stdscr, ACS_VLINE, ACS_HLINE);
                move(LINES / 7, (COLS / 2) - 4);
                waddstr(stdscr, "Bye bye!");
                refresh();
                getch();
                endwin();
                return 0;
        }
    }
}
