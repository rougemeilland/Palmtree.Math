all: ../../dist/Debug/x64/Palmtree.Math.Core.Rtnl.dll

clean:
	rm -f ../../dist/Debug/x64/Palmtree.Math.Core.Rtnl.dll ../build/x64_Debug/Palmtree.Math.Core.Rtnl.map
	rm -r -f ../build/x64_Debug

OBJS = ../build/x64_Debug/pmc_add.o ../build/x64_Debug/pmc_bytes.o ../build/x64_Debug/pmc_compare.o ../build/x64_Debug/pmc_divide.o ../build/x64_Debug/pmc_dllmain.o ../build/x64_Debug/pmc_equals.o ../build/x64_Debug/pmc_from.o ../build/x64_Debug/pmc_initialize.o ../build/x64_Debug/pmc_interface_csharp.o ../build/x64_Debug/pmc_invert.o ../build/x64_Debug/pmc_log.o ../build/x64_Debug/pmc_memory.o ../build/x64_Debug/pmc_multiply.o ../build/x64_Debug/pmc_parse.o ../build/x64_Debug/pmc_pow.o ../build/x64_Debug/pmc_resourceholder_rtnl.o ../build/x64_Debug/pmc_round.o ../build/x64_Debug/pmc_rtnl_cppinterface.o ../build/x64_Debug/pmc_statistics.o ../build/x64_Debug/pmc_subtruct.o ../build/x64_Debug/pmc_to.o ../build/x64_Debug/pmc_tostring.o ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll ../../dist/Release/x64/Palmtree.Math.Core.Sint.dll

../../dist/Debug/x64/Palmtree.Math.Core.Rtnl.dll: $(OBJS) ../Palmtree.Math.Core.Rtnl.def
	mkdir -p ../../dist/Debug/x64
	g++ -o ../../dist/Debug/x64/Palmtree.Math.Core.Rtnl.dll $(OBJS) ../Palmtree.Math.Core.Rtnl.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Debug/Palmtree.Math.Core.Rtnl.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x64/

../build/x64_Debug/pmc_add.o: ../pmc_add.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_add.o ../pmc_add.cpp

../build/x64_Debug/pmc_bytes.o: ../pmc_bytes.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_bytes.o ../pmc_bytes.cpp

../build/x64_Debug/pmc_compare.o: ../pmc_compare.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_compare.o ../pmc_compare.cpp

../build/x64_Debug/pmc_divide.o: ../pmc_divide.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_divide.o ../pmc_divide.cpp

../build/x64_Debug/pmc_dllmain.o: ../pmc_dllmain.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x64_Debug/pmc_equals.o: ../pmc_equals.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_equals.o ../pmc_equals.cpp

../build/x64_Debug/pmc_from.o: ../pmc_from.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_from.o ../pmc_from.cpp

../build/x64_Debug/pmc_initialize.o: ../pmc_initialize.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_initialize.o ../pmc_initialize.cpp

../build/x64_Debug/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x64_Debug/pmc_invert.o: ../pmc_invert.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_invert.o ../pmc_invert.cpp

../build/x64_Debug/pmc_log.o: ../pmc_log.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_log.o ../pmc_log.cpp

../build/x64_Debug/pmc_memory.o: ../pmc_memory.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_memory.o ../pmc_memory.cpp

../build/x64_Debug/pmc_multiply.o: ../pmc_multiply.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_multiply.o ../pmc_multiply.cpp

../build/x64_Debug/pmc_parse.o: ../pmc_parse.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_parse.o ../pmc_parse.cpp

../build/x64_Debug/pmc_pow.o: ../pmc_pow.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_pow.o ../pmc_pow.cpp

../build/x64_Debug/pmc_resourceholder_rtnl.o: ../pmc_resourceholder_rtnl.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_resourceholder_rtnl.o ../pmc_resourceholder_rtnl.cpp

../build/x64_Debug/pmc_round.o: ../pmc_round.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_round.o ../pmc_round.cpp

../build/x64_Debug/pmc_rtnl_cppinterface.o: ../pmc_rtnl_cppinterface.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../pmc_rtnl_cppinterface.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_rtnl_cppinterface.o ../pmc_rtnl_cppinterface.cpp

../build/x64_Debug/pmc_statistics.o: ../pmc_statistics.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_statistics.o ../pmc_statistics.cpp

../build/x64_Debug/pmc_subtruct.o: ../pmc_subtruct.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x64_Debug/pmc_to.o: ../pmc_to.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_rtnl_internal.h  ../pmc_resourceholder_rtnl.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_to.o ../pmc_to.cpp

../build/x64_Debug/pmc_tostring.o: ../pmc_tostring.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Sint/pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_rtnl.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Sint/pmc_sint_cppinterface.h  ../pmc_rtnl_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORERTNL_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sint/ -o ../build/x64_Debug/pmc_tostring.o ../pmc_tostring.cpp

