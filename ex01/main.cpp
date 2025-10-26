#include "Serializer.hpp"
#include <iostream>

class Data
{
private:
	int value;

public:
	void setValue(int val) { value = val; }
	int getValue() const { return value; }
};

int main()
{
	Data data;
	data.setValue(42);

	uintptr_t raw = Serializer::serialize(&data);

	Data* deserializedData = Serializer::deserialize(raw);

	if (deserializedData == &data)
		std::cout << "Deserialized value: " << deserializedData->getValue() << std::endl;
	else
		std::cout << "Deserialization failed!" << std::endl;

	return 0;
}
