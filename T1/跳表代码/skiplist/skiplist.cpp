
#include"skiplist.h"

using namespace std;

extern long long count[10]; 

template<class K,class E>
skiplist<K,E>::skiplist(K largekey,int maxpairs,float p)
{
	cutoff = p * RAND_MAX;
	max_levels = (int)ceil(logf((float)maxpairs) / logf(1 / p)) - 1;   //计算跳表的层数 
	levels = 0;
	dsize = 0;
	tailkey = largekey;
	pair<K,E> tailpair(make_pair(tailkey,tailkey));
	headnode = new skipnode<K,E>(tailpair,max_levels+1);
	tailnode = new skipnode<K,E>(tailpair,0);
	last = new skipnode<K,E>* [max_levels+1];
	max_pairs = maxpairs;
	for(int i = 0 ; i <= max_levels; i++)
	{
		headnode->next[i] = tailnode;
	}
	memset(count,0,sizeof count);
}
template<class K,class E>
skiplist<K,E>::~skiplist()
{
	skipnode<K,E>* tempnode;
	while(headnode != tailnode)
	{
		tempnode = headnode->next[0];
		delete headnode;
		headnode = tempnode;
	}
	delete []last;
}
template<class K,class E>
bool skiplist<K,E>::find(const K& tempkey)   
{
	if(tempkey >= tailkey) return false;  //表示该值的节点不存在 
	skipnode<K,E>* tempnode = headnode;
	for(int i = levels ; i >= 0 ; i--)
	{
		while(tempnode->next[i]->element.first < tempkey )
		{
			tempnode = tempnode->next[i];
			count[0]++;
		}
	}
	if(tempnode->next[0]->element.first == tempkey ) return true;
	else return false;
}
template<class K,class E>
skipnode<K,E>* skiplist<K,E>::search(const K& tempkey)
{
	if(tempkey >= tailkey)  return NULL;
	
	skipnode<K,E>* tempnode = headnode;
	for(int i = levels ; i >= 0 ; i--)
	{
		while(tempnode->next[i]->element.first < tempkey )
		{
			tempnode = tempnode->next[i];
			count[5]++;
		}
		last[i] = tempnode;
	}
	if(tempnode->next[0]->element.first == tempkey ) return tempnode->next[0];
	else return NULL;
}
template<class K,class E>
void skiplist<K,E>::insert(const pair<const K, E>& thepair)
{
	count[5] = 0;
	skipnode<K,E>* temp = this->search(thepair.first);
	if(temp != NULL)
	{
		temp->element.second = thepair.second;
		return ;
	}
	int templevel = rand_level();
	if(templevel > levels)
	{
		levels = levels+1;
		templevel = levels;
		last[templevel] = headnode;
	}
	skipnode<K,E>* tskipnode = new skipnode<K,E>(thepair,templevel + 1);
	for(int i = 0 ;i <= templevel ; i++)
	{
		tskipnode->next[i] = last[i]->next[i];
		last[i]->next[i] = tskipnode;
	}
	dsize++;
	count[1] =count[1] + count[5];
	return;
}
template<class K,class E>
int skiplist<K,E>::rand_level()
{
	int x = 0;
	while(rand() <= cutoff)
	{
		x++;
	}
	return (x <= max_levels) ? x : max_levels;
}
template<class K,class E>
void skiplist<K,E>::erase(const K& tempkey)
{
	count[5] = 0;
	skipnode<K,E>* tempnode = this->search(tempkey);
	if(tempnode == NULL) return ;
	
	for(int j = 0 ;j <= levels && last[j]->next[j] == tempnode;j++)
	{
		last[j]->next[j] = tempnode -> next[j];
	}

	while(levels > 0 && headnode->next[levels] == tailnode)
	{
		levels --;
	}
	delete tempnode;
	dsize--;
	count[2] =count[2] + count[5];
	return ;
}
template<class K,class E>
void skiplist<K,E>::yihuo()
{
	int ans = 0;
	skipnode<K,E>* tempnode = headnode->next[0];
	
	if(tempnode == tailnode ) 
	{
		cout<<0<<endl;
		return ;
	}
	if(tempnode->next[0] == tailnode)
	{
		cout<<tempnode->element.first<<endl;
		return;
	}
	ans = (tempnode->element.first) ^ (tempnode->next[0]->element.first);
	tempnode=tempnode->next[0]->next[0];
	while(tempnode != tailnode)
	{
		ans = ans ^ tempnode->element.first;
		tempnode = tempnode->next[0];
	}
	cout<<ans<<endl;
	return;
}
template<class K,class E>
void skiplist<K,E>::erasemin()
{
	skipnode<K,E>* tempnode = headnode;
	if(tempnode->next[0] == tailnode) 
	{
		cout<<-1<<endl;
		count[2]++;
		return;
	}
	skipnode<K,E>* deletenode = headnode->next[0];
	cout<<deletenode->element.first<<endl;
	
	for(int i = 0 ; i <= levels&&headnode->next[i] == deletenode ; i++)
	{
		headnode->next[i] = deletenode->next[i];
	}

	delete deletenode;
	dsize--;
}
template<class K,class E>
void skiplist<K,E>::erasemax()
{
	skipnode<K,E>* tempnode = headnode;
	if(tempnode->next[0] == tailnode)
	{
		cout<<-1<<endl;
		count[2]++;
		return ;
	}
	for(int i = levels ; i >= 0 ; --i)
	{
		if(tempnode->next[i] == tailnode) continue;
		while( tempnode->next[i]->next[i] != tailnode )
		{
			tempnode = tempnode->next[i];
			count[2]++;
		 } 
		last[i] = tempnode;
	}
	skipnode<K,E>* maxnode = tempnode->next[0];
	cout<<maxnode->element.first<<endl;
	
	for(int i = 0 ;i <= levels && last[i]->next[i] == maxnode ; i++)
	{
		last[i]->next[i] = maxnode->next[i];
	}
	
	while(levels > 0 && headnode->next[levels] == tailnode)
	{
		--levels;
	}
	delete maxnode;
	dsize --;
	return;
}



