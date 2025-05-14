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
	std::copy(list.begin(), list.end(), this->ptr.get());
}

CustomArray::CustomArray(const CustomArray& originalArray)
{
	this->arrSize = originalArray.size();
	this->ptr = std::make_unique<int[]>(this->size());
	const std::span<const int>source{ originalArray.ptr.get(), originalArray.size() };
	std::copy(std::begin(source), std::end(source), this->ptr.get());
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

CustomArray::CustomArray(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		throw std::runtime_error("Невозможно открыть файл: " + filename);
	}

	size_t count = 0;
	int temp;
	while (in >> temp) ++count;

	if (!in.eof()) {
		throw std::runtime_error("Неверные данные в файле: " + filename);
	}

	in.clear();
	in.seekg(0);

	ptr = std::make_unique<int[]>(count);
	arrSize = count;
	for (size_t i = 0; i < arrSize; ++i) {
		if (!(in >> ptr[i])) {
			throw std::runtime_error("Ошибка чтения файла: " + filename);
		}
	}

	in >> std::ws;
	if (!in.eof()) {
		throw std::runtime_error("Лишние данные в файле: " + filename);
	}
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
		output << item << (i < this->arrSize ? ", " : "");
	}
	return output.str();
}

bool CustomArray::operator==(const CustomArray& rightArray) const noexcept
{
		const std::span<const int> leftArr{ this->ptr.get(), this->arrSize };
		const std::span<const int> rightArr{ rightArray.ptr.get(), rightArray.arrSize };
		return std::equal(std::begin(leftArr), std::end(leftArr), std::begin(rightArr), std::end(rightArr));
}

int& CustomArray::operator[](size_t index)
{
	if (index >= this->arrSize) {
		throw std::out_of_range("ERROR");
	}
	return this->ptr[index];
}

const int& CustomArray::operator[](size_t index) const
{
	if (index >= this->arrSize) {
		throw std::out_of_range("ERROR");
	}
	return this->ptr[index];
}

CustomArray::operator bool() const noexcept
{
	return size() != 0;
}

CustomArray& CustomArray::operator++()
{
	const std::span<int> items{ this->ptr.get(), this->arrSize };
	std::for_each(std::begin(items), std::end(items), [](auto& i) {++i;});
	return *this;
}

CustomArray CustomArray::operator++(int)
{
	CustomArray temp(*this);
	++(*this);
	return temp;
}

CustomArray& CustomArray::operator+=(int value)
{
	const std::span<int> items{ this->ptr.get(), this->arrSize };
	std::for_each(std::begin(items), std::end(items), [value](auto& i) {i+=value;});
	return *this;
}

void CustomArray::saveToFile(const std::string& filename) const {
	std::ofstream out(filename);
	if (!out) {
		throw std::runtime_error("Невозможно открыть файл для чтения: " + filename);
	}
	const std::span<const int> items{ ptr.get(), arrSize };
	for (size_t i = 0; i < arrSize; ++i) {
		out << items[i];
		if (i != arrSize - 1) {
			out << ' ';
		}
	}
}

void CustomArray::moveToFile(const std::string& filename) {
	saveToFile(filename);
	arrSize = 0;
	ptr = std::make_unique<int[]>(0);
}

void CustomArray::loadFromFile(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		throw std::runtime_error("Невозможно открыть файл: " + filename);
	}

	size_t count = 0;
	int temp;
	while (in >> temp) ++count;

	if (!in.eof()) {
		throw std::runtime_error("Неверные данные в файле: " + filename);
	}

	in.clear();
	in.seekg(0);

	ptr = std::make_unique<int[]>(count);
	arrSize = count;
	for (size_t i = 0; i < arrSize; ++i) {
		if (!(in >> ptr[i])) {
			throw std::runtime_error("Ошибка чтения файла: " + filename);
		}
	}

	in >> std::ws;
	if (!in.eof()) {
		throw std::runtime_error("Лишние данные в файле: " + filename);
	}
}

std::istream& operator>>(std::istream& in, CustomArray& obj)
{
	std::span<int> items(obj.ptr.get(), obj.arrSize);
	for (auto& i : items)
	{
		in >> i;
	}
	return in;
}

void swap(CustomArray& firstObj, CustomArray& secondObj) noexcept
{
	std::swap(firstObj.arrSize, secondObj.arrSize);
	firstObj.ptr.swap(secondObj.ptr);
}

std::ostream& operator<<(std::ostream& out, const CustomArray& obj)
{
	out << obj.toString();
	return out;
}