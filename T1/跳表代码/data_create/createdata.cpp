#include<bits/stdc++.h>

using namespace std;

int N,M;
int main()
{
	freopen("input_11.txt","w",stdout);
	cin>>N>>M;
	cout<<N<<" "<<M<<endl;
	for(int i = 0 ; i < N ; i++)
	{
		cout<<rand()%100000<<" ";
	}
	cout<<endl;
	
	for(int i = 0 ; i < M ; i++)
	{
		int op = rand()%5;
		op++;
		if(op == 4 || op == 5)
		{
			cout<<op<<endl;
		} 
		else cout<<op<<" "<<rand()%100000<<endl;
	}
}
