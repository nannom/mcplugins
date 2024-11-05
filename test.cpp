#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
std::map<std::string, std::string> readFilesWithExtension(const std::string& directoryPath, const std::string& extension) {
    std::map<std::string, std::string> fileContents;

    // 디렉토리 내 모든 파일 탐색
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // 일반 파일인지 확인하고 확장자가 일치하는지 검사
        if (fs::is_regular_file(entry) && entry.path().extension() == extension) {
            std::string fileName = entry.path().filename().string();
            std::ifstream file(entry.path());

            if (file.is_open()) {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                fileContents[fileName] = content; // 파일 이름을 키로, 내용을 값으로 저장
                file.close();
            } else {
                std::cerr << "파일을 열 수 없습니다: " << entry.path() << std::endl;
            }
        }
    }

    return fileContents; // 파일 내용을 담고 있는 map 반환
}
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
    std::string indent = "  "; // 네 칸 공백 문자열
    size_t pos = str.find(indent);
    
    // 모든 네 칸 공백 문자열 제거
    while (pos != std::string::npos) {
        str.erase(pos, indent.length());
        pos = str.find(indent, pos);
    }
}
void otherfiles(string str,int& i) {
    ofstream file(string("datapack/data/") + classname + string("/function/file") + to_string(file_number) + string(".mcfunction"));
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
    deleteAllFilesInDirectory("datapack/data/skul/function");
    //cout << "class name:";
    //cin >> classname;
    map<string,string> files = readFilesWithExtension("inputs",".mcfunction");
    for(auto file : files) {
        string str = file.second;
        removeIndentation(str);
        ofstream output(string("datapack/data/") + classname + string("/function/") + file.first);
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
    }
    return 0;
}