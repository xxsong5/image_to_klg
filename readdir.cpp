/*************************************************************************
	> File Name: readdir.cpp
	> Author: Xuxiansong
	> Mail: 2808595125@163.com 
	> Created Time: 2017年06月22日 星期四 16时21分35秒
 ************************************************************************/

#include <iostream>
#include "readdir.h"

using namespace std;

void taitsDir(std::string dir_path,std::vector<string>& vfull, isYES func)
{
    if(dir_path[dir_path.length()-1]!='/')dir_path+="/";

    DIR* dp;
    struct dirent *dir;

    if((dp=opendir(dir_path.c_str())) == NULL) {
        cerr<< "open dirent failed!\n";
        return;
    }

    while((dir=readdir(dp)) !=NULL){
        string name=dir->d_name;
        if(func(name))
          vfull.push_back(dir_path+name);
    }
}















