#include "help.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

int itemCounter = 0;//��¼����itemFile��λ��
int ownerCounter = 0;//��¼����ownerFile��λ�ã�
int numCounter = 0;//��¼����numFile��λ��

ofstream outItem;
ofstream outOwner;
ofstream outNum;
ofstream outSummary;
ifstream inItem;
ifstream inOwner;
ifstream inNum;
ifstream inSummary;

//���ļ��ж��ַ���
string readFileIntoString(char * filename, int &counter)
{
ifstream ifile(filename);
//���ļ����뵽ostringstream����buf��
ostringstream buf;
char ch;
ifile.seekg(counter);
while(buf&&ifile.get(ch)&&(ch!=' '))
{
    buf.put(ch);
    counter++;
}
counter++;
//������������buf�������ַ���
return buf.str();
}

//��һ����Ʒ���г�ʼ��
HelpItem::HelpItem(string item, string owner, int num)
{
    itemName = item;
    ownerName = owner;
    leftNum = num;
}

//�Ƚ�����Ʒ�Ƿ���ͬ����Ʒ���Ƿ�����ͬһ���ˣ�
bool HelpItem::compareTwo(string item, string owner)
{
    if ((item.compare(this->itemName) || owner.compare(this->ownerName)) == 0) return true;
    else return false;
}

//�Ƚ�����Ʒ�Ƿ���ͬһ����Ʒ
bool HelpItem::compareOne(string item)
{
    if (item.compare(this->itemName) == 0) return true;
    else return false;
}

//��ʾһ����Ʒ����Ϣ
void HelpItem::show()
{
   cout << "itemname:" << this -> itemName << "     �����ˣ�"
    << this -> ownerName << "      ������" << this ->leftNum << endl ;
}

//"="���������
HelpItem &HelpItem::operator=(const HelpItem &item)
{
    itemName = item.itemName;
    ownerName = item.ownerName;
    leftNum = item.leftNum;
    return *this;
}

//��һ����Ʒ����Ϣ������ļ���
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



//��ʼ����Ʒ�б�
HelpList::HelpList()
{
    HelpItem *tmp = new HelpItem [100];
    infoList = tmp;
    listRead();
}

//������Ʒ, ����б���������false
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

//ɾ����Ʒ
bool HelpList::deleteItem(string item, string owner, int deleteNum)
{
    int track = -1;
    if (numofItem == 0) return false;
    else
    {
        //�ҵ�Ҫɾ����Ԫ�ص��±�
        for (int i=0; i<numofItem; ++i)
        {
            if (infoList[i].compareTwo(item, owner)) track=i;
        }
          if (track == -1) return false;

        //ɾ�������������ȫ��ɾ���Ͳ���ɾ����
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

//������Ʒ
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
    if (counter == 0) cout << "û�и���Ʒ" << endl ;
}

//��ʾ��Ʒ�б���
void HelpList::presentList()
{
    for (int i=0; i<numofItem; ++i) infoList[i].show();
}

HelpList::~HelpList()
{
    delete [] infoList;
}

//����ʼʱ�����ļ���ʼ���б�
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

//��һ��������Ϣ������ļ���
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


