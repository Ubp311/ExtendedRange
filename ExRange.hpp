#include    <iostream>
#include    <vector>
#include    <string>


using namespace std;

const unsigned long long  kUIntLimit = 4294967296ULL;
const unsigned int  kIntLimit = 2147483648U;
const unsigned int  kValStrParseLimit = 100000000U;
const unsigned int  kValStrParseLimitDigitNum = 8U;

const size_t  kKaratsubaLimit = 5;

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

class InstanceManager
{
private:
    static InstanceManager*   instance;
    vector<void*>  instances;
    InstanceManager();
    ~InstanceManager();
public:
    static  InstanceManager& getInstance()
    {
        if(instance == nullptr)
            instance = new InstanceManager();
        return  *instance;
    };
    inline void    pushBackInstance(void* ptr)
    {
        instances.push_back(ptr);
    };
    inline void    popBackInstance()
    {
        instances.pop_back();
    };
    int    operator[](size_t index)
    {

    };
};

InstanceManager* InstanceManager::instance = nullptr;

namespace bigMath
{
    template <typename T>
    class ExRangeRef;

    template <typename T>
    class ExRange
    {
    };

    template <>
    class ExRange<unsigned int>
    {
    };

    template <>
    class ExRange<int>
    {
    private:
        vector<unsigned int> val;
        bool isNegative;
    public:
        ExRange();
        ExRange(const int &_val);
        ExRange(int &&_val);
        ExRange(const unsigned long long &_val);
        ExRange(unsigned long long &&_val);
        ExRange(const ExRange &_var);
        ExRange(const string &_varStr);

        friend istream &operator>>(istream &in, const ExRange &_var);
        friend ostream &operator<<(ostream &out, const ExRange &_var);
        ExRange operator=(const int &_val);
        ExRange operator=(const int &&_val);
        ExRange operator=(const long long &_val);
        ExRange operator=(const long long &&_val);
        ExRange operator=(const ExRange &_var);
        ExRange operator=(const string &_valStr);
        inline unsigned int &operator[](size_t index);

        void clear();
        bool getNegativeSign();
        bool &getNegativeSignRef();
        vector<unsigned int> &getValuesRef();
        inline size_t getSize();
        inline void pushBack(const unsigned int &_val);
        inline void pushBack(const unsigned int &&_val);
        inline void popBack();

        inline ExRange basicMultiply(const ExRange<int> &_var) const;
        static unsigned int divideAndGetRemainder(ExRange<int> &var, const unsigned int &val);

        ExRange operator*(int _val) const;
        ExRange operator/(int _val) const;
        ExRange operator%(int _val) const;
        ExRange operator+(int _val) const;
        ExRange operator-(int _val) const;
        friend const ExRange &operator*(const int &val, const ExRange &_var);
        friend const ExRange &operator/(const int &val, const ExRange &_var);
        friend const ExRange &operator%(const int &val, const ExRange &_var);
        friend const ExRange &operator+(const int &val, const ExRange &_var);
        friend const ExRange &operator-(const int &val, const ExRange &_var);
        ExRange operator*(ExRange &_var);
        ExRange operator/(ExRange &_var);
        ExRange operator%(ExRange &_var);
        ExRange operator+(const ExRange &_var) const;
        ExRange operator-(const ExRange &_var) const;
        ExRange &operator*=(int _val);
        ExRange &operator/=(int _val);
        ExRange &operator%=(int _val);
        ExRange &operator+=(int _val);
        ExRange &operator-=(int _val);
        ExRange &operator*=(ExRange &_var);
        ExRange &operator/=(ExRange &_var);
        ExRange &operator%=(ExRange &_var);
        ExRange &operator+=(ExRange &_var);
        ExRange &operator-=(ExRange &_var);
        ExRange operator&(const ExRange &_var) const;

        string decode(const ExRange &_var);

