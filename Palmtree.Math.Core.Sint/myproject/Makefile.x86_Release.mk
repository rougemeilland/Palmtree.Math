all: ../../dist/Release/x86/Palmtree.Math.Core.Sint.dll

clean:
	rm -f ../../dist/Release/x86/Palmtree.Math.Core.Sint.dll ../build/x86_Release/Palmtree.Math.Core.Sint.map
	rm -r -f ../build/x86_Release

OBJS = ../build/x86_Release/pmc_add_sub.o ../build/x86_Release/pmc_bitwiseand.o ../build/x86_Release/pmc_bitwiseor.o ../build/x86_Release/pmc_bytes.o ../build/x86_Release/pmc_compare.o ../build/x86_Release/pmc_divrem.o ../build/x86_Release/pmc_dllmain.o ../build/x86_Release/pmc_equals.o ../build/x86_Release/pmc_exclusiveor.o ../build/x86_Release/pmc_from.o ../build/x86_Release/pmc_greatestcommondivisor.o ../build/x86_Release/pmc_initialize.o ../build/x86_Release/pmc_interface_csharp.o ../build/x86_Release/pmc_memory.o ../build/x86_Release/pmc_multiply.o ../build/x86_Release/pmc_onecomplement.o ../build/x86_Release/pmc_parse.o ../build/x86_Release/pmc_shift.o ../build/x86_Release/pmc_sint_cppinterface.o ../build/x86_Release/pmc_statistics.o ../build/x86_Release/pmc_to.o ../build/x86_Release/pmc_tostring.o ../build/x86_Release/version.o ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll

../../dist/Release/x86/Palmtree.Math.Core.Sint.dll: $(OBJS) ../Palmtree.Math.Core.Sint.def
	mkdir -p ../../dist/Release/x86
	g++ -o ../../dist/Release/x86/Palmtree.Math.Core.Sint.dll $(OBJS) ../Palmtree.Math.Core.Sint.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Release/Palmtree.Math.Core.Sint.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x86/

../build/x86_Release/pmc_add_sub.o: ../pmc_add_sub.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_add_sub.o ../pmc_add_sub.cpp

../build/x86_Release/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x86_Release/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x86_Release/pmc_bytes.o: ../pmc_bytes.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_bytes.o ../pmc_bytes.cpp

../build/x86_Release/pmc_compare.o: ../pmc_compare.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_compare.o ../pmc_compare.cpp

../build/x86_Release/pmc_divrem.o: ../pmc_divrem.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_divrem.o ../pmc_divrem.cpp

../build/x86_Release/pmc_dllmain.o: ../pmc_dllmain.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x86_Release/pmc_equals.o: ../pmc_equals.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_equals.o ../pmc_equals.cpp

../build/x86_Release/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x86_Release/pmc_from.o: ../pmc_from.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_from.o ../pmc_from.cpp

../build/x86_Release/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x86_Release/pmc_initialize.o: ../pmc_initialize.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_initialize.o ../pmc_initialize.cpp

../build/x86_Release/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x86_Release/pmc_memory.o: ../pmc_memory.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../../Palmtree.Math.Core.Uint/pmc_inline_func.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_memory.o ../pmc_memory.cpp

../build/x86_Release/pmc_multiply.o: ../pmc_multiply.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_multiply.o ../pmc_multiply.cpp

../build/x86_Release/pmc_onecomplement.o: ../pmc_onecomplement.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_onecomplement.o ../pmc_onecomplement.cpp

../build/x86_Release/pmc_parse.o: ../pmc_parse.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_parse.o ../pmc_parse.cpp

../build/x86_Release/pmc_shift.o: ../pmc_shift.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../../Palmtree.Math.Core.Uint/pmc_resourceholder.h  ../pmc_sint_internal.h  ../pmc_resourceholder_sint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_shift.o ../pmc_shift.cpp

../build/x86_Release/pmc_sint_cppinterface.o: ../pmc_sint_cppinterface.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../pmc_sint_cppinterface.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_sint_cppinterface.o ../pmc_sint_cppinterface.cpp

../build/x86_Release/pmc_statistics.o: ../pmc_statistics.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_statistics.o ../pmc_statistics.cpp

../build/x86_Release/pmc_to.o: ../pmc_to.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_to.o ../pmc_to.cpp

../build/x86_Release/pmc_tostring.o: ../pmc_tostring.cpp  ../../Palmtree.Math.Core.Uint/pmc.h  ../../Palmtree.Math.Core.Uint/pmc_uint.h  ../../Palmtree.Math.Core.Uint/pmc_cpuid.h  ../pmc_sint.h  ../../Palmtree.Math.Core.Uint/pmc_internal.h  ../../Palmtree.Math.Core.Uint/pmc_exception.h  ../../Palmtree.Math.Core.Uint/pmc_uint_cppinterface.h  ../pmc_sint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DPALMTREEMATHCORESINT_EXPORTS -O2 -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Uint/ -o ../build/x86_Release/pmc_tostring.o ../pmc_tostring.cpp

../build/x86_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	windres -c 65001 -o ../build/x86_Release/version.o ../version.rc

