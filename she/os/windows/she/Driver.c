#include <ntddk.h>
#include <wdf.h>

// Forward declarations
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD EvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP EvtDriverContextCleanup;

// DriverEntry: Entry point for the driver
NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;

    WDF_DRIVER_CONFIG_INIT(&config, EvtDeviceAdd);
    config.EvtDriverUnload = EvtDriverContextCleanup;

    status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Error: WdfDriverCreate failed with status 0x%x\n", status));
        return status;
    }

    KdPrint(("Driver loaded successfully\n"));
    return STATUS_SUCCESS;
}

// EvtDeviceAdd: Called when a device is added to the driver
NTSTATUS EvtDeviceAdd(
    _In_ WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
) {
    NTSTATUS status;
    WDFDEVICE hDevice;

    UNREFERENCED_PARAMETER(Driver);

    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &hDevice);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Error: WdfDeviceCreate failed with status 0x%x\n", status));
        return status;
    }

    KdPrint(("Device added successfully\n"));
    return STATUS_SUCCESS;
}

// EvtDriverContextCleanup: Called when the driver is unloaded
VOID EvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
) {
    UNREFERENCED_PARAMETER(DriverObject);
    KdPrint(("Driver unloaded\n"));
}
