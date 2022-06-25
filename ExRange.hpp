#include    <iostream>
#include    <vector>
#include    <string>


using namespace std;

const unsigned long long  kUIntLimit = 4294967296ULL;
const unsigned int  kIntLimit = 2147483648U;
const unsigned int  kValStrParseLimit = 100000000U;
const unsigned int  kValStrParseLimitDigitNum = 8U;

const size_t  kKaratsubaLimit = 4;

string uitos(unsigned int _val)
{
    string  resultStr;

    unsigned int    tempVal = _val;
    unsigned int    mul = 1U;

    if (_val == 0U)
        return  "0";
    while (tempVal != 0U)
    {
        tempVal /= 10U;
        mul *= 10U;
    }
    mul /= 10U;
    while (mul != 0U)
    {
        resultStr += _val / mul + '0';
        _val -= _val / mul * mul;
        mul /= 10U;
    }

    return  resultStr;
};
int  myCeil(double val)
{
    return  (val >= 0.0) ? val - int(1.0 - val + (int)val) + 1.0 : val;
};
size_t  myCeil(size_t operand, size_t divide)
{
    if(divide != 0 && operand % divide > 0)
        return  operand / divide + 1;
    if(divide == 0)
        throw "Division by zero.";
    return operand / divide;
};
size_t bitCeil(size_t operand, size_t div)
{
    size_t temp1, temp2, expVal = 1;
    size_t size = 0;

    if (div != 0 && operand % div != 0)
        temp2 = temp1 = operand / div + 1;
    else if (div == 0)
        throw "Division by zero.";
    else
        temp2 = temp1 = operand / div;
    if (temp1 == 0)
        return 0;
    while (temp1 != 0)
    {
        size++;
        temp1 >>= 1;
        expVal <<= 1;
    }
    expVal >>= 1;
    if (temp2 == expVal)
        return size;

    return size + 1;
};

template<typename T>
class MemoryManager
{
private:
    static MemoryManager*   instance;
    MemoryManager();
    ~MemoryManager();
public:
    static  MemoryManager& getIstnace()
    {
        if(instance == nullptr)
            instance = new MemoryManager();
        return  *instance;
    };
};

template<typename T>
class ExRange
{ 
};

template<>
class ExRange<unsigned int>
{

};

template<>
class ExRange<int>
{
private:
    vector<unsigned int> val;
    bool    isNegative;
public:
    ExRange();
    ExRange(const int &_val);
    ExRange(const int &&_val);
    ExRange(const unsigned long long &_val);
    ExRange(const ExRange &_var);
    ExRange(const string &_varStr);
    ExRange operator=(const ExRange& _var);
    ExRange operator=(const string& _valStr);
    inline unsigned int&   operator[](size_t index);
    void    clear();
    bool    getNegativeSign();
    bool&   getNegativeSignRef();
    vector<unsigned int>&   getValuesRef();
    inline size_t  getSize();
    inline void    pushBack(const unsigned int& _val);
    inline void    pushBack(const unsigned int&& _val);
    inline void    popBack();
    
    inline  ExRange basicMultiply(const ExRange<int> &_var) const;
    static unsigned int   divideAndGetRemainder(ExRange<int>& var, const unsigned int& val);

    ExRange& operator*(int _val) const;
    ExRange operator/(int _val) const;
    ExRange operator%(const int _val) const;
    ExRange operator+(int _val) const;
    ExRange operator-(int _val) const;
    ExRange operator*(ExRange& _var);
    ExRange operator/(ExRange& _var);
    ExRange operator%(ExRange& _var);
    ExRange operator+(const ExRange& _var) const;
    ExRange operator-(const ExRange& _var) const;
    ExRange&    operator*=(int _val);
    ExRange&    operator/=(int _val);
    ExRange&    operator%=(int _val);
    ExRange&    operator+=(int _val);
    ExRange&    operator-=(int _val);
    ExRange&    operator*=(ExRange& _var);
    ExRange&    operator/=(ExRange& _var);
    ExRange&    operator%=(ExRange& _var);
    ExRange&    operator+=(ExRange& _var);
    ExRange&    operator-=(ExRange& _var);
    ExRange  operator&(const ExRange& _var) const;

    static string   decode(const ExRange& _var);

    bool    operator==(const int& _val) const;
    bool    operator!=(const int& _val) const;
    bool    operator>(int _val) const;
    bool    operator<(int _val) const;
    bool    operator>=(int _val) const;
    bool    operator<=(int _val) const;
    bool    operator==(const ExRange& _var) const;
    bool    operator!=(const ExRange& _var) const;
    bool    operator>(const ExRange& _var) const;
    bool    operator<(const ExRange& _var) const;
    bool    operator>=(const ExRange& _var) const;
    bool    operator<=(const ExRange& _var) const;
};

template<typename T>
class ExRangeRef
{
};

