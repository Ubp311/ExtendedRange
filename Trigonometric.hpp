#include    "ExRange.hpp"


using namespace std;

namespace bigMath
{
    ExRange<double>& sin();
    ExRange<double>& cos();
    ExRange<double>& tan();
    ExRange<double>& cot();
    ExRange<double>& sec();
    ExRange<double>& csc();

    ExRange<double>& rad2Deg(const ExRange<double>& val);
    ExRange<double>& Deg2Rad(const ExRange<double>& val);
    
}