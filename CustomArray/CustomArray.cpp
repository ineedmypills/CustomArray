#include "CustomArray.hpp"

CustomArray::CustomArray(size_t size)
{
	this->arrSize = size;
	this->ptr = std::make_unique<int[]>(size);
}

CustomArray::CustomArray(std::initializer_list<int> list)
{
	this->arrSize = list.size();
	this->ptr = std::make_unique<int[]>(list.size());
	std::copy(list.begin, list.end, this->ptr.get());
}

CustomArray::CustomArray(const CustomArray& originalArray)
{
	this->arrSize = originalArray.size();
	this->ptr = std::make_unique<int[]>(this->size());
	const std::span<const int>source{ originalArray.ptr.get(), originalArray.size() };
	std::copy(std::begin(source), std::end(source), this->ptr.get())
}

size_t CustomArray::size() const noexcept
{
	return arrSize;
}
