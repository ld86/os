#include <efi/efi.h>
#include <efi/efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    EFI_MEMORY_DESCRIPTOR descriptors[1024];
    UINTN size = 1024 * sizeof(EFI_MEMORY_DESCRIPTOR);
    UINTN a,b;
    UINT32 c;
    UINTN status;

    status = uefi_call_wrapper(
            SystemTable->BootServices->GetMemoryMap,
            5, 
            &size, descriptors, &a, &b, &c);

    if ( status == EFI_SUCCESS )
    {
        SIMPLE_TEXT_OUTPUT_INTERFACE *conout;
        conout = SystemTable->ConOut;
        uefi_call_wrapper(conout->OutputString, 2, conout, L"GetMemoryMap() Success!\n\r");
        int i;
        for (i = 0; i < size/sizeof(EFI_MEMORY_DESCRIPTOR); ++i)
        {
            uefi_call_wrapper(conout->OutputString, 2, conout, L"1\n\r");
            Print(L"%X\n",descriptors[i].PhysicalStart);
        }
    }        
    return EFI_SUCCESS;
}
