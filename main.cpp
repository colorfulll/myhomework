#include <iostream>
#include "help.h"
using namespace std;

int main()
{
    cout  << "�����Ʒ������1��\nɾ����Ʒ������2��\n������Ʒ������3��\n��ʾ�б�������4��\n�����ļ�������5��" << endl ;
    HelpList myList;
    while(1)  //����һֱ��ѭ��������
    {
       int signal;
       int judge = 0;//�����ж�ѭ����ʱ����
       cin >> signal;
       switch (signal)
       {
            case 1:
            {
                string addName, addOwner;
                int num;
                cout << "������Ҫ��ӵĲ�Ʒ���֣�" ;
                cin >> addName;
                cout << "�������Ʒӵ���ߣ�";
                cin >> addOwner;
                cout << "��������Ҫ��ӵ�������";
                cin >> num ;
                if(myList.addItem(addName, addOwner, num)) cout << "��ӳɹ���"<<endl;
                else cout << "���ʧ�ܣ�"<<endl;
                break;
            }

            case 2:
                {
                    string delName, delOwner;
                    int delNum;
                    cout << "������ɾ���Ĳ�Ʒ���֣�" ;
                    cin >> delName;
                    cout << "�������Ʒӵ���ߣ�";
                    cin >> delOwner;
                    cout << "��������Ҫɾ����������";
                    cin >> delNum;
                    if (myList.deleteItem(delName, delOwner, delNum)) cout << "ɾ���ɹ���" << endl ;
                    else cout << "ɾ��ʧ��" << endl ;
                    myList.presentList();
                    break;
                }

            case 3:
                {
                    string findName;
                    cout << "������Ҫ���ҵĲ�Ʒ��";
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
    cout << "����ɹ���" ;
    return 0;
}