template<>
class ExRangeRef<int>
{
private:
    vector<unsigned int> &valRef;
    size_t  startIndex, endIndex;
    bool &isNegative;
public:
    ExRangeRef(ExRange<int> &_var) : valRef(_var.getValuesRef()), isNegative(_var.getNegativeSignRef())
    {
        startIndex = 0;
        endIndex = 0;
    };
    ExRangeRef(ExRange<int> &_var, const size_t& _startIndex, const size_t& _endIndex) : valRef(_var.getValuesRef()), isNegative(_var.getNegativeSignRef())
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
    };
    inline size_t   getStartIndex();
    inline void   setStartIndex(const size_t& index);
    inline size_t   getEndIndex();
    inline void   setEndIndex(const size_t& index);

    ExRange<int>    operator+(const ExRangeRef &_varRef);
    ExRangeRef  &operator=(const ExRangeRef<int> &_var);
    inline  ExRange<int>    basicMultiply(const ExRangeRef& _var) const;

    bool    operator==(const int &_val) const;
    bool    operator!=(const int &_val) const;
    bool    operator>(int _val) const;
    bool    operator<(int _val) const;
    bool    operator>=(int _val) const;
    bool    operator<=(int _val) const;
};

ExRange<int>::ExRange()
{
    isNegative = false;
};

ExRange<int>::ExRange(const int &_val)
{
    if (_val >= 0)
    {
        val.push_back(_val);
        isNegative = false;
    }
    else
    {
        val.push_back(_val * -1);
        isNegative = true;
    }
};

ExRange<int>::ExRange(const int && _val)
{
    if (_val >= 0)
    {
        val.push_back(_val);
        isNegative = false;
    }
    else
    {
        val.push_back(_val * -1);
        isNegative = true;
    }
}

ExRange<int>::ExRange(const unsigned long long &_val)
{
    val.push_back((unsigned int)_val);
    if (_val >= kUIntLimit)
        val.push_back(_val >> 32);
    isNegative = false;
};

ExRange<int>::ExRange(const ExRange &_var)
{
    for (size_t i = 0; i < _var.val.size(); i++)
        val.push_back(_var.val[i]);
    isNegative = _var.isNegative;
};

ExRange<int>::ExRange(const string &_valStr)
{
    size_t i = 0;
    size_t j = 0;

    ExRange<int> quotient;
    unsigned long long partialQuotient = 0ULL;
    unsigned long long tempPartialQuotient = 0ULL;
    unsigned long long remainder = 0ULL;

    int sign = 1;

    int mul = 1;

    isNegative = false;

    if (!_valStr.empty())
    {
        if (_valStr[i] == '-')
        {
            sign = -1;
            isNegative = true;
        }
        for (i = _valStr.size() - 1; i > 0; i--)
        {
            if (isdigit(_valStr[i]))
            {
                if (j % kValStrParseLimitDigitNum == 0)
                {
                    quotient.val.push_back(0U);
                    mul = 1;
                }
                quotient.val[quotient.val.size() - 1] += mul * (_valStr[i] - '0');
                mul *= 10;
                j++;
            }
        }
        if (!isNegative)
        {
            if (j % kValStrParseLimitDigitNum == 0)
            {
                quotient.val.push_back(0U);
                mul = 1;
            }
            quotient.val[quotient.val.size() - 1] += mul * (_valStr[i] - '0');
        }
        while (quotient != 0)
        {
            remainder = quotient.val[quotient.val.size() - 1] % kUIntLimit;
            quotient.val.pop_back();
            for (i = 0; i < quotient.val.size(); i++)
            {
                remainder *= kValStrParseLimit;
                remainder += quotient.val[quotient.val.size() - i - 1];
                quotient.val[quotient.val.size() - i - 1] = remainder / kUIntLimit;
                remainder %= kUIntLimit;
            }
            val.push_back(remainder);
            if (!quotient.val.empty() && quotient.val[quotient.val.size() - 1] == 0U)
                quotient.val.pop_back();
            if (quotient.val.empty())
                quotient.val.push_back(0U);
        }
        if (val.empty())
            val.push_back(0U);
    }
};

ExRange<int>    ExRange<int>::operator=(const ExRange& _var)
{
    val.clear();

    for (size_t i = 0; i < _var.val.size(); i++)
        val.push_back(_var.val[i]);
    isNegative = _var.isNegative;

    return *this;
};

ExRange<int>    ExRange<int>::operator=(const string& _valStr)
{
    size_t i = 0;
    size_t j = 0;

    ExRange<int> quotient;
    unsigned long long partialQuotient = 0ULL;
    unsigned long long tempPartialQuotient = 0ULL;
    unsigned long long remainder = 0ULL;

    int sign = 1;

    int mul = 1;

    val.clear();

    if (!_valStr.empty())
    {
        if (_valStr[i] == '-')
        {
            sign = -1;
            isNegative = true;
        }
        for (i = _valStr.size() - 1; i > 0; i--)
        {
            if (_valStr[i] >= '0' && _valStr[i] <= '9')
            {
                if (j % kValStrParseLimitDigitNum == 0)
                {
                    quotient.val.push_back(0U);
                    mul = 1;
                }
                quotient.val[quotient.val.size() - 1] += mul * (_valStr[i] - '0');
                mul *= 10;
                j++;
            }
        }
        if (!isNegative)
        {
            if (j % kValStrParseLimitDigitNum == 0)
            {
                quotient.val.push_back(0U);
                mul = 1;
            }
            quotient.val[quotient.val.size() - 1] += mul * (_valStr[i] - '0');
        }
        while (quotient != 0)
        {
            remainder = quotient.val[quotient.val.size() - 1] % kUIntLimit;
            quotient.val.pop_back();
            for (i = 0; i < quotient.val.size(); i++)
            {
                remainder *= kValStrParseLimit;
                remainder += quotient.val[quotient.val.size() - i - 1];
                quotient.val[quotient.val.size() - i - 1] = remainder / kUIntLimit;
                remainder %= kUIntLimit;
            }
            val.push_back(remainder);
            if (!quotient.val.empty() && quotient.val[quotient.val.size() - 1] == 0U)
                quotient.val.pop_back();
            if (quotient.val.empty())
                quotient.val.push_back(0U);
        }
        if (val.empty())
            val.push_back(0U);
    }

    return *this;
};

