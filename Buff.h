#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

template <typename T>
class Buff
{
public:
	void randomThread();
	void inputThread();
	void twoThreads();
	void printBuffer();
private:
	char buf[10];
	char ch;
	int counter = 10;
};

// prints a random letter every .1 second to console
template<typename T>
inline void Buff<T>::randomThread()
{
	cout << "\t";
		char random;
		for (int i = 0 ; i < counter; i++) {
			random = rand() % 26 + 97;
			cout << random<< ' ';
			buf[i] = random;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		cout << endl;
}

// prints keyboard input to console
template<typename T>
inline void Buff<T>::inputThread()
{}

// creates two threads both printing to console
template<typename T>
inline void Buff<T>::twoThreads()
{}

// prints the circular buffer
template<typename T>
inline void Buff<T>::printBuffer()
{
	cout << "buf:\t";
	for (int i = 0; i < counter; i++) {
		cout << buf[i] << ' ';
	}
	cout << endl;
}

