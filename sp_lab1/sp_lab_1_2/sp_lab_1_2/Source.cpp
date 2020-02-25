#include <stdio.h>
#include <Windows.h>
#include <locale.h>

#define nNumberOfBytesToRead  2048

///C:\Users\алина\source\repos\sp_lab_1_2\Debug\sp_lab_1_2.exe -a C:\FF\ascii_file.txt C:\FF\out_filee.txt
//C:\Users\алина\source\repos\sp_lab_1_2\Debug\sp_lab_1_2.exe -u C:\FF\unicode_file.txt C:\FF\out_file.txt

void a_in_u(HANDLE ascii_file, HANDLE out_file) {
	BYTE lpBuffer[nNumberOfBytesToRead];
	DWORD lpNumberOfBytesRead;
	while (ReadFile(ascii_file, lpBuffer, nNumberOfBytesToRead, (LPDWORD)& lpNumberOfBytesRead, NULL))
	{
		if (lpNumberOfBytesRead == 0) {
			break;
		}
		else {
			int str_length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpBuffer, lpNumberOfBytesRead, NULL, 0);
			wchar_t* str = new wchar_t[str_length];
			MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpBuffer, lpNumberOfBytesRead, str, str_length);
			if (!WriteFile(out_file, str, str_length * sizeof(wchar_t), (LPDWORD)& lpNumberOfBytesRead, NULL)) {
				printf("\nError converting from ASCII!\n");
			}
		}
	}
	CloseHandle(ascii_file);
	CloseHandle(out_file);
}

void u_in_a(HANDLE unicode_file, HANDLE out_file) {
	setlocale(LC_ALL, "Russian");
	BYTE lpBuffer[nNumberOfBytesToRead];
	DWORD lpNumberOfBytesRead;
	while (ReadFile(unicode_file, lpBuffer, nNumberOfBytesToRead, (LPDWORD)& lpNumberOfBytesRead, NULL))
	{
		if (lpNumberOfBytesRead == 0) {
			break;
		}
		else {
			int u_str_length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpBuffer, lpNumberOfBytesRead, NULL, 0);
			wchar_t* u_str = new wchar_t[u_str_length];
			MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpBuffer, lpNumberOfBytesRead, u_str, u_str_length);
			int a_str_length = WideCharToMultiByte(CP_ACP, 0, u_str, u_str_length, NULL, 0, NULL, NULL);
			char* a_str = new char[a_str_length];
			WideCharToMultiByte(CP_ACP, 0, u_str, u_str_length, a_str, a_str_length, NULL, NULL);
			if (!WriteFile(out_file, a_str, a_str_length * sizeof(char), (LPDWORD)& lpNumberOfBytesRead, NULL)) {
				printf("\nError converting from UNICODE!\n");
			}
		}
	}
	CloseHandle(unicode_file);
	CloseHandle(out_file);
}
void main(int argc, char* argv[]) {
	if (argc != 4 || ((strcmp(argv[1], "-a") != 0) && (strcmp(argv[1], "-u")) != 0)) {
		printf("Arguments:\n");
		printf("-a keys from ASCII to UNICODE\n");
		printf("-u keys from UNICODE to ASCII\n");
		printf("Full path to FILE with text\n");
		printf("Full path to FILE with coding result\n");
	}

	HANDLE input_file = CreateFileA(argv[2], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE output_file = CreateFileA(argv[3], GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (input_file != INVALID_HANDLE_VALUE && output_file != INVALID_HANDLE_VALUE) {
		if (strcmp(argv[1], "-a") == 0)
			a_in_u(input_file, output_file);
		if (strcmp(argv[1], "-u") == 0) 
			u_in_a(input_file, output_file);
		printf("Operation completed successfully!");
	}
	else {
		setlocale(LC_ALL, "Russian");
		printf("Error!!!\n");
	}
}