inline unsigned int&   ExRange<int>::operator[](size_t index)
{
    return  val[index];
};

void    ExRange<int>::clear()
{
    isNegative = false;
    val.clear();
};

bool    ExRange<int>::getNegativeSign()
{
    return  isNegative;
};

bool&   ExRange<int>::getNegativeSignRef()
{
    return  isNegative;
};

vector<unsigned int>&   ExRange<int>::getValuesRef()
{
    return  val;
};

inline size_t  ExRange<int>::getSize()
{
    return  val.size();
};

inline void ExRange<int>::pushBack(const unsigned int& _val)
{
    val.push_back(_val);
};

inline void ExRange<int>::pushBack(const unsigned int&& _val)
{
    val.push_back(_val);
};

inline void ExRange<int>::popBack()
{
    val.pop_back();
};

ExRange<int>    ExRange<int>::basicMultiply(const ExRange<int> &_var) const
{
    ExRange<int> result;

    size_t i = 0, j = 0;

    unsigned long long mul;
    unsigned int carry;

    try
    {
        if(val.empty() || _var.val.empty())
            throw   string("There is null among operands.");
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }

    if (*this == 0 || _var == 0)
        return ExRange(0);
    result.isNegative = (_var < 0) ? !isNegative : isNegative;
    if (*this == 1 || _var == 1)
        return *this;
    else if (_var == -1 || *this == -1)
    {
        return !isNegative;
    }

    for (; i < val.size(); i++)
    {
        carry = 0U;
        for (j = 0; j < _var.val.size(); j++)
        {
            mul = (unsigned long long)val[i] * (unsigned long long)_var.val[j] + carry;
            carry = mul / kUIntLimit;
            mul %= kUIntLimit;
            if (i + j == result.val.size())
                result.val.push_back(0U);
            if (mul + result[i + j] >= kIntLimit)
            {
                carry++;
                result[i + j] = (mul + result[i + j]) - kUIntLimit;
            }
            else
                result[i + j] += mul;
        }
        if (carry != 0U)
            result.pushBack(carry);
    }

    return result;
};

unsigned int    ExRange<int>::divideAndGetRemainder(ExRange<int>& var, const unsigned int& val)
{
    size_t i = var.getSize() - 1;

    unsigned long long remainder = 0ULL;

    try
    {
        if(var.val.empty())
            throw   string("Operand is null value.");
        else if(val == 0U)
            throw   val;
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }
    catch(const unsigned int& e)
    {
        cerr << "Not divisible by " << e << '\n';
    }

    if (val == 0U)
        return 0U;
    for (; i > 0; i--)
    {
        remainder += var[i];
        var[i] = remainder / val;
        remainder %= val;
        remainder *= kUIntLimit;
    }
    remainder += var[i];
    var[i] = remainder / val;
    remainder %= val;
    i = var.getSize() - 1;
    if (var[i] == 0U && i != 0)
        var.popBack();

    return (unsigned int)remainder;
};

ExRange<int>&    ExRange<int>::operator*(int _val) const
{
    ExRange<int>*   result = new ExRange<int>();

    size_t i = 0;

    unsigned long long mul;
    unsigned int carry = 0U;
    unsigned int tempVal = 0;

    try
    {
        if(val.empty())
            throw   "Operand is null value.";
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }

    result->isNegative = isNegative;
    if (_val == 0 || *this == 0)
        return ExRange(0);
    else if (_val < 0)
    {
        _val *= -1;
        result.isNegative = !isNegative;
    }
    if (_val == 1)
        return *this;
    for (; i < val.size(); i++)
    {
        mul = (unsigned long long)val[i] * _val + carry;
        result.val.push_back(mul % kUIntLimit);
        carry = mul / kUIntLimit;
    }
    if (carry != 0U)
        result.val.push_back(carry);

    return result;
};

ExRange<int>    ExRange<int>::operator/(int _val) const
{
    ExRange<int> result;

    size_t i = val.size() - 1;

    unsigned long long remainder = 0ULL;

    result.isNegative = isNegative;
    try
    {
        if(val.empty())
            throw   string("Operand is null value.");
        if (_val == 0)
            throw _val;
        else if (_val < 0)
        {
            _val *= -1;
            result.isNegative = !isNegative;
        }
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }
    catch (const int &e)
    {
        cerr << "Not divisible by " << e << '\n';
    }

    result.val.resize(i + 1);
    for (; i > 0; i--)
    {
        remainder += val[i];
        result.val[i] = remainder / _val;
        remainder %= _val;
        remainder *= kUIntLimit;
    }
    remainder += val[i];
    result.val[i] = remainder / _val;
    i = result.val.size() - 1;
    if (result.val[i] == 0U && i != 0)
        result.val.pop_back();

    return result;
};

ExRange<int>    ExRange<int>::operator%(const int _val) const
{

};

