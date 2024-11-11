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
int pares(ofstream& output,int& i,string todo,int plus_buffer) {
    int result = last_memory;
    memory[last_memory] = 0;
    last_memory++;
    while(codes[i].first != ")") {
        if(codes[i].second == 4) {
            if(codes[i].first == "print") {
                i+=2;
                output << pares(output,i,"print ");

            }
        }
        else if(codes[i].second == 2) {
            if(codes[i].first == "(") {
                pares(output,i,"");
            }
            else if(codes[i].first == "+") {
                if(codes[i-1].second == 1) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) + 3 << "," << atoi(codes[i+1].first.c_str()) + 3 << "," << args.top() + 3 << endl;
                    output << "nif " << plus_buffer << endl;
                    memory[args.top()] = 0;
                    memory[args.top() + 1] = 0;
                    memory[args.top() + 2] = 0;
                    memory[args.top() + 3] = 0;
                }
                else if(codes[i-1].second == 3) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) << "," << atoi(codes[i+1].first.c_str()) << "," << args.top() << endl;
                }
            }
        }
    }
    output << todo;
    return result;
}
int main() {
    ifstream input("main.ccn");
    ofstream output("out.cn");
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    output << "call _main" << endl <<  "end" << endl;
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
    for(int i = 0;i<codes.size();i++) {
        if(codes[i].second == 6) {
            if(codes[i+1].second == 4) {
                output << "_" << codes[i+1].first << ":" << endl;
                stacks.push(string("ret"));
                while(codes[i].first != ")") {
                    i++;
                }
                i+=2;
            }
        }
        else if(codes[i].second == 4) {
            if(codes[i].first == "print") {
                i+=2;
                output << pares(output,i,"print ",plus_buffer);

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
                pares(output,i,"",plus_buffer);
            }
            else if(codes[i].first == ";") {
            }
            else if(codes[i].first == "+") {
                if(codes[i-1].second == 1) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) + 3 << "," << atoi(codes[i+1].first.c_str()) + 3 << "," << args.top() + 3 << endl;
                    output << "nif " << plus_buffer << endl;
                    memory[args.top()] = 0;
                    memory[args.top() + 1] = 0;
                    memory[args.top() + 2] = 0;
                    memory[args.top() + 3] = 0;
                }
                else if(codes[i-1].second == 3) {
                    output << "ad2 " << atoi(codes[i-1].first.c_str()) << "," << atoi(codes[i+1].first.c_str()) << "," << args.top() << endl;
                }
                lines++;
            }
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