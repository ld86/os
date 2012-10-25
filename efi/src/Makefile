ARCH     = x86_64
EFIROOT  = /usr/local
HDRROOT  = /usr/include/efi
INCLUDES = -I/usr/include/efi/x86_64 -I/usr/include/efi

CRTOBJS  = /usr/lib/crt0-efi-$(ARCH).o
CFLAGS   = -O2 -fPIC -Wall -fshort-wchar -fno-strict-aliasing \
           -fno-merge-constants
CPPFLAGS = -DCONFIG_$(ARCH)
FORMAT   = efi-app-$(ARCH)
INSTALL  = install
LDFLAGS  = -nostdlib
LDSCRIPT = /usr/lib/elf_$(ARCH)_efi.lds
LDFLAGS += -T $(LDSCRIPT) -shared -Bsymbolic -L/usr/lib $(CRTOBJS)
LOADLIBS = -lefi -lgnuefi $(shell $(CC) -print-libgcc-file-name)

all:
	gcc main.c $(INCLUDES) $(CFLAGS) -c -o main.o
	ld $(LDFLAGS) main.o -o main.so $(LOADLIBS)
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel \
                -j .rela -j .reloc --target=$(FORMAT) main.so main.efi
