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
	cout<<"��������������"<<endl;
	cin>>n;
	cout<<"�����뻺������С��"<<endl;
	cin>>m;
	cout<<"������鲢·��"<<endl;
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
	out1<<"��������С: "<<m<<endl;
	out1<<"�鲢·��: "<<k<<endl; 
	out1<<"���̷��ʴ���Ϊ��"<<visitnum<<endl;
	out1<<"��������ʱ��Ϊ: "<<static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" <<endl; 
	out1.close();*/
	return 0;
}
