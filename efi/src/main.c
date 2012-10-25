#include <efi/efi.h>
#include <efi/efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    char descriptors[1024 * sizeof(EFI_MEMORY_DESCRIPTOR)];
    UINTN size = 1024 * sizeof(EFI_MEMORY_DESCRIPTOR);
    UINTN a,ActualSize;
    UINT32 c;
    UINTN status;

    status = uefi_call_wrapper(
            SystemTable->BootServices->GetMemoryMap,
            5, 
            &size, &descriptors, &a, &ActualSize, &c);

    if ( status == EFI_SUCCESS )
    {
        Print(L"GetMemoryMap() Success!\n");
        int i;
        Print(L"%d %d\n",size,ActualSize);
        for (i = 0; i < size/ActualSize; ++i)
        {
            EFI_MEMORY_DESCRIPTOR descriptor = *((EFI_MEMORY_DESCRIPTOR*) descriptors + i * ActualSize);

            switch (descriptor.Type)
            {
                case EfiReservedMemoryType:
                    Print(L"EfiReservedMemoryType\n");
                    break;
                case EfiLoaderCode:
                    Print(L"EfiLoaderCode\n");
                    break;
                case EfiLoaderData:
                    Print(L"EfiLoaderData\n");
                    break;
                case EfiBootServicesCode:
                    Print(L"EfiBootServicesCode\n");
                    break;
                case EfiBootServicesData:
                    Print(L"EfiBootServicesData\n");
                    break;
                case EfiRuntimeServicesCode:
                    Print(L"EfiRuntimeServicesCode\n");
                    break;
                case EfiRuntimeServicesData:
                    Print(L"EfiRuntimeServicesData\n");
                    break;
                case EfiConventionalMemory:
                    Print(L"EfiConventionalMemory\n");
                    break;
                case EfiUnusableMemory:
                    Print(L"EfiUnusableMemory\n");
                    break;
                case EfiACPIReclaimMemory:
                    Print(L"EfiACPIReclaimMemory\n");
                    break;
                case EfiACPIMemoryNVS:
                    Print(L"EfiACPIMemoryNVS\n");
                    break;
                case EfiMemoryMappedIO:
                    Print(L"EfiMemoryMappedIO\n");
                    break;
                case EfiMemoryMappedIOPortSpace:
                    Print(L"EfiMemoryMappedIOPortSpace\n");
                    break;
                case EfiPalCode:
                    Print(L"EfiPalCode\n");
                    break;
                case EfiMaxMemoryType:
                    Print(L"EfiMaxMemoryType\n");
                    break;
                default:
                    Print(L"UnknownMemoryType\n");
                    break;
            }
            Print(L"    PhysicalStart:  %X\n", descriptor.PhysicalStart);
            Print(L"    VirtualStart:   %X\n", descriptor.VirtualStart);
            Print(L"    NumberOfPages:  %X\n", descriptor.NumberOfPages);
        }
    }        
    return EFI_SUCCESS;
}
