#ifndef MCTEXTLINE_H
#define MCTEXTLINE_H
#include <string>

class MCTextLine
{
public:
    MCTextLine();
    virtual ~MCTextLine();
    std::string text;
    std::string full_line;
    int line_nr = 0;

protected:

private:
};

#endif // MCTEXTLINE_H
