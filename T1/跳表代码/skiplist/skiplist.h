#ifndef SKIPH
#define SKIPH
#include<bits/stdc++.h>

using namespace std;

extern long long count[10]; 

template<class K,class E>
struct skipnode
{
	typedef pair<K,E> pairtype;
	pairtype element;
	skipnode<K,E>** next;
	skipnode(const pairtype& thepair,int size)
	{
		element = thepair;
		next = new skipnode<K,E>* [size];
	}
	~skipnode()
	{
		delete []next;
	}
};

template<class K,class E>
class skiplist
{
	public:
		skiplist(K largekey = 100000,int maxpairs = 100000,float p = 0.5);
		~skiplist();
		bool find(const K& tempkey);    //count[0]
		skipnode<K,E>* search(const K& tempkey);   
		void insert(const pair<const K, E>& thepair);     //count[1]
		int rand_level(); 
		void erase(const K& tempkey);  //count[2]
		void yihuo();  
		void erasemin();   
		void erasemax();   
		void resize();    //count[3]
		void timeprint(); 
		
		
		
	private:
		float cutoff;
		skipnode<K,E>* headnode;
		skipnode<K,E>* tailnode;
		skipnode<K,E>** last;
		int levels;
		int max_levels;
		int dsize;
		K tailkey;
		int max_pairs;
        long long count[10];   
};


#endif
