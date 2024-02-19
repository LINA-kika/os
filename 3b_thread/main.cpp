/*Разработайте программу, которая позволит изменять класс приоритета
процесса и приоритеты потоков этого процесса.*/
#include<Windows.h>
#include<iostream>


DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int param;
	param = *(int*)lpParameter;

	std::cout << "I am ThreadProc= " << param  << std::endl;

	while (TRUE)
	{
		std::cout << "ThreadProc " << param << " in while!" << std::endl;

		Sleep(35);

		std::cout << "ThreadProc " << param << " now awake!" << std::endl;
	}

}

int main(int argc, char* argv[]) {
	HANDLE mHandle[4];
	DWORD mArg[4], mId[4];
	int i;

	std::cout << "Process priority: " << GetPriorityClass(GetCurrentProcess()) << std::endl;
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	std::cout << "Process priority changed to: " << GetPriorityClass(GetCurrentProcess()) << std::endl;

	for (i = 0; i < 4; i++)

	{
		mArg[i] = i;
		mHandle[i] = CreateThread(NULL, 0, ThreadProc, mArg + i, 0, mId + i);
	}
	Sleep(200);
	for (int i = 0; i < 4; i++) {
		int priority = GetThreadPriority(mHandle[i]);
		std::cout << "Thread " << i << " priority: " << priority << std::endl;
	}
	std::cout << "PRIORITY CHANGED " << std::endl;
	SetThreadPriority(mHandle[3], THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(mHandle[2], THREAD_PRIORITY_ABOVE_NORMAL);
	SetThreadPriority(mHandle[0], THREAD_PRIORITY_BELOW_NORMAL);
	Sleep(200);
	for (int i = 0; i < 4; i++) {
		int priority = GetThreadPriority(mHandle[i]);
		std::cout << "Thread " << i << " priority: " << priority << std::endl;
	}
	std::cout << "3 THREAD BOOST DISABLED" << std::endl;
	SetThreadPriorityBoost(mHandle[3], TRUE);
	Sleep(200);
	std::cout << "3 THREAD BOOST IS WORKING AGAIN" << std::endl;
	SetThreadPriorityBoost(mHandle[3], FALSE);
	std::cout << "2 THREAD STOPPED" << std::endl;
	SuspendThread(mHandle[2]);
	Sleep(200);
	std::cout << "2 THREAD IS WORKING AGAIN	" << std::endl;
	ResumeThread(mHandle[2]);
	for (int i = 0; i < 4; i++) {
		CloseHandle(mHandle[i]);
	}
	std::cout << "ALL THREADS ARE CLOSED " << std::endl;
	Sleep(400);
	return 0;
}