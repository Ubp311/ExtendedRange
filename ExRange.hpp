#include    <iostream>
#include    <vector>
#include    <string>


using namespace std;

const unsigned long long  kUIntLimit = 4294967296ULL;
const unsigned int  kIntLimit = 2147483648U;
const unsigned int  kValStrParseLimit = 100000000U;
const unsigned int  kValStrParseLimitDigitNum = 8U;

const size_t  kKaratsubaLimit = 50;

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
size_t bitCeil(size_t operand, size_t div) // 3
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
class ExRange
{
};

template<>
class ExRange<unsigned int>
{
private:
    vector<unsigned int>    val;
public:
    ExRange() {};
    ExRange(unsigned int& _val)
    {
        val.push_back(_val);
    };
};



template<>
class ExRange<int>
{
private:
    vector<unsigned int>    val;
    bool    isNegative;
    
public:
    ExRange()
    {
        isNegative = false;
    };
    ExRange(int&& _val)
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
    ExRange(int& _val)
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
    ExRange(unsigned long long& _val)
    {
        val.push_back((unsigned int)_val);
        if(_val >= kUIntLimit)
            val.push_back(_val >> 32);
    };
    ExRange(const ExRange& _var)
    {
        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
        isNegative = _var.isNegative;
    };
    ExRange(const string& _valStr)
    {
        size_t  i = 0;
        size_t  j = 0;

        ExRange<int>    quotient;
        unsigned long long  partialQuotient = 0ULL;
        unsigned long long  tempPartialQuotient = 0ULL;
        unsigned long long  remainder = 0ULL;

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

    ExRange operator=(const ExRange& _var)
    {
        val.clear();

        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
        isNegative = _var.isNegative;

        return  *this;
    };
    ExRange operator=(const string& _valStr)
    {
        size_t  i = 0;
        size_t  j = 0;

        ExRange<int>    quotient;
        unsigned long long  partialQuotient = 0ULL;
        unsigned long long  tempPartialQuotient = 0ULL;
        unsigned long long  remainder = 0ULL;

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

        return  *this;
    };

    unsigned int&   operator[](size_t index)
    {
        return  val[index];
    };
    void    clear()
    {
        isNegative = false;
        val.clear();
    };
    bool    getNegativeSign()
    {
        return  isNegative;
    }
    size_t  getSize()
    {
        return  val.size();
    };
    void    pushBack(unsigned int& _val)
    {
        val.push_back(_val);
    };
    void    pushBack(unsigned int&& _val)
    {
        val.push_back(_val);
    };
    void    popBack()
    {
        val.pop_back();
    };
    ExRange operator*(int _val)
    {
        ExRange<int> result;

        size_t  i = 0;

        unsigned long long  mul;
        unsigned int    carry = 0U;
        unsigned int    tempVal = 0;

        result.isNegative = isNegative;
        if(_val == 0)
            return  ExRange(0);
        else if (_val < 0)
        {
            _val *= -1;
            result.isNegative = !isNegative;
        }
        if(_val == 1)
            return  *this;
        for (; i < val.size(); i++)
        {
            mul = (unsigned long long)val[i] * _val + carry;
            result.val.push_back(mul % kUIntLimit);
            carry = mul / kUIntLimit;
        }
        if (carry != 0U)
            result.val.push_back(carry);

        return  result;
    };

    ExRange operator/(int _val)
    {
        ExRange<int>    result;

        size_t  i = val.size() - 1;

        unsigned long long    remainder = 0ULL;

        result.isNegative = isNegative;
        try
        {
            if (_val == 0)
                throw   _val;
            else if (_val < 0)
            {
                _val *= -1;
                result.isNegative = !isNegative;
            }
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
        }
        
        result.val.resize(i + 1);
        for(; i > 0; i--)
        {
            remainder += val[i];
            result.val[i] = remainder / _val;
            remainder %= _val;
            remainder *= kUIntLimit;
        }
        remainder += val[i];
        result.val[i] = remainder / _val;
        i = result.val.size() - 1;
        if(result.val[i] == 0U && i != 0)
            result.val.pop_back();

        return  result;
    };

    ExRange operator%(int _val)
    {
        unsigned long long  remainder = 0ULL;

        return  ExRange<int>(remainder);
    };

    ExRange operator+(int _val)
    {
        ExRange<int>    result;

        size_t  i = 0;

        int carry = 0;

        if (isNegative && _val > 0 || !isNegative && _val < 0)
        {
            if(_val < 0)
                _val *= -1;
            result.val.push_back(val[i] - _val);
            result.isNegative = isNegative;
            if (val[i] < result.val[i])
            {
                if(val.size() == 1)
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
                if(result.val[i] == 0U)
                    result.val.pop_back();
            }
        }
        else
        {
            if (_val != 0)
            {
                if(_val < 0)
                    _val *= -1;
                result.val.push_back(val[i] + _val);
            }
            else
                return  *this;
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

        return  result;
    };
    ExRange operator-(int _val)
    {
        ExRange<int>    result;

        size_t  i = 0;

        int carry = 0;

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
                return  *this;
            result.isNegative = isNegative;
            if (val[i] < result.val[i])
            {
                if(val.size() == 1)
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
                if(result.val[i] == 0U)
                    result.val.pop_back();
                result.isNegative = isNegative;
            }
        }

        return  result;
    };
    ExRange operator*(ExRange& _var)
    {
        ExRange<int> result;
        ExRange<int> z[3];
        ExRange<int&> zRef0 = z[0], zRef1 = z[1];

        vector<size_t> sizes;

        size_t maxSize = (val.size() >= _var.getSize()) ? val.size() : _var.getSize();
        size_t expVal = bitCeil(maxSize, kKaratsubaLimit) - 1;
        size_t splitedMinSize = maxSize / (1 << expVal);
        size_t remainder = maxSize % (1 << expVal);
        size_t currentIndex = 0;
        size_t i = 0, j = 0;

        unsigned long long mul;
        unsigned int carry = 0U;

        if (_var == 0)
            return ExRange(0);
        result.isNegative = (_var < 0) ? !isNegative : isNegative;

        sizes.push_back(0);
        if (splitedMinSize == kKaratsubaLimit / 2 && remainder < (1 << expVal) / 2)
        {
            for (; i < remainder; i++)
            {
                sizes.push_back(kKaratsubaLimit / 2 + 1);
                sizes.push_back(kKaratsubaLimit / 2);
            }
            for (i = 0; i < (1 << expVal) / 2 - remainder; i++)
                sizes.push_back(kKaratsubaLimit);
        }
        else
        {
            for (; i < 1 << expVal; i++)
            {
                if (i % 2 == 0)
                    sizes.push_back(((i / 2 < remainder) ? splitedMinSize + 1 : splitedMinSize));
                else
                    sizes.push_back(((1 << expVal) / 2 + i / 2 < remainder) ? splitedMinSize + 1 : splitedMinSize);
            }
        }
        for (i = 1; i < sizes.size() / 2; i++)
        {
            z[0].clear();
            z[1].clear();
            z[2].clear();
            for (; j < sizes[i * 2]; j++)
            {
                carry = 0U;
                for (size_t k = 0; k < sizes[i * 2 - 1]; k++)
                {
                    mul = (unsigned long long)val[j] * (unsigned long long)_var.val[k] + carry;
                    carry = mul / kUIntLimit;
                    mul %= kUIntLimit;
                    if (j + k == z[0].getSize())
                        z[0].val.push_back(0U);
                    if (mul + z[0][j + k] >= kIntLimit)
                    {
                        carry++;
                        z[0][j + k] = (mul + z[0][j + k]) - kUIntLimit;
                    }
                    else
                        z[0][j + k] += mul;
                }
                if (carry != 0U)
                    result.val.push_back(carry);
            }
            for(j = 0; j < sizes[i * 2 + 1]; j++)
            {
                carry = 0U;
                for(size_t k = 0; k < sizes[i * 2]; k++)
                {
                    mul = (unsigned long long)val[j] * (unsigned long long)_var[k] + carry;
                    carry = mul / kUIntLimit;
                    mul %= kUIntLimit;
                    if (j + k == z[1].getSize())
                        z[1].val.push_back(0U);
                    if (mul + z[1][j + k] >= kIntLimit)
                    {
                        carry++;
                        z[1][j + k] = (mul + z[1].val[j + k]) - kUIntLimit;
                    }
                    else
                        z[1][j + k] += mul;
                }
            }
            zRef0 = zRef0.split(sizes[i * 2 - 1], sizes[i * 2]);
            zRef1 = zRef1.split(sizes[i * 2], sizes[i * 2 + 1]);
            z[2] = zRef0 + zRef1;
        }
        return  result;
    };
    ExRange operator/(const ExRange& _var)
    {
        ExRange<int>    result;

        return  result;
    };
    ExRange operator+(const ExRange& _var)
    {
        ExRange<int>    result;

        size_t  i;

        int carry = 0;

        if(isNegative != _var.isNegative)
        {
            bool    isValLarger;

            if(val.size() > _var.val.size())
                isValLarger = true;
            else if(val.size() < _var.val.size())
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
                for(; i < _var.val.size(); i++)
                {
                    result.val.push_back(_var.val[i] + carry);
                    carry = 0;
                    if(_var.val[i] < result.val[i])
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
                for(; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + carry);
                    carry = 0;
                    if(val[i] < result.val[i])
                        carry = -1;
                }
                result.isNegative = isNegative;
            }
            for(i = result.val.size() - 1; i > 0; i--)
            {
                if(result.val[i] == 0U)
                {
                    result.val.pop_back();
                    continue;
                }
                break;
            }
        }
        else
        {
            for(i = 0; i < val.size() && i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] + _var.val[i] + carry);
                carry = 0;
                if((val[i] > result.val[i] || _var.val[i] != 0U) && val[i] >= result.val[i])
                    carry = 1;
            }
            for(; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if(val[i] > result.val[i])
                    carry = 1;
            }
            for(; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0;
                if(_var.val[i] > result.val[i])
                    carry = 1;
            }
            if(carry != 0)
                result.val.push_back(carry);
            result.isNegative = isNegative;
        }

        return  result;
    };
    ExRange operator-(const ExRange& _var)
    {
        ExRange<int>    result;

        size_t  i;

        int carry = 0;

        if(isNegative != _var.isNegative)
        {
            for(i = 0; i < val.size() && i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] + _var.val[i] + carry);
                carry = 0;
                if((val[i] > result.val[i] || _var.val[i] != 0U) && val[i] >= result.val[i])
                    carry = 1;
            }
            for(; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if(val[i] > result.val[i])
                    carry = 1;
            }
            for(; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0;
                if(_var.val[i] > result.val[i])
                    carry = 1;
            }
            if(carry != 0)
                result.val.push_back(carry);
            result.isNegative;
        }
        else
        {
            bool    isValLarger;

            if(val.size() > _var.val.size())
                isValLarger = true;
            else if(val.size() < _var.val.size())
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
                for(; i < _var.val.size(); i++)
                {
                    result.val.push_back(_var.val[i] + carry);
                    carry = 0;
                    if(_var.val[i] < result.val[i])
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
                for(; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + carry);
                    carry = 0;
                    if(val[i] < result.val[i])
                        carry = -1;
                }
                result.isNegative = isNegative;
            }
            for(i = result.val.size() - 1; i > 0; i--)
            {
                if(result.val[i] == 0U)
                {
                    result.val.pop_back();
                    continue;
                }
                break;
            }
        }

        return  result;
    };
    static unsigned int   divideAndGetRemainder(ExRange<int>& var, const unsigned int& val)
    {
        size_t  i = var.getSize() - 1;

        unsigned long long  remainder = 0ULL;

        if(val == 0U)
            return  0U;
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

        return  (unsigned int)remainder;
    };

    static string   decode(const ExRange& _var)
    {
        string  resultStr;

        ExRange<int>    quotient(_var);
        vector<int> remainders;

        size_t  i = 0;

        unsigned int    remainder = 0U;

        unsigned int    tempVal;
        int digitNum = 0;

        if(_var.isNegative)
            resultStr += '-';
        while(quotient > kValStrParseLimit)
            remainders.push_back(divideAndGetRemainder(quotient, kValStrParseLimit));
        remainders.push_back(quotient[0]);
        i = remainders.size() - 1;
        resultStr += uitos(remainders[remainders.size() - 1]);
        for(i = remainders.size() - 2; i > 0 && remainders.size() > 1; i--)
        {
            tempVal = remainders[i];
            digitNum = 0;
            while(tempVal != 0)
            {
                tempVal /= 10;
                digitNum++;
            }
            for(int i = 0; i < kValStrParseLimitDigitNum - digitNum; i++)
                resultStr += '0';
            if(remainders[i] != 0U)
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

        return  resultStr;
    };
    
    ExRange&    operator*=(int _val)
    {
        size_t  i = 0;

        unsigned long long  mul;
        unsigned int    carry = 0U;
        unsigned int    tempVal = 0;

        isNegative = isNegative;
        if(_val == 0)
        {
            isNegative = false;
            val.clear();
        }
        else if (_val < 0)
        {
            _val *= -1;
            isNegative = !isNegative;
        }
        if(_val == 1)
            return  *this;
        for (; i < val.size(); i++)
        {
            mul = (unsigned long long)val[i] * _val + carry;
            val[i] = mul % kUIntLimit;
            carry = mul / kUIntLimit;
        }
        if (carry != 0U)
            val.push_back(carry);

        return  *this;
    };
    ExRange&    operator/=(int _val)
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
    ExRange&    operator%=(int _val)
    {

    };
    ExRange&    operator+=(int _val)
    {
        size_t  i = 0;

        int carry = 0;

        if (isNegative && _val > 0 || !isNegative && _val < 0)
        {
            if(_val < 0)
                _val *= -1;
            val.push_back(val[i] - _val);
            isNegative = isNegative;
            if (val[i] < val[i])
            {
                if(val.size() == 1)
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
                if(val[i] == 0U)
                    val.pop_back();
            }
        }
        else
        {
            if (_val != 0)
            {
                if(_val < 0)
                    _val *= -1;
                val.push_back(val[i] + _val);
            }
            else
                return  *this;
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

        return  *this;
    };
    ExRange&    operator-=(int _val)
    {
        size_t  i = 0;

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
                return  *this;
            isNegative = isNegative;
            if (val[i] < val[i])
            {
                if(val.size() == 1)
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
                if(val[i] == 0U)
                    val.pop_back();
                isNegative = isNegative;
            }
        }

        return  *this;
    };
    ExRange  operator&(const ExRange<int>& _var)
    {
        ExRange<int>    result;

        size_t  i;

        for(i = 0; i < val.size() && i < _var.val.size(); i++)
            result.val.push_back(val[i] & _var.val[i]);

        return  result;
    };

    bool    operator==(int _val)
    {
        if (val.size() > 1)
            return  false;
        else if (val.size() == 1)
        {
            if (!isNegative)
            {
                if (val[0] == _val)
                    return  true;
                return  false;
            }
            else
            {
                if (val[0] == _val * -1)
                    return  true;
                return  false;
            }
        }
        else
            return  false;
    };
    bool    operator!=(int _val)
    {
        if (val.size() > 1)
            return  true;
        else if (val.size() == 1)
        {
            if (!isNegative)
            {
                if (val[0] != _val)
                    return  true;
                return  false;
            }
            else
            {
                if (val[0] != _val * -1)
                    return  true;
                return  false;
            }
        }
        else
            return  false;
    };
    bool    operator>(int _val) const
    {
        if(val.size() > 1)
        {
            if(!isNegative)
                return  true;
            else
                return  false;
        }
        else if(val.size() == 1)
        {
            if(!isNegative)
            {
                if(_val < 0)
                    return  true;
                else if(val[0] <= _val)
                    return  false;
                else
                    return  true;
            }
            else
            {
                if(_val > 0)
                    return  false;
                else
                {
                    _val *= -1;
                    if(val[0] < _val)
                        return  true;
                    else
                        return  false;
                }
            }
        }

        return  false;
    };
    bool    operator<(int _val)
    {
        if(val.size() > 1)
        {
            if(!isNegative)
                return  false;
            else
                return  true;
        }
        else
        {

        }

        return  false;
    };

    bool    operator>=(const unsigned int& _val)
    {
        if(val.size() > 1)
            return  true;
        else
        {
            if(val[0] >= _val)
                return  true;
            else
                return  false;
        }
    };
    bool    operator>(const unsigned int& _val)
    {
        if(val.size() > 1)
            return  true;
        else
        {
            if(val[0] > _val)
                return  true;
            else
                return  false;
        }
    };
    ExRange operator<<(size_t val)
    {
    
    };

    ExRange operator>>(size_t val)
    {

    };

    ExRange operator<<(const ExRange<unsigned int>& val)
    {

    };
    ExRange operator>>(const ExRange<unsigned int>& val)
    {

    };
};

