#ifndef HELP_H_INCLUDED
#define HELP_H_INCLUDED
#include <string>
using namespace std;
//HelpItem储存物品信息
class HelpItem
{
    private:
        string itemName;
        string ownerName;

    public:
        int leftNum;
        HelpItem(){};
        HelpItem(string item, string owner, int num);
        bool compareTwo(string item, string owner);//既比较物品又比较主人；
        bool compareOne(string item);//只比较物品；
        void show();
        void itemStore();//将一条信息写入file；
        void itemRead();//将file中的信息读入；
        HelpItem &operator=(const HelpItem &item);//"="运算符重载；
        ~HelpItem(){};
};

//将所有物品信息存为一个表
class HelpList
{
    private:
        HelpItem *infoList;
        int numofItem;

    public:
        HelpList();
        bool addItem(string item, string owner, int addNum);
        bool deleteItem(string item, string owner, int deleteNum);
        void presentList();
        void findItem(string item);
        void listRead();//将原文件中的信息读入；
        void listStore();//将一个表的信息全部写入file；
        ~HelpList();
};



#endif // HELP_H_INCLUDED
