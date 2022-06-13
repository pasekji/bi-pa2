#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

#define BASE 10

string intToStr(int number)
{
	stringstream ss;
	ss << number;
	string res;
	ss >> res;
	return res;
}

int myMax(int a, int b)
{
	return a < b ? b : a;
}

bool myIsDigit(char c)
{
	return c >= '0' && c <= '9';
}

int myDivide(int divisor, int dividor)
{
	if (divisor >= 0) return divisor / dividor;
	else
	{
		return -((-divisor + (dividor - 1)) / dividor);
	}
}

class CBigInt;
ostream& operator<<(ostream& os, const CBigInt& bigint);
CBigInt operator+(const CBigInt& first, const CBigInt& other);
CBigInt operator*(const CBigInt& first, const CBigInt& other);
bool operator>=(const CBigInt& first, const CBigInt& other);

class CBigInt
{
private:
	int getDigit(unsigned int i) const
	{
		if (digits.size() <= i)
			return 0;
		else
			return digits[i];
	}
public:
	int sign;
	vector<int> digits;
	// default constructor
	CBigInt() : sign(1) {}
	// copying/assignment/destruction
	// string constructor
	CBigInt(string strNumber) : sign(1)
	{
		size_t nZeros = 0;
		if (strNumber[0] == '-')
		{
			sign = -1;
			nZeros++;
		}
		if (strNumber.size() == nZeros)
			throw invalid_argument("Number cantains nothing or just sign.");
		while (nZeros < strNumber.size() && strNumber[nZeros] == '0')
			nZeros++;
		for (unsigned int i = 0; i < strNumber.size() - nZeros; i++)
		{
			char c = strNumber[strNumber.size() - 1 - i];
			if (!myIsDigit(c))
				throw invalid_argument("Number contains invalid character");
			digits.push_back(c - '0');
		}
	}
	CBigInt(const char* cStr) : CBigInt(string(cStr)) {}
	// int constructor
	CBigInt(int number) : CBigInt(intToStr(number)) {}
	CBigInt addAbsoluteValues(const CBigInt& other, int sign) const
	{
		CBigInt res;
		int newDigits = myMax(digits.size(), other.digits.size());
		int carry = 0;
		for (int i = 0; i < newDigits; i++)
		{
			int newDigit = getDigit(i) + sign * other.getDigit(i) + carry;
			carry = myDivide(newDigit, BASE);
			newDigit = (BASE + newDigit) % BASE;
			res.digits.push_back(newDigit);
		}
		if (carry)
			res.digits.push_back(carry);
		return res;
	}
	CBigInt abs() const
	{
		CBigInt res = *this;
		res.sign = 1;
		return res;
	}
	void removeZeros()
	{
		while (digits.back() == 0)
			digits.pop_back();
		if (digits.size() == 0)
			sign = 1;
	}
public:
	CBigInt multiplyByDigit(int multiplier, int shift) const
	{
		CBigInt res;
		for (int i = 0; i < shift; i++)
			res.digits.push_back(0);
		int carry = 0;
		for (int digit : digits)
		{
			int newDigit = digit * multiplier + carry;
			carry = newDigit / BASE;
			newDigit %= BASE;
			res.digits.push_back(newDigit);
		}
		if (carry)
			res.digits.push_back(carry);
		return res;
	}
public:
	// operator +=, any of {CBigInt/int/string}
	CBigInt& operator+=(const CBigInt& other)
	{
		*this = *this + other;
		return *this;
	}
	// operator *=, any of {CBigInt/int/string}
	CBigInt& operator*=(const CBigInt& other)
	{
		*this = *this * other;
		return *this;
	}
	// output operator <<
	// input operator >>
private:
	// todo
};

// operator +, any combination {CBigInt/int/string} + {CBigInt/int/string}
CBigInt operator+(const CBigInt& first, const CBigInt& other)
{
	if (first.sign == other.sign)
	{
		CBigInt res = first.addAbsoluteValues(other, 1);
		res.sign = first.sign;
		return res;
	}
	if (first.abs() >= other.abs())
	{
		CBigInt res = first.addAbsoluteValues(other, -1);
		res.sign = first.sign;
		res.removeZeros();
		return res;
	}
	else
	{
		CBigInt res = other.addAbsoluteValues(first, -1);
		res.sign = other.sign;
		res.removeZeros();
		return res;
	}
}

// operator *, any combination {CBigInt/int/string} * {CBigInt/int/string}
CBigInt operator*(const CBigInt& first, const CBigInt& other)
{
	CBigInt res;
	int shift = 0;
	for (int digit : other.digits)
	{
		res += first.multiplyByDigit(digit, shift);
		shift++;
	}
	res.sign = first.sign * other.sign;
	if (res.digits.size() == 0)
		res.sign = 1;
	return res;
}