        bool operator==(const int &_val) const;
        bool operator!=(const int &_val) const;
        bool operator>(int _val) const;
        bool operator<(int _val) const;
        bool operator>=(int _val) const;
        bool operator<=(int _val) const;
        bool operator==(const ExRange &_var) const;
        bool operator!=(const ExRange &_var) const;
        bool operator>(const ExRange &_var) const;
        bool operator<(const ExRange &_var) const;
        bool operator>=(const ExRange &_var) const;
        bool operator<=(const ExRange &_var) const;

        friend class ExRangeRef<int>;
        friend class ExRange<unsigned int>;
        friend class ExRange<float>;
        friend class ExRange<double>;
    };

    template <typename T>
    class ExRangeRef
    {
    };

    template <>
    class ExRangeRef<int>
    {
    private:
        vector<unsigned int> &valRef;
        bool &isNegative;
        size_t startIndex, endIndex;

    public:
        ExRangeRef(ExRange<int> &_var) : valRef(_var.getValuesRef()), isNegative(_var.getNegativeSignRef())
        {
            startIndex = 0;
            endIndex = 0;
        };
        ExRangeRef(ExRange<int> &_var, const size_t &_startIndex, const size_t &_endIndex) : valRef(_var.getValuesRef()), isNegative(_var.getNegativeSignRef())
        {
            startIndex = _startIndex;
            endIndex = _endIndex;
        };
        inline size_t getStartIndex();
        inline void setStartIndex(const size_t &index);
        inline size_t getEndIndex();
        inline void setEndIndex(const size_t &index);
        inline size_t getSize();

        inline void pushBack(ExRange<int> &_var, size_t startIndex, size_t endIndex);
        inline void popBack();
        inline void clear();

        ExRangeRef &operator=(const ExRangeRef<int> &_var);

        ExRange<int> operator+(const ExRangeRef &_varRef);
        ExRangeRef<int> &operator+=(const ExRangeRef &_varRef);
        inline ExRange<int> basicMultiply(const ExRangeRef &_var);

        bool operator==(const int &_val) const;
        bool operator!=(const int &_val) const;
        bool operator>(int _val) const;
        bool operator<(int _val) const;
        bool operator>=(int _val) const;
        bool operator<=(int _val) const;
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

    ExRange<int>::ExRange(int &&_val)
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

    ExRange<int> ExRange<int>::operator=(const ExRange &_var)
    {
        val.clear();

        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
        isNegative = _var.isNegative;

        return *this;
    };

    ExRange<int> ExRange<int>::operator=(const string &_valStr)
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

    unsigned int &ExRange<int>::operator[](size_t index)
    {
        return val[index];
    };

    void ExRange<int>::clear()
    {
        isNegative = false;
        val.clear();
    };

    bool ExRange<int>::getNegativeSign()
    {
        return isNegative;
    };

    bool &ExRange<int>::getNegativeSignRef()
    {
        return isNegative;
    };

    vector<unsigned int> &ExRange<int>::getValuesRef()
    {
        return val;
    };

    size_t ExRange<int>::getSize()
    {
        return val.size();
    };

    void ExRange<int>::pushBack(const unsigned int &_val)
    {
        val.push_back(_val);
    };

    void ExRange<int>::pushBack(const unsigned int &&_val)
    {
        val.push_back(_val);
    };

    void ExRange<int>::popBack()
    {
        val.pop_back();
    };

