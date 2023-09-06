#include"catalogtree.h"



vector<string> catalogtree::split(string p)
{
    stringstream pp(p);
    string ppp;
    vector<string> ans;
    while(getline(pp,ppp,'/'))
    {
        ans.push_back(ppp);
    }
    return ans;
}


void catalogtree::dir()
{
    vector<file> temp = curPath.back()->child;//复制一份
    sort(temp.begin(), temp.end());//进行排序,文件在前
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i].exist) {
           cout<<temp[i].name;
           if(temp[i].dir == false)
           {
           	cout<<"*";		   
		    }
       		 cout<<endl;
		}
	}
}

void catalogtree::showpath()
{
    if(curPath.size() == 1) cout<<"/"<<endl;
    else{
        for(int i = 1 ; i < curPath.size() ; i ++)
        {
            cout<< "/" << curPath[i]->name;
        }
    	cout<<endl;
	}
    
}

void catalogtree::cdback()
{
    if(curPath.size() == 1) return ;
    this->curPath.pop_back();
}

void catalogtree::cd(string p)
{
    if(p[0] == '/')
    {
        vector<string> tempfile = this->split(p);
        vector<file *> ans;
        ans.push_back(&this->root);
        for(int i = 1 ; i < tempfile.size(); i ++)
        {
            bool flag = false;
            for(int j = 0 ; j < ans.back()->child.size() ; j ++)
            {
                if(tempfile[i] == ans.back()->child[j].name && ans.back()->child[j].dir == true &&ans.back()->child[j].exist == true)
                {
                    ans.push_back(&ans.back()->child[j]);
                    flag = true;
                    break;
                }
            }
            if(flag == false) return;   
        }
        curPath.assign(ans.begin(),ans.end());
    }
    else
    {
        for(int i = 0 ; i < curPath.back()->child.size() ; i ++)
        {
            if(p == curPath.back()->child[i].name && curPath.back()->child[i].dir == true && curPath.back()->child[i].exist == true)
            {
                 curPath.push_back(&curPath.back()->child[i]);
                 break;
            }
        }
    }
}

void catalogtree::mkFile(string p, bool isdir)
{
    file temp(p,isdir);
    for(auto &it : this->curPath.back()->child)
    {
        if(it.name == p)
        {
            if(it.exist == false)
            {
                it.exist = true;
            }
        	return;
		}
        
    }
    string pathOfTemp;
    if (curPath.size() == 1) {
        pathOfTemp = '/';
    } else {
        for (int i = 1; i < this->curPath.size(); i++) {
            pathOfTemp += "/" + curPath[i]->name;
        }
    }
    temp.path = pathOfTemp;
    curPath.back()->child.push_back(temp);
}

void catalogtree::save(char* a)
{
    freopen(a, "w", stdout);
    this->showpath();
    queue<file *> q;
    q.push(&root);
    while (q.empty() == false) {
        file *cur = q.front();
        q.pop();
        if (cur->child.empty()) {
            continue;
        }
        int realNumOfChildren = cur->child.size();
        for (auto &it: cur->child) {
            if (it.exist == false) {
                realNumOfChildren--;
            }
        }

        cout << cur->path << "\t" << cur->name << "\t" << realNumOfChildren << "\t";
        for (auto &it: cur->child) {
            if (it.exist == true) {
                cout << it.name << "\t" << it.dir << "\t";
                q.push(&it);
            }
        }
        cout << endl;
    }
    fclose(stdout);
    
}
/*
catalogtree catalogtree::load(char * a)
{
    ifstream loadFile(a);
    string s, savePath;
    loadFile >> savePath;
    catalogtree ans;
    loadFile >> ans.root.name;
    ans.root.dir = true;
    int numOfChildren;
    loadFile >> numOfChildren;
    for (int i = 0; i < numOfChildren; i++) {
        loadFile >> s;//读入孩子节点的名字
        bool isdir;
        loadFile >> isdir;
        ans.mkFile(s, isdir);
    }

    while (loadFile >> s) {//读入路径
        ans.cd(s);//进入路径
        loadFile >> s;//读入节点名字
        ans.cd(s);//前面已经创建过这个节点了，此时直接进入节点
        loadFile >> numOfChildren;
        for (int j = 0; j < numOfChildren; j++) {//开始建文件
            loadFile >> s;
            bool isdir;
            loadFile >> isdir;
            ans.mkFile(s, isdir);
        }

    }
    ans.cd(savePath);
    loadFile.close();
    return ans;
}
*/
void catalogtree::del(string p)
{
    for (auto it = curPath.back()->child.begin(); it != curPath.back()->child.end(); it++) {//遍历,查看是否已经存在
        if (it->name == p) {//有这个文件
            it->exist = false;//标记删除
            return;
        }
    }
}


