#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <set>
using namespace std;
map<int,unsigned char> memory;
int last_memory = 0;
vector<pair<string,int>> codes;
bool isAllDigits(const std::string& str) {
    // 문자열의 모든 문자가 숫자인지 확인
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c);  // 문자가 숫자인지 확인
    });
}
bool checkFirstAndLastChar(const std::string& str,char a) {
    // 문자열의 길이가 2 이상이어야 첫 글자와 마지막 글자를 비교할 수 있음
    if (str.size() >= 2) {
        return str.front() == a && str.back() == a;
    }
    return false;
}
std::string unsignedCharToHex(unsigned char value) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << std::hex << (int)value;
    return ss.str();
}
std::string toHexString(int value) {
    std::stringstream ss;
    ss << std::hex << value;  // 16진수로 변환
    return ss.str();
}
/*
type
0 text
1 int
2 
3 char
4 function
5 addr
6
*/
int main() {
    ifstream input("main.ccn");
    ofstream output("out.cn");
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    cout << file << endl;
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
                int num = atoi(number.c_str());
                memory[last_memory] = (num >> 24) & 0xFF;
                memory[last_memory + 1] = (num >> 16) & 0xFF;
                memory[last_memory + 2] = (num >> 8) & 0xFF;
                memory[last_memory + 3] = num & 0xFF;
                codes.push_back({to_string(last_memory),1});
                last_memory+=4;
            }
            else if(file[i] == '\"') {
                i++;
                string text = "";
                while(file[i] != '\"') {
                    text += file[i];
                    i++;
                }
                codes.push_back({text,5});
            }
            else if(file[i] == '\'') {
                i++;
                string text = "";
                while(file[i] != '\'') {
                    text += file[i];
                    i++;
                }
                memory[last_memory] = text[0];
                codes.push_back({to_string(last_memory),3});
                last_memory++;
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
    int plus_buffer = last_memory;
    memory[plus_buffer] = 0;
    last_memory++;
    int lines = 0;
    stack<string> stacks;
    stack<int> args;
    string have_to_do = "";
    for(int i = 0;i<codes.size();i++) {
        if(codes[i].second == 6) {
            if(codes[i+1].second == 4) {
                stacks.push(string("ret"));
                while(codes[i].first != ")") {
                    i++;
                }
                i+=2;
            }
        }
        else if(codes[i].second == 4) {
            if(codes[i].first == "print") {
                have_to_do += "print ";
                have_to_do += to_string(last_memory);
            }
        }
        else if(codes[i].second == 2) {
            if(codes[i].first == "}") {
                output << stacks.top() << endl;
                lines++;
            }
            else if(codes[i].first == "{") {
                stacks.push("");
            }
            else if(codes[i].first == "(") {
                args.push(last_memory);
                memory[last_memory] = 0;
                last_memory++;
            }
            else if(codes[i].first == ")") {
                args.pop();
            }
            else if(codes[i].first == ";") {
                output << have_to_do << endl;
                lines++;
                have_to_do = "";
            }
            else if(codes[i].first == "+") {
                if(codes[i-1].second == 0) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) + 3 << "," << atoi(codes[i+1].first.c_str()) + 3 << "," << args.top() + 3 << endl;
                    output << "nif " << plus_buffer << endl;
                    memory[args.top()] = 0;
                    memory[args.top() + 1] = 0;
                    memory[args.top() + 2] = 0;
                    memory[args.top() + 3] = 0;
                }
                else if(codes[i-1].second == 1) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) << "," << atoi(codes[i+1].first.c_str()) << "," << args.top() << endl;
                }
                lines++;
            }
        }
        else if(codes[i].second == 1) {
            memory[args.top()] = memory[atoi(codes[i].first.c_str())];
            memory[args.top() + 1] = memory[atoi(codes[i].first.c_str()) + 1];
            memory[args.top() + 2] = memory[atoi(codes[i].first.c_str()) + 2];
            memory[args.top() + 3] = memory[atoi(codes[i].first.c_str()) + 3];
        }
        else if(codes[i].second == 0) {
            memory[args.top()] = memory[atoi(codes[i].first.c_str())];
        }
    }
    output << "DATA ";
    for(auto datas : memory) {
        output << unsignedCharToHex(datas.second);
    }
    output.close();
    input.close();
    return 0;
}