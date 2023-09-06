#pragma once
#include<bits/stdc++.h>

using namespace std;

const int N = 5010;


class graph
{
    public:
    int h[N],w[N],e[N],ne[N];
    int idx = 0;
    int tp[N];
    int in1[N];
    int p[N];
    bool s[N];
    int tpn = 0;
    int ansnum ;
    int n , m , l;
    bool vis[N];
    bool flag = true;
    int tnum;
    bool judge1 (int tnum);
    long long m_use;
    graph(int n , int m , int l,int type)
    {
        this->n  = n;
        this->m  = m;
        this->l  = l;
        memset(h,-1,sizeof h);
		memset(in1,0,sizeof in1);
		memset(s,false,sizeof s);
		memset(tp,0,sizeof tp);
        idx = 0;
        m_use = 0;
        if(type == 1)
        {
        	m_use += n * 6;
        	m_use += m * 3;
        	m_use = m_use * 4;
		}
		else if(type == 2)
		{
			m_use += n * 4;
			m_use += m * 3;
			m_use = m_use * 4;
		}
        

    }
    void add(int x , int y ,int z);
    void tpsort();
    bool judge();
    void solve1(int ss,int num);
    void solve2();
};
