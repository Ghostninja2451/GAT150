#pragma once
#include<string>

namespace henry
{
	class Resource
	{
	public:
		virtual bool Load(const std::string& filename, void* data = nullptr) = 0;

	};

}