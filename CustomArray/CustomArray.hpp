#ifndef _CUSTOMARRAY_HPP_
#define _CUSTOMARRAY_HPP_
#include <iostream>
#include <Windows.h>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <span>
#include <utility>
#include <sstream>

class CustomArray final
{
public:
	explicit CustomArray(size_t size);
	explicit CustomArray(std::initializer_list<int> list);
	CustomArray(const CustomArray& originalArray);
	CustomArray& operator= (const CustomArray& rightArray);
	CustomArray(CustomArray&& original) noexcept;
	CustomArray& operator= (CustomArray&& rightArray) noexcept;
	~CustomArray();

	size_t size() const noexcept;
	std::string toString() const;

	bool operator==(const CustomArray& rightArray) const noexcept;
	int& operator[](size_t index);
	const int& operator[](size_t index) const;
	explicit operator bool() const noexcept;

	CustomArray& operator++();
	CustomArray operator++(int);
	CustomArray& operator+=(int value);

private:
	std::unique_ptr<int[]> ptr;
	size_t arrSize{ 0 };

	friend std::istream& operator>> (std::istream& in, CustomArray& obj);
	friend void swap(CustomArray& firstObj, CustomArray& secondObj) noexcept;
};

std::ostream& operator<<(std::ostream out, const CustomArray& obj);

#endif //!_CUSTOMARRAY_HPP_

