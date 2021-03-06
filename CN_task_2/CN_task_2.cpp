#include "pch.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{

	DWORD dwRetVal;
	IPAddr DestIp = 0;
	IPAddr SrcIp = 0;       /* default for src ip */
	ULONG MacAddr[2];       /* for 6-byte hardware addresses */
	ULONG PhysAddrLen = 6;  /* default to length of six bytes */

	char DestIpString[32];
	printf(" Enter the ip address : ");
    scanf(" %s", DestIpString);

	char *SrcIpString = NULL;

	BYTE *bPhysAddr;
	unsigned int i;

	DestIp = inet_addr(DestIpString);

	memset(&MacAddr, 0xff, sizeof(MacAddr));

	printf("Sending ARP request for IP address: %s\n", DestIpString);

	dwRetVal = SendARP(DestIp, 0, &MacAddr, &PhysAddrLen);

	if (dwRetVal == NO_ERROR) {
		bPhysAddr = (BYTE *)& MacAddr;
		if (PhysAddrLen) {
			for (i = 0; i < (int)PhysAddrLen; i++) {
				if (i == (PhysAddrLen - 1))
					printf("%.2X\n", (int)bPhysAddr[i]);
				else
					printf("%.2X-", (int)bPhysAddr[i]);
			}
		}
		else
			printf
			("Warning: SendArp completed successfully, but returned length=0\n");

	}
	else {
		printf("Error: SendArp failed with error: %d", dwRetVal);
		switch (dwRetVal) {
		case ERROR_GEN_FAILURE:
			printf(" (ERROR_GEN_FAILURE)\n");
			break;
		case ERROR_INVALID_PARAMETER:
			printf(" (ERROR_INVALID_PARAMETER)\n");
			break;
		case ERROR_INVALID_USER_BUFFER:
			printf(" (ERROR_INVALID_USER_BUFFER)\n");
			break;
		case ERROR_BAD_NET_NAME:
			printf(" (ERROR_GEN_FAILURE)\n");
			break;
		case ERROR_BUFFER_OVERFLOW:
			printf(" (ERROR_BUFFER_OVERFLOW)\n");
			break;
		case ERROR_NOT_FOUND:
			printf(" (ERROR_NOT_FOUND)\n");
			break;
		default:
			printf("\n");
			break;
		}
	}

	return 0;
}
