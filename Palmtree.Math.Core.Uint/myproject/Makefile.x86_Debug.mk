all: ../../dist/Debug/x86/Palmtree.Math.Core.Uint.dll

clean:
	rm -f ../../dist/Debug/x86/Palmtree.Math.Core.Uint.dll ../build/x86_Debug/Palmtree.Math.Core.Uint.map
	rm -r -f ../build/x86_Debug

OBJS = ../build/x86_Debug/pmc_add.o ../build/x86_Debug/pmc_atoi.o ../build/x86_Debug/pmc_basic_divrem.o ../build/x86_Debug/pmc_basic_multiply.o ../build/x86_Debug/pmc_basic_multiply_classic.o ../build/x86_Debug/pmc_basic_multiply_karatsuba.o ../build/x86_Debug/pmc_basic_multiply_schonHagestrassen.o ../build/x86_Debug/pmc_basic_multiply_toomcook.o ../build/x86_Debug/pmc_bitwiseand.o ../build/x86_Debug/pmc_bitwiseor.o ../build/x86_Debug/pmc_bytes.o ../build/x86_Debug/pmc_compare.o ../build/x86_Debug/pmc_cpuid.o ../build/x86_Debug/pmc_divideexactly.o ../build/x86_Debug/pmc_divrem.o ../build/x86_Debug/pmc_dllmain.o ../build/x86_Debug/pmc_equals.o ../build/x86_Debug/pmc_exclusiveor.o ../build/x86_Debug/pmc_from.o ../build/x86_Debug/pmc_greatestcommondivisor.o ../build/x86_Debug/pmc_initialize.o ../build/x86_Debug/pmc_interface_csharp.o ../build/x86_Debug/pmc_internaltest.o ../build/x86_Debug/pmc_itoa.o ../build/x86_Debug/pmc_lock.o ../build/x86_Debug/pmc_log.o ../build/x86_Debug/pmc_memory.o ../build/x86_Debug/pmc_modpow.o ../build/x86_Debug/pmc_multiply.o ../build/x86_Debug/pmc_onecompliment_and_bitwiseand.o ../build/x86_Debug/pmc_parse.o ../build/x86_Debug/pmc_parserstate.o ../build/x86_Debug/pmc_pow.o ../build/x86_Debug/pmc_random.o ../build/x86_Debug/pmc_resourceholder.o ../build/x86_Debug/pmc_resourceholder_uint.o ../build/x86_Debug/pmc_round.o ../build/x86_Debug/pmc_shift.o ../build/x86_Debug/pmc_statistics.o ../build/x86_Debug/pmc_stringio.o ../build/x86_Debug/pmc_subtruct.o ../build/x86_Debug/pmc_thousandseparatedstringwriter.o ../build/x86_Debug/pmc_threadcontext.o ../build/x86_Debug/pmc_to.o ../build/x86_Debug/pmc_tostring.o ../build/x86_Debug/pmc_tostringformatter.o ../build/x86_Debug/pmc_tostringformattercustom.o ../build/x86_Debug/pmc_tostringformattertypec.o ../build/x86_Debug/pmc_tostringformattertyped.o ../build/x86_Debug/pmc_tostringformattertypee.o ../build/x86_Debug/pmc_tostringformattertypef.o ../build/x86_Debug/pmc_tostringformattertypeg.o ../build/x86_Debug/pmc_tostringformattertypen.o ../build/x86_Debug/pmc_tostringformattertypep.o ../build/x86_Debug/pmc_tostringformattertypex.o ../build/x86_Debug/pmc_uint_cppinterface.o ../build/x86_Debug/pmc___unit_type_array_chainbuffertag.o ../build/x86_Debug/version.o ../../dist/Release/x86/Palmtree.Math.Core.Sfmt.dll

../../dist/Debug/x86/Palmtree.Math.Core.Uint.dll: $(OBJS) ../Palmtree.Math.Core.Uint.def
	mkdir -p ../../dist/Debug/x86
	g++ -o ../../dist/Debug/x86/Palmtree.Math.Core.Uint.dll $(OBJS) ../Palmtree.Math.Core.Uint.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Debug/Palmtree.Math.Core.Uint.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x86/

../build/x86_Debug/pmc_add.o: ../pmc_add.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_add.o ../pmc_add.cpp

../build/x86_Debug/pmc_atoi.o: ../pmc_atoi.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_atoi.o ../pmc_atoi.cpp

../build/x86_Debug/pmc_basic_divrem.o: ../pmc_basic_divrem.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_divrem.o ../pmc_basic_divrem.cpp

