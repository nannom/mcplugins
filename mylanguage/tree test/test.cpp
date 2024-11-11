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
std::string unsignedCharToHex(unsigned char value) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << std::hex << (int)value;
    return ss.str();
}
string ntext = " /+-*!@#$%^&(){}[]\\\n`~,.|;\t\r";
string math = "+-*/";
set<string> vars = {"int","char"};
class Code {
public:
    int type;
    string name;
    int addr;
};
class CodeTree {
public:
    Code code;
    vector<CodeTree*> childs;
    CodeTree* parent;
    void printTree(int depth = 0) {
        // 현재 노드를 depth에 맞춰 출력
        for (int i = 0; i < depth; ++i) {
            cout << "    "; // 들여쓰기 (depth에 따라 변경)
        }
        cout << "- " << code.name << endl;

        // 자식 노드를 재귀적으로 출력
        for (auto child : childs) {
            child->printTree(depth + 1);
        }
    }
    void outcode(ofstream& output) {
        if(code.type == 6) {
            
        }
    }
};


map<string,CodeTree> functions;
map<int,unsigned char> memory;
int last_memory = 0;
int main() {
    ifstream input("test.ccn");
    ofstream output("out.cn");
    vector<Code> codes;
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    for(int i = 0;i<file.length();i++) {
        Code code;
        if(ntext.find(file[i]) != string::npos) {
            if(file[i] != ' ' && file[i] != '\t' && file[i] != '\n') {
                string str;
                str+=file[i];
                code.addr = 0;
                code.name = str;
                code.type = 2;
                codes.push_back(code);
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
                code.addr = last_memory;
                code.name = number;
                code.type = 1;
                codes.push_back(code);
                last_memory+=4;
            }
            else if(file[i] == '\"') {
                i++;
                string text = "";
                while(file[i] != '\"') {
                    text += file[i];
                    i++;
                }
                code.name=text;
                code.addr = 0;
                code.type = 5;
                codes.push_back(code);
            }
            else if(file[i] == '\'') {
                i++;
                string text = "";
                while(file[i] != '\'') {
                    text += file[i];
                    i++;
                }
                memory[last_memory] = text[0];
                code.addr = last_memory;
                code.name = text;
                code.type = 3;
                codes.push_back(code);
                last_memory++;
            }
            else {
                string text = "";
                while(ntext.find(file[i]) == string::npos) {
                    text += file[i];
                    i++;
                }
                if(vars.find(text) != vars.end()) {
                    code.addr = 0;
                    code.name = text;
                    code.type = 6;
                    codes.push_back(code);
                }
                else {
                    code.addr = 0;
                    code.name = text;
                    code.type = 0;
                    codes.push_back(code);
                }
                i--;
            }
        }
    }
    CodeTree* tree = new CodeTree();
    CodeTree* top = tree;
    tree->code.name = "";
    tree->parent = nullptr;
    for(int i = 0;i<codes.size();i++) {
        Code code = codes[i];
        CodeTree* child = new CodeTree();
        if(code.name == "{" || vars.find(code.name) != vars.end()) {
            child->code = code;
            tree->childs.push_back(child);
            child->parent = tree;
            tree = child;
        }
        else if(code.name == "(") {
            child->code = code;
            child->parent = tree->childs.back();
            tree->childs.back()->childs.push_back(child);
            tree = child;
        }
        else if(code.name == "}") {
            tree = tree->parent;
        }
        else if(code.name == ")") {
            tree = tree->parent->parent;
        }
        else if(math.find(code.name) != string::npos) {
            if(i != 0) {
                if(i != codes.size() - 1) {
                    CodeTree* ch2 = tree->childs.back();
                    tree->childs.pop_back();
                    ch2->parent = child;
                    child->childs.push_back(ch2);
                    CodeTree* ch22 = new CodeTree();
                    ch22->parent = child;
                    ch22->code = codes[i+1];
                    child->code = code;
                    child->childs.push_back(ch22);
                    tree->childs.push_back(child);
                    i++;
                }
            }
            else {
                if(i != codes.size() - 1) {

                }
            }
        }
        else {
            child->code = code;
            child->parent = tree;
            tree->childs.push_back(child);
        }
    }
    top->printTree();
    output << "call _main" << endl << "end" << endl;
    //outputtree(output,top);
    output << "DATA ";
    for(auto datas : memory) {
        output << unsignedCharToHex(datas.second);
    }
    output.close();
    input.close();
}