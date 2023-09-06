#include"catalogtree.h"
#include"catalogtree.cpp"
#include<bits/stdc++.h>

using namespace std;


int main()
{
    cout<<"请输入对应的指令"<<endl;
	cout<<"quit表示退出"<<endl;
	
	freopen("in7.txt", "r", stdin);
    //ifstream in1("in7.txt");
	freopen("ans7.txt", "w", stdout);

    string getop;
    catalogtree tree;
    while (getline(cin, getop)) {
        string op, num; 
        stringstream option(getop);
        option >> op >> num;
        if (op == "dir") {
            tree.dir();
        }
        if (op == "cd" && num == "") {
            tree.showpath(); 
        } else if (op == "cd" && num == ".." ) {
            tree.cdback();
        } else if (op == "cd" ) {
            tree.cd(num);
        }

        if (op == "mkdir") {
            tree.mkFile(num, true);
        }
        if (op == "mkfile") {
            tree.mkFile(num, false);
        }
        if (op == "delete") {
            tree.del(num);
        }
        if (op == "save") {

            char t[100];
            strcpy(t, num.c_str());
            tree.save(t);
            freopen("ans7.txt", "w", stdout);
        }
        if (op == "load") {
            char t[100];
            string temp;
            strcpy(t, num.c_str());
            tree = load(t,temp);
            tree.cd(temp);
        }
        if (op == "quit") {
            return 0;
        }
    }
    return 0;
}