ExRange<int>    ExRange<int>::operator+(int _val) const
{
    ExRange<int> result;

    size_t i = 0;

    int carry = 0;

    try
    {
        if(val.empty())
            throw   string("There is null among operands.");
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }
    if (isNegative && _val > 0 || !isNegative && _val < 0)
    {
        if (_val < 0)
            _val *= -1;
        result.val.push_back(val[i] - _val);
        result.isNegative = isNegative;
        if (val[i] < result.val[i])
        {
            if (val.size() == 1)
            {
                result.val[i] *= -1;
                result.isNegative = !isNegative;
            }
            carry = -1;
        }
        for (i++; i < val.size() - 1; i++)
        {
            result.val.push_back(val[i] + carry); // -1 + 3 = 2 -> 1 - 3 = -2 // - | 2 | 3 + 5 ->  2 | 3 - 5 // 2 | 3 - 5 -> 2 |
            carry = 0;
            if (val[i] < result.val[i])
                carry = -1;
        }
        if (i == val.size() - 1)
        {
            result.val.push_back(val[i] + carry);
            if (result.val[i] == 0U)
                result.val.pop_back();
        }
    }
    else
    {
        if (_val != 0)
        {
            if (_val < 0)
                _val *= -1;
            result.val.push_back(val[i] + _val);
        }
        else
            return *this;
        if (val[i] > result.val[i])
            carry = 1;
        for (i++; i < val.size(); i++)
        {
            result.val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > result.val[i])
                carry = 1;
        }
        if (carry != 0)
            result.val.push_back(carry);
        result.isNegative = isNegative;
    }

    return result;
};

ExRange<int>    ExRange<int>::operator-(int _val) const
{
    ExRange<int> result;

    size_t i = 0;

    int carry = 0;

    try
    {
        if(val.empty())
            throw   "There is null among operands.";
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }

    if (isNegative && _val > 0 || !isNegative && _val < 0)
    {
        if (_val < 0)
            _val *= -1;
        result.val.push_back(val[i] + _val);
        if (val[i] > result.val[i])
            carry = 1;
        for (i++; i < val.size(); i++)
        {
            result.val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > result.val[i])
                carry = 1;
        }
        if (carry != 0)
            result.val.push_back(carry);
        result.isNegative = isNegative;
    }
    else
    {
        if (_val != 0)
        {
            if (_val < 0)
                _val *= -1;
            result.val.push_back(val[i] - _val);
        }
        else
            return *this;
        result.isNegative = isNegative;
        if (val[i] < result.val[i])
        {
            if (val.size() == 1)
            {
                result.val[i] *= -1;
                result.isNegative = !isNegative;
            }
            carry = -1;
        }
        for (i++; i < val.size(); i++)
        {
            result.val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] < result.val[i])
                carry = -1;
        }
        if (i == val.size() - 1)
        {
            result.val.push_back(val[i] + carry);
            if (result.val[i] == 0U)
                result.val.pop_back();
            result.isNegative = isNegative;
        }
    }

    return result;
};

ExRange<int>    ExRange<int>::operator*(ExRange<int>& _var)
{
    try
    {
        if (val.empty())
            throw string("There is null among operands");
        else if (_var.val.empty())
            throw string("There is null among operands");
    }
    catch (const string &e)
    {
        cerr << e << '\n';
    }

    ExRange<int>    result;
    ExRange<int>    z[3];
    ExRangeRef<int> p0 = *this, p1 = *this;
    ExRangeRef<int> _p0 = _var, _p1 = _var;

    vector<size_t>  sizes;

    size_t  maxSize;
    size_t  minSize;
    if(val.size() >= _var.getSize())
    {
        maxSize = val.size();
        minSize = _var.getSize();
    }
    else
    {
        maxSize = _var.getSize();
        minSize = val.size();
    }
    bool    maxIs_var = (maxSize == _var.getSize()) ? true : false;
    size_t  expVal = bitCeil(maxSize, kKaratsubaLimit) - 1;
    size_t  splitedMinSize = maxSize / (1 << expVal);
    size_t  remainder = maxSize % (1 << expVal);
    size_t  currentIndex = 0;
    size_t  deltaSize;
    size_t  i = 0, j = 0;
    
    if (_var == 0)
        return ExRange(0);
    result.isNegative = (_var < 0) ? !isNegative : isNegative;
    if (_var == 1)
        return *this;
    else if (_var == -1)
    {
        result = *this;
        result.isNegative = _var.isNegative;

        return  result;
    }
    if (splitedMinSize == kKaratsubaLimit / 2 && remainder < (1 << expVal) / 2)
    {
        for (i = 0; i < (1 << expVal) / 2 - remainder; i++)
        {
            deltaSize = currentIndex - minSize - 1;
        }
        for (i = 0; i < remainder; i++)
        {
            deltaSize = currentIndex - minSize - 1;
            for(j = 0; j < kKaratsubaLimit / 2 + 1; j++)
            {
                // 
            }
            for(j = 0; j < kKaratsubaLimit / 2; j++)
            {
                // 1
            }
        }
    }
    else
    {
        for (; i < 1 << expVal; i++)
        {
            if (i % 2 == 0)
            {
                for(j = 0; j < splitedMinSize; j++)
                {

                }
                if(i / 2 >= remainder)
                {

                }
            }
            else
            {
                for(j = 0; j < splitedMinSize; j++)
                {

                }
                if((1 << expVal) / 2 + i / 2 >= remainder)
                {
                    
                }
            }
        }
    }
    i = sizes.size() - 1;
    if (i == 1)
    {
        z[0].isNegative = result.isNegative;
        return z[0];
    }
    //----------------------------------------

    return result;
};

