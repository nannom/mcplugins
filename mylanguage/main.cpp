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
using namespace std;
map<int,unsigned char> memory;
int last_memory = 0;
queue<queue<pair<string,int>>> codes;
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
/*
type
1:int
2:char
*/
int main() {
    ifstream input("main.ccn");
    ofstream output("out.cn");
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    cout << file << endl;
    {
        queue<pair<string,int>> line;
        pair<string,int> code;
        for(int i = 0;i<file.length();i++) {
            if(file[i] == ' ') {
                if(code.first != "") {
                    if(isAllDigits(code.first)) {
                        int number = atoi(code.first.c_str());
                        memory[last_memory] = (number >> 24) & 0xFF;
                        memory[last_memory + 1] = (number >> 16) & 0xFF;
                        memory[last_memory + 2] = (number >> 8) & 0xFF;
                        memory[last_memory + 3] = number & 0xFF;
                        code.first = to_string(last_memory);
                        last_memory += 4;
                        code.second = 1;
                    }
                    else if(checkFirstAndLastChar(code.first,'\'')) {
                        memory[last_memory] = code.first[1];
                        code.first = to_string(last_memory);
                        last_memory++;
                        code.second = 2;
                    }
                    else {
                        code.second = 0;
                    }
                    line.push(code);
                    code.first = "";
                    code.second = 0;
                }
            }
            else if(file[i] == '\n') {
                codes.push(line);
                queue<pair<string,int>> ne;
                line = ne;
            }
            else if(file[i] == ',') {
                if(code.first != "") {
                    if(isAllDigits(code.first)) {
                        int number = atoi(code.first.c_str());
                        memory[last_memory] = (number >> 24) & 0xFF;
                        memory[last_memory + 1] = (number >> 16) & 0xFF;
                        memory[last_memory + 2] = (number >> 8) & 0xFF;
                        memory[last_memory + 3] = number & 0xFF;
                        code.first = to_string(last_memory);
                        last_memory += 4;
                        code.second = 1;
                    }
                    else if(checkFirstAndLastChar(code.first,'\'')) {
                        memory[last_memory] = code.first[1];
                        code.first = to_string(last_memory);
                        last_memory++;
                        code.second = 2;
                    }
                    else {
                        code.second = 0;
                    }
                    line.push(code);
                    line.push({",",0});
                    code.first = "";
                }
            }
            else if(file[i] == ';') {
                if(code.first != "") {
                    cout << code.first << endl;
                    if(isAllDigits(code.first)) {
                        int number = atoi(code.first.c_str());
                        memory[last_memory] = (number >> 24) & 0xFF;
                        memory[last_memory + 1] = (number >> 16) & 0xFF;
                        memory[last_memory + 2] = (number >> 8) & 0xFF;
                        memory[last_memory + 3] = number & 0xFF;
                        code.first = to_string(last_memory);
                        last_memory += 4;
                        code.second = 1;
                    }
                    else if(checkFirstAndLastChar(code.first,'\'')) {
                        memory[last_memory] = code.first[1];
                        code.first = to_string(last_memory);
                        last_memory++;
                        code.second = 2;
                    }
                    else {
                        code.second = 0;
                    }
                    line.push(code);
                    line.push({";",0});
                    code.first = "";
                }
            }
            else {
                code.first += file[i];
            }
        }
        if(!line.empty()) {
            codes.push(line);
        }
    }
    cout << last_memory << endl;
    int plus_buffer = last_memory;
    memory[plus_buffer] = 0;
    last_memory++;
    while(!codes.empty()) {
        queue<pair<string,int>> line = codes.front();
        queue<pair<string,int>> line2 = line;
        queue<int> args;
        int number = 0;
        bool isin = false;
        while(!line2.empty()) {
            string code = line2.front().first;
            cout << code << endl;
            if(isAllDigits(code)) {
                number = atoi(code.c_str());
                isin = true;
            }
            else if(code == "+") {
                line2.pop();
                int first = number;
                int second = atoi(line2.front().first.c_str());
                int result = last_memory;
                if(line2.front().second == 1) {
                    memory[last_memory] = 0;
                    memory[last_memory + 1] = 0;
                    memory[last_memory + 2] = 0;
                    memory[last_memory + 3] = 0;
                    last_memory += 4;
                    output << string("ad2 ") + to_string(first + 3) + "," + to_string(second + 3) + "," + to_string(result + 3) + "\n";
                    output << string("nif ") + to_string(plus_buffer) << endl;
                    output << string("ad3 ") + to_string(first + 2) + "," + to_string(second + 2) + "," + to_string(plus_buffer) + "," + to_string(result + 2) + "\n";
                    output << string("nif ") + to_string(plus_buffer) << endl;
                    output << string("ad3 ") + to_string(first + 1) + "," + to_string(second + 1) + "," + to_string(plus_buffer) + "," + to_string(result + 1) + "\n";
                    output << string("nif ") + to_string(plus_buffer) << endl;
                    output << string("ad3 ") + to_string(first) + "," + to_string(second) + "," + to_string(plus_buffer) + "," + to_string(result) + "\n";
                }
                else if(line2.front().second == 2) {
                    memory[last_memory] = 0;
                    last_memory += 1;
                    output << string("ad2 ") + to_string(first) + "," + to_string(second) + "," + to_string(result) + "\n";
                }
                number = result;
            }
            else if(code == ",") {
                args.push(number);
                isin = false;
            }
            else if(code == ";") {
                if(isin) {
                    args.push(number);
                }
                break;
            }
            line2.pop();
        }
        output << line.front().first;
        if(!args.empty()) {
            output << " ";
        }
        else {
            output << endl;
        }
        while(!args.empty()) {
            output << args.front();
            if(args.size() != 1) {
                output << ",";
            }
            else {
                output << endl;
            }
            args.pop();
        }
        codes.pop();
    }
    output << "DATA ";
    for(auto datas : memory) {
        output << unsignedCharToHex(datas.second);
    }
    output.close();
    input.close();
    return 0;
}