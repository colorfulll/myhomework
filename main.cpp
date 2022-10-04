#include <iostream>
#include "help.h"
using namespace std;

int main()
{
    cout  << "添加物品请输入1；\n删除物品请输入2；\n查找物品请输入3；\n显示列表请输入4；\n保存文件请输入5；" << endl ;
    HelpList myList;
    while(1)  //程序一直在循环中运行
    {
       int signal;
       int judge = 0;//用于判断循环何时结束
       cin >> signal;
       switch (signal)
       {
            case 1:
            {
                string addName, addOwner;
                int num;
                cout << "请输入要添加的产品名字：" ;
                cin >> addName;
                cout << "请输入产品拥有者：";
                cin >> addOwner;
                cout << "请输入想要添加的数量：";
                cin >> num ;
                if(myList.addItem(addName, addOwner, num)) cout << "添加成功！"<<endl;
                else cout << "添加失败！"<<endl;
                break;
            }

            case 2:
                {
                    string delName, delOwner;
                    int delNum;
                    cout << "请输入删除的产品名字：" ;
                    cin >> delName;
                    cout << "请输入产品拥有者：";
                    cin >> delOwner;
                    cout << "请输入想要删除的数量：";
                    cin >> delNum;
                    if (myList.deleteItem(delName, delOwner, delNum)) cout << "删除成功！" << endl ;
                    else cout << "删除失败" << endl ;
                    myList.presentList();
                    break;
                }

            case 3:
                {
                    string findName;
                    cout << "请输入要查找的产品；";
                    cin >> findName;
                    myList.findItem(findName);
                    cout << endl ;
                    break;
                }

            case 4:
                {
                    myList.presentList();
                    break;
                }
            case 5:
                {
                    judge = 1;
                    break;
                }
        }
    if (judge == 1) break;
    }
    myList.listStore();
    cout << "保存成功！" ;
    return 0;
}
