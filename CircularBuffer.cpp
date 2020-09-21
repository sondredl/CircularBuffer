#include <time.h>	
#include "Buff.h"


char createRandomChar();
void readInput(Buff<char>* bufferPtr, bool*) ;
void readFromBuffer(Buff<char>* bufferPtr, bool*);
void writeBufferToConsole(Buff<char>* bufferPtr, bool*);

int main()
{
	srand(time(NULL));
	Buff<char> *buffer = new Buff<char> (10);
//	for(int i = 0; i < 10; i++) { cout << createRandomChar() << "\n"; }
	bool running = true;

	thread readConsole(readInput, buffer, &running);
	thread readRB(readFromBuffer, buffer, &running);
	thread writeRandom(writeBufferToConsole, buffer, &running);

	readConsole.join();
	readRB.join();
	writeRandom.join();
}

// returns random lower case letter
char createRandomChar() {
	char ch = rand() % 26 + 97;
	return ch;
}

// reads value  from console
void readInput(Buff<char>* bufferPtr, bool* running) {
//	while (*running) {
		if (cin.get()) { cout << "cin = true\n"; bufferPtr->writeToBuffer(cin.get()); }
		else bufferPtr->writeToBuffer(createRandomChar());
//	}
}

// reads value from Circular Buffer
void readFromBuffer(Buff<char>* bufferPtr, bool* running) 
{
	while (*running) {
		bufferPtr->readFromBuffer();
	}
}

// Writes Circular Buffer to console
void writeBufferToConsole(Buff<char>* bufferPtr, bool* running) 
{
	while (*running) {
		bufferPtr->readFromBuffer();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}
