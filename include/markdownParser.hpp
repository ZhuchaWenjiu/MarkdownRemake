#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

class block{
    public:
        block *pre; // 指向前一个块
        block *next; // 指向下一个块
        lineContent content; // 块里面的文本内容
        int tag; // 块应该采用的渲染方式
        bool flags[5];  // 未来可能使用的标记
}; // 块内数据


class lineContent{
    public:
        bool isBlock = true;
        bool needParser = true;
        std::vector<std::string> contents;
        std::vector<int> tags;
}; // 行内数据

class markdownParser
{
private:
    int maxLength = 10240;
    std::string fileName;
    std::ifstream mdFile;
    std::ofstream htmlFile;
    std::string outFileName = "./out.html";
    block *startNode = new block();
    block *endNode = new block();
    std::vector<std::string> regexParStr;
public:
    void initNodes();
    void initregexParstr();
    void insertBlock(block node);
    void insertBlock(int idx, block node);
    void insertBlock(block* idx, block node);
    markdownParser(std::string fileName);
    markdownParser();
    ~markdownParser();
};

