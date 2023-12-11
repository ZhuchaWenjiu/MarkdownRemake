#include "../include/markdownParser.hpp"

void markdownParser::initNodes(){
    // 由于是转成 html 因此 开头和结尾是固定的，可以直接先申请两个块
    lineContent hContent, eContent;
    hContent.needParser = false; eContent.needParser = false; // 开头和结尾不需要解析
    std::string headstr = "<!DOCTYPE html><html><head>\
        <meta charset=\"utf-8\">\
        <title>Markdown</title>\
        <link rel=\"stylesheet\" href=\"github-markdown.css\">\
        </head><body><article class=\"markdown-body\">";
    std::string endstr = "</article></body></html>";
    hContent.contents.push_back(headstr); eContent.contents.push_back(endstr);
    
    startNode->next = endNode; startNode->pre = nullptr;
    startNode->content = hContent;startNode->tag = 0;

    endNode ->pre = startNode; endNode ->next = nullptr;
    endNode ->content = eContent; endNode ->tag = 0;

}

markdownParser::markdownParser(){
    initNodes();
}

markdownParser::markdownParser(std::string filename){
    initNodes();
    mdFile.open(filename, std::ios::in);
    if (!mdFile.is_open()){
        std::cerr << "open file error \n";
    }

    if(!mdFile){
        std::cerr << "open file error \n";
    }

    char buf[1024]; // 行最大长度
    bool concatBlock = false;
    while (mdFile.getline(buf, sizeof(buf))){
        for (size_t i = 0; i < count; i++)
        {
            /* code */
        }
        
    }
    
    
}

markdownParser::~markdownParser(){
    delete startNode;
}


void markdownParser::insertBlock(block node){
    auto pre = endNode->pre;
    node.next = endNode; node.pre = pre;
    pre->next = &node; endNode->pre = &node;
}

void markdownParser::insertBlock(int idx, block node){
    // after idx
    int start = 0;
    auto pre = startNode;
    while (start < idx && pre->next != nullptr){
        pre = pre->next;
        start++;
    }
    node.next = pre->next; node.pre = pre;
    pre->next->pre = &node;  pre->next = &node; 
}

void markdownParser::insertBlock(block* idx, block node){
    // after idx
    node.next = idx->next; node.pre = idx;
    idx->next->pre = &node;  idx->next = &node; 
}

void markdownParser::initregexParstr(){
    regexParStr.push_back("^(#+)(.*)"); // h1 - h5
    regexParStr.push_back("\n(&gt;|\\>)(.*)"); // 引用 
}