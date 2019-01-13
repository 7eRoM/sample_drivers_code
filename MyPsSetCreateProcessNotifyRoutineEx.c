/*
Develop: Windows10 1809, VisualStudio 2017, SDK: 10.0.17763.0, WDK 10
Tests: Windows10 1511

Properties -> Configuration Properties -> C/C++ -> General -> Warning Level: Level1 (/W1)
Properties -> Configuration Properties -> Linker -> General -> Treat Linker Warning As Errors: No (/WX:NO)
Properties -> Configuration Properties -> Linker -> Command Line -> Additional Options: /INTEGRITYCHECK
Properties -> Configuration Properties -> Driver Settings -> General -> Target OS Version: Windows 10 or higher
Properties -> Configuration Properties -> Inf2Cat -> General -> Use Local Time: Yes (/uselocaltime)
*/


#include "ntddk.h"

void ProcessNotifyRoutineEx(PEPROCESS Process, HANDLE ProcessId, PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	if (CreateInfo)
	{
		DbgPrintEx(
			DPFLTR_IHVDRIVER_ID,
			DPFLTR_ERROR_LEVEL,
			"[*] PID: %d  ***  ParentPID: %d  ***  ImageName: %wZ  ***  CmdLine: %wZ \r\n",
			ProcessId,
			CreateInfo->ParentProcessId,
			CreateInfo->ImageFileName,
			CreateInfo->CommandLine
		);
	}
	else
	{
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[*] Process %d has ended\n", ProcessId);
	}
}

VOID Unload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS ntstatus = PsSetCreateProcessNotifyRoutineEx(ProcessNotifyRoutineEx, TRUE);
	if (!NT_SUCCESS(ntstatus))
	{
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[-] Error in removing routine: Unable to call PsSetCreateProcessNotifyRoutineEx ...\r\n");
	}
	else
	{
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[+] Routine has been removed successfully!\r\n");
	}
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "GoodBye Driver ...\r\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = Unload;

	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Hello Driver ...\r\n");
	
	NTSTATUS ntstatus = PsSetCreateProcessNotifyRoutineEx(ProcessNotifyRoutineEx, FALSE);
	if (!NT_SUCCESS(ntstatus))
	{
		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[-] Error in adding routine: Unable to call PsSetCreateProcessNotifyRoutineEx ...\r\n");
		return ntstatus;
	}
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[+] Routine has been added successfully!\r\n");
	
	return STATUS_SUCCESS;
}
