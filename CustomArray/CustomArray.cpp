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

CustomArray& CustomArray::operator=(const CustomArray& rightArray)
{
	CustomArray temp(rightArray);
	if (this != &rightArray) 
	{
		swap(*this, temp);
}
	return *this;
}

CustomArray::CustomArray(CustomArray&& original) noexcept
{
	this->arrSize = std::exchange(original.arrSize, 0);
	this->ptr = std::move(original.ptr);
}

CustomArray& CustomArray::operator=(CustomArray&& rightArray) noexcept
{
	if (this != &rightArray) {
		this->arrSize = std::exchange(rightArray.arrSize, 0);
		this->ptr = std::move(rightArray.ptr);
	}
	return *this;
}

CustomArray::~CustomArray()
{

}

size_t CustomArray::size() const noexcept
{
	return arrSize;
}

std::string CustomArray::toString() const
{
	const std::span<const int> arrayItems{ this->ptr.get(), this->arrSize };
	std::ostringstream output;
	for (size_t i = 0; const auto & item : arrayItems)
	{
		i++;
		output << item << (i < this->arrSize ? ", " : "";
	}
	return output.str();
}

bool CustomArray::operator==(const CustomArray& rightArray) const noexcept
{
		const std::span<const int> leftArr{ this->ptr.get(), this->arrSize };
		const std::span<const int> rightArr{ rightArray.ptr.get(), rightArray.arrSize };
		return std::equal(std::begin(leftArr), std::end(leftArr), std::begin(rightArr), std::end(rightArr));
}

CustomArray::operator bool() const noexcept
{
	return size() != 0;
}
