#include "help.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

int itemCounter = 0;//记录读到itemFile的位置
int ownerCounter = 0;//记录读到ownerFile的位置；
int numCounter = 0;//记录读到numFile的位置

ofstream outItem;
ofstream outOwner;
ofstream outNum;
ofstream outSummary;
ifstream inItem;
ifstream inOwner;
ifstream inNum;
ifstream inSummary;

//从文件中读字符串
string readFileIntoString(const char * filename, int &counter)
{
ifstream ifile(filename);
//将文件读入到ostringstream对象buf中
ostringstream buf;
char ch;
ifile.seekg(counter);
while(buf&&ifile.get(ch)&&(ch!=' '))
{
    buf.put(ch);
    counter++;
}
counter++;
//返回与流对象buf关联的字符串
return buf.str();
}

//对一种物品进行初始化
HelpItem::HelpItem(string item, string owner, int num)
{
    itemName = item;
    ownerName = owner;
    leftNum = num;
}

//比较两物品是否是同种物品且是否属于同一个人；
bool HelpItem::compareTwo(string item, string owner)
{
    if ((item.compare(this->itemName) || owner.compare(this->ownerName)) == 0) return true;
    else return false;
}

//比较两物品是否是同一种物品
bool HelpItem::compareOne(string item)
{
    if (item.compare(this->itemName) == 0) return true;
    else return false;
}

//显示一种物品的信息
void HelpItem::show()
{
   cout << "itemname:" << this -> itemName << "     所有人："
    << this -> ownerName << "      数量：" << this ->leftNum << endl ;
}

//"="运算符重载
HelpItem &HelpItem::operator=(const HelpItem &item)
{
    itemName = item.itemName;
    ownerName = item.ownerName;
    leftNum = item.leftNum;
    return *this;
}

//将一件物品的信息储存进文件中
void HelpItem::itemStore()
{
    outItem<< this->itemName << " " ;
    outOwner<< this->ownerName << " " ;
    outNum<< this->leftNum << " " ;
}

void HelpItem::itemRead()
{
    char ch;
    this->itemName = readFileIntoString("itemFile", itemCounter);
    this->ownerName = readFileIntoString("ownerFile", ownerCounter);
    inNum.open("numFile");
    inNum.seekg(numCounter);
    inNum.get(ch);
    this->leftNum = ch-'0';
    numCounter+=2;
}



//初始化物品列表
HelpList::HelpList()
{
    HelpItem *tmp = new HelpItem [100];
    infoList = tmp;
    listRead();
}

//添加物品, 如果列表已满返回false
bool HelpList::addItem(string item, string owner, int addNum)
{
    if (numofItem == 100) return false;
    else
    {
        HelpItem *tmp = new HelpItem(item, owner, addNum);
        infoList[numofItem]= *tmp;
        numofItem++;
        return true;
    }
}

//删除物品
bool HelpList::deleteItem(string item, string owner, int deleteNum)
{
    int track = -1;
    if (numofItem == 0) return false;
    else
    {
        //找到要删除的元素的下标
        for (int i=0; i<numofItem; ++i)
        {
            if (infoList[i].compareTwo(item, owner)) track=i;
        }
          if (track == -1) return false;

        //删除有两种情况，全部删除和部分删除；
        if (deleteNum == infoList[track].leftNum)
        {
            --numofItem;
            for (int i=track; i<numofItem; ++i) infoList[i] = infoList[i+1];
        }
        else
        {
            infoList[track].leftNum -= deleteNum;
        }
    return true;
    }
}

//查找物品
void HelpList::findItem(string item)
{
    int counter = 0;
    for (int i=0; i<numofItem; ++i)
    {
        if (infoList[i].compareOne(item))
        {
            infoList[i].show();
            counter++;
        }
    }
    if (counter == 0) cout << "没有该物品" << endl ;
}

//显示物品列表；
void HelpList::presentList()
{
    for (int i=0; i<numofItem; ++i) infoList[i].show();
}

HelpList::~HelpList()
{
    delete [] infoList;
}

//程序开始时根据文件初始化列表
void HelpList::listRead()
{
    char ch;
    inSummary.open("summary");
    ch = inSummary.get();
    this->numofItem = ch-'0';
    for (int i=0; i<this->numofItem; ++i)
    {
        this->infoList[i].itemRead();
    }
    inSummary.close();

}

//将一个表的信息储存进文件中
void HelpList::listStore()
{
    outItem.open("itemFile");
    outOwner.open("ownerFile");
    outNum.open("numFile");
    for (int i=0; i<this->numofItem; ++i)
    {
        this->infoList[i].itemStore();
    }
    outSummary.open("summary");
    outSummary << numofItem;
    outItem.close();
    outOwner.close();
    outNum.close();
    outSummary.close();
}