../build/x86_Debug/pmc_basic_multiply.o: ../pmc_basic_multiply.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_inline_func.h  ../pmc_uint_internal.h  ../pmc_autogenerated_inline_func.h  ../pmc_basic.h  ../pmc_multiply_classic.h  ../pmc_multiply_karatsuba.h  ../pmc_multiply_toomcook.h  ../pmc_multiply_schonHagestrassen.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_multiply.o ../pmc_basic_multiply.cpp

../build/x86_Debug/pmc_basic_multiply_classic.o: ../pmc_basic_multiply_classic.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_multiply_classic.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_multiply_classic.o ../pmc_basic_multiply_classic.cpp

../build/x86_Debug/pmc_basic_multiply_karatsuba.o: ../pmc_basic_multiply_karatsuba.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_basic.h  ../pmc_multiply_karatsuba.h  ../pmc_multiply_classic.h  ../pmc_resourceholder_uint.h  ../pmc_signedunitarray.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_multiply_karatsuba.o ../pmc_basic_multiply_karatsuba.cpp

../build/x86_Debug/pmc_basic_multiply_schonHagestrassen.o: ../pmc_basic_multiply_schonHagestrassen.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_multiply_schonHagestrassen.h  ../pmc_multiply_toomcook.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_multiply_schonHagestrassen.o ../pmc_basic_multiply_schonHagestrassen.cpp

../build/x86_Debug/pmc_basic_multiply_toomcook.o: ../pmc_basic_multiply_toomcook.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_multiply_toomcook.h  ../pmc_multiply_karatsuba.h  ../pmc_multiply_classic.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_basic_multiply_toomcook.o ../pmc_basic_multiply_toomcook.cpp

../build/x86_Debug/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x86_Debug/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x86_Debug/pmc_bytes.o: ../pmc_bytes.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_bytes.o ../pmc_bytes.cpp

../build/x86_Debug/pmc_compare.o: ../pmc_compare.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_inline_func.h  ../pmc_uint_internal.h  ../pmc_autogenerated_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_compare.o ../pmc_compare.cpp

../build/x86_Debug/pmc_cpuid.o: ../pmc_cpuid.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_cpuid.o ../pmc_cpuid.cpp

../build/x86_Debug/pmc_divideexactly.o: ../pmc_divideexactly.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_divideexactly.o ../pmc_divideexactly.cpp

../build/x86_Debug/pmc_divrem.o: ../pmc_divrem.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_divrem.o ../pmc_divrem.cpp

../build/x86_Debug/pmc_dllmain.o: ../pmc_dllmain.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x86_Debug/pmc_equals.o: ../pmc_equals.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_inline_func.h  ../pmc_uint_internal.h  ../pmc_autogenerated_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_equals.o ../pmc_equals.cpp

../build/x86_Debug/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x86_Debug/pmc_from.o: ../pmc_from.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_from.o ../pmc_from.cpp

../build/x86_Debug/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x86_Debug/pmc_initialize.o: ../pmc_initialize.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_initialize.o ../pmc_initialize.cpp

../build/x86_Debug/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x86_Debug/pmc_internaltest.o: ../pmc_internaltest.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_internaltest.o ../pmc_internaltest.cpp

../build/x86_Debug/pmc_itoa.o: ../pmc_itoa.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_itoa.o ../pmc_itoa.cpp

../build/x86_Debug/pmc_lock.o: ../pmc_lock.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_lock.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_lock.o ../pmc_lock.cpp

../build/x86_Debug/pmc_log.o: ../pmc_log.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_log.o ../pmc_log.cpp

../build/x86_Debug/pmc_memory.o: ../pmc_memory.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../pmc_threadcontext.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_memory.o ../pmc_memory.cpp

../build/x86_Debug/pmc_modpow.o: ../pmc_modpow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_modpow.o ../pmc_modpow.cpp

../build/x86_Debug/pmc_multiply.o: ../pmc_multiply.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_multiply.o ../pmc_multiply.cpp

../build/x86_Debug/pmc_onecompliment_and_bitwiseand.o: ../pmc_onecompliment_and_bitwiseand.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_onecompliment_and_bitwiseand.o ../pmc_onecompliment_and_bitwiseand.cpp

../build/x86_Debug/pmc_parse.o: ../pmc_parse.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_string.h  ../pmc_parserstate.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_parse.o ../pmc_parse.cpp

../build/x86_Debug/pmc_parserstate.o: ../pmc_parserstate.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_parserstate.h  ../pmc_parser.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_parserstate.o ../pmc_parserstate.cpp

../build/x86_Debug/pmc_pow.o: ../pmc_pow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_pow.o ../pmc_pow.cpp

