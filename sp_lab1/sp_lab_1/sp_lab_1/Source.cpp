#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <windows.h>

//C:\Users\алина\source\repos\sp_lab_1\sp_lab_1\Debug\sp_lab_1.exe -e
// C:\Users\алина\source\repos\sp_lab_1\Debug\sp_lab_1.exe -s
void generate_error() {
	setlocale(LC_ALL, "Russian");
	MEMORYSTATUS memory;
	GlobalMemoryStatus(&memory);
	HLOCAL alloc_memory = LocalAlloc(LPTR, memory.dwTotalVirtual * 1000);
	if (alloc_memory == NULL) {
		LPVOID e_mess;
		DWORD e_code = GetLastError();
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
			e_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& e_mess, 0, NULL);
		char* err_mess = (char*)e_mess;
		printf("ERROR was generated: failed with 0x%x code\n", e_code);
		wprintf(L"ERROR formatted message: %s\n", err_mess);
	}
}
void info_system()
{
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	printf("Hardware information: \n");
	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n",siSysInfo.dwNumberOfProcessors);
	printf("  Page size: %u\n", siSysInfo.dwPageSize);
	printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
	printf("  Minimum application address: %lx\n",siSysInfo.lpMinimumApplicationAddress);
	printf("  Maximum application address: %lx\n",siSysInfo.lpMaximumApplicationAddress);
	printf("  Active processor mask: %u\n",siSysInfo.dwActiveProcessorMask);
}

void main(int argc, char* argv[]) {
	if (argc != 2 || ((strcmp(argv[1], "-e") != 0) && (strcmp(argv[1], "-s"))) != 0)
	{
		printf("Select keys:\n");
		printf("-e  generate and output error\n");
		printf("-s  output system information\n");
	}
	else
	{
		if (strcmp(argv[1], "-e") == 0)
			generate_error();
		if (strcmp(argv[1], "-s") == 0)
			info_system();
	}

}



















