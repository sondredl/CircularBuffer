//#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <time.h>
using namespace std;

template <typename T>
class Buff
{
public:
	Buff(int s);
	~Buff();
	bool canWrite();
	bool canRead();
	void writeToBuffer(char);
	void readFromBuffer();
private:
	T* buf;
	int posWrite = 0;
	int posRead = 0;
	int size;
};

template<typename T>
inline Buff<T>::Buff(int s)
{
	buf = new T[s];
	size = s;
}

template<typename T>
inline Buff<T>::~Buff()
{
	delete buf[T];
}

// check if buffer can write to current position
template<typename T>
inline bool Buff<T>::canWrite()
{
	if (posRead <= posWrite) { return true; }
	return false;
}

// check if buffer can read from current position
template<typename T>
inline bool Buff<T>::canRead()
{
	if (posWrite != posRead) { return false; }
//	else return true;
}

// writes input to buffer
template<typename T>
inline void Buff<T>::writeToBuffer(char ch)
{
	if(canWrite()) { 
		buf[posWrite] = ch;
		if (posWrite == 10) { posWrite = 0; }
		else posWrite++;
	}
}

// prints buffer to console
template<typename T>
inline void Buff<T>::readFromBuffer()
{
	if (canRead()) {
		cout << buf[posRead];
		if (posRead == 10) { 
			cout << "\n";
			posRead = 0; }
		else posRead++;
	}
}

