#include <iostream>
#include <vector>
using std::string;
using std::vector;
struct Personal
{
    string duty{};
    vector<Personal>underlings{};

  //  Personal() = default;
    /*Personal operator=(const Personal& personal)
    {
        Personal result;
        result.duty = personal.duty;
        result.underlings = personal.underlings;
        return result;
    }*/
    
};