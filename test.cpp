#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
void deleteAllFilesInDirectory(const std::string& directoryPath) {
    // 쉘 명령어를 사용하여 모든 파일 삭제
    std::string command = "rm -f " + directoryPath + "/*";
    
    // system 함수를 사용하여 명령어 실행
    int result = system(command.c_str());
    
    if (result == 0) {
        std::cout << "모든 파일이 삭제되었습니다." << std::endl;
    } else {
        std::cerr << "파일 삭제 중 오류가 발생했습니다." << std::endl;
    }
}
int file_number = 1;
string classname = "skul";
void removeIndentation(std::string& str) {
    std::string indent = "    "; // 네 칸 공백 문자열
    size_t pos = str.find(indent);
    
    // 모든 네 칸 공백 문자열 제거
    while (pos != std::string::npos) {
        str.erase(pos, indent.length());
        pos = str.find(indent, pos);
    }
}
void otherfiles(string str,int& i) {
    ofstream file(string("datapack/data/") + classname + string("/functions/file") + to_string(file_number) + string(".mcfunction"));
    file_number++;
    if(!file) {
        printf("file error!!");
        return;
    }
    while(str[i] != ')') {
        if(str[i] == '(') {
            i+=2;
            file << "function ";
            file << classname;
            file << ":file";
            file << file_number;
            otherfiles(str,i);
        }
        else {
            file << str[i];
        }
        i++;
    }
    file.close();
}
int main() {
    deleteAllFilesInDirectory("outputs");
    //cout << "class name:";
    //cin >> classname;
    ifstream input("input.mcfunction");
    if(!input) {
        printf("파일 읽기 오류\n");
        return 0;
    }
    string str((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    removeIndentation(str);
    ofstream output(string("datapack/data/") + classname + string("/functions/tick.mcfunction"));
    if(!output) {
        printf("파일 생성 불가\n");
        return 0;
    }
    for(int i = 0;i < str.length();i++) {
        if(str[i] == '(') {
            i+=2;
            output << "function ";
            output << classname;
            output << ":file";
            output << file_number;
            otherfiles(str,i);
        }
        else {
            output << str[i];
        }
    }
    output.close();
    return 0;
}