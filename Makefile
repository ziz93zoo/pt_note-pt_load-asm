NASM = nasm
LD = ld
NFLAGS = -f elf64

all: infector labos

infector:
	$(NASM) $(NFLAGS) main/pt_note_to_pt_load_infector.s -o main/pt_note_to_pt_load_infector.o
	$(LD) main/pt_note_to_pt_load_infector.o -o main/pt_note_to_pt_load_infector

labos:
	$(NASM) $(NFLAGS) labos/01_hello.s -o labos/01_hello.o
	$(LD) labos/01_hello.o -o labos/01_hello
	$(NASM) $(NFLAGS) labos/03_bytes.s -o labos/03_bytes.o
	$(LD) labos/03_bytes.o -o labos/03_bytes

clean:
	rm -f main/*.o labos/*.o saine-code/safe_code
	rm -f main/pt_note_to_pt_load_infector
	rm -f labos/01_hello labos/03_bytes

.PHONY: all infector labos clean
