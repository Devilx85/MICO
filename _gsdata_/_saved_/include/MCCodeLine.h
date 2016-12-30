#ifndef MCCODELINE_H
#define MCCODELINE_H
#include <MCDataNode.h>
#include <MCFParams.h>
#include <vector>
#include <string>
#include <chrono>

class MCFParams;

class MCCodeLine : public MCDataNode
{
    public:
        MCCodeLine();
        virtual ~MCCodeLine();

    int time_data = 0;
    std::chrono::high_resolution_clock::time_point start_m;
    std::chrono::high_resolution_clock::time_point end_m;
    int fselect_tries;
    int executed_count = 0;
    long long exec_time=0;
    bool has_subexr = false;
    bool commented = false;
    int cached_f = -1;

    protected:

    private:
};

#endif // MCCODELINE_H
