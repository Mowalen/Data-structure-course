#include<bits/stdc++.h>
#include"losertree.h"
#include"losertree.cpp"
using namespace std;

long long visitnum = 0;
long long n;
long long m;
long long k;


int main()
{
	clock_t start_time = clock();
	string name="data2";
	cout<<"请输入数据数量"<<endl;
	cin>>n;
	cout<<"请输入缓冲区大小："<<endl;
	cin>>m;
	cout<<"请输入归并路数"<<endl;
	cin>>k;
	int x = SequentialStringConstruction(m,name,visitnum);
	int ** input = new int * [x];
	for (int i = 0; i < x; i++) {
		input[i] = new int [ m ];
	}
	GenerateTheFinalResult(k,x,m,visitnum,input);
	clock_t end_time = clock();
	delete []input;
	/*string name1 = "answer.txt";
	ofstream out1(name1,ios::app);
	out1<<name<<endl;
	out1<<"缓冲区大小: "<<m<<endl;
	out1<<"归并路数: "<<k<<endl; 
	out1<<"磁盘访问次数为："<<visitnum<<endl;
	out1<<"程序运行时间为: "<<static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" <<endl; 
	out1.close();*/
	return 0;
}
