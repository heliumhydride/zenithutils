// IMPORTANT: to make this only run on Windows and not redefine int uname(...) on Unix
#ifdef _WIN32
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <windows.h>
#include <sysinfoapi.h>

#include "../include/utsname_winnt.h"

int uname(struct utsname* uts) {
  // structs to init: sysname;nodename;release;version;machine
  OSVERSIONINFO os_info;
  SYSTEM_INFO sys_info;
  
  memset(&os_info, 0, sizeof(OSVERSIONINFO));
	os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  GetVersionEx(&os_info);
  GetSystemInfo(&sys_info);

  DWORD computername_size = sizeof(uts->nodename);

  if(GetComputerName(uts->nodename, &computername_size) == 0 ) { // For some reason winapi functions return nonzero on success and zero on failure ...
		strcpy(uts->nodename, "unknown");
	}

  // TODO: Fix 6.2 (Windows 8) being return on Win10+
  sprintf(uts->release, "%u.%u", (unsigned int)os_info.dwMajorVersion,
			(unsigned int)os_info.dwMinorVersion);
	sprintf(uts->version, "%u", (unsigned int)os_info.dwBuildNumber);

  strcpy(uts->sysname, "WinNT");


  switch (sys_info.wProcessorArchitecture) {
  	case PROCESSOR_ARCHITECTURE_AMD64:
  		strcpy(uts->machine, "x86_64");
  		break;
  	case PROCESSOR_ARCHITECTURE_INTEL:
  		strcpy(uts->machine, "i686");
  		if (sys_info.wProcessorLevel < 6) {
  			uts->machine[1] = '3';
  		}
  		break;
  	case PROCESSOR_ARCHITECTURE_ARM64:
  		strcpy(uts->machine, "aarch64");
  		break;
  	default:
  		strcpy(uts->machine, "unknown");
  		break;
	}
}

// remember the #ifdef from earlier ?
#endif
