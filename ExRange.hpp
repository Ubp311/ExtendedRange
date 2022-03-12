#include    <iostream>
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

    size_t  getSize()
    {
        return  val.size();
    };

    void    pushBack(unsigned int& _val)
    {
        val.push_back(_val);
    };

    void    popBack()
    {
        val.pop_back();
    }

    /*ExRange& split(size_t firstIndex, size_t lastIndex)
    {
        ExRange<int>    result;

        try
        {
            for (size_t i = firstIndex; i <= lastIndex; i++)
                result.val.push_back(val[i]);
            return  result;
        }
        catch (size_t index)
        {
            throw out_of_range("Error : Out of the range");  
        } 
    };*/

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
        ExRange<int>    result;
        ExRange<int>    z0, z1, z2;

        struct parsedStrs
        {
            size_t  startIndex, size;
            parsedStrs*   parent, *current, *prev;
            parsedStrs*   left;
            parsedStrs*   right;
            parsedStrs()
            {
                size = 0;
                startIndex = 0;
                parent = nullptr;
                prev = nullptr;
                left = nullptr;
                right = nullptr;
            };
            parsedStrs(const ExRange& _var)
            {
                size = _var.val.size();
                current = this;

                while(current != nullptr)
                {
                    if(prev == current->parent && size > 50)
                    {
                        prev = current;
                        left = new parsedStrs();
                        right = new parsedStrs();
                        left->parent = right->parent = current;
                        left->size = right->size = size / 2;
                        if(size % 2 == 1)
                            right->size++;
                        size /= 2;
                        current->startIndex = startIndex;
                        current = left;
                    }
                    else
                    {
                        if(prev == current->parent)
                        {
                            prev = current;
                            current->startIndex = startIndex;
                            startIndex += size;
                            current = current->parent;
                        }
                        else if(prev == current->left)
                        {
                            prev = current;
                            current = current->right;
                        }
                        else if(prev == current->right)
                        {
                            prev = current;
                            size = current->size;
                            current = current->parent;
                        }
                    }
                }
            };
            unsigned int&   operator[](size_t index)
            {
                
            };
            ~parsedStrs()
            {

            };
        };

        size_t  i, j;

        unsigned long long  mul;
        unsigned int    carry = 0U;

         if(_var == 0)
            return  ExRange(0);
        result.isNegative = (_var < 0) ? !isNegative : isNegative;
        if(val.size() > 50 && _var.val.size() > 50)
        {
            parsedStrs    a(*this), b(_var);
        }
        else
        {
            for (i = 0; i < val.size(); i++)
            {
                carry = 0U;

                for (j = 0; i < _var.val.size(); j++)
                {
                    mul = (unsigned long long)val[i] * (unsigned long long)_var.val[i] + carry;
                    carry = mul / kUIntLimit;
                    mul %= kUIntLimit;
                    if (i + j == result.val.size())
                        result.val.push_back(0U);
                    if (mul + result.val[i + j] >= kUIntLimit)
                    {
                        carry++;
                        result.val[i + j] = (mul + result.val[i + j]) - kUIntLimit;
                    }
                    else
                        result.val[i + j] += mul;
                }
                if (carry != 0U)
                    result.val.push_back(carry);
            }
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
    /*static string decode(const ExRange& _var)
    {
        string  resultStr;

        size_t  i, j, k;

        const unsigned int  base[2] = { kUIntLimit % kValStrParseLimit, kUIntLimit / kValStrParseLimit };
        ExRange<int>    mul(1);
        ExRange<int>    tempMul(0);
        ExRange<int>    result;

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
                carry = 0U;

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
                            if(j + k + 1 >= result.val.size())
                                result.val.push_back(1U);
                            else
                                result.val[j + k + 1]++;
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
    };*/
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

    ExRange  operator&(const ExRange<int>& _var)
    {
        ExRange<int>    result;

        size_t  i;

        for(i = 0; i < val.size() && i < _var.val.size(); i++)
            result.val.push_back(val[i] & _var.val[i]);

        return  result;
    };

    bool    operator==(int _val) const
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
    bool    operator!=(int _val) const
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
class ExRange<float>
{

};

template<>
class ExRange<double>
{

};