#pragma once
#include <iostream>

namespace scalar {

/*
Scalar holds the value and derivate of a variable in the system
*/

class Scalar 
{
	double m_value = 0.0;
	double m_derivative = 0.0;

public:

	Scalar() = default;
	Scalar(double value) : m_value(value) {};
	Scalar(double value, double deriv) : m_value(value), m_derivative(deriv) {};
	
	double value() const { return m_value; }
	void setValue(double value) { m_value = value; }

	double derivative() const { return m_derivative; }
	void setDerivative(double derivative) { m_derivative = derivative; }

	//Equality Operators
	Scalar& operator=(double value)
	{
		m_value = value;
		return *this;
	}

	bool operator==(const Scalar& rhs) const
	{
		return (m_value == rhs.value());
	}

	bool operator!=(const Scalar& rhs) const
	{
		return !(*this == rhs);
	}

	//Mathematical Operators
	Scalar operator+(Scalar rhs) const
	{
		rhs.m_value += m_value;

		return rhs;
	}

	Scalar& operator+=(const Scalar& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Scalar operator-(Scalar rhs) const
	{
		rhs.m_value = m_value - rhs.m_value;

		return rhs;
	}

	Scalar& operator-=(const Scalar& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Scalar operator*(double rhs) const
	{
		return { m_value * rhs };
	}

	friend Scalar operator*(double lhs, const Scalar& rhs)
	{
		return lhs * rhs;
	}

	Scalar& operator*=(double rhs)
	{
		m_value *= rhs;
		return *this;
	}

	Scalar operator/(double rhs) const
	{
		return  m_value / rhs ;
	}

	Scalar& operator/=(double rhs)
	{
		m_value /= rhs;
		return *this;
	}

	Scalar operator-() const
	{
		return *this * -1.0;
	}
};

} //namespace scalar