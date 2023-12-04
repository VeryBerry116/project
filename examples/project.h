#include "openai.hpp"

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
    unsigned int    hw_count;
    unsigned int    goal;

public:
    Member(unsigned int data_in, std::string name, std::string pw);
    ~Member();

    unsigned int getID();
    bool log_in(std::string pw);
    void show_member_info();
    void body_check(int h, int w);
    void show_body_chart();
};

class Male_Member : public Member {
public:
    Male_Member(unsigned int data_in, std::string name, std::string pw);
    Male_Member(unsigned int data_in, std::string name, std::string pw,
        unsigned int b, unsigned int s, unsigned int d, unsigned int wf);
    ~Male_Member(){
    }

    void make_work_out_plan();
    void save_file();

private:
    unsigned int    bench;
    unsigned int    squat;
    unsigned int    deadlift;
    unsigned int    work_out_frequency;
};

class Female_Member : public Member {
public:
    Female_Member(unsigned int data_int, std::string name, std::string pw);
    Female_Member(unsigned int data_in, std::string name, std::string pw, unsigned int c);
    ~Female_Member(){
    }

    void save_file();

private:
    unsigned int    cardio;
};

Member::Member(unsigned int data_in, std::string name, std::string pw) : 
    ID(data_in), nickname(name), password(pw) {  
    head = NULL;
    hw_count = 0;
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

unsigned int Member::getID()
{
    return ID;
}

bool Member::log_in(std::string pw)
{
    std::cout << password << " " << pw << std::endl;
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
    hw_count++;

    if(head == NULL)
        head = temp;
    else
    {
        node* tempt = head;
        while(tempt->next_node != NULL)
            tempt = tempt->next_node;
        tempt->next_node = temp;
    }
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

Male_Member::Male_Member(unsigned int data_in, std::string name, std::string pw) : Member(data_in, name, pw){
    bench = 0;
    squat = 0;
    deadlift = 0;
    work_out_frequency = 0;
}

Male_Member::Male_Member(unsigned int data_in, std::string name, std::string pw,
    unsigned int b, unsigned int s, unsigned int d, unsigned int wf) :
    Member(data_in, name, pw), bench(b), squat(s), deadlift(d), work_out_frequency(wf) {
}

void Male_Member::make_work_out_plan()
{
    if(bench != 0)
    {
        std::cout << std::endl;
        std::cout << "Last your work out plan information" << std::endl;
        std::cout << "Bench\tSquat\tDeadlift\tWF\n";
        std::cout << bench << "\t" << squat << "\t" << deadlift << "\t\t" << work_out_frequency;
        std::cout << std::endl << std::endl;
    }
    std::cout << "What do you bench? ";
    std::cin >> bench;
    std::cout << "What do you squat? ";
    std::cin >> squat;
    std::cout << "What do you deadlift? ";
    std::cin >> deadlift;
    std::cout << "How much exercise will you do (per week, 1 ~ 7)? ";
    std::cin >> work_out_frequency;

    std::string cmd = "I'm man. My bench 1RM weight is ";
    cmd.append(std::to_string(bench));
    cmd.append("kg. My squat 1RM weight is ");
    cmd.append(std::to_string(squat));
    cmd.append("kg. My deadlift 1RM weight is ");
    cmd.append(std::to_string(deadlift));
    cmd.append("kg. Make work out program for 7 days. I will go gym ");
    cmd.append(std::to_string(work_out_frequency));
    cmd.append(" times per week. Return work out program with weight, reps.");

    
}

void Male_Member::save_file()
{
    std::string f = "db/";
    f.append(std::to_string(ID));
    f.append(".txt");
    std::ofstream memberData;
    memberData.open(f, std::ios::out | std::ios::trunc);
    memberData << nickname << "\n";
    memberData << password << "\n";
    memberData << bench << "\n";
    memberData << squat << "\n";
    memberData << deadlift << "\n";
    memberData << work_out_frequency << "\n";
    memberData << hw_count << "\n";

    node* temp = head;
    while(temp != NULL)
    {
        memberData << temp->height << "\n";
        memberData << temp->weight << "\n";
        temp = temp->next_node;
    }

    memberData.close();

}

Female_Member::Female_Member(unsigned int data_in, std::string name, std::string pw) : Member(data_in, name, pw){
    cardio = 0;
}

Female_Member::Female_Member(unsigned int data_in, std::string name, std::string pw, unsigned int c) :
    Member(data_in, name, pw), cardio(c){
}

void Female_Member::save_file()
{
    std::string f = "db/";
    f.append(std::to_string(ID));
    f.append(".txt");
    std::ofstream memberData;
    memberData.open(f, std::ios::out | std::ios::trunc);
    memberData << nickname << "\n";
    memberData << password << "\n";
    memberData << cardio << "\n";
    memberData << hw_count << "\n";

    node* temp = head;
    while(temp != NULL)
    {
        memberData << temp->height << "\n";
        memberData << temp->weight << "\n";
        temp = temp->next_node;
    }

    memberData.close();
}


void show_menu();
void show_member_menu();
int find_member(std::string name);
void save_db();