template<class K,class E>
void skiplist<K,E>::resize()
{
	vector<K> num;
	int nums = 0;
	skipnode<K,E>* temp1 = headnode->next[0];
	skipnode<K,E>* temp2 = headnode->next[0];
	
	while(temp1 != tailnode)
	{
		temp2 = temp1;
		num.push_back(temp1->element.first);
		temp1 = temp1->next[0];
		delete temp2;
		nums ++;
	}
	delete []last;
	delete headnode;
	levels = 0;
	dsize = 0;
    pair<K,E> tailpair(make_pair(tailkey,tailkey));
    headnode = new skipnode<K,E>(tailpair,max_levels+1);
    last = new skipnode<K,E>* [max_levels+1];
    
	for(int i = 0 ; i <= max_levels ; i++)
	{
		headnode->next[i] = tailnode;
	}
	for(int i = 0 ; i <= max_levels ; i ++)
	{
		last[i] = headnode;
	}
	int ttlevel = (int)ceil(logf((float)(nums+1)) / logf(1 / 0.5)) - 1; 
	for(int i = 0 ; i < nums; i++)
	{
	
		int a = i + 1;
		int tlevel = 0;
		while(a % 2 == 0)
		{
			tlevel ++;
			a = a / 2;	
		} 
		pair<K,E> tempi(make_pair(num[i],num[i]));
		skipnode<K,E>* tskipnode = new skipnode<K,E>(tempi,tlevel + 1);
		if(tlevel > levels)
		{
			levels = levels+1;
			tlevel = levels;
			last[tlevel] = headnode;
		}
		count[5] = 0;
		this->search(num[i]);
		for(int i = 0 ; i <= tlevel ; i ++)
		{
			tskipnode->next[i] = last[i]->next[i];
			last[i]->next[i] = tskipnode;
		}
		dsize++;
	}
}
template<class K,class E>
void skiplist<K,E>::timeprint()
{
	cout<<"find操作比较次数："<<count[0]<<endl;
	cout<<"insert操作比较次数："<<count[1]<<endl;
	cout<<"erase操作比较次数："<<count[2]<<endl;
	cout<<"总比较次数: "<<count[0]+count[1]+count[2]<<endl; 
}
