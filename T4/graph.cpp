#include"graph.h"
#include<bits/stdc++.h>

using namespace std;

void graph::add(int x ,int y , int z)
{
    e[idx] = y;
	w[idx] = z;
	ne[idx] = h[x];
	h[x] = idx++;
    in1[y] ++;
}

void graph::tpsort()
{
	tpn = 0;
	queue<int> q;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(in1[i] == 0) q.push(i);
	}
	while(q.size())
	{
		auto t = q.front();
		q.pop();
		tp[++tpn] = t;
		for(int i = h[t] ; i != -1 ;i = ne[i])
		{
			int j = e[i];
			in1[j] --;
			if(in1[j] == 0) q.push(j);
		}
	}
}



bool graph::judge()
{
    flag = true;
	s[1] = true;
	vis[1] = true;
	memset(vis,false,sizeof vis);
	for(int i = 1 ;i <= n ; i++)
	{
		p[i] = l;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		int t = tp[i];
		if(p[t] < 0) 
		{
			//flag = false;
			return false;
		}
		if(s[t])
		{
			p[t] = l;
		}
		for(int j = h[t] ; j != -1 ; j = ne[j])
		{
			int u = e[j];
			if(!vis[u])
			{
				p[u] = p[t] - w[j] ; 
				vis[u] = true;
			}
		
			else p[u] = min(p[u],p[t] - w[j]);
			
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		if(p[i] < 0) return false;
	}
	return true;
}


bool graph::judge1(int tnum)
{
    flag = true;
	s[1] = true;
	vis[1] = true;
	memset(vis,false,sizeof vis);
	for(int i = 1 ;i <= n ; i++)
	{
		p[i] = l;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		int t = tp[i];
		if(p[t] < 0) 
		{
			//flag = false;
			if(i <= tnum ) flag = false; 
			return false;
		}
		if(s[t])
		{
			p[t] = l;
		}
		for(int j = h[t] ; j != -1 ; j = ne[j])
		{
			int u = e[j];
			if(!vis[u])
			{
				p[u] = p[t] - w[j] ; 
				vis[u] = true;
			}
		
			else p[u] = min(p[u],p[t] - w[j]);
			
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		int t = tp[i];
		if(p[t] < 0 )
		{
			if(t <= tnum) flag = false;
			return false;
		}
	}
	return true;
}
void graph::solve1(int ss, int num)
{
	
	if(ss > this->n + 1 || num > ansnum) return;
	else if(judge1(ss-1))
	{
		ansnum = min(ansnum,num);
		return;
	}
	else if(flag == false) 
	{
		return;
	}
	s[tp[ss]] = true;
	solve1(ss+1,num+1);
	s[tp[ss]] = false;
	solve1(ss+1,num);
}
void graph::solve2()
{
	int a[N];
	int tempnum;
	memset(s,false,sizeof s);
	memset(a,0,sizeof a);
	int h = n - 1;
	int temp = 1;
	while(h != 0)
	{
		temp = temp * 2;
		h--;
	}
	a[2] = -1;
	for(int i = 1 ; i <= temp ; i++)
	{
		tempnum = 0;
		a[2] ++;
		int j = 2;
		while(a[j] > 1)
		{
			a[j] = 0;
			a[j+1]++;
			j++;
		}
		memset(s,false,sizeof s);
		for(int z = 2 ; z <= n ; z++)
		{
			if(a[z] == 1) 
			{
				s[z] = true;
				tempnum++;	
			}
			else s[z] = false;
		}
		if(judge()) 
		{
			ansnum = min(tempnum,ansnum);
		}
	}
	m_use += n * 4;
}

