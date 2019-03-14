all: ../../dist/x64_Debug/Palmtree.Math.Core.Sint.Launcher.exe

clean:
	rm -f ../../dist/x64_Debug/Palmtree.Math.Core.Sint.Launcher.exe ../build/x64_Debug/Palmtree.Math.Core.Sint.Launcher.map
	rm -r -f ../build/x64_Debug

test:

OBJS = ../build/x64_Debug/main.o

../../dist/x64_Debug/Palmtree.Math.Core.Sint.Launcher.exe: $(OBJS)
	mkdir -p ../../dist/x64_Debug
	gcc -o ../../dist/x64_Debug/Palmtree.Math.Core.Sint.Launcher.exe $(OBJS)  -Wl,-Map=../build/x64_Debug/Palmtree.Math.Core.Sint.Launcher.map 

../build/x64_Debug/main.o: ../main.c  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	gcc -c -save-temps=obj -Werror -D_M_IX64 -g -D_DEBUG  -o ../build/x64_Debug/main.o ../main.c

