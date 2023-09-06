#include"catalogtree.h"
#include"catalogtree.cpp"
#include<bits/stdc++.h>

using namespace std;

int main()
{
	catalogtree temp;
	temp.mkFile("dir",true);
	
	temp.mkFile("file",false);
	temp.mkFile("dir2",true);
	temp.cd("/dir");
	temp.mkFile("file1",false);
	temp.copyfile(false,"/","/dir2","dir");
	temp.cdback();
	temp.dir();
	printf("\n");
	temp.cd("/dir2");
	temp.dir();
//temp.cd("/3");
}
