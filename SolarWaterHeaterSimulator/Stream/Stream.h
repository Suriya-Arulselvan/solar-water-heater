#pragma once
#include <iostream>

namespace stream {

class Stream
{
	std::string m_name;
public:
	Stream() = default;

	Stream(const Stream&) = default;
	Stream(Stream&&) = default;

	Stream& operator=(const Stream&) = default;
	Stream& operator=(Stream&&) = default;

	~Stream() = default;

	Stream(const std::string& name) : m_name(name) {}
	Stream(std::string&& name) : m_name(std::move(name)) {}

	const std::string& name() const { return m_name; }
	void setName(const std::string& name) { m_name = name; }
	void setName(std::string&& name) { m_name = std::move(name); }
};

} //namespace stream
