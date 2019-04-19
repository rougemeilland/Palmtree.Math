all: ../../dist/Release/x64/Palmtree.Math.Core.Sfmt.dll

clean:
	rm -f ../../dist/Release/x64/Palmtree.Math.Core.Sfmt.dll ../build/x64_Release/Palmtree.Math.Core.Sfmt.map
	rm -r -f ../build/x64_Release

OBJS = ../build/x64_Release/pmc_random.o ../build/x64_Release/SFMT.o ../build/x64_Release/version.o

../../dist/Release/x64/Palmtree.Math.Core.Sfmt.dll: $(OBJS) 
	mkdir -p ../../dist/Release/x64
	g++ -o ../../dist/Release/x64/Palmtree.Math.Core.Sfmt.dll $(OBJS)  -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Release/Palmtree.Math.Core.Sfmt.map 

../build/x64_Release/pmc_random.o: ../pmc_random.cpp  ../SFMT-params.h  ../pmc_sfmt.h  ../SFMT.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESFMT_EXPORTS -DSFMT_MEXP=19937 -O2 -std=c++1z  -o ../build/x64_Release/pmc_random.o ../pmc_random.cpp

../build/x64_Release/SFMT.o: ../SFMT.c  ../SFMT-params.h  ../SFMT.h  ../SFMT-common.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	gcc -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESFMT_EXPORTS -DSFMT_MEXP=19937 -O2  -o ../build/x64_Release/SFMT.o ../SFMT.c

../build/x64_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	windres -c 65001 -o ../build/x64_Release/version.o ../version.rc