    ExRange<int> ExRange<int>::basicMultiply(const ExRange<int> &_var) const
    {
        ExRange<int> result;

        size_t i = 0, j = 0;

        unsigned long long mul;
        unsigned int carry;

        try
        {
            if (val.empty() || _var.val.empty())
                throw string("There is null among operands.");
        }
        catch (const string &e)
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

    unsigned int ExRange<int>::divideAndGetRemainder(ExRange<int> &var, const unsigned int &val)
    {
        size_t i = var.getSize() - 1;

        unsigned long long remainder = 0ULL;

        try
        {
            if (var.val.empty())
                throw string("Operand is null value.");
            else if (val == 0U)
                throw val;
        }
        catch (const string &e)
        {
            cerr << e << '\n';
        }
        catch (const unsigned int &e)
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

    ExRange<int> ExRange<int>::operator*(int _val) const
    {
        ExRange<int> result;

        size_t i = 0;

        unsigned long long mul;
        unsigned int carry = 0U;
        unsigned int tempVal = 0;

        try
        {
            if (val.empty())
                throw "Operand is null value.";
        }
        catch (const string &e)
        {
            cerr << e << '\n';
        }

        result.isNegative = isNegative;
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

    ExRange<int> ExRange<int>::operator/(int _val) const
    {
        ExRange<int> result;

        size_t i = val.size() - 1;

        unsigned long long remainder = 0ULL;

        result.isNegative = isNegative;
        try
        {
            if (val.empty())
                throw string("Operand is null value.");
            if (_val == 0)
                throw _val;
            else if (_val < 0)
            {
                _val *= -1;
                result.isNegative = !isNegative;
            }
        }
        catch (const string &e)
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

    ExRange<int> ExRange<int>::operator%(const int _val) const {

    };

    ExRange<int> ExRange<int>::operator+(int _val) const
    {
        ExRange<int> result;

        size_t i = 0;

        int carry = 0;

        try
        {
            if (val.empty())
                throw string("There is null among operands.");
        }
        catch (const string &e)
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

    ExRange<int> ExRange<int>::operator-(int _val) const
    {
        ExRange<int> result;

        size_t i = 0;

        int carry = 0;

        try
        {
            if (val.empty())
                throw "There is null among operands.";
        }
        catch (const string &e)
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

    ExRange<int> ExRange<int>::operator*(ExRange<int> &_var)
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

        ExRange<int> result;
        ExRangeRef<int> resultRef = result;
        ExRange<int> z[3];
        ExRangeRef<int> zRef[3] = {z[0], z[1], z[2]};
        ExRangeRef<int> p[2] = {*this, *this};
        ExRangeRef<int> _p[2] = {_var, _var};

        size_t maxSize;
        size_t minSize;
        if (val.size() >= _var.getSize())
        {
            maxSize = val.size();
            minSize = _var.getSize();
        }
        else
        {
            maxSize = _var.getSize();
            minSize = val.size();
        }

        if (_var == 0)
            return ExRange(0);
        result.isNegative = (_var < 0) ? !isNegative : isNegative;
        if (_var == 1)
            return *this;
        else if (_var == -1)
        {
            result = *this;
            result.isNegative = _var.isNegative;

            return result;
        }

        if (val.size() > kKaratsubaLimit && _var.getSize() > kKaratsubaLimit)
        {
            bool maxIs_var = (maxSize == _var.getSize()) ? true : false;
            size_t expVal = bitCeil(maxSize, kKaratsubaLimit) - 1;
            size_t splitedMinSize = maxSize / (1 << expVal);
            size_t remainder = maxSize % (1 << expVal);
            size_t currentIndex = 0;
            size_t deltaSize;
            size_t i = 0, j = 0;

            if (splitedMinSize == kKaratsubaLimit / 2 && remainder < (1 << expVal) / 2)
            {
                for (i = 0; i < (1 << expVal) / 2 - remainder; i++)
                {
                    int tempI = i % 2;

                    p[tempI].setStartIndex(currentIndex - 1);
                    _p[tempI].setStartIndex(currentIndex - 1);
                    currentIndex += kKaratsubaLimit;
                    p[tempI].setEndIndex(currentIndex - 1);
                    _p[tempI].setEndIndex(currentIndex - 1);
                    z[tempI] = p[tempI].basicMultiply(_p[tempI]);
                    if (tempI == 1)
                    {
                        z[2] = (p[0] + p[1]).basicMultiply(_p[0] + _p[1]) - z[0] - z[1];
                        for (int i = 0; i < 3; i++)
                        {
                            zRef[i].setStartIndex(p[i].getStartIndex());
                            zRef[i].setEndIndex(p[i].getStartIndex() + zRef[i].getSize());
                            resultRef += zRef[i];
                        }
                    }
                }
                for (; i < (1 << expVal) / 2; i++)
                {
                    int tempI = i % 2;

                    p[tempI].setStartIndex(currentIndex - 1);
                    _p[tempI].setStartIndex(currentIndex - 1);
                    currentIndex += kKaratsubaLimit / 2 + 1;
                    p[tempI].setEndIndex(currentIndex - 1);
                    _p[tempI].setEndIndex(currentIndex - 1);
                    z[tempI] = p[tempI].basicMultiply(_p[tempI]);
                    if (tempI == 1)
                    {
                        z[2] = (p[0] + p[1]).basicMultiply(_p[0] + _p[1]) - z[0] - z[1];
                        for (int i = 0; i < 2; i++)
                        {
                            zRef[i].setStartIndex(p[i].getStartIndex());
                            zRef[i].setEndIndex(p[i].getStartIndex() + zRef[i].getSize());
                            resultRef += zRef[i];
                        }
                        zRef[i].setStartIndex(p[1].getEndIndex());
                        zRef[i].setEndIndex(p[1].getEndIndex() + zRef[2].getSize());
                        resultRef += zRef[2];
                    }
                }
                if (i % 2 == 1)
                {
                    z[2] = (p[0]).basicMultiply(_p[0]) - z[0];
                    for (int i = 0; i < 2; i++)
                    {
                        zRef[i].setStartIndex(p[i].getStartIndex());
                        zRef[i].setEndIndex(p[i].getStartIndex() + zRef[i].getSize());
                        resultRef += zRef[i];
                    }
                    zRef[i].setStartIndex(p[1].getEndIndex());
                    zRef[i].setEndIndex(p[1].getEndIndex() + zRef[2].getSize());
                    resultRef += zRef[2];
                }
            }
            else
            {
                for (; i < 1 << expVal; i++)
                {
                    if (i % 2 == 0)
                    {
                        p[i].setStartIndex(currentIndex);
                        _p[i].setStartIndex(currentIndex);
                        currentIndex += (i / 2 < remainder) ? splitedMinSize + 1 : splitedMinSize;
                        p[i].setEndIndex(currentIndex);
                        _p[i].setEndIndex(currentIndex);
                        z[i] = p[i].basicMultiply(_p[i]);
                    }
                    else
                    {
                        p[i].setStartIndex(currentIndex);
                        _p[i].setStartIndex(currentIndex);
                        currentIndex += ((1 << expVal) / 2 + i / 2 < remainder) ? splitedMinSize + 1 : splitedMinSize;
                        p[i].setEndIndex(currentIndex);
                        _p[i].setEndIndex(currentIndex);
                        z[i] = p[i].basicMultiply(_p[i]);
                        z[2] = (p[0] + p[1]).basicMultiply(_p[0] + _p[1]) - z[0] - z[1];
                        for (int i = 0; i < 2; i++)
                        {
                            zRef[i].setStartIndex(p[i].getStartIndex());
                            zRef[i].setEndIndex(p[i].getEndIndex() + zRef[i].getSize());
                            resultRef += zRef[i];
                        }
                        zRef[i].setStartIndex(p[1].getEndIndex());
                        zRef[i].setEndIndex(p[1].getEndIndex() + zRef[2].getSize());
                        resultRef += zRef[2];
                    }
                }
            }
            //----------------------------------------
        }
        else
            result = basicMultiply(_var);

        return result;
    };

    ExRange<int> ExRange<int>::operator/(ExRange<int> &_var)
    {
        ExRange<int> result;
        ExRangeRef<int> varRef = *this, _varRef = _var;

        result.isNegative = (!_var.isNegative) ? isNegative : !isNegative;

        try
        {
            if (_var == 0)
            {
                throw 0;
            }
        }
        catch (const int &e)
        {
            cerr << "Not divisible by " << e << '\n';
        }

        if (*this < _var)
            return 0;
        else if (*this == _var)
            return 1;
        else if (_var == 1 || _var == -1)
            return *this;

        return result;
    };

    ExRange<int> ExRange<int>::operator%(ExRange<int> &_var){

    };

    ExRange<int> ExRange<int>::operator+(const ExRange<int> &_var) const
    {
        ExRange<int> result;

        size_t i;

        unsigned int carry = 0U;

        if (isNegative != _var.isNegative)
        {
            if (val.size() > _var.val.size())
            {
                for (i = 0; i < _var.val.size(); i++)
                {
                    result.val.push_back(val[i] - _var.val[i] - carry); // 0 - 0 - 1 // 3 - kU-1 - 1 // 9 8 9 8 - 0 9 9 9 = 8 8 9 9
                    carry = 0U;
                    if (val[i] <= result.val[i] && _var.val[i] != 0U)
                        carry = 1U;
                }
                for (; i < val.size(); i++)
                {
                    result.val.push_back(val[i] - carry);
                    carry = 0U;
                    if (val[i] < result.val[i])
                        carry = 1U;
                }
                result.isNegative = _var.isNegative;
            }
            else if (val.size() < _var.val.size())
            {
                for (i = 0; i < val.size(); i++)
                {
                    result.val.push_back(_var.val[i] - val[i] - carry); // 0 - 0 - 1 = kU-1 // 3 - kU-1 - 1 = 3 // 3 - 0 - 0 = 3
                    carry = 0U;
                    if (_var.val[i] <= result.val[i] && val[i] != 0U)
                        carry = 1U;
                }
                for (; i < _var.val.size(); i++)
                {
                    result.val.push_back(_var.val[i] - carry);
                    carry = 0U;
                    if (_var.val[i] < result.val[i])
                        carry = 1U;
                }
                result.isNegative = isNegative;
            }
            else
            {
                size_t maxMatch = val.size() - 1;

                for (i = val.size() - 1; i > 0; i--)
                {
                    maxMatch = i;
                    if (val[i] != _var.val[i])
                        break;
                }
                if (val[i] > _var.val[i])
                {
                    for (i = 0; i <= maxMatch; i++)
                    {
                        result.val.push_back(val[i] - _var.val[i] - carry);
                        carry = 0U;
                        if (val[i] <= result.val[i] && _var.val[i] != 0U)
                            carry = 1U;
                    }
                }
                else
                {
                    for (i = 0; i <= maxMatch; i++)
                    {
                        result.val.push_back(_var.val[i] - val[i] - carry);
                        carry = 0U;
                        if (_var.val[i] <= result.val[i] && val[i] != 0U)
                            carry = 1U;
                    }
                }
            }
            if (result.val[--i] == 0U)
                result.val.pop_back();
        }
        else
        {
            for (i = 0; i < val.size() && i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] + _var.val[i] + carry);
                carry = 0U;
                if (val[i] >= result.val[i] && _var.val[i] != 0U)
                    carry = 1U;
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0U;
                if (val[i] > result.val[i])
                    carry = 1U;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0U;
                if (_var.val[i] > result.val[i])
                    carry = 1U;
            }
            if (carry != 0U)
                result.val.push_back(carry);
            result.isNegative = isNegative;
        }

        return result;
    };

    ExRange<int> ExRange<int>::operator-(const ExRange &_var) const
    {
        ExRange<int> result;

        size_t i;

        unsigned int carry = 0U;

        if (isNegative != _var.isNegative)
        {
            for (i = 0; i < val.size() && i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] + _var.val[i] + carry);
                carry = 0U;
                if (val[i] >= result.val[i] && _var.val[i] != 0U)
                    carry = 1U;
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0U;
                if (val[i] > result.val[i])
                    carry = 1U;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0U;
                if (_var.val[i] > result.val[i])
                    carry = 1U;
            }
            if (carry != 0U)
                result.val.push_back(carry);
            result.isNegative = isNegative;
        }
        else
        {
            if (val.size() > _var.val.size())
            {
                for (i = 0; i < _var.val.size(); i++)
                {
                    result.val.push_back(val[i] - _var.val[i] - carry);
                    carry = 0U;
                    if (val[i] <= result.val[i] && _var.val[i] != 0U)
                        carry = 1U;
                }
                for (; i < val.size(); i++)
                {
                    result.val.push_back(val[i] - carry);
                    carry = 0U;
                    if (val[i] < result.val[i])
                        carry = 1U;
                }
                result.isNegative = _var.isNegative;
            }
            else if (val.size() < _var.val.size())
            {
                for (i = 0; i < val.size(); i++)
                {
                    result.val.push_back(_var.val[i] - val[i] - carry);
                    carry = 0U;
                    if (_var.val[i] <= result.val[i] && val[i] != 0U)
                        carry = 1U;
                }
                for (; i < _var.val.size(); i++)
                {
                    result.val.push_back(_var.val[i] - carry);
                    carry = 0U;
                    if (_var.val[i] < result.val[i])
                        carry = 1U;
                }
                result.isNegative = isNegative;
            }
            else
            {
                size_t maxMatch = val.size() - 1;

                for (i = val.size() - 1; i > 0; i--)
                {
                    maxMatch = i;
                    if (val[i] != _var.val[i])
                        break;
                }
                if (val[i] > _var.val[i])
                {
                    for (i = 0; i <= maxMatch; i++)
                    {
                        result.val.push_back(val[i] - _var.val[i] - carry);
                        carry = 0U;
                        if (val[i] <= result.val[i] && _var.val[i] != 0U)
                            carry = 1U;
                    }
                }
                else
                {
                    for (i = 0; i <= maxMatch; i++)
                    {
                        result.val.push_back(_var.val[i] - val[i] - carry);
                        carry = 0U;
                        if (_var.val[i] <= result.val[i] && val[i] != 0U)
                            carry = 1U;
                    }
                }
            }
            if (result.val[--i] == 0U)
                result.val.pop_back();
        }

        return result;
    };

    ExRange<int> &ExRange<int>::operator*=(int _val)
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

    ExRange<int> &ExRange<int>::operator/=(int _val)
    {
        size_t i = val.size() - 1;

        unsigned long long remainder = 0ULL;

        try
        {
            if (_val == 0)
                throw _val;
            else if (_val < 0)
            {
                _val *= -1;
                isNegative = !isNegative;
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << endl;
        }

        if (val.size() > 1)
        {
            if (val[i] < _val)
            {
                remainder = val[i];
                remainder *= kUIntLimit;
                i--;
            }
        }
        for (; i > 0; i--)
        {
            remainder += val[i];
            val[i] = remainder / _val;
            remainder %= _val;
            remainder *= kUIntLimit;
        }
        remainder += val[i];
        val[i] = remainder / _val;

        return *this;
    };

    ExRange<int> &ExRange<int>::operator%=(int _val){

    };

    ExRange<int> &ExRange<int>::operator+=(int _val)
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

    ExRange<int> &ExRange<int>::operator-=(int _val)
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

    ExRange<int> ExRange<int>::operator&(const ExRange &_var) const
    {
        ExRange<int> result;

        size_t i;

        for (i = 0; i < val.size() && i < _var.val.size(); i++)
            result.val.push_back(val[i] & _var.val[i]);

        return result;
    };

    string ExRange<int>::decode(const ExRange<int> &_var)
    {
        string resultStr;

        ExRange<int> quotient(_var);
        vector<int> remainders;

        size_t i = 0;

        unsigned int remainder = 0U;

        unsigned int tempVal;
        int digitNum = 0;

        if (_var.val.empty())
            return "null";

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

    bool ExRange<int>::operator==(const int &_val) const
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

    bool ExRange<int>::operator!=(const int &_val) const
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

    bool ExRange<int>::operator>(int _val) const
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

    bool ExRange<int>::operator<(int _val) const
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

    bool ExRange<int>::operator>=(int _val) const // isNegative : true, val : 0 , isNegative : false, val : 0
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

    bool ExRange<int>::operator<=(int _val) const
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

    bool ExRange<int>::operator==(const ExRange<int> &_var) const
    {
        size_t i;

        if (val.size() != _var.val.size())
            return false;
        else
        {
            for (i = val.size() - 1; i > 0; i--)
            {
                if (val[i] != _var.val[i])
                    return false;
            }
            return true;
        }
    };

    bool ExRange<int>::operator<(const ExRange<int> &_var) const
    {
        size_t i;

        if (val.size() > _var.val.size())
            return false;
        else if (val.size() == _var.val.size())
        {
            for (i = val.size() - 1; i > 0; i--)
            {
                if (val[i] != _var.val[i])
                    break;
            }
            if (val[i] >= _var.val[i])
                return false;
            else
                return true;
        }
        else
            return true;
    };

    size_t ExRangeRef<int>::getStartIndex()
    {
        return startIndex;
    };

    void ExRangeRef<int>::setStartIndex(const size_t &index)
    {
        startIndex = index;
    };

    size_t ExRangeRef<int>::getEndIndex()
    {
        return endIndex;
    };

    void ExRangeRef<int>::setEndIndex(const size_t &index)
    {
        endIndex = index;
    };

    size_t ExRangeRef<int>::getSize()
    {
        return endIndex - startIndex;
    };

    void ExRangeRef<int>::pushBack(ExRange<int> &_var, size_t startIndex, size_t endIndex)
    {
        for (size_t i = startIndex; i <= endIndex; i++)
            valRef.push_back(_var[i]);
    };

    void ExRangeRef<int>::popBack()
    {
        valRef.pop_back();
    };

    void ExRangeRef<int>::clear()
    {
        valRef.clear();
    };

    ExRange<int> ExRangeRef<int>::operator+(const ExRangeRef<int> &_varRef)
    {
        ExRange<int> result;

        size_t i = endIndex, j = _varRef.endIndex;

        int carry = 0;

        if (isNegative != _varRef.isNegative)
        {
        }
        else
        {
        }

        return result;
    };

    ExRangeRef<int> &ExRangeRef<int>::operator+=(const ExRangeRef<int> &_varRef)
    {
        size_t i = startIndex, j = _varRef.startIndex;

        unsigned int carry = 0U;
        unsigned int tempVal;

        size_t maxIndex = (endIndex - startIndex > _varRef.endIndex - _varRef.startIndex) ? endIndex : _varRef.startIndex;
        for (; i <= maxIndex; i++, j++)
        {
            tempVal = valRef[i];
            valRef[i] += _varRef.valRef[j] + carry;
            carry = 0U;
            if (valRef[i] >= tempVal && _varRef.valRef[j] != 0U)
                carry = 1U;
        }

        return *this;
    };

    ExRangeRef<int> &ExRangeRef<int>::operator=(const ExRangeRef<int> &_varRef)
    {
        valRef = _varRef.valRef;
        startIndex = _varRef.startIndex;
        endIndex = _varRef.endIndex;

        return *this;
    };

    ExRange<int> ExRangeRef<int>::basicMultiply(const ExRangeRef &_varRef)
    {
        ExRange<int> result;

        size_t i = 0, j = 0;

        unsigned long long mul;
        unsigned int carry;

        try
        {
            if (valRef.empty() || _varRef.valRef.empty())
                throw string("There is null among operands.");
            if (startIndex >= valRef.size() || endIndex >= valRef.size() || _varRef.startIndex >= _varRef.valRef.size() || _varRef.endIndex >= _varRef.valRef.size())
                throw string("Index out of range."); // 5 * 3 + 2 * 6 -> 15 + 12 ->
        }
        catch (const string &e)
        {
            cerr << e << '\n';
        }

        if (*this == 0 || _varRef == 0)
            return ExRange<int>(0);
        result.getNegativeSignRef() = (_varRef < 0) ? !isNegative : isNegative;
        if (*this == 1 || _varRef == 1)
            return ExRange<int>(1);
        else if (_varRef == -1 || *this == -1)
            return !isNegative;
        for (i = startIndex; i < endIndex; i++)
        {
            carry = 0U;
            for (j = _varRef.startIndex; j < _varRef.endIndex; j++)
            {
                mul = (unsigned long long)valRef[i] * (unsigned long long)_varRef.valRef[j] + carry;
                carry = mul / kUIntLimit;
                mul %= kUIntLimit;
                if (i + j - startIndex - _varRef.startIndex == result.getSize())
                    result.pushBack(0U);
                if (mul + result[i + j - startIndex - _varRef.startIndex] >= kIntLimit)
                {
                    carry++;
                    result[i + j - startIndex - _varRef.startIndex] = (mul + result[i + j - startIndex - _varRef.startIndex]) - kUIntLimit;
                }
                else
                    result[i + j - startIndex - _varRef.startIndex] += mul;
            }
            if (carry != 0U)
                result.pushBack(carry);
        }

        return result;
    };

    bool ExRangeRef<int>::operator==(const int &_val) const
    {
        if (valRef.size() > 1)
            return false;
        else if (valRef.size() == 1)
        {
            if (!isNegative)
            {
                if (valRef[0] == _val)
                    return true;
                return false;
            }
            else
            {
                if (valRef[0] == _val * -1)
                    return true;
                return false;
            }
        }
        else
            return false;
    };

    bool ExRangeRef<int>::operator!=(const int &_val) const {

    };

    bool ExRangeRef<int>::operator<(int _val) const {

    };

    bool ExRangeRef<int>::operator>(int _val) const {

    };

    bool ExRangeRef<int>::operator<=(int _val) const {

    };

    bool ExRangeRef<int>::operator>=(int _val) const {

    };

    template <>
    class ExRange<float>
    {
    };

    template <>
    class ExRangeRef<float>
    {
    };

    template <>
    class ExRange<double>
    {
    private:
        vector<double> val;

    public:
        ExRange();
        ExRange(const ExRange &_var);
        ExRange(const string &_valStr);
        ~ExRange();
        ExRange &operator=(const ExRange &_var);
        ExRange &operator=(const string &_valStr);
        inline double &operator[](size_t index);

        inline vector<double> &getValuesRef()
        {
            return val;
        };
        ExRange &operator*(const int &_val);
        ExRange &operator/(const int &_val);
        ExRange &operator+(const int &_val);
        ExRange &operator-(const int &_val);
        ExRange &operator*(const ExRange<int> &_var);
        ExRange &operator/(const ExRange<int> &_var);
        ExRange &operator+(const ExRange<int> &_var);
        ExRange &operator-(const ExRange<int> &_var);
        ExRange &operator*(const ExRange<double> &_var);
        ExRange &operator/(const ExRange<double> &_var);
        ExRange &operator+(const ExRange<double> &_var);
        ExRange &operator-(const ExRange<double> &_var);
    };

    template <>
    class ExRangeRef<double>
    {
    private:
        vector<double> &valRef;
        size_t startIndex, endIndex;

    public:
        ExRangeRef(ExRange<double> &_var, const size_t &_startIndex, const size_t &_endIndex) : valRef(_var.getValuesRef())
        {
            startIndex = _startIndex;
            endIndex = _endIndex;
        };
    };
}