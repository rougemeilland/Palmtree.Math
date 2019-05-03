all: ../../dist/Release/x86/Palmtree.Math.Core.Uint.Launcher.exe

clean:
	rm -f ../../dist/Release/x86/Palmtree.Math.Core.Uint.Launcher.exe ../build/x86_Release/Palmtree.Math.Core.Uint.Launcher.map
	rm -r -f ../build/x86_Release

OBJS = ../build/x86_Release/main.o ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll

../../dist/Release/x86/Palmtree.Math.Core.Uint.Launcher.exe: $(OBJS) 
	mkdir -p ../../dist/Release/x86
	g++ -o ../../dist/Release/x86/Palmtree.Math.Core.Uint.Launcher.exe $(OBJS)  -lkernel32 -luser32 -mconsole -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Release/Palmtree.Math.Core.Uint.Launcher.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x86/

../build/x86_Release/main.o: ../main.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/main.o ../main.cpp

