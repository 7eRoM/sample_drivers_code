/*
Note: Link to ntoskrnl.lib

Similar to "Windows Defender", use the undocumented "SeRegisterImageVerificationCallback" routine to set a callback that triggers whenever a new driver image is loaded into kernel memory.
*/

#include <ntddk.h>
#include <wdm.h>

// Global variable to store the callback handle
PVOID g_CallbackHandle = NULL;

// Image verification callback function
VOID MyImageVerificationCallback(
    _In_opt_ PVOID CallbackContext,
    _In_ SE_IMAGE_TYPE ImageType,
    _Inout_ PBDCB_IMAGE_INFORMATION ImageInformation)
{
    UNREFERENCED_PARAMETER(CallbackContext);
    UNREFERENCED_PARAMETER(ImageType);
    UNREFERENCED_PARAMETER(ImageInformation);

    DbgPrint("Image Loaded: %wZ\n", &ImageInformation->ImageName);
}

// Driver unload routine
VOID DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (g_CallbackHandle)
    {
        SeUnregisterImageVerificationCallback(g_CallbackHandle);
        g_CallbackHandle = NULL;
    }
    DbgPrint("Driver Unloaded.\n");
}

// Driver entry point
extern "C"
NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    NTSTATUS status = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    // Register the image verification callback
    status = SeRegisterImageVerificationCallback(
        SeImageTypeDriver,                
        SeImageVerificationCallbackInformational,   
        MyImageVerificationCallback,       // Callback function
        NULL,                              // Callback context
        NULL,                              // Token (not used)
        &g_CallbackHandle                  // Handle to unregister later
    );

    if (!NT_SUCCESS(status))
    {
        DbgPrint("Failed to register image verification callback: 0x%08X\n", status);
    }
    else
    {
        DbgPrint("Image verification callback registered successfully.\n");
    }

    return status;
}
