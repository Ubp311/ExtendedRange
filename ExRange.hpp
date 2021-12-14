#include    <vector>
#include    <string>


using namespace std;

const unsigned long long  kUIntLimit = 4294967296ULL;
const unsigned int  kIntLimit = 2147483648U;
const unsigned int  kValStrParseLimit = 100000000U;
const unsigned int  kValStrParseLimitDigitNum = 8U;

string  uitos(unsigned int val)
{
    string  resultStr;

    unsigned int tempVal = val;
    unsigned int mul = 1U;

    if (val == 0U)
        return  "0";
    while (tempVal != 0U)
    {
        tempVal /= 10U;
        mul *= 10U;
    }
    mul /= 10U;
    while (mul != 0U)
    {
        resultStr += val / mul + '0';
        val -= val / mul * mul;
        mul /= 10U;
    }
    
    return  resultStr;
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
    ExRange()
    {
        val = vector<unsigned int>();
    };
    ExRange(unsigned int _val)
    {
        val.push_back(_val);
    };
    ExRange(const ExRange<unsigned int>& _var)
    {
        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
    };
    ExRange(const ExRange<int>& _var)
    {
        
    };
};

template<>
class ExRange<int>
{
private:
    vector<unsigned int>    val;
public:
    ExRange()
    {
        val.clear();
    };
    ExRange(int _val)
    {
        val.clear();
        val.push_back(_val);
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

        int isNegative = 0;

        val.clear();

        if (!_valStr.empty())
        {
            if (_valStr[i] == '-')
            {
                sign = -1;
                isNegative = 1;
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
                size_t  tempSize;

                partialQuotient = quotient.val[quotient.val.size() - 1] / kUIntLimit;
                remainder = quotient.val[quotient.val.size() - 1] % kUIntLimit;
                quotient.val[quotient.val.size() - 1] = partialQuotient;
                if (partialQuotient == 0ULL)
                    quotient.val.pop_back();
                tempSize = quotient.val.size();
                for (size_t i = 0; i < tempSize; i++)
                {
                    remainder *= kValStrParseLimit;
                    remainder += quotient.val[tempSize - i - 1];
                    quotient.val[tempSize - i - 1] = remainder / kUIntLimit;
                    if (quotient.val[tempSize - i - 1] == 0U)
                        quotient.val.pop_back();
                    remainder %= kUIntLimit;
                }
                remainders.val.push_back(remainder);
                if (quotient.val.empty())
                    quotient.val.push_back(0U);
            }
            if (remainders.val.empty())
                remainders.val.push_back(0U);
            else
            {
                if (!isNegative)
                {
                    if (remainders.val[remainders.val.size() - 1] >= kIntLimit)
                        remainders.val.push_back(0U);
                }
                else
                {
                    if (remainders.val[remainders.val.size() - 1] > kIntLimit)
                    {
                        remainders.val[remainders.val.size() - 1] = remainders.val[remainders.val.size() - 1] - kIntLimit;
                        remainders.val.push_back(0U);
                    }
                    else
                        remainders.val[remainders.val.size() - 1] *= -1;
                }
            }

            val = remainders.val;
        }
    }

