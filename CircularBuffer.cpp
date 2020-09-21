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

// reads value  from console or randomly generated
void writeConsoleToBuffer(Buff<char>* bufferPtr) {
	while (true) {
		if (bufferPtr->canWrite()) {
//			this_thread::sleep_for(chrono::milliseconds(200));
//			unique_lock<mutex> threadLock(writeLock);
			char ch;
			cin.get(ch);
			bufferPtr->writeToBuffer(ch); 
//			readCv.notify_all();

		}
	}
}

// reads value from Circular Buffer
void writeRandomToBuffer(Buff<char>* bufferPtr) 
{
	while (true) {
		if (bufferPtr->canWrite()) {
			bufferPtr->writeToBuffer(createRandomChar());
		}
	}
}

// Writes Circular Buffer to console
void readBufferToConsole(Buff<char>* bufferPtr) 
{
	while (true) {
		if (bufferPtr->canRead()) {
//			this_thread::sleep_for(chrono::milliseconds(200));
			char ch = bufferPtr->readFromBuffer();
			cout << ch << ' ';
		}
		
//		cout << "get write: " << bufferPtr->getWrite() << "  get read: " << bufferPtr->canRead() << endl;
	}
}

int main()
{
	srand(time(NULL));
	Buff<char> *buffer = new Buff<char> (10);
//	for(int i = 0; i < 10; i++) { cout << createRandomChar() << "\n"; }

	thread readConsole(writeConsoleToBuffer, buffer);
	thread readRB(writeRandomToBuffer, buffer);
	thread writeRandom(readBufferToConsole, buffer);

	readConsole.join();
	readRB.join();
	writeRandom.join();
}

