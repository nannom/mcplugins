#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
int main() {
    ifstream input("test.ccn");
    ofstream output("out.cn");
    vector<pair<string,int>> codes;
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    string ntext = " /+-*/!@#$%^&(){}[]\\\n`~,.|;\t";
    set<string> vars = {"int","char"};
    for(int i = 0;i<file.length();i++) {
        if(ntext.find(file[i]) != string::npos) {
            if(file[i] != ' ' && file[i] != '\t') {
                string str;
                str+=file[i];
                codes.push_back({str,2});
            }
        }
        else {
            if(isdigit(file[i])) {
                string number = "";
                while(isdigit(file[i])) {
                    number += file[i];
                    i++;
                }
                i--;
                codes.push_back({number,1});
            }
            else if(file[i] == '\"') {
                i++;
                string text = "";
                while(file[i] != '\"') {
                    text += file[i];
                    i++;
                }
                codes.push_back({text,3});
            }
            else {
                string text = "";
                while(ntext.find(file[i]) == string::npos) {
                    text += file[i];
                    i++;
                }
                if(vars.find(text) != vars.end()) {
                    codes.push_back({text,6});
                }
                else {
                    codes.push_back({text,0});
                }
                i--;
            }
        }
    }
    for(int i = 0;i<codes.size();i++) {
        if(codes[i].second == 0) {
            if(codes[i+1].second == 2) {
                if(codes[i+1].first == "(") {
                    codes[i].second = 4;
                }
            }
        }
    }
    for(auto code : codes) {
        switch (code.second)
        {
        case 0:
            output << "v " << code.first << endl;
            break;
        case 1:
            output << "n " << code.first << endl;
            break;
        case 2:
            output << "o " << code.first << endl;
            break;
        case 3:
            output << "t " << code.first << endl;
            break;
        case 4:
            output << "f " << code.first << endl;
            break;
        case 6:
            output << "n " << code.first << endl;
            break;
        
        default:
            break;
        }
    }
    output.close();
    input.close();
}