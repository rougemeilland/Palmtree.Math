all: ../../dist/Release/x64/Palmtree.Math.Core.Uint.Experiment.Karatsuba.exe

clean:
	rm -f ../../dist/Release/x64/Palmtree.Math.Core.Uint.Experiment.Karatsuba.exe ../build/x64_Release/Palmtree.Math.Core.Uint.Experiment.Karatsuba.map
	rm -r -f ../build/x64_Release

OBJS = ../build/x64_Release/main.o ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll

../../dist/Release/x64/Palmtree.Math.Core.Uint.Experiment.Karatsuba.exe: $(OBJS) 
	mkdir -p ../../dist/Release/x64
	g++ -o ../../dist/Release/x64/Palmtree.Math.Core.Uint.Experiment.Karatsuba.exe $(OBJS)  -lkernel32 -luser32 -mconsole -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Release/Palmtree.Math.Core.Uint.Experiment.Karatsuba.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x64/

../build/x64_Release/main.o: ../main.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Release/main.o ../main.cpp

