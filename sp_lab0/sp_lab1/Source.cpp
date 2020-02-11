
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[])
{
	cout << "     data type      " << "byte" << "      " << "    min value ... max value  " << endl 

		<< "char               =  " << sizeof(char) << "            " << (CHAR_MIN) << " ... " << fixed << setprecision(2)
		<< (CHAR_MAX) << endl
		<< "short              =  " << sizeof(short int) << "            " << (SHRT_MIN) << " ... " << fixed << setprecision(2)
		 << (SHRT_MAX) << endl
		<< "int                =  " << sizeof(int) << "            " << (INT_MIN) << " ... " << fixed << setprecision(2)
		 << (INT_MAX) << endl
		<< "long               =  " << sizeof(long int) << "            " << (LONG_MIN) << " ... " << fixed << setprecision(2)
		 << (LONG_MAX) << endl
		<< "long long          =  " << sizeof(long long) << "            " << (LLONG_MIN) << " ... " << fixed << setprecision(2)
		 << (LLONG_MAX) << endl
		
		<< "unsigned char      =  " << sizeof(unsigned char) << "         " <<  "   0"  << " ... " << fixed << setprecision(2)
		 << (UCHAR_MAX) << endl
		<< "unsigned short     =  " << sizeof(unsigned short int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		 << (USHRT_MAX)<< endl

		<< "unsigned int       =  " << sizeof(unsigned int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		 << (UINT_MAX) << endl

		<< "unsigned long      =  " << sizeof(unsigned long int) << "         " << "   0" << " ... " << fixed << setprecision(2)
		 << (ULONG_MAX) << endl
		<< "unsigned long long =  " << sizeof(unsigned long long) << "         " <<"   0" << " ... " << fixed << setprecision(2)
		 << (ULLONG_MAX) << endl;
		
		
	system("pause");
	return 0;
}