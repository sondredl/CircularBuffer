#include <time.h>	
#include "Buff.h"

// returns random lower case letter
char createRandomChar() {
	char ch = rand() % 26 + 97;
	return ch;
}

// reads value  from console
void readInput(Buff<char>* bufferPtr) {
	if (cin.get()) { bufferPtr->writeToBuffer(cin.get()); }
	else bufferPtr->writeToBuffer(createRandomChar());
}

// reads value from Circular Buffer
void readFromBuffer(Buff<char>* bufferPtr) 
{
	bufferPtr->readFromBuffer();
}

// Writes Circular Buffer to console
void writeBufferToConsole(Buff<char>* bufferPtr) 
{
	bufferPtr->readFromBuffer();
	this_thread::sleep_for(chrono::milliseconds(100));
}

int main()
{
	srand(time(NULL));
	Buff<char> *buffer = new Buff<char> (10);

	thread readConsole(readInput, buffer);
	thread readRB(readFromBuffer, buffer);
	thread writeRandom(writeBufferToConsole, buffer);
	readConsole.join();
	readRB.join();
	writeRandom.join();
}

