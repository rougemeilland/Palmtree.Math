all: ../../dist/Release/x86/Palmtree.Math.Core.Rtnl.dll

clean:
	rm -f ../../dist/Release/x86/Palmtree.Math.Core.Rtnl.dll ../build/x86_Release/Palmtree.Math.Core.Rtnl.map
	rm -r -f ../build/x86_Release

OBJS = ../build/x86_Release/pmc_add.o ../build/x86_Release/pmc_bytes.o ../build/x86_Release/pmc_compare.o ../build/x86_Release/pmc_divide.o ../build/x86_Release/pmc_dllmain.o ../build/x86_Release/pmc_equals.o ../build/x86_Release/pmc_from.o ../build/x86_Release/pmc_initialize.o ../build/x86_Release/pmc_interface_csharp.o ../build/x86_Release/pmc_invert.o ../build/x86_Release/pmc_log.o ../build/x86_Release/pmc_memory.o ../build/x86_Release/pmc_multiply.o ../build/x86_Release/pmc_parse.o ../build/x86_Release/pmc_pow.o ../build/x86_Release/pmc_random.o ../build/x86_Release/pmc_resourceholder_rtnl.o ../build/x86_Release/pmc_round.o ../build/x86_Release/pmc_rtnl_cppinterface.o ../build/x86_Release/pmc_statistics.o ../build/x86_Release/pmc_subtruct.o ../build/x86_Release/pmc_to.o ../build/x86_Release/pmc_tostring.o ../build/x86_Release/version.o ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll ../../dist/Release/x86/Palmtree.Math.Core.Sint.dll

../../dist/Release/x86/Palmtree.Math.Core.Rtnl.dll: $(OBJS) ../Palmtree.Math.Core.Rtnl.def
	mkdir -p ../../dist/Release/x86
	g++ -o ../../dist/Release/x86/Palmtree.Math.Core.Rtnl.dll $(OBJS) ../Palmtree.Math.Core.Rtnl.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Release/Palmtree.Math.Core.Rtnl.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x86/

../build/x86_Release/pmc_add.o: ../pmc_add.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_add.o ../pmc_add.cpp

../build/x86_Release/pmc_bytes.o: ../pmc_bytes.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_bytes.o ../pmc_bytes.cpp

../build/x86_Release/pmc_compare.o: ../pmc_compare.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_compare.o ../pmc_compare.cpp

../build/x86_Release/pmc_divide.o: ../pmc_divide.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_divide.o ../pmc_divide.cpp

../build/x86_Release/pmc_dllmain.o: ../pmc_dllmain.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x86_Release/pmc_equals.o: ../pmc_equals.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_equals.o ../pmc_equals.cpp

../build/x86_Release/pmc_from.o: ../pmc_from.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_from.o ../pmc_from.cpp

../build/x86_Release/pmc_initialize.o: ../pmc_initialize.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_initialize.o ../pmc_initialize.cpp

../build/x86_Release/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x86_Release/pmc_invert.o: ../pmc_invert.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_invert.o ../pmc_invert.cpp

../build/x86_Release/pmc_log.o: ../pmc_log.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_log.o ../pmc_log.cpp

../build/x86_Release/pmc_memory.o: ../pmc_memory.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_memory.o ../pmc_memory.cpp

../build/x86_Release/pmc_multiply.o: ../pmc_multiply.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_multiply.o ../pmc_multiply.cpp

../build/x86_Release/pmc_parse.o: ../pmc_parse.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_parse.o ../pmc_parse.cpp

../build/x86_Release/pmc_pow.o: ../pmc_pow.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_pow.o ../pmc_pow.cpp

../build/x86_Release/pmc_random.o: ../pmc_random.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_random.o ../pmc_random.cpp

../build/x86_Release/pmc_resourceholder_rtnl.o: ../pmc_resourceholder_rtnl.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_resourceholder_rtnl.o ../pmc_resourceholder_rtnl.cpp

../build/x86_Release/pmc_round.o: ../pmc_round.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_round.o ../pmc_round.cpp

../build/x86_Release/pmc_rtnl_cppinterface.o: ../pmc_rtnl_cppinterface.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../pmc_rtnl_cppinterface.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_rtnl_cppinterface.o ../pmc_rtnl_cppinterface.cpp

../build/x86_Release/pmc_statistics.o: ../pmc_statistics.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_statistics.o ../pmc_statistics.cpp

../build/x86_Release/pmc_subtruct.o: ../pmc_subtruct.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x86_Release/pmc_to.o: ../pmc_to.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_to.o ../pmc_to.cpp

../build/x86_Release/pmc_tostring.o: ../pmc_tostring.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORERTNL_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x86_Release/pmc_tostring.o ../pmc_tostring.cpp

../build/x86_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	windres -c 65001 -o ../build/x86_Release/version.o ../version.rc

