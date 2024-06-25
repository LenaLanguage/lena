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

DEFINE_GUID (GUID_DEVINTERFACE_she,
    0xce7886ea,0x00a7,0x4a8e,0x84,0x99,0x32,0x9a,0xfe,0x04,0xd9,0x57);
// {ce7886ea-00a7-4a8e-8499-329afe04d957}