ExRange<int>    ExRange<int>::operator/(ExRange<int>& _var)
{
    ExRange<int>    result;
    ExRangeRef<int> varRef = *this, _varRef = _var;

    result.isNegative = (!_var.isNegative) ? isNegative : !isNegative;

    try
    {
        if(_var == 0)
        {
            throw   0;
        }
    }
    catch(const int& e)
    {
        cerr << "Not divisible by " << e << '\n';
    }

    if(*this < _var)
        return  0;
    else if(*this == _var)
        return  1;
    else if(_var == 1 || _var == -1)
        return  *this;

    return  result;
};

ExRange<int>    ExRange<int>::operator%(ExRange<int>& _var)
{

};

ExRange<int>    ExRange<int>::operator+(const ExRange<int>& _var) const
{
    ExRange<int> result;

    size_t i;

    int carry = 0;

    if (isNegative != _var.isNegative)
    {
        bool isValLarger;

        if (val.size() > _var.val.size())
            isValLarger = true;
        else if (val.size() < _var.val.size())
            isValLarger = false;
        else
        {
            for (i = val.size() - 1; i > 0; i--)
            {
                if (val[i] != _var.val[i])
                    break;
            }
            isValLarger = (val[i] > _var.val[i]) ? true : false;
        }
        if (!isValLarger)
        {
            for (i = 0; i < val.size(); i++)
            {
                result.val.push_back(_var.val[i] - val[i] + carry); // 0 - 0 - 1 // 3 - kU-1 - 1 // 9 8 9 8 - 0 9 9 9
                carry = 0;
                if ((_var.val[i] < result.val[i] || val[i] != 0U) && _var.val[i] <= result.val[i])
                    carry = -1;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0;
                if (_var.val[i] < result.val[i])
                    carry = -1;
            }
            result.isNegative = _var.isNegative;
        }
        else
        {
            for (i = 0; i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] - _var.val[i] + carry); // 0 - 0 - 1 = kU-1 // 3 - kU-1 - 1 = 3 // 3 - 0 - 0 = 3
                carry = 0;
                if ((val[i] < result.val[i] || _var.val[i] != 0U) && val[i] <= result.val[i])
                    carry = -1;
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if (val[i] < result.val[i])
                    carry = -1;
            }
            result.isNegative = isNegative;
        }
        for (i = result.val.size() - 1; i > 0; i--)
        {
            if (result.val[i] == 0U)
            {
                result.val.pop_back();
                continue;
            }
            break;
        }
    }
    else
    {
        for (i = 0; i < val.size() && i < _var.val.size(); i++)
        {
            result.val.push_back(val[i] + _var.val[i] + carry);
            carry = 0;
            if ((val[i] > result.val[i] || _var.val[i] != 0U) && val[i] >= result.val[i])
                carry = 1;
        }
        for (; i < val.size(); i++)
        {
            result.val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > result.val[i])
                carry = 1;
        }
        for (; i < _var.val.size(); i++)
        {
            result.val.push_back(_var.val[i] + carry);
            carry = 0;
            if (_var.val[i] > result.val[i])
                carry = 1;
        }
        if (carry != 0)
            result.val.push_back(carry);
        result.isNegative = isNegative;
    }

    return result;
};

ExRange<int>    ExRange<int>::operator-(const ExRange<int>& _var) const
{
    ExRange<int> result;

    size_t i;

    int carry = 0;

    if (isNegative != _var.isNegative)
    {
        for (i = 0; i < val.size() && i < _var.val.size(); i++)
        {
            result.val.push_back(val[i] + _var.val[i] + carry);
            carry = 0;
            if ((val[i] > result.val[i] || _var.val[i] != 0U) && val[i] >= result.val[i])
                carry = 1;
        }
        for (; i < val.size(); i++)
        {
            result.val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > result.val[i])
                carry = 1;
        }
        for (; i < _var.val.size(); i++)
        {
            result.val.push_back(_var.val[i] + carry);
            carry = 0;
            if (_var.val[i] > result.val[i])
                carry = 1;
        }
        if (carry != 0)
            result.val.push_back(carry);
        result.isNegative;
    }
    else
    {
        bool isValLarger;

        if (val.size() > _var.val.size())
            isValLarger = true;
        else if (val.size() < _var.val.size())
            isValLarger = false;
        else
        {
            for (i = val.size() - 1; i > 0; i--)
            {
                if (val[i] != _var.val[i])
                    break;
            }
            isValLarger = (val[i] > _var.val[i]) ? true : false;
        }
        if (!isValLarger)
        {
            for (i = 0; i < val.size(); i++)
            {
                result.val.push_back(_var.val[i] - val[i] + carry); // 0 - 0 - 1 // 3 - kU-1 - 1
                carry = 0;
                if ((_var.val[i] < result.val[i] || val[i] != 0U) && _var.val[i] <= result.val[i])
                    carry = -1;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0;
                if (_var.val[i] < result.val[i])
                    carry = -1;
            }
            result.isNegative = !_var.isNegative;
        }
        else
        {
            for (i = 0; i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] - _var.val[i] + carry); // 0 - 0 - 1 = kU-1 // 3 - kU-1 - 1 = 3 // 3 - 0 - 0 = 3
                carry = 0;
                if ((val[i] < result.val[i] || _var.val[i] != 0U) && val[i] <= result.val[i])
                    carry = -1;
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if (val[i] < result.val[i])
                    carry = -1;
            }
            result.isNegative = isNegative;
        }
        for (i = result.val.size() - 1; i > 0; i--)
        {
            if (result.val[i] == 0U)
            {
                result.val.pop_back();
                continue;
            }
            break;
        }
    }

    return result;
};

