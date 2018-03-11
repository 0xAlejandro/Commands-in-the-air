/*************************************************** Main Program *************************************************
File:			  Main.cpp
Description:	  This is the main file.
Developer:		  Alejandro Chávez Gómez.
*******************************************************************************************************************/

/*											     	  Libraries											     	  */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>

/*											   Declaration of constants								              */
#define EXIT_SUCCESS 0;
#define EXIT_FAILURE -1;

/*											   Declaration of functions								              */
int scan();

/*										 Main Function - Start of the program									  */
int main(int argc, char** argv)
{
	do {
		system("cls");
		printf("[*] Starting program...\n");
		scan();
		Sleep(10000);
	} while (true);
	printf("[*] Ending program...\n");
	
	return EXIT_SUCCESS;
}
/*										 End of Main Function - End of program									  */