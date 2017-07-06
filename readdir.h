/*************************************************************************
	> File Name: readdir.h
	> Author: Xuxiansong
	> Mail: 2808595125@163.com 
	> Created Time: 2017年06月22日 星期四 16时20分50秒
 ************************************************************************/

#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>

typedef bool(*isYES)(const std::string& );

void taitsDir(std::string dir_path, std::vector<std::string>& vfull, isYES func= [](const std::string&)->bool{return 1;});