ExRange<int>&   ExRange<int>::operator*=(int _val)
{
    size_t i = 0;

    unsigned long long mul;
    unsigned int carry = 0U;
    unsigned int tempVal = 0;

    isNegative = isNegative;
    if (_val == 0)
    {
        isNegative = false;
        val.clear();
    }
    else if (_val < 0)
    {
        _val *= -1;
        isNegative = !isNegative;
    }
    if (_val == 1)
        return *this;
    for (; i < val.size(); i++)
    {
        mul = (unsigned long long)val[i] * _val + carry;
        val[i] = mul % kUIntLimit;
        carry = mul / kUIntLimit;
    }
    if (carry != 0U)
        val.push_back(carry);

    return *this;
};

ExRange<int>&   ExRange<int>::operator/=(int _val)
{
    size_t  i = val.size() - 1;

        unsigned long long  remainder = 0ULL;

        try
        {
            if(_val == 0)
                throw   _val;
            else if (_val < 0)
            {
                _val *= -1;
                isNegative = !isNegative;
            }
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
        }
        
        if(val.size() > 1)
        {
            if(val[i] < _val)
            {
                remainder = val[i];
                remainder *= kUIntLimit;
                i--;
            }
        }
        for(; i > 0; i--)
        {
            remainder += val[i];
            val[i] = remainder / _val;
            remainder %= _val;
            remainder *= kUIntLimit;
        }
        remainder += val[i];
        val[i] = remainder / _val;

        return  *this;
};

ExRange<int>&   ExRange<int>::operator%=(int _val)
{

};

ExRange<int>&   ExRange<int>::operator+=(int _val)
{
    size_t i = 0;

    int carry = 0;

    if (isNegative && _val > 0 || !isNegative && _val < 0)
    {
        if (_val < 0)
            _val *= -1;
        val.push_back(val[i] - _val);
        isNegative = isNegative;
        if (val[i] < val[i])
        {
            if (val.size() == 1)
            {
                val[i] *= -1;
                isNegative = !isNegative;
            }
            carry = -1;
        }
        for (i++; i < val.size() - 1; i++)
        {
            val.push_back(val[i] + carry); // -1 + 3 = 2 -> 1 - 3 = -2 // - | 2 | 3 + 5 ->  2 | 3 - 5 // 2 | 3 - 5 -> 2 |
            carry = 0;
            if (val[i] < val[i])
                carry = -1;
        }
        if (i == val.size() - 1)
        {
            val.push_back(val[i] + carry);
            if (val[i] == 0U)
                val.pop_back();
        }
    }
    else
    {
        if (_val != 0)
        {
            if (_val < 0)
                _val *= -1;
            val.push_back(val[i] + _val);
        }
        else
            return *this;
        if (val[i] > val[i])
            carry = 1;
        for (i++; i < val.size(); i++)
        {
            val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > val[i])
                carry = 1;
        }
        if (carry != 0)
            val.push_back(carry);
        isNegative = isNegative;
    }

    return *this;
};

ExRange<int>&   ExRange<int>::operator-=(int _val)
{
    size_t i = 0;

    int carry = 0;

    if (isNegative && _val > 0 || !isNegative && _val < 0)
    {
        if (_val < 0)
            _val *= -1;
        val.push_back(val[i] + _val);
        if (val[i] > val[i])
            carry = 1;
        for (i++; i < val.size(); i++)
        {
            val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] > val[i])
                carry = 1;
        }
        if (carry != 0)
            val.push_back(carry);
        isNegative = isNegative;
    }
    else
    {
        if (_val != 0)
        {
            if (_val < 0)
                _val *= -1;
            val.push_back(val[i] - _val);
        }
        else
            return *this;
        isNegative = isNegative;
        if (val[i] < val[i])
        {
            if (val.size() == 1)
            {
                val[i] *= -1;
                isNegative = !isNegative;
            }
            carry = -1;
        }
        for (i++; i < val.size(); i++)
        {
            val.push_back(val[i] + carry);
            carry = 0;
            if (val[i] < val[i])
                carry = -1;
        }
        if (i == val.size() - 1)
        {
            val.push_back(val[i] + carry);
            if (val[i] == 0U)
                val.pop_back();
            isNegative = isNegative;
        }
    }

    return *this;
};

ExRange<int>    ExRange<int>::operator&(const ExRange& _var) const
{
    ExRange<int> result;

    size_t i;

    for (i = 0; i < val.size() && i < _var.val.size(); i++)
        result.val.push_back(val[i] & _var.val[i]);

    return result;
};

