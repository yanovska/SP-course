#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <locale.h>


void create_dir() {
	char dir_name[MAX_PATH];
	printf("Input dir name or path:");
	scanf_s("%s", dir_name, MAX_PATH);
	if (CreateDirectoryA((LPCSTR)dir_name, NULL)) {
		printf("Directory was created\n");
	}
	else {
		printf("\n ****ERROR*****\n");
	}
}

void print_dir() {
	setlocale(LC_ALL, "Russian");
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;
	char szDirName[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szDirName);
	hFind = FindFirstFileA(strcat(szDirName, "\\*"), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("\n ****ERROR*****");
	}
	else {
		do {
			printf("\n");
			SYSTEMTIME systemTime;
			FileTimeToSystemTime(&FindFileData.ftCreationTime, &systemTime);
			printf("Name             %s\n", (char*)FindFileData.cFileName);
			printf("Creation time => %02d-%02d-%d %02d:%02d:%02d\n",
				systemTime.wMonth, systemTime.wDay, systemTime.wYear,
				systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
			printf("Size in bytes => %d\n", FindFileData.nFileSizeLow);
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
}

void file_info() {
	char file_path[MAX_PATH];
	BY_HANDLE_FILE_INFORMATION lpFileInformation;
	scanf_s("%s", file_path, MAX_PATH);
	HANDLE file = CreateFileA(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetFileInformationByHandle(file, &lpFileInformation)) {
		
		SYSTEMTIME systemTime;
		FileTimeToSystemTime(&(lpFileInformation.ftCreationTime), &systemTime);
		wprintf(L"Creation time: %02d-%02d-%d %02d:%02d:%02d\n",
			systemTime.wMonth, systemTime.wDay, systemTime.wYear,
			systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		FileTimeToSystemTime(&(lpFileInformation.ftLastAccessTime), &systemTime);
		wprintf(L"Size in bytes: %d\n", lpFileInformation.nFileSizeLow);
	}
	else {
		printf("\n ****ERROR*****");
	}
	CloseHandle(file);
}

void remove_file() {
	char file_path[MAX_PATH];
	printf("Input file path:");
	scanf_s("%s", file_path, MAX_PATH);
	if (DeleteFileA(file_path)) {
		printf("File was deleted\n");
	}
	else {
		printf("\n ****ERROR*****");
	}
}

void remove_dir() {
	char dir_path[MAX_PATH];
	printf("Input directory path:");
	scanf_s("%s", dir_path, MAX_PATH);
	if (RemoveDirectoryA(dir_path)) {
		printf("Directory was deleted\n");
	}
	else {
		printf("\n ****ERROR*****");
	}
}

void copy_file() {
	char file_path_e[MAX_PATH];
	char file_path_n[MAX_PATH];
	printf("Input path to existing file:");
	scanf_s("%s", file_path_e, MAX_PATH);
	printf("Input path to new file:");
	scanf_s("%s", file_path_n, MAX_PATH);
	if (CopyFileA((LPCSTR)file_path_e, (LPCSTR)file_path_n, FALSE)) {
		printf("File was copied\n");
	}
	else {
		printf("\n ****ERROR*****");
	}
}

void change_dir() {
	DWORD dwNumberOfChar;
	char szDirName[MAX_PATH];
	dwNumberOfChar = GetCurrentDirectoryA(MAX_PATH, szDirName);
	if (dwNumberOfChar != 0) {
		printf("Current directory name => %s\n", szDirName);
	}
	else {
		printf("\n ****ERROR*****");
	}
	DWORD dwNumberOfChar2;
	char dir_path[MAX_PATH];
	char szDirName2[MAX_PATH];
	printf("Input directory path:");
	scanf_s("%s", dir_path, MAX_PATH);
	if (SetCurrentDirectoryA((LPCSTR)dir_path))
	{
		dwNumberOfChar2 = GetCurrentDirectoryA(MAX_PATH, szDirName2);
		if (dwNumberOfChar2 != 0) {
			printf("Current directory name => %s\n", szDirName2);
		}
		else {
			printf("\n ****ERROR*****");
		}
	}
	else {
		printf("\n ****ERROR*****");
	}
}

void main(int argc, char* argv[])
{
	while (true) {
		printf("\n Directory             pwd \n");
		printf(" Change directory      cd      path \n");
		printf(" Create directory      mkdir   directory \n");
		printf(" Delete directory      rmd     path   \n");
		printf(" Information file      ls      file\n");
		printf(" Copy file             cp      file \n");
		printf(" Delete file           rmf     path   \n");
		
		char com[6];
		printf("Input command:");
		scanf_s("%s", com, 6);
		if (strcmp(com, "cd") == 0) {
			change_dir();
		}
		else if (strcmp(com, "pwd") == 0) {
			print_dir();
		}
		else if (strcmp(com, "cp") == 0) {
			copy_file();
		}
		else if (strcmp(com, "mkdir") == 0) {
			create_dir();
		}
		else if (strcmp(com, "rmd") == 0) {
			remove_dir();
		}
		else if (strcmp(com, "ls") == 0) {
			file_info();
		}
		else if (strcmp(com, "rmf") == 0) {
			remove_file();
		}
		else {
			printf("\n****Incorrect input****");
		}
	}
	exit(0);
}
