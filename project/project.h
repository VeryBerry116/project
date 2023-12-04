#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <map>

unsigned int work_per_week[8][7] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 0, 0, 0 },
    { 1, 0, 1, 0, 1, 0, 0 },
    { 1, 0, 1, 0, 1, 0, 1 },
    { 1, 1, 0, 1, 1, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 }
};

// chest = 1, back = 2, leg = 3, arm = 4, shoulder =5
unsigned int work_partition[4][5] = {
    { 1, 3, 2, 3, 0 },          // 2
    { 1, 2, 3, 0, 0 },          // 3
    { 1, 2, 3, 4, 0 },          // 4
    { 1, 2, 3, 4, 5 }           // 5
};

class Member{
protected:
    class node {
    public:
        node(unsigned int h, unsigned int w, node* next_node) : 
            height(h), weight(w), next_node(next_node) {
        }
        ~node(){
        }

    public:
        unsigned int    height, weight;
        node*           next_node;
    };

    unsigned int    ID;
    std::string     password;
    std::string     nickname;
    node*           head;
    unsigned int    goal;

public:
    Member(unsigned int data_in, std::string name);
    ~Member();

    bool match_nickname(std::string name);
    unsigned int getID();
    bool log_in(std::string pw);
    void show_member_info();
    void body_check(int h, int w);
    void show_body_chart();
};


class Male_Member : public Member {
public:
    Male_Member(unsigned int data_in, std::string name);
    Male_Member(unsigned int data_in, std::string name, 
        unsigned int b, unsigned int s, unsigned int d, unsigned int wf, unsigned int wp);
    ~Male_Member(){
    }

    //void make_work_out_plan;

    void save_file();


private:
    unsigned int    bench;
    unsigned int    squat;
    unsigned int    deadlift;
    unsigned int    work_out_frequency;
    unsigned int    work_out_partition;
};

class Female_Member : public Member {
public:
    Female_Member(unsigned int data_int, std::string name);
    Female_Member(unsigned int data_in, std::string name, unsigned int c);
    ~Female_Member(){
    }

    void save_file();

private:
    unsigned int    cardio;
};

Member::Member(unsigned int data_in, std::string name) : 
    ID(data_in), nickname(name) {  
    std::cout << "Enter Password (0000 ~ 9999) : ";
    std::cin >> password;

    head = NULL;
    goal = 0;
}

Member::~Member() {
    node* temp1;
    node* temp2;
    temp1 = head;
    while(1)
    {
        if(temp1 == NULL)
            break;
        temp2 = temp1;
        temp1 = temp1->next_node;
        delete temp2;
    }
    std::cout << nickname << " is deleted" << std::endl;
}

bool Member::match_nickname(std::string name)
{
    return nickname.compare(name) == 0 ? true : false;
}

unsigned int Member::getID()
{
    return ID;
}

bool Member::log_in(std::string pw)
{
    return password.compare(pw) == 0 ? true : false;
}

void Member::show_member_info()
{
    std::cout << "============== Member Info ==============" << std::endl;
    std::cout << "Nickname : " << nickname << std::endl;
    std::cout << "Member ID : " << ID << std::endl;
}

void Member::body_check(int h, int w) {
    node* temp = new node(h, w, NULL);

    if(head == NULL)
        head = temp;
    else
    {
        node* tempt = head;
        while(tempt->next_node != NULL)
            tempt = tempt->next_node;
        tempt->next_node = temp;
    }
    std::cout << std::endl;
}

void Member::show_body_chart() {
    node* temp = head;
    if(temp == NULL)
    {
        std::cout << "No Data. Do Bodycheck!" << std::endl;
        return;
    }
    while(temp != NULL)
    {
        if(temp != head)
            std::cout << " > ";
        std::cout << temp->height << "/" << temp->weight;
        temp = temp->next_node;
    }
    std::cout << std::endl << std::endl;
}

Male_Member::Male_Member(unsigned int data_in, std::string name) : Member(data_in, name){
    bench = 0;
    squat = 0;
    deadlift = 0;
    work_out_frequency = 0;
    work_out_partition = 0;
}

Male_Member::Male_Member(unsigned int data_in, std::string name, 
    unsigned int b, unsigned int s, unsigned int d, unsigned int wf, unsigned int wp) :
    Member(data_in, name), bench(b), squat(s), deadlift(d), work_out_frequency(wf), work_out_partition(wp) {
}


void Male_Member::save_file()
{
    std::string f = "db/";
    f.append(std::to_string(ID));
    f.append(".txt");
    std::ofstream memberData;
    memberData.open(f, std::ios::out | std::ios::trunc);
    memberData << password << " ";
    memberData << nickname << " ";
    
    
    memberData.close();

}

Female_Member::Female_Member(unsigned int data_in, std::string name) : Member(data_in, name){
    cardio = 0;
}

Female_Member::Female_Member(unsigned int data_in, std::string name, unsigned int c) :
    Member(data_in, name), cardio(c){
}

void Female_Member::save_file()
{
    std::cout << "woman save";
    
}


void show_menu();
void show_member_menu();
int find_member(std::string name);
void save_db();