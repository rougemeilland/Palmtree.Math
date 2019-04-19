all: ../../dist/Debug/x64/Palmtree.Math.Core.Sint.dll

clean:
	rm -f ../../dist/Debug/x64/Palmtree.Math.Core.Sint.dll ../build/x64_Debug/Palmtree.Math.Core.Sint.map
	rm -r -f ../build/x64_Debug

OBJS = ../build/x64_Debug/pmc_add_sub.o ../build/x64_Debug/pmc_bitwiseand.o ../build/x64_Debug/pmc_bitwiseor.o ../build/x64_Debug/pmc_bytes.o ../build/x64_Debug/pmc_compare.o ../build/x64_Debug/pmc_divide.o ../build/x64_Debug/pmc_divrem.o ../build/x64_Debug/pmc_dllmain.o ../build/x64_Debug/pmc_equals.o ../build/x64_Debug/pmc_exclusiveor.o ../build/x64_Debug/pmc_from.o ../build/x64_Debug/pmc_greatestcommondivisor.o ../build/x64_Debug/pmc_initialize.o ../build/x64_Debug/pmc_interface_csharp.o ../build/x64_Debug/pmc_invert.o ../build/x64_Debug/pmc_log.o ../build/x64_Debug/pmc_memory.o ../build/x64_Debug/pmc_multiply.o ../build/x64_Debug/pmc_onecomplement.o ../build/x64_Debug/pmc_parse.o ../build/x64_Debug/pmc_pow.o ../build/x64_Debug/pmc_random.o ../build/x64_Debug/pmc_resourceholder_sint.o ../build/x64_Debug/pmc_round.o ../build/x64_Debug/pmc_shift.o ../build/x64_Debug/pmc_sint_cppinterface.o ../build/x64_Debug/pmc_statistics.o ../build/x64_Debug/pmc_to.o ../build/x64_Debug/pmc_tostring.o ../build/x64_Debug/version.o ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll

../../dist/Debug/x64/Palmtree.Math.Core.Sint.dll: $(OBJS) ../Palmtree.Math.Core.Sint.def
	mkdir -p ../../dist/Debug/x64
	g++ -o ../../dist/Debug/x64/Palmtree.Math.Core.Sint.dll $(OBJS) ../Palmtree.Math.Core.Sint.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Debug/Palmtree.Math.Core.Sint.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x64/

../build/x64_Debug/pmc_add_sub.o: ../pmc_add_sub.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_add_sub.o ../pmc_add_sub.cpp

../build/x64_Debug/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x64_Debug/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x64_Debug/pmc_bytes.o: ../pmc_bytes.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_bytes.o ../pmc_bytes.cpp

../build/x64_Debug/pmc_compare.o: ../pmc_compare.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_compare.o ../pmc_compare.cpp

../build/x64_Debug/pmc_divide.o: ../pmc_divide.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_divide.o ../pmc_divide.cpp

../build/x64_Debug/pmc_divrem.o: ../pmc_divrem.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_divrem.o ../pmc_divrem.cpp

../build/x64_Debug/pmc_dllmain.o: ../pmc_dllmain.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x64_Debug/pmc_equals.o: ../pmc_equals.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_equals.o ../pmc_equals.cpp

../build/x64_Debug/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x64_Debug/pmc_from.o: ../pmc_from.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_from.o ../pmc_from.cpp

../build/x64_Debug/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x64_Debug/pmc_initialize.o: ../pmc_initialize.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_initialize.o ../pmc_initialize.cpp

../build/x64_Debug/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x64_Debug/pmc_invert.o: ../pmc_invert.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_invert.o ../pmc_invert.cpp

../build/x64_Debug/pmc_log.o: ../pmc_log.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_log.o ../pmc_log.cpp

../build/x64_Debug/pmc_memory.o: ../pmc_memory.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_memory.o ../pmc_memory.cpp

../build/x64_Debug/pmc_multiply.o: ../pmc_multiply.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_multiply.o ../pmc_multiply.cpp

../build/x64_Debug/pmc_onecomplement.o: ../pmc_onecomplement.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_onecomplement.o ../pmc_onecomplement.cpp

../build/x64_Debug/pmc_parse.o: ../pmc_parse.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_parse.o ../pmc_parse.cpp

../build/x64_Debug/pmc_pow.o: ../pmc_pow.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_pow.o ../pmc_pow.cpp

../build/x64_Debug/pmc_random.o: ../pmc_random.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_random.o ../pmc_random.cpp

../build/x64_Debug/pmc_resourceholder_sint.o: ../pmc_resourceholder_sint.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../../Palmtree.Math.Core.Uint/pmc_threadcontext.h  ../../Palmtree.Math.Core.Uint/pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_resourceholder_sint.o ../pmc_resourceholder_sint.cpp

../build/x64_Debug/pmc_round.o: ../pmc_round.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_round.o ../pmc_round.cpp

../build/x64_Debug/pmc_shift.o: ../pmc_shift.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_shift.o ../pmc_shift.cpp

../build/x64_Debug/pmc_sint_cppinterface.o: ../pmc_sint_cppinterface.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_sint_cppinterface.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_sint_cppinterface.o ../pmc_sint_cppinterface.cpp

../build/x64_Debug/pmc_statistics.o: ../pmc_statistics.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_statistics.o ../pmc_statistics.cpp

../build/x64_Debug/pmc_to.o: ../pmc_to.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_to.o ../pmc_to.cpp

../build/x64_Debug/pmc_tostring.o: ../pmc_tostring.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_bidirectionallistheader.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -D_M_X64 -DPALMTREEMATHCORESINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x64_Debug/pmc_tostring.o ../pmc_tostring.cpp

../build/x64_Debug/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	windres -c 65001 -o ../build/x64_Debug/version.o ../version.rc

