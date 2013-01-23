#include <efi/efi.h>
#include <efi/efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_MEMORY_DESCRIPTOR *descriptors;
    EFI_STATUS status;
    UINTN neededMemory = 0, actualSize, descriptors_size;
    UINT64 totalMemory = 0;

    InitializeLib(ImageHandle, SystemTable);
    status = uefi_call_wrapper(SystemTable->BootServices->GetMemoryMap, 
            5, 
            &neededMemory, NULL, NULL, NULL, NULL);
    if ( status != EFI_BUFFER_TOO_SMALL )
    {
        Print(L"Something going wrong\n");
        return EFI_SUCCESS;
    }

    status = uefi_call_wrapper(SystemTable->BootServices->AllocatePool,
            3, 
            EfiLoaderData, neededMemory, &descriptors);
    if (status != EFI_SUCCESS)
    {
        Print (L"AllocatePool failed\n");
        return EFI_SUCCESS;
    }

    status = uefi_call_wrapper(
            SystemTable->BootServices->GetMemoryMap,
            5, 
            &descriptors_size, descriptors, NULL, &actualSize, NULL);

    if ( status == EFI_SUCCESS )
    {
        UINTN count = descriptors_size / actualSize;
        UINTN i;
        for ( i = 0; i < count; ++i )
        {
            if ( descriptors[i].Type == EfiLoaderData ||
                    descriptors[i].Type == EfiBootServicesData || 
                    descriptors[i].Type == EfiRuntimeServicesData ||
                    descriptors[i].Type == EfiConventionalMemory)
            {
                totalMemory += descriptors[i].NumberOfPages * 4096;
            }
        }
        Print(L"%d\n", totalMemory);
    }        

    uefi_call_wrapper(SystemTable->BootServices->FreePool, 1, descriptors);
    return EFI_SUCCESS;
}
