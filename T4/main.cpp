#include<bits/stdc++.h>
#include"graph.h"
#include"graph.cpp"
#include<time.h>
#include<windows.h> 


using namespace std;


int n , m , l;


int main()
{
	clock_t start,end;
	ofstream fout("output1.txt");
	//fout<<"2.time" <<" "<<"2.space"<<endl; 
	for(int z = 1 ; z <= 100 ; z++)
	{
		LARGE_INTEGER nFreq;
		LARGE_INTEGER t1;
		LARGE_INTEGER t2;
		
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&t1);
		
		start = clock();
		ifstream fin("input"+to_string(z)+".in");
		fin >> n >> m >> l;
		graph temp(n,m,l,1);
		for(int i = 0 ; i < m ; i ++)
		{
			int a , b , c;
			fin >> a >> b >> c;
			temp.add(a,b,c);
		}
		temp.ansnum = 1000;
		temp.tpsort();
		//temp.solve2();
		temp.solve1(2,0);
		fout<<temp.ansnum<<endl;
		fin.close();
		//fout.close();
		QueryPerformanceCounter(&t2);
		double cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;	
		//temp.getsize();
		//fout<<"样例"<<" "<<z<<" "<<cost*1000000<<" us"<<" "; 
		//fout<<"占用空间"<<" "<<temp.m_use<<" bytes\n";
	}
}
