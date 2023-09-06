#include"Losertree.h"
#include<bits/stdc++.h>

using namespace std;



template<class T>
int losertree<T>::win(int x ,int y)
{
	return player[x] <= player[y] ? x : y;
}

template<class T>
int losertree<T>::lose(int x,int y)
{
	return player[x] <= player[y] ? y : x;
}

template<class T>
losertree<T>::losertree(T* p ,int num)   //初始化 
{
	int n = 2 * num;
	playnum = num;
	tree = new int [n];
	winner = new int [n];
	player = new T [n];
	for(int i = 0; i < num ; i ++) player[i] = p[i];
	if(num % 2 == 0)  //存在偶数个选手
	{
		for(int i = 2 * num - 2 ; i >= num ; i-=2)
		{
			tree[i / 2]  = lose(i - num , i - num + 1);
			winner[i / 2] = win(i - num , i - num + 1);
		}	
		for(int i = num - 2 ; i >= 2 ; i = i - 2)
		{
			tree[i / 2] = lose(winner[i] , winner[i + 1]);
			winner[i / 2] = win(winner[ i ], winner [i + 1]);
		}
		tree[0] = winner[1];
	} 
	else
	{
		winner[num] = 0;
		for(int i = 2 * num - 2 ; i >= num ; i = i - 2)
		{
			tree[i  / 2] = lose(i - num , i - num - 1); 
			winner[i / 2] = win(i - num , i - num - 1);
		}
		for(int i = num - 1 ; i >= 2 ; i = i - 2)
		{
			tree[ i / 2 ] = lose(winner[i] , winner[i + 1]);
			winner[i / 2] = win(winner[i], winner[i + 1]) ;
		}
		tree[0] = winner[1];
	}
}

template<class T>
void losertree<T>::replay(int p,T newvalue)  //重构 
{
	player[p] = newvalue;
	winner[p + playnum] = p;
	for(int i = playnum + p ; i/2 >= 1 ; i = i / 2)  //向上依次比较 
	{
		int bel = tree[i / 2];
		tree[i / 2] = lose(bel,winner[i]);
		winner[i / 2] = win(bel,winner[i]);
	}
	tree[0] = winner[1];
}

 
int SequentialStringConstruction(int buffsize,string name,long long & visitnum)  //生成顺串 
{
	bool s[15];
	ofstream out[15];
	memset(s,false,sizeof s);
	int snum = 1;
	SequentialStringPlayer* buffer = new SequentialStringPlayer[buffsize + 10];  //取缓冲大小的元素 
	ifstream in1(name+".txt");
	int nums;  //表示数据数量 
	in1>>nums;

	for(int j = 0 ; j < buffsize && in1 >> buffer[j].key ; j++  )
	{
		buffer[j].id = 1;
		visitnum ++;
	}
	losertree<SequentialStringPlayer> temp(buffer,buffsize);  //建立输者树 
	int tempnum ;
	for(int i = 0 ; i < nums ;i ++)
	{
		if(in1 >> tempnum)  visitnum ++;
		else{
			tempnum = INT_MIN;
		}

		SequentialStringPlayer tempwinner = buffer[temp.getwinner()];
		if(tempwinner.id == INT_MAX || tempwinner.key == INT_MIN ) break;
		SequentialStringPlayer tempp;
		tempp.key = tempnum ; 
		if(tempnum == INT_MIN ) tempp.id = INT_MAX;
		else if(tempnum >= tempwinner.key)
		{
		    tempp.id = tempwinner.id;
		}
		else 
		{
			tempp.id = tempwinner.id + 1;
		}
		buffer[temp.getwinner()] = tempp;
		temp.replay(temp.getwinner(),tempp);
		string smallfile="myans0-"+to_string(tempwinner.id)+".txt";  //找到对应文件输出 
		snum = max(snum,tempwinner.id);
		if(s[tempwinner.id] == false)
		{
			out[tempwinner.id].open(smallfile,ios::app);
			s[tempwinner.id] = true;
		}
		out[tempwinner.id] <<tempwinner.key<<" "; 
		/*ofstream out(smallfile,ios::app);
		out<<tempwinner.key<<" ";
		out.close();*/
		visitnum++;
	}

	delete []buffer;
	return snum;
}


void GenerateTheFinalResult(int k,int snum,int buffsize,long long &visitnum ,int ** & input)  //归并 
{
	int floor = 0; // 表示第几次归并
	int index[15];
	
	while(snum > 1)  //文件数量大于1 
	{
		ifstream* fin = new ifstream[snum];
		string* filename = new string[snum];
		for(int i = 0 ;i < snum ; i ++)
		{
			filename[i]= "myans"+to_string(floor)+"-"+to_string(i+1)+".txt";
			fin[i].open(filename[i]);
		}
		for(int i = 0 ; i < snum ; i++)
		{
			int in = 0;
			for (; in < buffsize && fin[i] >> input[i][in]; in++) {
				visitnum ++;
			}
			if (in < buffsize) {
				for (; in < buffsize; in++) {
					input[i][in] = INT_MAX;  
				}
			}
			index[i] = 0;	
		}
		int tempi = 0;
		int tempk = 0;
		++floor;
		while(tempi < snum)  //tempi为此时归并的文件的开始编号 
		{
			int curmax,curmerge;
			curmax = min(tempi + k , snum);
			curmerge = curmax - tempi;//当前归并文件数量 
			int tempnums[20];
			for(int j = tempi ; j < curmax ; j ++)
			{
				tempnums[j - tempi] = input[j][index[j]];
				index[j]++;
				visitnum++;
			}
			losertree<int> temptree(tempnums,curmerge);
			string file1 = "myans"+to_string(floor) + "-" + to_string(tempk+1)+".txt";  //找到对应文件 
			ofstream out1(file1);
			
			if(curmerge == 1)
			{
				out1<<tempnums[0]<<" ";
				while (index[tempi] <buffsize && input[tempi][index[tempi]] != INT_MAX) {  
					out1 << input[tempi][index[tempi]++] << " ";
					visitnum++;
				}
				int nextnum ;
				while (fin[tempi] >> nextnum) { 
					out1 << nextnum << " ";
					visitnum++;
				}
			}
			else
			{
				while(1)
				{
					int tempx = temptree.getwinner();
					int tempy = tempnums[tempx];
					if(tempy == INT_MAX) break;
					out1<<tempy<<" ";
					visitnum++;
					int nextnum ;
					
					int tempz = tempx + tempi;
					if(index[tempz] < buffsize)
					{
						nextnum = input[tempz][index[tempz]++];
						
					}
					else
					{
					 	int i = 0;
						for( ; i < buffsize && fin[tempz] >> input[tempz][i] ; i++)
						{
							visitnum++;		
						}	
						if (i < buffsize) {
							for (; i < buffsize; i++) {
								input[tempz][i] = INT_MAX;
							}
						}
						index[tempz] = 0;
						nextnum = input[tempz][index[tempz]++];
					}	
					tempnums[tempx] = nextnum;
					temptree.replay(tempx,nextnum);
				}	
			}	
			tempi += curmerge;
			out1.close();
			tempk++;
		}
		for(int j = 0 ; j < snum ; j++)
		{
			fin[j].close();
		}
		delete []fin;
		delete []filename;
		int temp1,temp2;
		if(snum % k == 0) 
		{
			temp1 = 0;
		}
		else temp1 = 1;
		
		if(snum % k != 0)
		{
			snum = snum / k + temp1;
		}
		else
		{
			snum = snum / k;
		}
		
	}
	delete []input;
	 
}
