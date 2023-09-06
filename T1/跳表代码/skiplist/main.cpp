#include<bits/stdc++.h>
#include"skiplist.h"
#include"skiplist.cpp"

using namespace std;

int M,N;

int main()
{
	freopen("input_11.txt","r",stdin);
	freopen("output.txt","w",stdout);
	skiplist<int,int> s;
	cin>>M>>N;
	for(int i = 0 ; i < N ; i++)
	{
		int x;
		cin>>x;
		pair<int,int> temp(make_pair(x,x));
		s.insert(temp);
	}
	for(int i = 0 ; i < M ; i++)
	{
   	//	if(i%500 == 0 && i != 0)  s.resize();
		int x ;
		cin>>x;
		if(x == 1)
		{
			int num;
			cin>>num;
			if(s.find(num) ) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;

		}
		else if(x == 2)
		{
			int num;
			cin>>num;
			pair<int,int> temp(make_pair(num,num));
			s.insert(temp);
			s.yihuo();
		}
		else if(x == 3)
		{
			int num;
			cin>>num;
			s.erase(num);
			s.yihuo();
		}
		else if(x == 4)
		{
			s.erasemin();
		}
		else if(x == 5)
		{
			s.erasemax();
		}
	}
	s.timeprint();
}
