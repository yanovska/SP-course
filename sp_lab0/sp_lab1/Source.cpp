
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[])
{
	cout << "     data type      " << "byte" << "      " << "    min value ... max value  " << endl 

		<< "char               =  " << sizeof(char) << "            " << (CHAR_MIN) << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ char*/ << (pow(2, sizeof(char) * 8.0-1) - 1) << endl
		<< "short              =  " << sizeof(short int) << "            " << (SHRT_MIN) << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ short int*/ << (pow(2, sizeof(short int) * 8.0 - 1) - 1) << endl
		<< "int                =  " << sizeof(int) << "            " << (INT_MIN) << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ int*/ << (pow(2, sizeof(int) * 8.0 - 1) - 1) << endl
		<< "long               =  " << sizeof(long int) << "            " << (LONG_MIN) << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ long int*/ << (pow(2, sizeof(long int) * 8.0 - 1) - 1) << endl
		<< "long long          =  " << sizeof(long long) << "            " << (LLONG_MIN) << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ double*/ << (pow(2, sizeof(long long) * 8.0 - 1) - 1) << endl
		
		<< "unsigned char      =  " << sizeof(unsigned char) << "         " << "   0" << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ unsigned short int*/ << (pow(2, sizeof(unsigned char) * 8.0) - 1) << endl
		<< "unsigned short     =  " << sizeof(unsigned short int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ unsigned short int*/ << (pow(2, sizeof(unsigned short int) * 8.0) - 1) << endl

		<< "unsigned int       =  " << sizeof(unsigned int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ unsigned int*/ << (pow(2, sizeof(unsigned int) * 8.0) - 1) << endl

		<< "unsigned long      =  " << sizeof(unsigned long int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ undigned long int*/ << (pow(2, sizeof(unsigned long int) * 8.0) - 1) << endl
		<< "unsigned long long =  " << sizeof(unsigned long long) << "         " <<"   0" << " ... " << fixed << setprecision(2)
		/*��������� ������������ �������� ��� ���� ������ float*/ << (pow(2, sizeof(unsigned long long) * 8.0) - 1) << endl;
		
		
	system("pause");
	return 0;
}