// comparison operators, any combination {CBigInt/int/string} {<,<=,>,>=,==,!=} {CBigInt/int/string}
bool operator<(const CBigInt& first, const CBigInt& other)
{
	if (first.sign != other.sign) return first.sign == -1;
	if (first.digits.size() < other.digits.size()) return first.sign == 1;
	if (first.digits.size() > other.digits.size()) return first.sign == -1;

	for (unsigned int i = 0; i < first.digits.size(); i++)
	{
		int d1 = first.digits[first.digits.size() - 1 - i];
		int d2 = other.digits[first.digits.size() - 1 - i];
		if (d1 < d2) return first.sign == 1;
		if (d1 > d2) return first.sign == -1;
	}
	return false;
}
bool operator>(const CBigInt& first, const CBigInt& other)
{
	return other < first;
}
bool operator==(const CBigInt& first, const CBigInt& other)
{
	return !(first < other) && !(first > other);
}
bool operator!=(const CBigInt& first, const CBigInt& other)
{
	return !(first == other);
}
bool operator<=(const CBigInt& first, const CBigInt& other)
{
	return (first < other) || (first == other);
}
bool operator>=(const CBigInt& first, const CBigInt& other)
{
	return (first > other) || (first == other);
}

ostream& operator<<(ostream& os, const CBigInt& bigint)
{
	if (bigint.sign == -1)
		os << "-";
	for (unsigned int i = 0; i < bigint.digits.size(); i++)
		os << bigint.digits[bigint.digits.size() - 1 - i];
	if (bigint.digits.size() == 0)
		os << "0";
	return os;
}

istream& operator>>(istream& is, CBigInt& bigInt)
{
	stringstream ss;

	char c;
	while (isspace(is.peek()))
		c = is.get();
	if (is.peek() == '-')
	{
		is >> c;
		ss << c;
	}
	c = is.peek();
	if (!myIsDigit(c))
	{
		is.setstate(ios::failbit);
		return is;
	}
	while (myIsDigit(c))
	{
		is >> c;
		ss << c;
		c = is.peek();
	}
	string res;
	ss >> res;
	bigInt = CBigInt(res);
	return is;
}

#ifndef __PROGTEST__
static bool equal(const CBigInt& x, const char* val)
{
	ostringstream oss;
	oss << x;
	return oss.str() == val;
}
int main(void)
{
	CBigInt a, b;
	istringstream is;
	a = 10;
	a += 20;
	assert(equal(a, "30"));
	a *= 5;
	assert(equal(a, "150"));
	b = a + 3;
	assert(equal(b, "153"));
	b = a * 7;
	assert(equal(b, "1050"));
	assert(equal(a, "150"));

	a = 10;
	a += -20;
	assert(equal(a, "-10"));
	a *= 5;
	assert(equal(a, "-50"));
	b = a + 73;
	assert(equal(b, "23"));
	b = a * -7;
	assert(equal(b, "350"));
	assert(equal(a, "-50"));

	a = "12345678901234567890";
	a += "-99999999999999999999";
	assert(equal(a, "-87654321098765432109"));
	a *= "54321987654321987654";
	assert(equal(a, "-4761556948575111126880627366067073182286"));
	a *= 0;
	assert(equal(a, "0"));
	a = 10;
	b = a + "400";
	assert(equal(b, "410"));
	b = a * "15";
	assert(equal(b, "150"));
	assert(equal(a, "10"));

	is.clear();
	is.str(" 1234");
	assert(is >> b);
	assert(equal(b, "1234"));
	is.clear();
	is.str(" 12 34");
	assert(is >> b);
	assert(equal(b, "12"));
	is.clear();
	is.str("999z");
	assert(is >> b);
	assert(equal(b, "999"));
	is.clear();
	is.str("abcd");
	assert(!(is >> b));
	is.clear();
	is.str("- 758");
	assert(!(is >> b));
	a = 42;
	try
	{
		a = "-xyz";
		assert("missing an exception" == NULL);
	}
	catch (const invalid_argument& e)
	{
		assert(equal(a, "42"));
	}

	a = "73786976294838206464";
	assert(a < "1361129467683753853853498429727072845824");
	assert(a <= "1361129467683753853853498429727072845824");
	assert(!(a > "1361129467683753853853498429727072845824"));
	assert(!(a >= "1361129467683753853853498429727072845824"));
	assert(!(a == "1361129467683753853853498429727072845824"));
	assert(a != "1361129467683753853853498429727072845824");
	assert(!(a < "73786976294838206464"));
	assert(a <= "73786976294838206464");
	assert(!(a > "73786976294838206464"));
	assert(a >= "73786976294838206464");
	assert(a == "73786976294838206464");
	assert(!(a != "73786976294838206464"));
	assert(a < "73786976294838206465");
	assert(a <= "73786976294838206465");
	assert(!(a > "73786976294838206465"));
	assert(!(a >= "73786976294838206465"));
	assert(!(a == "73786976294838206465"));
	assert(a != "73786976294838206465");
	a = "2147483648";
	assert(!(a < -2147483647 - 1));
	assert(!(a <= -2147483647 - 1));
	assert(a > -2147483647 - 1);
	assert(a >= -2147483647 - 1);
	assert(!(a == -2147483647 - 1));
	assert(a != -2147483647 - 1);

	return 0;
}
#endif /* __PROGTEST__ */
