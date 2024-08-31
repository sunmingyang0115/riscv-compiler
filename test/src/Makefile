AS = riscv64-linux-gnu-as 
LD = riscv64-linux-gnu-ld

OUT = a.out

$(OUT): stdlib.o main.o start.o
	$(LD) stdlib.o main.o start.o -o $(OUT)

stdlib.o: stdlib.s
	$(AS) stdlib.s -o stdlib.o

start.o: start.s
	$(AS) start.s -o start.o

main.o: main.s
	$(AS) main.s -o main.o

clean:
	rm *.o $(OUT)

.PHONY: clean all