string   ExRange<int>::decode(const ExRange<int>& _var)
{
    string resultStr;

    ExRange<int> quotient(_var);
    vector<int> remainders;

    size_t i = 0;

    unsigned int remainder = 0U;

    unsigned int tempVal;
    int digitNum = 0;

    if(_var.val.empty())
        return  "null";

    if (_var.isNegative)
        resultStr += '-';
    while (quotient > kValStrParseLimit)
        remainders.push_back(divideAndGetRemainder(quotient, kValStrParseLimit));
    remainders.push_back(quotient[0]);
    i = remainders.size() - 1;
    resultStr += uitos(remainders[remainders.size() - 1]);
    for (i = remainders.size() - 2; i > 0 && remainders.size() > 1; i--)
    {
        tempVal = remainders[i];
        digitNum = 0;
        while (tempVal != 0)
        {
            tempVal /= 10;
            digitNum++;
        }
        for (int i = 0; i < kValStrParseLimitDigitNum - digitNum; i++)
            resultStr += '0';
        if (remainders[i] != 0U)
            resultStr += uitos(remainders[i]);
    }
    if (i == 0)
    {
        tempVal = remainders[i];
        digitNum = 0;
        while (tempVal != 0)
        {
            tempVal /= 10;
            digitNum++;
        }
        for (int i = 0; i < kValStrParseLimitDigitNum - digitNum; i++)
            resultStr += '0';
        if (remainders[i] != 0)
            resultStr += uitos(remainders[i]);
    }

    return resultStr;
};

bool    ExRange<int>::operator==(const int& _val) const
{
    if (val.size() > 1)
        return false;
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (val[0] == _val)
                return true;
            return false;
        }
        else
        {
            if (val[0] == _val * -1)
                return true;
            return false;
        }
    }
    else
        return false;
};

bool    ExRange<int>::operator!=(const int& _val) const
{
    if (val.size() > 1)
        return true;
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (val[0] != _val)
                return true;
            return false;
        }
        else
        {
            if (val[0] != _val * -1)
                return true;
            return false;
        }
    }
    else
        return false;
};

bool    ExRange<int>::operator>(int _val) const
{
    if (val.size() > 1)
    {
        if (!isNegative)
            return true;
        else
            return false;
    }
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (_val < 0)
                return true;
            else if (val[0] > _val)
                return true;
            else
                return false;
        }
        else
        {
            if (_val > 0)
                return false;
            else
            {
                _val *= -1;
                if (val[0] < _val)
                    return true;
                else
                    return false;
            }
        }
    }

    return false;
};

bool    ExRange<int>::operator<(int _val) const
{
    if (val.size() > 1)
    {
        if (!isNegative)
            return false;
        else
            return true;
    }
    else if(val.size() == 1)
    {
        if (!isNegative)
        {
            if (_val < 0)
                return false;
            else if (val[0] < _val)
                return true;
            else
                return false;
        }
        else
        {
            if (_val > 0)
                return true;
            else
            {
                _val *= -1;
                if (val[0] > _val)
                    return true;
                else
                    return false;
            }
        }
    }

    return false;
};

bool    ExRange<int>::operator>=(int _val) const    // isNegative : true, val : 0 , isNegative : false, val : 0
{
    if (val.size() > 1)
    {
        if (!isNegative)
            return false;
        else
            return true;
    }
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (_val < 0)
                return true;
            else if (val[0] < _val)
                return false;
            else
                return true;
        }
        else
        {
            if (_val > 0)
                return false;
            else
            {
                _val *= -1;
                if (val[0] < _val)
                    return false;
                else
                    return true;
            }
        }
    }

    return false;
};

bool    ExRange<int>::operator<=(int _val) const
{
    if (val.size() > 1)
    {
        if (!isNegative)
            return false;
        else
            return true;
    }
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (_val < 0)
                return false;
            else if (val[0] > _val)
                return false;
            else
                return true;
        }
        else
        {
            if (_val > 0)
                return true;
            else
            {
                _val *= -1;
                if (val[0] > _val)
                    return false;
                else
                    return true;
            }
        }
    }
};

size_t  ExRangeRef<int>::getStartIndex()
{
    return  startIndex;
};

void    ExRangeRef<int>::setStartIndex(const size_t& index)
{
    startIndex = index;
};

size_t  ExRangeRef<int>::getEndIndex()
{
    return  endIndex;
};

void    ExRangeRef<int>::setEndIndex(const size_t& index)
{
    endIndex = index;
};

