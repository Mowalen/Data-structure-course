#pragma once

struct SequentialStringPlayer   //结构体用于生成顺串 
{
	int id,key;  
	bool operator <= (SequentialStringPlayer & temp)  //名次为第一优先级 
	{
		if(id != temp.id)
		{
			return id < temp.id;
		}
		else return key < temp.key;
	}
}; 





template<class T>
class losertree
{
	public:
		losertree(T* p , int num); //初始化 
		void init(T* p );
		int win(int x , int y);
		int lose(int x , int y);
		int getwinner()
		{
			return tree[0];
		}
		void replay(int p , T newvalue);  //重构 
		~losertree()
		{
			delete []tree;
			delete []player;
			delete []winner;	
		}		
	private:
		int* tree;   //树的节点，用于存放输者 
		T* player; //用于存放选手 
		int playnum;//选手数量 
		int* winner;  //树的边，用于存放赢者 
		

}; 





























