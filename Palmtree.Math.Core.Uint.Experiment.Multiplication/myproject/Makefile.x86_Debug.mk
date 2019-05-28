all: ../../dist/Debug/x86/Palmtree.Math.Core.Uint.Experiment.Multiplication.exe

clean:
	rm -f ../../dist/Debug/x86/Palmtree.Math.Core.Uint.Experiment.Multiplication.exe ../build/x86_Debug/Palmtree.Math.Core.Uint.Experiment.Multiplication.map
	rm -r -f ../build/x86_Debug

OBJS = ../build/x86_Debug/main.o ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll

../../dist/Debug/x86/Palmtree.Math.Core.Uint.Experiment.Multiplication.exe: $(OBJS) 
	mkdir -p ../../dist/Debug/x86
	g++ -o ../../dist/Debug/x86/Palmtree.Math.Core.Uint.Experiment.Multiplication.exe $(OBJS)  -lkernel32 -luser32 -mconsole -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Debug/Palmtree.Math.Core.Uint.Experiment.Multiplication.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x86/

../build/x86_Debug/main.o: ../main.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Debug/main.o ../main.cpp

