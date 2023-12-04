//#include "openai.hpp"

#include "project.h"

std::map<std::string, Male_Member*> mlist;
std::map<std::string, Female_Member*> flist;

unsigned int member_count = 0;

int main(){
    int menu, submenu, num_member, nheight, nweight;
    std::string temp;
    std::string name, gender, pw;
    std::ifstream memberList("MemberList.txt");
    if(!memberList.fail())
    {
        std::cout << "Loading DB file..." << std::endl;
        while(1)
        {
            memberList >> temp;
            if(memberList.eof())
                break;
            num_member = atoi(temp.c_str());
            std::cout << num_member << std::endl;
        }
    }

    memberList.close();
    while(1)
    {
        show_menu();
        std::cout << "Enter : ";
        std::cin >> menu;
        if(menu == 1)
        {
            std::cout << "Enter Nickname : ";
            std::cin >> name;
            if(find_member(name) != 0)
            {
                std::cout << "He/She is already join" << std::endl << std::endl;
                continue;
            }
            std::cout << "Male or Female ? ";
            std::cin >> gender;
            if(gender == "Male")
            {
                Male_Member *mnode = new Male_Member(++member_count, name);
                mlist.insert(std::pair<std::string, Male_Member*>(name, mnode));
                std::cout << name << " (Male) : Register Complete" << std::endl << std::endl;
            }
            else if(gender == "Female")
            {
                Female_Member *fnode = new Female_Member(++member_count, name);
                flist.insert(std::pair<std::string, Female_Member*>(name, fnode));
                std::cout << name << " (Female) : Register Complete" << std::endl << std::endl;
            }
            else
            {
                std::cout << "Invalid Gender" << std::endl << std::endl;
                continue;
            }
        }
        else if(menu == 2)
        {
            std::cout << "Enter Nickname : ";
            std::cin >> temp;
            if(find_member(name) == 0)
                std::cout << "He/She is not joined" << std::endl << std::endl;
            else if(find_member(name) == 1)
            {
                Male_Member *mnode = (mlist.find(name))->second;
                std::cout << "Enter password : ";
                std::cin >> pw;
                if(!mnode->log_in(pw))
                {
                    std::cout << "Wrong Password" << std::endl << std::endl;
                    continue;
                }
                mlist.erase(name);
                delete mnode;
                std::cout << name << " (Male) : Delete Complete" << std::endl << std::endl;
            }
            else if(find_member(name) == 2)
            {
                Female_Member *fnode = (flist.find(name))->second;
                std::cout << "Enter password : ";
                std::cin >> pw;
                if(!fnode->log_in(pw))
                {
                    std::cout << "Wrong Password" << std::endl;
                    continue;
                }
                flist.erase(name);
                delete fnode;
                std::cout << name << " (Female) : Delete Complete" << std::endl << std::endl;
            }
        }
        else if(menu == 3)
        {
            std::cout << "Enter Nickname : ";
            std::cin >> temp;
            if(find_member(name) == 0)
                std::cout << "He/She is not joined" << std::endl;
            else if(find_member(name) == 1)
            {
                Male_Member *mnode = (mlist.find(name))->second;
                std::cout << "Enter password : ";
                std::cin >> pw;
                if(!mnode->log_in(pw))
                {
                    std::cout << "Wrong Password" << std::endl;
                    continue;
                }
                mnode->show_member_info();
                while(1)
                {
                    show_member_menu();
                    std::cout << "Enter : ";
                    std::cin >> submenu;
                    if(submenu == 1)
                    {
                        std::cout << "====== New Body Check ======" << std::endl;
                        std::cout << "Enter New Height : ";
                        std::cin >> nheight;
                        std::cout << "Enter New Weight : ";
                        std::cin >> nweight;
                        mnode->body_check(nheight, nweight);
                        std::cout << name << ": New Body Check Complete" << std::endl;
                    }
                    else if(submenu == 2)
                    {
                        mnode->show_body_chart();
                    }
                    else if(submenu == 3)
                    {
                        std::cout << "Now Plan" << std::endl;

                    }
                    else if(submenu == 4)
                    {
                        std::cout << "New Plan" << std::endl;
                    }
                    else if(submenu == 5)
                    {
                        std::cout << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Wrong Input! Try Again" << std::endl;
                    }
                }
            }
            else if(find_member(name) == 2)
            {
                Female_Member *fnode = (flist.find(name))->second;
                std::cout << "Enter password : ";
                std::cin >> pw;
                if(!fnode->log_in(pw))
                {
                    std::cout << "Wrong Password" << std::endl;
                    continue;
                }
                
            }
        }
        else if(menu == 4)
        {
            save_db();
        }
        else if(menu == 5)
        {
            save_db();
            std::cout << "Final Req Quit" << std::endl;
            break;
        }
        else
        {
            std::cout << "Wrong Input! Try Again" << std::endl;
        }
    }
}

void show_menu()
{
    std::cout << "=========================================" << std::endl;
    std::cout << "=============== Final Rep ===============" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "[1] Add Member        [2] Delete Member" << std::endl;
    std::cout << "[3] Find Member       [4] Save DB      " << std::endl;
    std::cout << "[5] Quit                               " << std::endl;
}

void show_member_menu()
{
    std::cout << "=========================================" << std::endl;
    std::cout << "[1] New Body Check    [2] Show Body Chart" << std::endl;
    std::cout << "[3] My Work Out Plan  [4] Make New Plan      " << std::endl;
    std::cout << "[5] Back                               " << std::endl;
}

int find_member(std::string name)
{
    if(mlist.find(name) != mlist.end())
        return 1;
    else if(flist.find(name) != flist.end())
        return 2;
    else
        return 0;
}

void save_db()
{
    std::ofstream memberList("MemberList.txt", std::ios::out | std::ios::trunc);
    std::map<std::string, Male_Member*>::iterator miter;
    std::map<std::string, Female_Member*>::iterator fiter;
    Male_Member* mnode;
    Female_Member* fnode;

    for(miter = mlist.begin(); miter != mlist.end(); miter++)
    {
        mnode = miter->second;
        unsigned int mid = mnode->getID();
        memberList << mid << " ";
        mnode->save_file();
    }
    memberList << "| ";
    for(fiter = flist.begin(); fiter != flist.end(); fiter++)
    {
        fnode = fiter->second;
        unsigned int fid = fnode->getID();
        memberList << fid << " ";
        fnode->save_file();
    }
    memberList.close();
}