../build/x86_Debug/pmc_random.o: ../pmc_random.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_random.o ../pmc_random.cpp

../build/x86_Debug/pmc_resourceholder.o: ../pmc_resourceholder.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc_inline_func.h  ../pmc___unit_type_array_chainbuffertag.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_resourceholder.o ../pmc_resourceholder.cpp

../build/x86_Debug/pmc_resourceholder_uint.o: ../pmc_resourceholder_uint.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_basic.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_resourceholder_uint.o ../pmc_resourceholder_uint.cpp

../build/x86_Debug/pmc_round.o: ../pmc_round.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_round.o ../pmc_round.cpp

../build/x86_Debug/pmc_shift.o: ../pmc_shift.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_shift.o ../pmc_shift.cpp

../build/x86_Debug/pmc_statistics.o: ../pmc_statistics.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_statistics.o ../pmc_statistics.cpp

../build/x86_Debug/pmc_stringio.o: ../pmc_stringio.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_stringio.o ../pmc_stringio.cpp

../build/x86_Debug/pmc_subtruct.o: ../pmc_subtruct.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x86_Debug/pmc_thousandseparatedstringwriter.o: ../pmc_thousandseparatedstringwriter.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_thousandseparatedstringwriter.o ../pmc_thousandseparatedstringwriter.cpp

../build/x86_Debug/pmc_threadcontext.o: ../pmc_threadcontext.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_threadcontext.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_threadcontext.o ../pmc_threadcontext.cpp

../build/x86_Debug/pmc_to.o: ../pmc_to.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_to.o ../pmc_to.cpp

../build/x86_Debug/pmc_tostring.o: ../pmc_tostring.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_tostringformattercustom.h  ../pmc_tostringformattertypec.h  ../pmc_tostringformattertyped.h  ../pmc_tostringformattertypee.h  ../pmc_tostringformattertypef.h  ../pmc_tostringformattertypeg.h  ../pmc_tostringformattertypen.h  ../pmc_tostringformattertypep.h  ../pmc_tostringformattertypex.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostring.o ../pmc_tostring.cpp

../build/x86_Debug/pmc_tostringformatter.o: ../pmc_tostringformatter.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformatter.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformatter.o ../pmc_tostringformatter.cpp

../build/x86_Debug/pmc_tostringformattercustom.o: ../pmc_tostringformattercustom.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformattercustom.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattercustom.o ../pmc_tostringformattercustom.cpp

../build/x86_Debug/pmc_tostringformattertypec.o: ../pmc_tostringformattertypec.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypec.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypec.o ../pmc_tostringformattertypec.cpp

../build/x86_Debug/pmc_tostringformattertyped.o: ../pmc_tostringformattertyped.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertyped.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertyped.o ../pmc_tostringformattertyped.cpp

../build/x86_Debug/pmc_tostringformattertypee.o: ../pmc_tostringformattertypee.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypee.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypee.o ../pmc_tostringformattertypee.cpp

../build/x86_Debug/pmc_tostringformattertypef.o: ../pmc_tostringformattertypef.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypef.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypef.o ../pmc_tostringformattertypef.cpp

../build/x86_Debug/pmc_tostringformattertypeg.o: ../pmc_tostringformattertypeg.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypeg.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypeg.o ../pmc_tostringformattertypeg.cpp

../build/x86_Debug/pmc_tostringformattertypen.o: ../pmc_tostringformattertypen.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypen.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypen.o ../pmc_tostringformattertypen.cpp

../build/x86_Debug/pmc_tostringformattertypep.o: ../pmc_tostringformattertypep.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypep.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypep.o ../pmc_tostringformattertypep.cpp

../build/x86_Debug/pmc_tostringformattertypex.o: ../pmc_tostringformattertypex.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_autogenerated_inline_func.h  ../pmc_tostringformattertypex.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_tostringformattertypex.o ../pmc_tostringformattertypex.cpp

../build/x86_Debug/pmc_uint_cppinterface.o: ../pmc_uint_cppinterface.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_uint_cppinterface.h  ../pmc_resourceholder_uint.h  ../pmc_string.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc_uint_cppinterface.o ../pmc_uint_cppinterface.cpp

../build/x86_Debug/pmc___unit_type_array_chainbuffertag.o: ../pmc___unit_type_array_chainbuffertag.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -g -D_DEBUG -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x86_Debug/pmc___unit_type_array_chainbuffertag.o ../pmc___unit_type_array_chainbuffertag.cpp

../build/x86_Debug/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x86_Debug
	windres -c 65001 -o ../build/x86_Debug/version.o ../version.rc

