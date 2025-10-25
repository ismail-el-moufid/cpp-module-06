#include "ScalarConverter.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

int		toInt(const std::string &s)
{
	std::istringstream iss(s);
	int val;
	iss >> val;
	return val;
}

float	toFloat(const std::string &s)
{
	if (s == "nanf") return 0.0f/0.0f;
	if (s == "+inff") return 1.0f/0.0f;
	if (s == "-inff") return -1.0f/0.0f;

	std::istringstream iss(s);
	float val;
	iss >> val;
	return val;
}

double	toDouble(const std::string &s)
{
	std::istringstream iss(s);
	double val;
	iss >> val;
	return val;
}


bool	isChar(const std::string &literal)
{
	return (literal.length() == 1 && !std::isdigit(literal[0]));
}

bool	isInt(const std::string &literal)
{
    size_t i = 0;

    if (literal[i] == '-' || literal[i] == '+')
        i++;

    if (i == literal.length())
        return false;

    for (; i < literal.length(); i++)
        if (!std::isdigit(literal[i]))
            return false;

    return true;
}


bool	isFloat(const std::string &literal)
{
	bool	hasDecimalPoint = false;
	size_t	i = 0;

	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return (true);

	if (literal[i] == '-' || literal[i] == '+')
		i++;

	for (; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (hasDecimalPoint)
				return (false);
			hasDecimalPoint = true;
		}
		else if (literal[i] == 'f' && i == literal.length() - 1)
		{
			std::cout << hasDecimalPoint << std::endl;
			return (hasDecimalPoint);
		}
		else if (!std::isdigit(literal[i]))
			return (false);
	}
	return (false);
}

bool	isDouble(const std::string &literal)
{
	bool	hasDecimalPoint = false;
	size_t	i = 0;

	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return (true);

	if (literal[i] == '-' || literal[i] == '+')
		i++;

	for (; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (hasDecimalPoint)
				return (false);
			hasDecimalPoint = true;
		}
		else if (!std::isdigit(literal[i]))
			return (false);
	}

	return (hasDecimalPoint);
}

void	displayChar(double doubleValue)
{
	if (isnan(doubleValue) || isinf(doubleValue))
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}

	char c = static_cast<char>(doubleValue);

	if (c >= 32 && c <= 126)
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
}

void	displayInt(double doubleValue)
{
	if (isnan(doubleValue) || isinf(doubleValue) || doubleValue > std::numeric_limits<int>::max() || doubleValue < std::numeric_limits<int>::min())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(doubleValue) << std::endl;
}

void	displayFloat(double doubleValue)
{
	if (isnan(doubleValue))
		std::cout << "float: nanf" << std::endl;
	else if (isinf(doubleValue))
		std::cout << "float: " << (doubleValue > 0 ? "+inff" : "-inff") << std::endl;
	else
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(doubleValue) << "f" << std::endl;
}

void	displayDouble(double doubleValue)
{
	if (isnan(doubleValue))
		std::cout << "double: nan" << std::endl;
	else if (isinf(doubleValue))
		std::cout << "double: " << (doubleValue > 0 ? "+inf" : "-inf") << std::endl;
	else
		std::cout << "double: " << std::fixed << std::setprecision(1) << doubleValue << std::endl;
}

void	convertChar(const std::string &literal)
{
	double	doubleValue = static_cast<double>(literal[0]);

	displayChar(doubleValue);
	displayInt(doubleValue);
	displayFloat(doubleValue);
	displayDouble(doubleValue);
}

void	convertInt(const std::string &literal)
{
	double	doubleValue = static_cast<double>(toInt(literal));

	displayChar(doubleValue);
	displayInt(doubleValue);
	displayFloat(doubleValue);
	displayDouble(doubleValue);
}

void	convertFloat(const std::string &literal)
{
	double	doubleValue = static_cast<double>(toFloat(literal));

	displayChar(doubleValue);
	displayInt(doubleValue);
	displayFloat(doubleValue);
	displayDouble(doubleValue);
}

void	convertDouble(const std::string &literal)
{
	double	doubleValue = toDouble(literal);

	displayChar(doubleValue);
	displayInt(doubleValue);
	displayFloat(doubleValue);
	displayDouble(doubleValue);
}

struct		Handler
{
	bool	(*check)(const std::string &);
	void	(*convert)(const std::string &);
};

void	ScalarConverter::convert(const std::string &literal)
{
	const Handler handlers[] = {{isChar, convertChar}, {isInt, convertInt}, {isFloat, convertFloat}, {isDouble, convertDouble}};
	const size_t handlerCount = sizeof(handlers) / sizeof(handlers[0]);

	for (size_t i = 0; i < handlerCount; ++i)
		if (handlers[i].check(literal))
			handlers[i].convert(literal);
}