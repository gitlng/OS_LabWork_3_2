#include <stdio.h>
#include <Windows.h>


DWORD WINAPI func1(LPVOID pVar) {
	long int* Var = (int*) pVar;  // new "var" is a copy of old "var" -> we will change new one
	int i = 0;

	for (i = 0; i < 100000000; i++) {
		(*Var)++;				// +1 to 'var' for 100000000 times
	}

	pVar = Var;					// and now old 'var' = new changed 'var' -> and this value is passed to the Thread
	return 0;
}

DWORD WINAPI func2(LPVOID pVar) {
	long int* Var = (int*) pVar;
	int i = 0;

	for (i = 0; i < 100000000; i++) {
		(*Var)--;				// -1 to 'var' for 100000000 times
	}

	pVar = Var;
	return 0;
}

int main() {
	int i;
	volatile long int var = 0;
	printf("\nVar = %d", var);

	HANDLE* handles_array[20];  // massive of threads

	for (i = 0; i < 10; i++) {
			if (handles_array[i] = CreateThread(NULL, // descriptor can't be inherited
												 0,    //  default size of stack
												 func1,	// the main func of the thread
												 &var,  // parameter for func1
												 NULL,  // flags of creation
												 NULL)) {  // id of thread (here is NO ID for the thread)
				printf("\nhandles_array[%d]  has created successfully.", i);
			}
			else{
				printf("\n\thandles_array[%d] ERROR.", i);
			}
		}

	for (i = 10; i < 20; i++) {
		if (handles_array[i] = CreateThread(NULL, 0, func2, &var, NULL, NULL)) {
			printf("\nhandles_array[%d] has created successfully.", i);
		}
		else {
			printf("\n\thandles_array[%d] ERROR.", i);
		}
	}

	WaitForMultipleObjects(20,				// count of threads
						   handles_array,   // the array of handles
						   TRUE,			// wait for ALL threads (not only for one)
						   INFINITE);		// wait INFINITE time

	printf("'\t\nNew var = %d", var);		// now var has changed

	return 0;
}
