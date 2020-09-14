#include <time.h>	
#include "Buff.h"

int main()
{
	srand(time(NULL));
	Buff<int> buffer;
	while(true) {
		buffer.randomThread();
		buffer.printBuffer();
		this_thread::sleep_for(chrono::seconds(2));
	}
}

