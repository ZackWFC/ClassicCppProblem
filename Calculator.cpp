#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
void getData(string aa,vector<string>&b){
    int len=aa.size();
    string a=aa;
    int pos=0;
    bool hasNum=false;
    for(int i=0;i<len;i++){
        if((aa[i]=='+')||(aa[i]=='-')||(aa[i]=='*')||(aa[i]=='/')){
            if(hasNum){
                string temp;
                temp=a.substr(0,pos);
                b.push_back(temp);
                a.erase(0,pos);
                hasNum=false;
                pos=0;
            }
            string temp;
            temp=a.substr(0,1);
            b.push_back(temp);
            a.erase(0,1);
        }
        if(i==len-1){
            b.push_back(a);
        }
        if(aa[i]>='0'&&aa[i]<='9'){
            hasNum=true;
            pos++;
            continue;
        }
    }
}
bool isSig(string a){
    if((a=="+")||(a=="-")||(a=="*")||(a=="/")){
        return true;
    }
    return false;
}

string Cal(string& a) {
    string T1 = "*";
    string T2 = "/";
    string T3 = "+";
    string T4 = "-";
    int posMinus = 0;
    vector<string> Data;
    getData(a, Data);
    int len = Data.size();
    for (int i = 0; i < len; i++) {
        if ((i == 0 && Data[i] == "-") || (Data[i] == "-") && isSig(Data[i - 1]) && !isSig(Data[i + 1])) {
            int tempI = stoi(Data[i + 1]);
            tempI = -tempI;
            Data[i + 1] = to_string(tempI);
            vector<string>::iterator it = Data.begin();
            it = it + i;
            Data.erase(it);
        }
    }
    while (Data.size() != 1) {
        vector<string>::iterator it1 = Data.begin();
        string S1 = "*";
        it1 = find(Data.begin(), Data.end(), S1);
        while (it1 != Data.end()) {
            vector<string>::iterator itA1 = it1 - 1;
            vector<string>::iterator itB1 = it1 + 1;
            *itA1 = to_string(stoi(*itA1) * stoi(*itB1));
            Data.erase(it1, itB1 + 1);
            it1 = find(Data.begin(), Data.end(), S1);
        }


        vector<string>::iterator it2 = Data.begin();
        string S2 = "/";
        it2 = find(Data.begin(), Data.end(), S2);
        while (it2 != Data.end()) {
            vector<string>::iterator itA2 = it2 - 1;
            vector<string>::iterator itB2 = it2 + 1;
            *itA2 = to_string(stoi(*itA2) / stoi(*itB2));
            Data.erase(it2, itB2 + 1);
            it2 = find(Data.begin(), Data.end(), S2);
        }
        vector<string>::iterator it4 = Data.begin();
        string S4 = "-";
        it4 = find(Data.begin(), Data.end(), S4);
        while (it4 != Data.end()) {
            vector<string>::iterator itA4 = it4 - 1;
            vector<string>::iterator itB4 = it4 + 1;
            *itA4 = to_string(stoi(*itA4) - stoi(*itB4));
            Data.erase(it4, itB4 + 1);
            it4 = find(Data.begin(), Data.end(), S4);
        }

        vector<string>::iterator it3 = Data.begin();
        string S3 = "+";
        it3 = find(Data.begin(), Data.end(), S3);
        while (it3 != Data.end()) {
            vector<string>::iterator itA3 = it3 - 1;
            vector<string>::iterator itB3 = it3 + 1;
            *itA3 = to_string(stoi(*itA3) + stoi(*itB3));
            Data.erase(it3, itB3 + 1);
            it3 = find(Data.begin(), Data.end(), S3);
        }



    }
    return Data[0];

    }
bool findAllSig(char L,char R,string &T,int& posL,int& posR){
    int len =T.size();
    bool hasSigL=false;
    int pos=0;
    for(int i=0;i<len;i++){
        if(T[i]==L){
            posL=i;
        }
        if(T[i]==R){
            posR=i;
            return true;
        }
    }
    return false;
}
void dealSmall(string& a){
    char TL='(';
    char TR=')';
    int posL=0;
    int posR=0;
    while(findAllSig(TL,TR,a,posL,posR)){
        string small=a.substr(posL+1,posR-posL-1);
        string smallCal=Cal(small);
        a.replace(posL,posR-posL+1,smallCal);
    }
}

void dealMid(string& a){
    char TL='[';
    char TR=']';
    int posL=0;
    int posR=0;

    while(findAllSig(TL,TR,a,posL,posR)){
        string small=a.substr(posL+1,posR-posL-1);
        string smallCal=Cal(small);
        a.replace(posL,posR-posL+1,smallCal);
    }
}

void dealLarge(string& a){
    char TL='{';
    char TR='}';
    int posL=0;
    int posR=0;
    while(findAllSig(TL,TR,a,posL,posR)){
        string small=a.substr(posL+1,posR-posL-1);
        string smallCal=Cal(small);
        a.replace(posL,posR-posL+1,smallCal);
    }
}

int main() {
    string input;
    getline(cin,input);
    dealSmall(input);
    dealMid(input);
    dealLarge(input);
    string final=Cal(input);
    cout<<final<<endl;
    return 0;
}
