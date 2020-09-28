//#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <time.h>
#include <condition_variable>
using namespace std;

template <typename T>
class Buff
{
public:
	Buff(int s);
	~Buff();
	T readFromBuffer();
	void writeToBuffer(char);
private:
	int nextIndex(int);
	bool canWrite();
	bool canRead();
	int getWrite();
	int getRead();
	void delay();
	void wait();
	T* buf;
	int posWrite;
	int posRead;
	int size;
};

template<typename T>
inline Buff<T>::Buff(int s)
{
	buf = new T[s];
	size = s;
	posRead = 0;
	posWrite = 0;
}

template<typename T>
inline Buff<T>::~Buff()
{
	delete buf;
}

template <typename T>
int Buff<T>::nextIndex(int i)
{
	return (i + 1) % size; // sirkulerer fra 1 til size
}

// check if buffer can write to current position
template<typename T>
inline bool Buff<T>::canWrite()
{
	return nextIndex(posWrite) == posRead;
}

// check if buffer can read from current position
template<typename T>
inline bool Buff<T>::canRead()
{
	return posWrite == posRead;
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

// returns content of buffer postion to be read
template<typename T>
inline T Buff<T>::readFromBuffer()
{
	T ch = buf[posRead];
	if(canRead()){
		return ch;
	}
}

template<typename T>
inline int Buff<T>::getWrite()
{
	return posWrite;
}

template<typename T>
inline int Buff<T>::getRead()
{
	return posRead;
}

template<typename T>
inline void Buff<T>::delay()
{
	this_thread::sleep_for(chrono::milliseconds(500));
}

template<typename T>
inline void Buff<T>::wait()
{
	while (cin);
}

