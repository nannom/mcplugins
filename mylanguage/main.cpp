#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>
using namespace std;
map<int,char> memory;
queue<queue<string>> codes;
int main() {
    ifstream input("main.ccn");
    string file((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    {
        queue<string> line;
        string code;
        for(int i = 0;i<file.length();i++) {
            if(file[i] == ' ') {
                if(code != "") {
                    line.push(code);
                    code = "";
                }
            }
            else if(file[i] == '\n') {
                if(code != "") {
                    line.push(code);
                    code = "";
                }
                codes.push(line);
                queue<string> ne;
                line = ne;
            }
            else if(file[i] == ';') {
                if(code != "") {
                    line.push(code);
                    code = "";
                }
            }
            else {
                code += file[i];
            }
        }
    }
    for(auto line : codes) {
        for(string code : line) {
            
        }
    }
    return 0;
}