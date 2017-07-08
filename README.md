# image_to_klg
This is the code for co-fusion and elastic-fusion, which can convert images to klg file. enjoy it! 

The main.cpp is an using example for tum rgbd datasets.


## how to combile  
mkdir build  
cd build  
cmake ..  
make  

## how to use for tum rgbd datasets  
There need two params which is assiostions.txt(in which directroy also include rgb and depth dirs) and savepath  
Example: ./toklg   .../yourTumDataAssociationFile.txt   .../youSaveFile.klg  
