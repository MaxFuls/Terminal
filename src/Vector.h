#pragma once
#include "Terminal.h"
#include "LogicElement.h"
#include "Dialog.h"

namespace vector {

	template<class S>
	class Vector {

	private:

		int size;
		int capacity;
		S* arr;

	public:

		Vector() : size(0), capacity(5) {

			arr = new S[capacity];
		}
		Vector(int capacity) : size(0) {

			if (capacity <= 0)
				throw std::invalid_argument("Vector capacity need be positive");
			
			else {
				arr = new S[capacity]();
				this->capacity = capacity;
			}
		}
		Vector(const Vector& vector) {
			
			
		}
		~Vector() {

			delete[] arr;
		}

		void pushback(const S& value) {

			if (size < capacity) {
				*(arr + size) = value;
				++size;
			}
			else {

				S* tmp = new S[capacity * 2];
				copy(arr, tmp, capacity);
				capacity *= 2;
				delete[] arr;
				arr = tmp;
				*(arr + size) = value;
				++size;

			}
		}
		void copy(S* firstPtr, S* secondPtr, int capacity) {

			for (int i{ 0 }; i < capacity; ++i)
				*(secondPtr + i) = *(firstPtr + i);
		}
		void clear() {
			
			S* tmp = new S[5];
			delete[] arr;
			arr = tmp;
			capacity = 5;
			size = 0;
		
		}

		void setSize(int size) {
			
			if (size>0)
				this->size = size;
			else
				throw std::invalid_argument("Capacity need be positive");
		}

		int getSize() {

			return size;
		}
		int getCapacity() {

			return capacity;
		}

		Vector& operator= (const Vector& vect) {

			if (this != &vect) {
				S* tmp = new S[vect.capacity];
				copy(vect.arr, tmp, vect.capacity);
				delete[] arr;
				arr = tmp;
				capacity = vect.capacity;
				size = vect.size;
			}
			return *this;
		}
		S& operator[] (int index) {

			if (index < size && index >= 0)
				return *(arr + index);
			else
				throw std::invalid_argument("Incorrect index");
		}
	};

}