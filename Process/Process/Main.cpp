#include <windows.h>

int main()

{
	STARTUPINFO start = { sizeof(start) };

	PROCESS_INFORMATION procinfo;

	TCHAR CommandLine[] = TEXT("../Debug/Seconds/Seconds.exe");

	CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &start, &procinfo);

	return 0;
}