template<>
class ExRange<int&>
{
private:
    ExRange<int>    &valRef;
    size_t  startIndex, endIndex;
public:
    ExRange(ExRange<int>& _var) : valRef(_var) 
    {
        startIndex = 0;
        endIndex = 0;
    };
    ExRange(ExRange<int>& _var, size_t _startIndex, size_t _endIndex) : valRef(_var) 
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
    };
    ExRange<int> operator+(const ExRange<int&> _varRef)
    {
        ExRange<int>    result;

        size_t  varSizeDiff = endIndex - startIndex;
        size_t  _varSizeDiff = _varRef.endIndex - _varRef.startIndex;

        size_t  i; 

        int carry = 0;

        if(valRef.getNegativeSign() != _varRef.valRef.getNegativeSign())
        {
            bool    isValLarger;

            if(varSizeDiff > _varSizeDiff)
                isValLarger = true;
            else if(varSizeDiff < _varSizeDiff)
                isValLarger = false;
            else
            {
                for(i = varSizeDiff - 1; i > 0; i--)
                {
                    if(valRef[startIndex + i] != _varRef.valRef[_varRef.startIndex + i])
                        break;
                }
                isValLarger = (valRef[startIndex + i] > _varRef.valRef[_varRef.startIndex + i]) ? true : false;
            }
            if(!isValLarger)
            {
                for (i = 0; i <= varSizeDiff; i++)
                {
                    result.pushBack(_varRef.valRef[startIndex + i] - valRef[_varRef.startIndex + i] + carry);
                    carry = 0;
                    if ((_varRef.valRef[_varRef.startIndex + i] < result[i] || valRef[startIndex + i] != 0U) && _varRef.valRef[_varRef.startIndex + i] <= result[i])
                        carry = -1;
                }
                for(; i <= _varSizeDiff; i++)
                {
                    result.pushBack(_varRef.valRef[_varRef.startIndex + i] + carry);
                    carry = 0;
                    if(_varRef.valRef[_varRef.startIndex + i] < result[i])
                        carry = -1;
                }
                if(_varRef.valRef.getNegativeSign())
                    result *= -1;
            }
            else
            {
                for (i = 0; i <= _varSizeDiff; i++)
                {
                    result.pushBack(valRef[startIndex + i] - _varRef.valRef[_varRef.startIndex + i] + carry); // 0 - 0 - 1 = kU-1 // 3 - kU-1 - 1 = 3 // 3 - 0 - 0 = 3
                    carry = 0;
                    if ((valRef[startIndex + i] < result[i] || _varRef.valRef[_varRef.startIndex + i] != 0U) && valRef[startIndex + i] <= result[i])
                        carry = -1;
                }
                for(; i < varSizeDiff; i++)
                {
                    result.pushBack(valRef[startIndex + i] + carry);
                    carry = 0;
                    if(valRef[startIndex + i] < result[i])
                        carry = -1;
                }
                if(valRef.getNegativeSign())
                    result *= -1;
            }
            for(i = result.getSize() - 1; i > 0; i--)
            {
                if(result[i] == 0U)
                {
                    result.popBack();
                    continue;
                }
                break;
            }
        }
        else
        {
            for(i = 0; i < varSizeDiff && i < _varSizeDiff; i++)
            {
                result.pushBack(valRef[startIndex + i] + _varRef.valRef[_varRef.startIndex + i] + carry);
                carry = 0;
                if((valRef[startIndex + i] > result[i] || _varRef.valRef[_varRef.startIndex + i] != 0U) && valRef[startIndex + i] >= result[i])
                    carry = 1;
            }
            for(; i < varSizeDiff; i++)
            {
                result.pushBack(valRef[startIndex + i] + carry);
                carry = 0;
                if(valRef[startIndex + i] > result[i])
                    carry = 1;
            }
            for(; i < _varSizeDiff; i++)
            {
                result.pushBack(_varRef.valRef[_varRef.startIndex + i] + carry);
                carry = 0;
                if(valRef[i] > result[i])
                    carry = 1;
            }
            if(carry != 0)
                result.pushBack(carry);
            if(_varRef.valRef.getNegativeSign())
                result *= -1;
        }

        return  result;
    };
    ExRange&    operator=(const ExRange<int&>& _var)
    {
        valRef = _var.valRef;

        return  *this;
    };
    ExRange&    split(size_t startIndex, size_t endIndex)
    {
        startIndex = startIndex;
        endIndex = endIndex;

        return  *this;
    };
};

template<>
class ExRange<float>
{

};

template<>
class ExRange<double>
{
private:
    vector<double>  val;
public:
    ExRange()
    {

    };
    ExRange(int _val)
    {

    };
    ExRange(unsigned int _val);
    ExRange(float _val);
    ExRange(double _val);
    ExRange(const string& _valStr)
    {

    };
    ExRange(const ExRange& _var);
    ExRange(const ExRange&& _var);

    ExRange operator=(const ExRange& _var)
    {
        
    };
    ExRange operator*(const ExRange& _var)
    {

    };
    ExRange operator/(const ExRange& _var)
    {
        
    };
};