catalogtree load(char * t,string & aaa)
{
	ifstream loadFile;
	//freopen(t,"r",stdin);
	loadFile.open(t, ios::in);
    string s, savePath;
    loadFile >> savePath;
    aaa = savePath;
    catalogtree ans;
    loadFile  >> ans.root.name;
    ans.root.dir = true;
    int numOfChildren;
    loadFile >> numOfChildren;
    for (int i = 0; i < numOfChildren; i++) {
        loadFile >> s;//读入孩子节点的名字
        bool isdir;
        loadFile >> isdir;
        ans.mkFile(s, isdir);
    }

    while (loadFile >> s) {
        ans.cd(s);
        loadFile>> s;
        ans.cd(s);
        loadFile >> numOfChildren;
        for (int j = 0; j < numOfChildren; j++) {//开始建文件
            loadFile >> s;
            bool isdir;
            loadFile >> isdir;
            ans.mkFile(s, isdir);
        }

    }
    ans.cd(savePath);
    //fclose(stdin);
	//cin.clear();
    return ans;
}


void catalogtree::copyfile(bool flag , string copypath , string targetpath,string copyname)
{
    this->cd(copypath);
    file target;
    for(auto i : this->curPath.back()->child)
    {
        if(i.name == copyname )
        {
            target.name = i.name;
            target.dir = i.dir;
            target.child = i.child;
            target.exist = true;
            if(flag == false)   //表示剪贴
            {
                this->del(copyname);
            }
            break;
        }
    }
    this->cd(targetpath);
    for(auto it : curPath.back()->child)
    {
        if(it.name == target.name)
        {
            cout<<"此文件已经存在"<<endl;
            return ;
        }
    }
    this->curPath.back()->child.push_back(target);
}

void catalogtree::checkdirsize(string filepath)
{
    long long ans = 0;
    this->cd(filepath);
    ans = curPath.back()->filesize;
    cout<<ans<<endl;
}


void catalogtree::mkfile_size(string name,bool isdir,int size)
{
    file temp(name,false,size);
    for(auto &it : this->curPath.back()->child)
    {
        if(it.name == name)
        {
            if(it.exist == false)
            {
                it.exist = true;
            }
        	return;
		}
        
    }
    string pathOfTemp;
    if (curPath.size() == 1) {
        pathOfTemp = '/';
    } else {
        for (int i = 1; i < this->curPath.size(); i++) {
            pathOfTemp += "/" + curPath[i]->name;
        }
    }
    temp.path = pathOfTemp;
    curPath.back()->child.push_back(temp);
    for(auto& it : curPath)
    {
        it->filesize += size;
    }
}


void catalogtree::del_size(string filename)
{
    int size = 0;
    for (auto it = curPath.back()->child.begin(); it != curPath.back()->child.end(); it++) {//遍历,查看是否已经存在
        if (it->name == filename) {//有这个文件
            size = it->filesize;
            it->exist = false;//标记删除
            break;
        }
    }
    for(auto& it : curPath)
    {
        it->filesize -= size;
    }
}


void catalogtree::rname(string filename,string newname)
{
     for (auto it = curPath.back()->child.begin(); it != curPath.back()->child.end(); it++) {//遍历,查看是否已经存在
        if (it->name == filename) {//有这个文件
            it->name = newname;
            if(it->dir == false) return ;
            else if(it->child.size() == 0) continue;
			else 
            {
                for(auto i : it->child)
                {
                    string str = i.path;
                    int p = str.find(filename);
                    string ans;
                    ans += str.substr(0,p);
                    ans += str.substr(p+filename.length(),string::npos);
                    i.path = ans;
                }
            }
        }
    }
}


void catalogtree::search(string filename)
{
    queue<file *> q;
    q.push(&root);
    while (q.empty() == false) {
        file *cur = q.front();
        q.pop();
        if (cur->child.empty()) {
            continue;
        }
        for (auto &it: cur->child) {
            if (it.exist == true && it.name == filename) {
                cout<<"found it"<<endl;
                return;
            }
            else if(it.exist == true && it.dir == true)
            {
                q.push(&it);
            }
        }
    }
    cout<<"not exist"<<endl;
}
