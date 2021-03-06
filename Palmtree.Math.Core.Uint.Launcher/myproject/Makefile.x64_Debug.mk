all: ../../dist/Debug/x64/Palmtree.Math.Core.Uint.Launcher.exe

clean:
	rm -f ../../dist/Debug/x64/Palmtree.Math.Core.Uint.Launcher.exe ../build/x64_Debug/Palmtree.Math.Core.Uint.Launcher.map
	rm -r -f ../build/x64_Debug

OBJS = ../build/x64_Debug/main.o ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll

../../dist/Debug/x64/Palmtree.Math.Core.Uint.Launcher.exe: $(OBJS) 
	mkdir -p ../../dist/Debug/x64
	g++ -o ../../dist/Debug/x64/Palmtree.Math.Core.Uint.Launcher.exe $(OBJS)  -lkernel32 -luser32 -mconsole -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Debug/Palmtree.Math.Core.Uint.Launcher.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x64/

../build/x64_Debug/main.o: ../main.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/main.o ../main.cpp

