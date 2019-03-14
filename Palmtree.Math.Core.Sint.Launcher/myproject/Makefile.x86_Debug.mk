all: ../../dist/x86_Debug/Palmtree.Math.Core.Sint.Launcher.exe

clean:
	rm -f ../../dist/x86_Debug/Palmtree.Math.Core.Sint.Launcher.exe ../build/x86_Debug/Palmtree.Math.Core.Sint.Launcher.map
	rm -r -f ../build/x86_Debug

test:

OBJS = ../build/x86_Debug/main.o

../../dist/x86_Debug/Palmtree.Math.Core.Sint.Launcher.exe: $(OBJS)
	mkdir -p ../../dist/x86_Debug
	gcc -o ../../dist/x86_Debug/Palmtree.Math.Core.Sint.Launcher.exe $(OBJS)  -Wl,-Map=../build/x86_Debug/Palmtree.Math.Core.Sint.Launcher.map 

../build/x86_Debug/main.o: ../main.c  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	gcc -c -save-temps=obj -Werror -D_M_IX86 -g -D_DEBUG  -o ../build/x86_Debug/main.o ../main.c

