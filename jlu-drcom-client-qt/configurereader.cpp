#include "configurereader.h"


ConfigureReader::ConfigureReader(std::string fileName)
{
    this->fileName=fileName;
    std::ifstream fin(fileName);
    std::string str;
    while(fin.peek()!=EOF){
        std::getline(fin,str);
        if(str[0]=='#'||str.size()==0)continue;
        std::string key,value;
        bool flag=true;
        for(char c:str){
            if(flag){
                if(c=='='){
                    flag=false;
                    continue;
                }
                key.push_back(c);
            }else{
                value.push_back(c);
            }
        }
        cfg[key]=value;
    }
    fin.close();
}

std::map<std::string, std::string> ConfigureReader::getCfg()
{
    return cfg;
}

void ConfigureReader::setCfg(std::string key, std::string value)
{
    cfg[key]=value;
}

void ConfigureReader::fresh()
{
    std::ofstream fout(this->fileName);
    for(auto &it:cfg){
        fout<<it.first<<'='<<it.second<<std::endl;
    }
    fout.close();
}
