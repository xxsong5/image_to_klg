/*************************************************************************
	> File Name: main.cpp
	> Author: Xuxiansong
	> Mail: 2808595125@163.com 
	> Created Time: 2017年07月06日 星期四 15时39分08秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "readdir.h"
using namespace std;


void convert2klg(const vector<string>& vcolors, const vector<string>& vdepths, string klgfile)
{
    FILE* log = fopen(klgfile.c_str(), "wb+");
    int32_t numFrames=vcolors.size();
    fwrite(&numFrames, sizeof(int32_t),1, log);

    double time=1000.0, step=(1.0/30);
    for(size_t i=0; i< vcolors.size(); ++i){
        time+=step;

        cv::Mat color=cv::imread(vcolors[i]);
        cv::Mat depth=cv::imread(vdepths[i],CV_LOAD_IMAGE_UNCHANGED);

        cv::flip(color, color, 0);
        cv::flip(color, color, 1);
        cv::flip(depth,depth,0);
        cv::flip(depth,depth,1);

        int64_t t64=(time*1000);
        int32_t coW=color.rows*color.step[0];
        int32_t deW=depth.rows*depth.step[0];

        //this is for tum rgbd datasets
        depth.convertTo(depth,CV_16UC1, 1/5.0);
        
        fwrite(&t64, sizeof(int64_t), 1, log);
        fwrite(&deW, sizeof(int32_t), 1, log);
        fwrite(&coW, sizeof(int32_t), 1, log);
        fwrite(depth.data, deW, 1, log);
        fwrite(color.data, coW, 1, log);

        cout<<i<<'/'<<vdepths.size()<<endl;
    }

    fflush(log);
    fclose(log);
}


void LoadImages(const string &strAssociationFilename, vector<string> &vstrImageFilenamesRGB,
                vector<string> &vstrImageFilenamesD, vector<double> &vTimestamps)
{
    string path=strAssociationFilename;
    int index=path.length()-1;
    for(;index >=0; --index)
        if(path[index]== '/')break;
    if(index<0)return;
    path.assign(path.begin(), path.begin()+index+1);


    ifstream fAssociation;
    fAssociation.open(strAssociationFilename.c_str());
    while(!fAssociation.eof())
    {
        string s;
        getline(fAssociation,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            double t;
            string sRGB, sD;
            ss >> t;
            vTimestamps.push_back(t);
            ss >> sRGB;
            vstrImageFilenamesRGB.push_back(path+sRGB);
            ss >> t;
            ss >> sD;
            vstrImageFilenamesD.push_back(path+sD);

        }
    }
}

int main(int argc ,char** argv)
{

    if(argc !=3 ){
        cerr<<" need assiostions.txt(in which directroy also include rgb and depth dirs) & savepath\n\n"<<
           "Example: ./toklg   .../your_tum_data_association_file.txt   .../your_save_file.klg\n";
        exit(0);
    }


    string path(argv[1]);
    if(path[path.length()-1] != '/')path+="/";

    vector<string> vcolor, vdepth;
    vector<double> vtime;

////////////////////////load_method_one/////////////////
//    taitsDir(path+"color/",vcolor, [](const string& name){
//                if(name.length()>3 && name[name.length()-3] == 'b')return true;
//                else return false;
//                });
//    taitsDir(path+"depth/",vdepth, [](const string& name){
//                if(name.length()>3 && name[name.length()-3] == 'p')return true;
//                else return false;
//                });
//    sort(vcolor.begin(), vcolor.end());
//    sort(vdepth.begin(), vdepth.end());
///////////////////////////////////////////////////////

/////////////////////tum_dataSets load method//////////
    LoadImages(argv[1], vcolor, vdepth,vtime);
//////////////////////////////////////////////////////
    if(vcolor.size()<=0)cerr<<"please check you inputs\n";

    convert2klg(vcolor, vdepth, argv[2]);

    return 0;
}





