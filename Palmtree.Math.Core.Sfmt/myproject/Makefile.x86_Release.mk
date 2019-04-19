all: ../../dist/Release/x86/Palmtree.Math.Core.Sfmt.dll

clean:
	rm -f ../../dist/Release/x86/Palmtree.Math.Core.Sfmt.dll ../build/x86_Release/Palmtree.Math.Core.Sfmt.map
	rm -r -f ../build/x86_Release

OBJS = ../build/x86_Release/pmc_random.o ../build/x86_Release/SFMT.o ../build/x86_Release/version.o

../../dist/Release/x86/Palmtree.Math.Core.Sfmt.dll: $(OBJS) 
	mkdir -p ../../dist/Release/x86
	g++ -o ../../dist/Release/x86/Palmtree.Math.Core.Sfmt.dll $(OBJS)  -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Release/Palmtree.Math.Core.Sfmt.map 

../build/x86_Release/pmc_random.o: ../pmc_random.cpp  ../SFMT-params.h  ../pmc_sfmt.h  ../SFMT.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESFMT_EXPORTS -DSFMT_MEXP=19937 -O2 -std=c++1z  -o ../build/x86_Release/pmc_random.o ../pmc_random.cpp

../build/x86_Release/SFMT.o: ../SFMT.c  ../SFMT-params.h  ../SFMT.h  ../SFMT-common.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	gcc -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESFMT_EXPORTS -DSFMT_MEXP=19937 -O2  -o ../build/x86_Release/SFMT.o ../SFMT.c

../build/x86_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	windres -c 65001 -o ../build/x86_Release/version.o ../version.rc