ExRange<int>    ExRangeRef<int>::operator+(const ExRangeRef<int> &_varRef)
{
    ExRange<int> result;

    size_t varSizeDiff = endIndex - startIndex;
    size_t _varSizeDiff = _varRef.endIndex - _varRef.startIndex;

    size_t i;

    int carry = 0;

    if (isNegative != _varRef.isNegative)
    {
        bool isValLarger;

        if (varSizeDiff > _varSizeDiff)
            isValLarger = true;
        else if (varSizeDiff < _varSizeDiff)
            isValLarger = false;
        else
        {
            for (i = varSizeDiff - 1; i > 0; i--)
            {
                if (valRef[startIndex + i] != _varRef.valRef[_varRef.startIndex + i])
                    break;
            }
            isValLarger = (valRef[startIndex + i] > _varRef.valRef[_varRef.startIndex + i]) ? true : false;
        }
        if (!isValLarger)
        {
            for (i = 0; i < varSizeDiff; i++)
            {
                result.pushBack(_varRef.valRef[startIndex + i] - valRef[_varRef.startIndex + i] + carry);
                carry = 0;
                if ((_varRef.valRef[_varRef.startIndex + i] < result[i] || valRef[startIndex + i] != 0U) && _varRef.valRef[_varRef.startIndex + i] <= result[i])
                    carry = -1;
            }
            for (; i < _varSizeDiff; i++)
            {
                result.pushBack(_varRef.valRef[_varRef.startIndex + i] + carry);
                carry = 0;
                if (_varRef.valRef[_varRef.startIndex + i] < result[i])
                    carry = -1;
            }
            if (_varRef.isNegative)
                result *= -1;
        }
        else
        {
            for (i = 0; i < _varSizeDiff; i++)
            {
                result.pushBack(valRef[startIndex + i] - _varRef.valRef[_varRef.startIndex + i] + carry); // 0 - 0 - 1 = kU-1 // 3 - kU-1 - 1 = 3 // 3 - 0 - 0 = 3
                carry = 0;
                if ((valRef[startIndex + i] < result[i] || _varRef.valRef[_varRef.startIndex + i] != 0U) && valRef[startIndex + i] <= result[i])
                    carry = -1;
            }
            for (; i < varSizeDiff; i++)
            {
                result.pushBack(valRef[startIndex + i] + carry);
                carry = 0;
                if (valRef[startIndex + i] < result[i])
                    carry = -1;
            }
            if (isNegative)
                result *= -1;
        }
        for (i = result.getSize() - 1; i > 0; i--)
        {
            if (result[i] == 0U)
            {
                result.popBack();
                continue;
            }
            break;
        }
    }
    else
    {
        for (i = 0; i < varSizeDiff && i < _varSizeDiff; i++)
        {
            result.pushBack(valRef[startIndex + i] + _varRef.valRef[_varRef.startIndex + i] + carry);
            carry = 0;
            if ((valRef[startIndex + i] > result[i] || _varRef.valRef[_varRef.startIndex + i] != 0U) && valRef[startIndex + i] >= result[i])
                carry = 1;
        }
        for (; i < varSizeDiff; i++)
        {
            result.pushBack(valRef[startIndex + i] + carry);
            carry = 0;
            if (valRef[startIndex + i] > result[i])
                carry = 1;
        }
        for (; i < _varSizeDiff; i++)
        {
            result.pushBack(_varRef.valRef[_varRef.startIndex + i] + carry);
            carry = 0;
            if (valRef[i] > result[i])
                carry = 1;
        }
        if (carry != 0)
            result.pushBack(carry);
        if (_varRef.isNegative)
            result *= -1;
    }

    return result;
};

ExRangeRef<int>&    ExRangeRef<int>::operator=(const ExRangeRef<int> &_varRef)
{
    valRef = _varRef.valRef;
    startIndex = _varRef.startIndex;
    endIndex = _varRef.endIndex;

    return *this;
};

ExRange<int>    ExRangeRef<int>::basicMultiply(const ExRangeRef& _varRef) const
{
    ExRange<int> result;

    size_t i = 0, j = 0;

    unsigned long long mul;
    unsigned int carry;

    try
    {
        if(valRef.empty() || _varRef.valRef.empty()))
            throw   string("There is null among operands.");
        if(startIndex >= valRef.size() || endIndex >= valRef.size() || _varRef.startIndex >= _varRef.valRef.size() || _varRef.endIndex >= _varRef.valRef.size())
            throw   string("Index out of range."); // 5 * 3 + 2 * 6 -> 15 + 12 ->
    }
    catch(const string& e)
    {
        cerr << e << '\n';
    }

    if (*this == 0 || _varRef == 0)
        return ExRange(0);
    result.isNegative = (_var < 0) ? !isNegative : isNegative;
    if (*this == 1 || _var == 1)
        return *this;
    else if (_var == -1 || *this == -1)
    {
        return !isNegative;
    }

    for (; i < valRef.size(); i++)
    {
        carry = 0U;
        for (j = 0; j < _var.val.size(); j++)
        {
            mul = (unsigned long long)val[i] * (unsigned long long)_var.val[j] + carry;
            carry = mul / kUIntLimit;
            mul %= kUIntLimit;
            if (i + j == result.val.size())
                result.val.push_back(0U);
            if (mul + result[i + j] >= kIntLimit)
            {
                carry++;
                result[i + j] = (mul + result[i + j]) - kUIntLimit;
            }
            else
                result[i + j] += mul;
        }
        if (carry != 0U)
            result.pushBack(carry);
    }

    return result;
};

bool    ExRangeRef<int>::operator==(const int& _var) const
{
    if (valRef.size() > 1)
        return false;
    else if (val.size() == 1)
    {
        if (!isNegative)
        {
            if (val[0] == _val)
                return true;
            return false;
        }
        else
        {
            if (val[0] == _val * -1)
                return true;
            return false;
        }
    }
    else
        return false;
};

bool    ExRangeRef<int>::operator==(const int& _val) const
{

};

bool    ExRangeRef<int>::operator!=(const int& _val) const
{

};

bool    ExRangeRef<int>::operator<(int _val) const
{

};

bool    ExRangeRef<int>::operator>(int _val) const
{

};

bool    ExRangeRef<int>::operator<=(int _val) const
{

};

bool    ExRangeRef<int>::operator>=(int _val) const
{

};

template<>
class ExRange<float>
{
};

template<>
class ExRangeRef<float>
{
};

template<>
class ExRange<double>
{
};

template<>
class ExRangeRef<double>
{
};