    ExRange(const ExRange& _var)
    {
        val.clear();

        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);
    };

    operator string()
    {
        
    };

    string decode(const ExRange& _var)
    {
        string  resultStr;

        size_t  i;

        const unsigned int base[2] = { kUIntLimit % kValStrParseLimit, kUIntLimit / kValStrParseLimit };
        ExRange<int>    mul(1);
        ExRange<int>    mulResult(0);
        ExRange<int>    result(0);

        bool    isOverflow = false;
        bool    isNegative = false;

        unsigned int    vals[2];

        if (val[val.size() - 1] == 0U && val.size() >= 2)
        {
            if (val[val.size() - 2] < kIntLimit)
            {
                isNegative = true;
                val[val.size() - 2] += kIntLimit;
            }
            isOverflow = true;
            val.pop_back();
        }
        else if (val[val.size() - 1] >= kIntLimit)
        {
            isNegative = true;
            val[val.size() - 1] *= -1;
        }
        for (i = 0; i < val.size(); i++)
        {
            mulResult.val.clear();
            vals[0] = val[i] % kValStrParseLimit;
            vals[1] = val[i] / kValStrParseLimit;
            for (size_t j = 0; j < mul.val.size(); j++)
            {
                unsigned long long  tempMul;
                unsigned int    carry = 0U;

                for (size_t k = 0; k < 2; k++)
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
                    result.val.push_back(carry);
            }
            for (size_t j = 0; j < mul.val.size(); j++)
            {
                unsigned long long  tempMul;
                unsigned int    carry = 0U;

                for (size_t k = 0; k < 2; k++)
                {
                    tempMul = (unsigned long long)mul.val[j] * (unsigned long long)base[k] + carry;
                    carry = tempMul / kValStrParseLimit;
                    tempMul %= kValStrParseLimit;
                    if (j + k >= mulResult.val.size())
                        mulResult.val.push_back(0U);
                    carry += ((unsigned long long)mulResult.val[j + k] + tempMul) / kValStrParseLimit;
                    mulResult.val[j + k] = ((unsigned long long)mulResult.val[j + k] + tempMul) % kValStrParseLimit;
                }
                if (carry != 0U)
                    mulResult.val.push_back(carry);
            }
            mul = mulResult;
        }
		for (; i > 0; i--)
		{
			if (result.val[i] != 0U)
				break;
			else
				result.val.pop_back();
		}
        if (isOverflow)
        {
            val.push_back(0U);
            if (isNegative)
                val[val.size() - 1] -= kIntLimit;
        }
        else if (isNegative)
        {
            val[val.size() - 1] *= -1;
            resultStr += '-';
        }
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
    }

    ExRange& operator=(const ExRange& _var)
    {
        val.clear();

        for (size_t i = 0; i < _var.val.size(); i++)
            val.push_back(_var.val[i]);

        return  *this;
    };

    ExRange& operator=(const string _valStr)
    {
        size_t  i = 0;
        size_t  j = 0;

        ExRange<int>    quotient, remainders;

        unsigned long long  partialQuotient;
        unsigned long long  tempPartialQuotient;
        unsigned long long  remainder;

        int sign = 1;
        bool    isNegative = 0;

        unsigned long long  mul;

        val.clear();

        if (!_valStr.empty())
        {
            if (_valStr[i] == '-')
            {
                sign = -1;
                isNegative = 1;
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
                size_t  tempSize;

                partialQuotient = quotient.val[quotient.val.size() - 1] / kUIntLimit;
                remainder = quotient.val[quotient.val.size() - 1] % kUIntLimit;
                quotient.val[quotient.val.size() - 1] = partialQuotient;
                if (partialQuotient == 0ULL)
                    quotient.val.pop_back();
                tempSize = quotient.val.size();
                for (size_t i = 0; i < tempSize; i++)
                {
                    remainder *= kValStrParseLimit;
                    remainder += quotient.val[tempSize - i - 1];
                    quotient.val[tempSize - i - 1] = remainder / kUIntLimit;
                    if (quotient.val[tempSize - i - 1] == 0U)
                        quotient.val.pop_back();
                    remainder %= kUIntLimit;
                }
                remainders.val.push_back(remainder);
                if (quotient.val.empty())
                    quotient.val.push_back(0U);
            }
            if (remainders.val.empty())
                remainders.val.push_back(0U);
            else
            {
                if (!isNegative)
                {
                    if (remainders.val[remainders.val.size() - 1] >= kIntLimit)
                        remainders.val.push_back(0U);
                }
                else
                {
                    if (remainders.val[remainders.val.size() - 1] > kIntLimit)
                    {
                        remainders.val[remainders.val.size() - 1] = remainders.val[remainders.val.size() - 1] - kIntLimit;
                        remainders.val.push_back(0U);
                    }
                    else
                        remainders.val[remainders.val.size() - 1] *= -1;
                }
            }

            val = remainders.val;
        }

        return  *this;
    };

    ExRange operator*(int _val)
    {
        ExRange result;

        size_t  i = 0;

        bool    valNegative = false;
        bool    isNegative = false;
        bool    isOverFlow = false;

        unsigned long long  mul;
        unsigned int    carry = 0U;
        unsigned int    tempVal = 0;

        if (_val < 0)
        {
            if (_val != kIntLimit)
                tempVal = _val * -1;
            else
                tempVal = _val;
            isNegative = true;
        }
        else
            tempVal = _val;
        if (val.size() > 1)
        {
            if (val[val.size() - 1] == 0)
            {
                if (val[val.size() - 2] < kIntLimit)
                {
                    val[val.size() - 2] += kIntLimit;
                    valNegative = true;
                    isNegative = !isNegative;
                }
                val.pop_back();
                isOverFlow = true;
            }
            else if (val[val.size() - 1] >= kIntLimit)
            {
                valNegative = true;
                isNegative = !isNegative;
                val[val.size() - 1] *= -1;
            }
            for (; i < val.size(); i++)
            {
                mul = (unsigned long long)val[i] * tempVal + carry;
                result.val.push_back(mul % kUIntLimit);
                carry = mul / kUIntLimit;
            }
            i--;
            if (carry != 0)
            {
                if (isNegative)
                    result.val.push_back(-1 * carry);
                else
                    result.val.push_back(carry);
            }
            else
            {
                if (result.val[i] >= kIntLimit)
                {
                    if (isNegative)
                    {
                        if (result.val[i] != kIntLimit)
                        {
                            result.val[i] -= kIntLimit;
                            result.val.push_back(0U);
                        }
                    }
                    else
                        result.val.push_back(0U);
                }
                else
                {
                    if (isNegative)
                        result.val[i] *= -1;
                }
            }
            if (isOverFlow)
            {
                val.push_back(0U);
                if (valNegative)
                    val[val.size() - 2] += kIntLimit;
            }
            else if (valNegative)
                val[val.size() - 1] *= -1;
        }
        else
        {
            if (val[i] >= kIntLimit)
            {
                val[i] *= -1;
                isNegative = !isNegative;
                valNegative = true;
            }
            mul = (unsigned long long)val[i] * tempVal;
            result.val.push_back(mul % kUIntLimit);
            if (mul / kUIntLimit != 0)
                result.val.push_back(mul / kUIntLimit);
            if (result.val[result.val.size() - 1] >= kIntLimit)
            {
                if (isNegative)
                {
                    if (result.val[result.val.size() - 1] != kIntLimit)
                    {
                        result.val[result.val.size() - 1] -= kIntLimit;
                        result.val.push_back(0U);
                    }
                }
                else
                    result.val.push_back(0U);
            }
            else
            {
                if (isNegative)
                    result.val[result.val.size() - 1] *= -1;
            }
            if (valNegative)
                val[i] *= -1;
        }

        return  result;
    };
    ExRange& operator/(int _val)
    {

    };
    ExRange& operator%(int _val)
    {

    };
    ExRange operator+(int _val)
    {
        ExRange result;

        size_t  i = 0;

        int carry = 0;

        bool    isNegative = false;
        bool    isOverflow = false;

        if (val.size() > 1)
        {
            int tempCarry = 0;

            if (val[val.size() - 1] == 0U)
            {
                if (val[val.size() - 2] < kIntLimit)
                {
                    val[val.size() - 2] += kIntLimit;
                    _val *= -1;
                    isNegative = true;
                }
                val.pop_back();
                isOverflow = true;
            }
            else if (val[val.size() - 1] >= kIntLimit)
            {
                val[val.size() - 1] *= -1;
                _val *= -1;
                isNegative = true;
            }
            if (_val > 0)
            {
                if (val[i] > val[i] + _val)
                    tempCarry = carry = 1;
            }
            else if (_val != kIntLimit)
            {
                if (val[i] < val[i] + _val)
                    tempCarry = carry = -1;
            }
            else
            {
                if (isNegative)
                {
                    if (val[i] >= kIntLimit)
                        tempCarry = carry = 1;

                }
                else
                {
                    if (val[i] < kIntLimit)
                        tempCarry = carry = -1;
                }
            }
            result.val.push_back(val[i] + _val);

            if (carry == 1)
            {
                for (++i; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + tempCarry);
                    tempCarry = 0;
                    if (result.val[i] == 0U)
                        tempCarry = carry;
                }
            }
            else if (carry == -1)
            {
                for (++i; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + tempCarry);
                    tempCarry = 0;
                    if (result.val[i] == -1)
                        tempCarry = carry;
                }
            }
            else
            {
                for (++i; i < val.size(); i++)
                    result.val.push_back(val[i]);
            }
            i--;
            if (tempCarry != 0)
            {
                if (isNegative)
                    tempCarry *= -1;
                result.val.push_back(tempCarry);
            }
            else
            {
                if (isNegative)
                {
                    if (result.val[i] > kIntLimit)
                    {
                        result.val[i] -= kIntLimit;
                        result.val.push_back(0U);
                    }
                    /*else if (result.val[i] == 0)
                    {
                        if (result.val[i - 1] >= kIntLimit)
                            result.val[i - 1] -= kIntLimit;
                        else
                        {
                            result.val[i - 1] *= -1;
                            result.val.pop_back();
                        }
                    }*/
                    else
                        result.val[i] *= -1;
                }
                else
                {
                    if (result.val[i] >= kIntLimit)
                        result.val.push_back(0U);
                    /*/else if (result.val[i] == 0U)
                    {
                        if (result.val[i - 1] < kIntLimit)
                            result.val.pop_back();
                    }*/
                }
            }
            if (isOverflow)
                val.push_back(0U);
            if (isNegative)
                val[val.size() - 2] -= kIntLimit;
        }
        else
        {
            result.val.push_back(val[i] + _val);
            if (val[i] >= kIntLimit)
            {
                if (_val < 0)
                {
                    if (result.val[i] == 0U && _val == kIntLimit)
                        result.val.push_back(-1);
                    else if (result.val[i] < kIntLimit)
                    {
                        result.val[i] = kIntLimit - result.val[i];
                        result.val.push_back(0U);
                    }
                }
            }
            else
            {
                if (_val > 0)
                {
                    if (result.val[i] >= kIntLimit)
                        result.val.push_back(0U);
                }
            }
        }

        return  result;
    };
    ExRange operator-(int _val)
    {
        ExRange result;

        size_t  i = 0;

        int carry = 0;

        bool    isNegative = false;
        bool    isOverflow = false;

        if (val.size() > 1)
        {
            int tempCarry = 0;

            if (val[val.size() - 1] == 0U)
            {
                if (val[val.size() - 2] < kIntLimit)
                {
                    val[val.size() - 2] += kIntLimit;
                    _val *= -1;
                    isNegative = true;
                }
                val.pop_back();
                isOverflow = true;
            }
            if (_val > 0)
            {
                if (val[i] < val[i] - _val)
                    tempCarry = carry = -1;
            }
            else if (_val != kIntLimit)
            {
                if (val[i] > val[i] - _val)
                    tempCarry = carry = 1;
            }
            else
                tempCarry = carry = isNegative ? -1 : 1;
            result.val.push_back(val[i] + _val);

            if (carry == 1)
            {
                for (++i; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + tempCarry);
                    tempCarry = 0;
                    if (result.val[i] == 0U)
                        tempCarry = carry;
                }
            }
            else if (carry == -1)
            {
                for (++i; i < val.size(); i++)
                {
                    result.val.push_back(val[i] + tempCarry);
                    tempCarry = 0;
                    if (result.val[i] == -1)
                        tempCarry = carry;
                }
            }
            else
            {
                for (++i; i < val.size(); i++)
                    result.val.push_back(val[i]);
            }
            i--;
            if (tempCarry != 0)
            {
                if (isNegative)
                    tempCarry *= -1;
                result.val.push_back(carry);
            }
            else
            {
                if (isNegative)
                {
                    if (result.val[i] > kIntLimit)
                    {
                        result.val[i] -= kIntLimit;
                        result.val.push_back(0U);
                    }
                    /*/else if (result.val[i] == 0U)
                    {
                        if (result.val[i - 2] >= kIntLimit)
                            result.val[i - 1] -= kIntLimit;
                        else if (result.val[i - 2] < kIntLimit)
                        {
                            result.val[i - 2] *= -1;
                            result.val.pop_back();
                        }
                    }*/
                    else
                        result.val[i - 1] -= kIntLimit;
                }
                else
                {
                    if (result.val[i - 1] >= kIntLimit)
                        result.val.push_back(0U);
                    /*else if (result.val[i - 1] == 0U)
                    {
                        if (result.val[i - 2] < kIntLimit)
                            result.val.pop_back();
                    }*/
                }
                if (isOverflow)
                    val.push_back(0U);
                if (isNegative)
                    val[val.size() - 2] -= kIntLimit;
            }
        }
        else
        {
            result.val.push_back(val[i] - _val);
            if (val[i] >= kIntLimit)
            {
                if (_val > 0)
                {
                    if (result.val[i] < kIntLimit)
                    {
                        result.val[i] = kIntLimit - result.val[i];
                        result.val.push_back(0U);
                    }
                }
            }
            else
            {
                if (_val < 0)
                {
                    if (result.val[i] >= kIntLimit)
                        result.val.push_back(0U);
                }
            }
        }

        return  result;
    };
    ExRange& operator*(const ExRange& _var);
    ExRange& operator/(const ExRange& _var);
    ExRange& operator%(const ExRange& _var);
    ExRange operator+(ExRange& _var)
    {
        ExRange<int>    result;

        size_t  i = 0;

        bool    isNegative = false;
        bool    varNegative = false, varOverflow = false;
        bool    _varNegative = false, _varOverflow = false;

        int carry = 0;

        if (val.size() > 1)
        {
            if (val[val.size() - 1] == 0U)
            {
                if (val[val.size() - 2] < kIntLimit)
                {
                    val[val.size() - 2] += kIntLimit;
                    varNegative = true;
                }
                val.pop_back();
                varOverflow = true;
            }
            else if (val[val.size() - 1] > kIntLimit)
            {
                val[val.size() - 1] *= -1;
                varNegative = true;
            }
        }
        else
        {
            if (val[i] >= kIntLimit)
            {
                val[i] *= -1;
                varNegative = true;
            }
        }
        if (_var.val.size() > 1)
        {
            if (_var.val[_var.val.size() - 1] == 0U)
            {
                if (_var.val[_var.val.size() - 2] < kIntLimit)
                {
                    _var.val[_var.val.size() - 2] += kIntLimit;
                    _varNegative = true;
                }
                _var.val.pop_back();
                _varOverflow = true;
            }
            else if (_var.val[_var.val.size() - 1] > kIntLimit)
            {
                _var.val[_var.val.size() - 1] *= -1;
                _varNegative = true;
            }
        }
        else
        {
            if (_var.val[i] >= kIntLimit)
            {
                _var.val[i] *= -1;
                _varNegative = true;
            }
        }

        if (varNegative != _varNegative)
        {
            int tempCarry;

            if (val.size() >= _var.val.size())
            {
                for (; i < val.size() && i < _var.val.size(); i++)
                {
                    result.val.push_back(val[i] - _var.val[i] + carry);
                    tempCarry = carry;
                    carry = 0;
                    if (val[i] <= val[i] - _var.val[i] + carry && _var.val[i] != 0U)
                        carry = -1;
                }
            }
            else
            {
                for (; i < val.size() && i < _var.val.size(); i++)
                {
                    result.val.push_back(_var.val[i] - val[i] + carry);
                    tempCarry = carry;
                    carry = 0;
                    if (_var.val[i] <= _var.val[i] - val[i] + carry && val[i] != 0U)
                        carry = -1;
                }
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                tempCarry = carry;
                carry = 0;
                if (val[i] < val[i] + carry)
                    carry = -1;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                tempCarry = carry;
                carry = 0;
                if (_var.val[i] < _var.val[i] + carry)
                    carry = -1;
            }
        }
        else
        {
            for (; i < val.size() && i < _var.val.size(); i++)
            {
                result.val.push_back(val[i] + _var.val[i] + carry);
                carry = 0;
                if (val[i] >= val[i] + _var.val[i] + carry && _var.val[i] != 0U)
                    carry = 1;
            }
            for (; i < val.size(); i++)
            {
                result.val.push_back(val[i] + carry);
                carry = 0;
                if (val[i] > val[i] + carry)
                    carry = 1;
            }
            for (; i < _var.val.size(); i++)
            {
                result.val.push_back(_var.val[i] + carry);
                carry = 0;
                if (_var.val[i] > _var.val[i] + carry)
                    carry = 1;
            }
            if (carry != 0)
                result.val.push_back(carry);
        }

        for (--i; i > 0; i--)
        {
            if (result.val[i] != 0U)
                break;
            result.val.pop_back();
        }
        i = result.val.size() - 1;
        if (val.size() >= _var.val.size())
            isNegative = varNegative;
        else
            isNegative = _varNegative;
        if (!isNegative)
        {
            if (result.val[i] >= kIntLimit && carry != -1)
                result.val.push_back(0U);
        }
        else
        {
            if (result.val[i] > kIntLimit && carry != -1)
            {
                result.val[i] -= kIntLimit;
                result.val.push_back(0U);
            }
            else
                result.val[i] *= -1;
        }
        if (varOverflow)
        {
            if (varNegative)
                val[val.size() - 1] -= kIntLimit;
            val.push_back(0U);
        }
        else if (varNegative)
            val[val.size() - 1] *= -1;
        if (_varOverflow)
        {
            if (_varNegative)
                _var.val[_var.val.size() - 1] -= kIntLimit;
            _var.val.push_back(0U);
        }
        else if (_varNegative)
            _var.val[_var.val.size() - 1] *= -1;

        return  result;
    };
    ExRange& operator-(const ExRange _var)
    {

    };

    bool    operator==(int _val)
    {
        if (val.size() > 1)
            return  false;
        else if (val[0] == _val)
            return  true;

        return  false;
    };
    bool    operator!=(int _val)
    {

        if (val.size() > 1)
            return  true;
        else if (val[0] != _val)
            return  true;

        return  false;
    };
    bool    operator>(unsigned int _val)
    {
        if (val.size() > 2)
            return  false;
        else if (val.size() == 2 && val[1] == 0U)
        {
            if (val[0] > _val)
                return  true;
        }

        return  false;
    };
    bool    operator==(const ExRange& _var)
    {
        if (val.size() != _var.val.size())
            return  false;
        else
        {
            for (size_t i = 0; i < val.size(); i++)
            {
                if (val[i] != _var.val[i])
                    return  false;
            }
        }

        return  true;
    };
    bool    operator!=(const ExRange& _var)
    {
        if (val.size() != _var.val.size())
            return  true;
        else
        {
            for (size_t i = 0; i < val.size(); i++)
            {
                if (val[i] != _var.val[i])
                    return   true;
            }
        }

        return  false;
    };
};