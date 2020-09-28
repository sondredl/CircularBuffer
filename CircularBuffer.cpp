#include <time.h>	
#include "Buff.h"

mutex writeLock;
mutex readLock;
condition_variable readCv;

// returns random lower case letter
char createRandomChar() {
	char ch = rand() % 29 + 97;
	return 'a';
}

// writes input to buffer
void writeConsoleToBuffer(Buff<char>* bufferPtr) {
	while (true) {
//		unique_lock<mutex> threadLock(writeLock);
		char ch;
		cin.get(ch);
		bufferPtr->writeToBuffer(ch); 
//		readCv.notify_all();
	}
}

// writes random to buffer
void writeRandomToBuffer(Buff<char>* bufferPtr){
	while(true){
		bufferPtr->writeToBuffer(createRandomChar());	
	}
}

// Writes Circular Buffer to console
void readBufferToConsole(Buff<char>* bufferPtr) 
{
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(200));
		char ch = bufferPtr->readFromBuffer();
		cout << ch << ' ';
	}
}		

int main()
{
	srand(time(NULL));
	Buff<char>* bufferPtr = new Buff<char> (10);

	thread writeRandom(writeRandomToBuffer, bufferPtr);
	thread writeInputToBuffer(writeConsoleToBuffer, bufferPtr);
	thread readBuffer(readBufferToConsole, bufferPtr);

	writeRandom.join();
	writeInputToBuffer.join();
	readBuffer.join();
}

