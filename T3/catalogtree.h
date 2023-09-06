#pragma once

#include<bits/stdc++.h>

using namespace std;

struct file {
    string name;//文件名
    string path;//到此文件的路径
    bool dir;//是否是目录
    bool exist;//是否删除
    vector<file> child;//子节点
    long long filesize;
    file(string name, bool isDir) {
        this->name = name;
        this->dir = isDir;
        this->exist = true;
    }

    file() {//默认构造函数,根节点
        this->name = "ROOT";
        this->dir = true;
        this->exist = true;
    }
    file(string name,bool isdir,int size)
    {
        this->filesize = size;
        this->name = name;
        this->dir = false;
    }

    bool operator < (file &f1) const {
    
        if (dir == f1.dir)
            return name < f1.name;
        if (dir == false && f1.dir == true)
            return true;
        if (dir == true && f1.dir == false)
            return false;
    }
};

class catalogtree 
{
private:

//  string password = "123456";


public:
    file root;//根节点
    vector<file *> curPath;//当前路径



    catalogtree() {
        curPath.push_back(&root);
    }

    void dir();

    void showpath();

    void cdback();

    void cd(string p);

    void mkFile(string name, bool isdir);

    void del(string fileName);

    void save(char *a);

    //catalogtree load(char *a);

    vector<string> split(string p);

    void copyfile(bool flag , string copypath , string targetpath,string copyname);  //粘贴或者剪贴

    void checkdirsize(string filepath);

    void mkfile_size(string name,bool isdir , int size);

    void del_size(string filename);

//  void root_op(string root_grade , string filename);

    void rname(string filename,string newname);

    void search(string filename);
};
