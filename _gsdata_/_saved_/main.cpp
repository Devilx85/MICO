#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "MCEngine.h"

using namespace std;

int main()
{
    MCEngine *Engine = new MCEngine();
    std::ifstream file("C:\\sc\\run.mico");
    std::string content((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

    int res = 0;
    //std::cout << content;
    res = Engine->LoadString(content);
    Engine->Run();
    std::cout << Engine->out_buffer;
    Engine->PrintLines(Engine->code);
    //Engine->PrintCode(Engine->code);
    std::cout << std::endl << Engine->exec_time " ms";
    delete Engine;
    return 0;
}
