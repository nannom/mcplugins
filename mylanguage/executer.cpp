#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
int main() {
    ifstream input("main.cne",ios::binary | std::ios::ate);
    long fileSize = input.tellg();
    input.seekg(0, std::ios::beg);
    unsigned char* memory = new unsigned char[fileSize];
    input.read((char*)memory,fileSize);
    int now = 0;
    int data = 0;
    while(memory[now] != 0xFF) {
        now++;
        if(now >= fileSize) {
            break;
        }
    }
    data = now + 1;
    now = 0;
    char result = 0;
    while(now < fileSize && memory[now] != 0xFF) {
        switch (memory[now])
        {
        case 0x01:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            int n2;
            memcpy(&n2,memory + now,4);
            int n3;
            now += 4;
            memcpy(&n3,memory + now,4);
            now += 4;
            int n4 = memory[data + n1] + memory[data + n2];
            memory[data + n3] = n4 & 0xFF;
            result = n4 >> 8;
            break;
        }
        case 0x11:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            memory[data + n1] = memory[data + n1] + 1;
            result = 0;
            break;
        }
        case 0x02:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            int n2;
            memcpy(&n2,memory + now,4);
            int n3;
            now += 4;
            memcpy(&n3,memory + now,4);
            now += 4;
            int n4;
            memcpy(&n4,memory + now,4);
            now += 4;
            int n5 = memory[data + n1] + memory[data + n2] + memory[data + n3];
            memory[data + n4] = n5 & 0xFF;
            result = n5 >> 8;
            break;
        }
        
        case 0x03:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            memory[data + n1] = ~memory[data + n1];
            result = 0;
            break;
        }
        case 0x31:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            int n2;
            memcpy(&n2,memory + now,4);
            now += 4;
            memory[data + n2] = memory[data + n1];
            result = 0;
            break;
        }
        case 0x04:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            memory[data + n1] = result;
            break;
        }
        case 0x06:
        {
            int n1;
            now++;
            memcpy(&n1,memory + now,4);
            now += 4;
            printf("%c", memory[data + n1]);
            break;
        }
        default:
            now++;
            break;
        }
    }
    delete[] memory;
}