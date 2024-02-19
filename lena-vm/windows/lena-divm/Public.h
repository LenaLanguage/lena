/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_lenadivm,
    0x00a58967,0x9aaf,0x42e3,0x88,0x9b,0x22,0xe9,0xdf,0x35,0x6a,0xae);
// {00a58967-9aaf-42e3-889b-22e9df356aae}
