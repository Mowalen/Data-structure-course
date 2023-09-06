#include<bits/stdc++.h>

using namespace std;

int N,M;
int main()
{
	freopen("input_10.txt","w",stdout);
	cin>>N>>M;
	cout<<M<<" "<<N<<endl;
	for(int i = 0 ; i < N ; i++)
	{
		cout<<rand()%100000<<" ";
	}
	cout<<endl;
	
	for(int i = 0 ; i < M ; i++)
	{
		int op = rand()%3;
		op++;
		cout<<op<<" "<<rand()%100000<<endl;
	}
}
