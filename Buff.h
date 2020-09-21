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
	T readFromBuffer();
	int getWrite();
	int getRead();
	void sleep();
	void wait();
private:
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
	delete buf[T];
}

// check if buffer can write to current position
template<typename T>
inline bool Buff<T>::canWrite()
{
	sleep();
	if (posRead <= posWrite) { return true; }
	return false;
}

// check if buffer can read from current position
template<typename T>
inline bool Buff<T>::canRead()
{
	sleep();
	if (posWrite >= posRead) { return true; }
	else return false;
}

// writes input to buffer
template<typename T>
inline void Buff<T>::writeToBuffer(char ch)
{
	sleep();
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
		if (posRead == 10) { 
			cout << "\n";
			posRead = 0; }
		else posRead++;
	return ch;
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
inline void Buff<T>::sleep()
{
	cout << "posWrite:" << posWrite << "  posRead: " << posRead << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
}

template<typename T>
inline void Buff<T>::wait()
{
	while (cin);
}

