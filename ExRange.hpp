#include    <vector>
#include    <string>


using namespace std;

const unsigned long long  kUIntLimit = 4294967296ULL;
const unsigned int  kIntLimit = 2147483648U;
const unsigned int  kValStrParseLimit = 100000000U;
const unsigned int  kValStrParseLimitDigitNum = 8U;

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
}

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
        if (_val > 0)
        {
            val.push_back(_val);
            isNegative = true;
        }
        else
        {
            val.push_back(_val * -1);
            isNegative = false;
        }
    }
    ExRange(int& _val)
    {
        if (_val > 0)
        {
            val.push_back(_val);
            isNegative = true;
        }
        else
        {
            val.push_back(_val * -1);
            isNegative = false;
        }
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

        ExRange<int>    quotient, remainders;
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
                remainders.val.push_back(remainder);
                if (!quotient.val.empty() && quotient.val[quotient.val.size() - 1] == 0U)
                    quotient.val.pop_back();
                if (quotient.val.empty())
                    quotient.val.push_back(0U);
            }
            if (remainders.val.empty())
                remainders.val.push_back(0U);
            val = remainders.val;
        }
    };
    ExRange operator=(const ExRange& _var)
    {
        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
        isNegative = _var.isNegative;

        return  *this;
    };
    ExRange operator=(const string& _valStr)
    {
        size_t  i = 0;
        size_t  j = 0;

        ExRange<int>    quotient, remainders;
        unsigned long long  partialQuotient = 0ULL;
        unsigned long long  tempPartialQuotient = 0ULL;
        unsigned long long  remainder = 0ULL;

        int sign = 1;

        int mul = 1;

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
                remainders.val.push_back(remainder);
                if (!quotient.val.empty() && quotient.val[quotient.val.size() - 1] == 0U)
                    quotient.val.pop_back();
                if (quotient.val.empty())
                    quotient.val.push_back(0U);
            }
            if (remainders.val.empty())
                remainders.val.push_back(0U);
            val = remainders.val;
        }

        return  *this;
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

        size_t  i;

        unsigned long long    partialQuotient;
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
        catch(int expn)
        {
            cout << "Error : Cannot be divided by zero." << endl;
        }
        
        partialQuotient = val[val.size() - 1] / _val;
        if(partialQuotient != 0)
            result.val.resize(val.size());
        else
            result.val.resize(val.size() - 1);
        remainder = val[val.size() - 1] % _val;
        remainder *= kUIntLimit;
        for(i = result.val.size() - 1; i > 0; i--)
        {
            remainder += val[i];
            result.val[i] = remainder / _val;
            remainder %= _val;
            remainder *= kUIntLimit;
        }
        remainder += val[i];
        result.val[i] = remainder / _val;

        return  result;
    };

    ExRange operator%(int _val)
    {
        ExRange<int>    result;

        return  result;
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
            if (val[i] < result.val[i])
            {
                if(val.size() == 1)
                    result.val[i] *= -1;
                result.isNegative = !isNegative;
                carry = -1;
            }
            else
                result.isNegative = isNegative;
            for (i++; i < val.size() - 1; i++)
            {
                result.val.push_back(val[i] + carry); // -1 + 3 = 2 -> 1 - 3 = -2
                carry = 0;
                if (result.val[i] == 0U && val[i] != 0U)
                {
                    result.val[i] *= -1;
                    carry = -1;
                }
            }
            if (i == val.size() - 1)
            {
                result.val.push_back(val[i] + carry);
                result.isNegative = isNegative;
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
            if (val[i] > val[i] + _val)
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
            if (_val != 0 && _val != kIntLimit)
            {
                if (_val < 0)
                    _val *= -1;
                result.val.push_back(val[i] - _val);
            }
            else if (_val == kIntLimit)
                result.val.push_back(val[i] + _val);
            else if(_val == 0)
                return  *this;
            if (val[i] < result.val[i])
            {
                if(val.size() == 1)
                    result.val[i] *= -1;
                result.isNegative = !isNegative;
                carry = -1;
            }
            else
                result.isNegative = isNegative;
            for (i++; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if (val[i] > result.val[i])
                {
                    result.val[i] *= -1;
                    carry = -1;
                }
            }
            if (i == val.size() - 1)
            {
                result.val.push_back(val[i] + carry);
                result.isNegative = isNegative;
            }
        }

        return  result;
    };
    static string decode(const ExRange& _var)
    {
        string  resultStr;

        size_t  i, j, k;

        const unsigned int  base[2] = { kUIntLimit % kValStrParseLimit, kUIntLimit / kValStrParseLimit };
        ExRange<int>    mul(1);
        ExRange<int>    tempMul(0);
        ExRange<int>    result(0);

        unsigned int    vals[2];

        unsigned int    carry;

        for (i = 0; i < _var.val.size(); i++)
        {
            unsigned int    tempCarry = 0U;

            tempMul.val.clear();
            vals[0] = _var.val[i] % kValStrParseLimit;
            vals[1] = _var.val[i] / kValStrParseLimit;
            for (j = 0; j < mul.val.size(); j++)
            {
                unsigned long long  tempMul;
                carry = tempCarry;
                tempCarry = 0U;

                for (k = 0; k < 2; k++)
                {
                    tempMul = (unsigned long long)mul.val[j] * (unsigned long long)vals[k] + carry;
                    carry = tempMul / kValStrParseLimit;
                    tempMul %= kValStrParseLimit;
                    if (j + k >= result.val.size())
                        result.val.push_back(0U);
                    carry += ((unsigned long long)result.val[j + k] + tempMul) / kValStrParseLimit;
                    result.val[j + k] = ((unsigned long long)result.val[j + k] + tempMul) % kValStrParseLimit;
                }
                if (carry != 0U)
                {
                    if (j + k < result.val.size())
                    {
                        result.val[j + k] += carry;
                        if (result.val[j + k] >= kValStrParseLimit)
                        {
                            result.val[j + k] %= kValStrParseLimit;
                            tempCarry = 1U;
                        }
                    }
                    else
                        result.val.push_back(carry);
                }
            }
            for (j = 0; j < mul.val.size(); j++)
            {
                unsigned long long  result;
                carry = 0U;

                for (k = 0; k < 2; k++)
                {
                    result = (unsigned long long)mul.val[j] * (unsigned long long)base[k] + carry;
                    carry = result / kValStrParseLimit;
                    result %= kValStrParseLimit;
                    if (j + k >= tempMul.val.size())
                        tempMul.val.push_back(0U);
                    carry += ((unsigned long long)tempMul.val[j + k] + result) / kValStrParseLimit;
                    tempMul.val[j + k] = ((unsigned long long)tempMul.val[j + k] + result) % kValStrParseLimit;
                }
                if (carry != 0U)
                    tempMul.val.push_back(carry);
            }
            mul.val = tempMul.val;
        }
        for (i = result.val.size() - 1; i > 0; i--)
        {
            if (result.val[i] != 0U)
                break;
            else
                result.val.pop_back();
        }
        if (_var.isNegative && (_var.val.size() > 1 || _var.val[0] != 0U))
            resultStr += '-';
        i = result.val.size() - 1;
        int tempVal;
        int digitNum;
        resultStr += uitos(result.val[i]);
        if (i != 0)
        {
            for (i--; i > 0; i--)
            {
                tempVal = result.val[i];
                digitNum = 0;

                while (tempVal != 0)
                {
                    tempVal /= 10;
                    digitNum++;
                }
                for (int i = 0; i < kValStrParseLimitDigitNum - digitNum; i++)
                    resultStr += '0';
                resultStr += uitos(result.val[i]);
            }
            tempVal = result.val[i];
            digitNum = 0;

            while (tempVal != 0)
            {
                tempVal /= 10;
                digitNum++;
            }
            for (int i = 0; i < kValStrParseLimitDigitNum - digitNum; i++)
                resultStr += '0';
            resultStr += uitos(result.val[i]);
        }

        return  resultStr;
    };

    bool    operator==(int _val)
    {
        /*if (val.size() > 2)
            return  false;
        else if (val.size() == 2)
        {
            if (_val > 0)
            {
                if (val[1] == 0U && val[0] == _val)
                    return  true;
            }
            else if (_val < 0)
            {
                if (val[1] == -1 && val[0] == _val * -1)
                    return  true;
            }
            return  false;
        }
        else if (val.size() == 1 && _val == 0)
            return  true;
        else
            return  false;*/
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
        /*if (val.size() > 2)
            return  true;
        else if (val.size() == 2)
        {
            if (_val > 0)
            {
                if (val[1] != 0U || val[0] != _val)
                    return  true;
            }
            else if (_val < 0)
            {
                if (val[1] != -1 && val[0] != _val * -1)
                    return  true;
            }
            return  false;
        }
        else if (val.size() != 1 || _val != 0)
            return  true;
        else
            return  false;*/
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
};

template<>
class ExRange<double>
{

};