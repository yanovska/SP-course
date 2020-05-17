#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <locale.h>
using namespace std;

const char FILE_NAME[] = "C:\\Users\\алина\\source\\repos\\sp_lab2.1\\new_file.txt";
//C:\Users\алина\source\repos\sp_lab2.1\Debug\sp_lab2.1.exe 3

 
void print_problems() {
	printf("\nSomething went wrong(\n");
	LPVOID e_mess;
	DWORD e_code = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		e_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& e_mess, 0, NULL);
	char* err_mess = (char*)e_mess;
	wprintf(L"ERROR was generated: failed with 0x%x code\n", e_code);
	wprintf(L"ERROR formatted message: %s\n", err_mess);
	exit(0);
}

struct RECORD {
	int record_number;
	FILETIME creation;
	char text[81];
	int counter;
};

struct HEADER {
	int not_empty_record_count;
	int file_size;
};

void incorrect_input() {
	printf("\n**************Error*********\n");
	printf("Only 1 arguments available:\n");
	printf("Number of records\n");
	exit(0);
}

void init_records(int init_num) {
	if (init_num > 0) {
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		RECORD r;
		SYSTEMTIME system_time, system_time2;
		FILETIME file_time;
		HEADER header_information;
		//init header
		header_information.not_empty_record_count = 0;
		header_information.file_size = sizeof(RECORD) * init_num + sizeof(header_information);
		//convert time
		GetLocalTime(&system_time);
		SystemTimeToFileTime(&system_time, &file_time);
		FileTimeToSystemTime(&file_time, &system_time2);
		//init records with empty & 0 values
		r.counter = 0; r.creation = file_time; strcpy(r.text, "");
		if (hFile != INVALID_HANDLE_VALUE) {
			//write header
			SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
			WriteFile(hFile, &header_information, sizeof(HEADER), NULL, NULL);
			//write records after header
			SetFilePointer(hFile, NULL, NULL, FILE_END);
			for (int i = 0; i < init_num; i++) {
				r.record_number = i;
				WriteFile(hFile, &r, sizeof(RECORD), NULL, NULL);
			}
			CloseHandle(hFile);
		}
		else {
			print_problems();
		}
	}
}

HEADER header_info(bool print) {
	HEADER header_information;
	DWORD bytes;
	HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		//read header info & put it into structure
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		ReadFile(hFile, &header_information, sizeof(HEADER), &bytes, NULL);
		CloseHandle(hFile);
		if (print) { //print info if it is needed
			printf("Header information\n");
			printf("File size in bytes: %d\nNot empty record count: %d\n",
				header_information.file_size, header_information.not_empty_record_count);
		}
		return header_information;
	}
	else {
		print_problems();
	}
}

vector<RECORD> records_info(int count, bool print) {
	//dynamic array of records
	//The vector is a container that organizes elements of a given type in a linear sequence.
	//It enables fast random access to any element, 
	//and dynamic additions and removals to and from the sequence. 
	vector<RECORD> records(0);
	RECORD r; //record item
	DWORD bytes;
	HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		SetFilePointer(hFile, sizeof(HEADER), NULL, FILE_BEGIN);
		do {
			ReadFile(hFile, &r, sizeof(RECORD), &bytes, NULL);
			records.push_back(r);//Adds an element to the end of the vector.
		} while (bytes != 0);
		if (print) { //print info if it is needed
			SYSTEMTIME systemTime;
			for (int i = 0; i < count; i++) {
				printf("Id: %d\t", records[i].record_number);
				printf("Counter: %d\t", records[i].counter);
				printf("Text: %s\t", records[i].text);
				FileTimeToSystemTime(&records[i].creation, &systemTime);
				printf("Creation time: %02d-%02d-%d\n",
					systemTime.wMonth, systemTime.wDay, systemTime.wYear);
			}
		}
		CloseHandle(hFile);
	}
	else {
		print_problems();
	}
	return records;
}

void delete_record(int count) {
	HEADER info_header = header_info(false);
	vector <RECORD> records = records_info(count, false);
	SYSTEMTIME systemTime;
	int id;
	printf("Input id to modify :");
	scanf("%d", &id);
	if (id >= 0 && id < count) {
		char str[81];
			//delete record is setting 0 values
			strcpy(records[id].text, "");
			info_header.not_empty_record_count--;
			records[id].counter = 0;
			FileTimeToSystemTime(&records[id].creation, &systemTime);
		//rewrite info
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		WriteFile(hFile, &header_info, sizeof(HEADER), NULL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_END);
		for (int i = 0; i < count; i++)
			WriteFile(hFile, &records[i], sizeof(RECORD), NULL, NULL);
		CloseHandle(hFile);
	}
	else {
		printf("************Incorrect id****************");
	}
}

void modify_record(int count) {
	HEADER info_header = header_info(false);
	vector <RECORD> records = records_info(count, false);
	SYSTEMTIME systemTime;
	int id;
	printf("Input id to modify :");
	scanf("%d", &id);
	if (id >= 0 && id < count) {
		char str[81];
			printf("Input text (80 symbols without space):");
			scanf("%s", records[id].text);
			strcpy(str, records[id].text);
			//modify header
			info_header.not_empty_record_count++;
			//modify record
			records[id].counter++;
			FileTimeToSystemTime(&records[id].creation, &systemTime);
		//rewrite info
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		WriteFile(hFile, &header_info, sizeof(HEADER), NULL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_END);
		for (int i = 0; i < count; i++)
			WriteFile(hFile, &records[i], sizeof(RECORD), NULL, NULL);
		CloseHandle(hFile);
	}
	else {
		printf("************Incorrect id***********");
	}
}

void main(int argc, char* argv[])
{
	if (argc != 2) {
		incorrect_input();
	}
	else {
		while (true)
		{
			int num = atoi(argv[1]);
			char command[3];
			init_records(num);
			printf("Input command:\n");
			printf("1.delete record\n");
			printf("2.modify record\n");
			printf("3.print records\n");
			scanf_s("%s", command, 3);
			if (strcmp(command, "1") == 0) {
				delete_record(num);
			}
			else if (strcmp(command, "2") == 0) {
				modify_record(num);
			}
			else if (strcmp(command, "3") == 0) {
				header_info(true);
				records_info(num, true);
			}
			else {
				printf("*****************Incorrect command***********\n");
				exit(0);
			}
		}
	}
}
