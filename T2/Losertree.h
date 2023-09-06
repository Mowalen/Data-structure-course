#pragma once

struct SequentialStringPlayer   //�ṹ����������˳�� 
{
	int id,key;  
	bool operator <= (SequentialStringPlayer & temp)  //����Ϊ��һ���ȼ� 
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
		losertree(T* p , int num); //��ʼ�� 
		void init(T* p );
		int win(int x , int y);
		int lose(int x , int y);
		int getwinner()
		{
			return tree[0];
		}
		void replay(int p , T newvalue);  //�ع� 
		~losertree()
		{
			delete []tree;
			delete []player;
			delete []winner;	
		}		
	private:
		int* tree;   //���Ľڵ㣬���ڴ������ 
		T* player; //���ڴ��ѡ�� 
		int playnum;//ѡ������ 
		int* winner;  //���ıߣ����ڴ��Ӯ�� 
		

}; 





























