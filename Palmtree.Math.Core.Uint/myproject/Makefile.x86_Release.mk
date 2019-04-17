all: ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll

clean:
	rm -f ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll ../build/x86_Release/Palmtree.Math.Core.Uint.map
	rm -r -f ../build/x86_Release

OBJS = ../build/x86_Release/pmc_add.o ../build/x86_Release/pmc_atoi.o ../build/x86_Release/pmc_bitwiseand.o ../build/x86_Release/pmc_bitwiseor.o ../build/x86_Release/pmc_bytes.o ../build/x86_Release/pmc_compare.o ../build/x86_Release/pmc_cpuid.o ../build/x86_Release/pmc_divrem.o ../build/x86_Release/pmc_dllmain.o ../build/x86_Release/pmc_equals.o ../build/x86_Release/pmc_exclusiveor.o ../build/x86_Release/pmc_from.o ../build/x86_Release/pmc_greatestcommondivisor.o ../build/x86_Release/pmc_initialize.o ../build/x86_Release/pmc_interface_csharp.o ../build/x86_Release/pmc_internaltest.o ../build/x86_Release/pmc_itoa.o ../build/x86_Release/pmc_lock.o ../build/x86_Release/pmc_log.o ../build/x86_Release/pmc_memory.o ../build/x86_Release/pmc_modpow.o ../build/x86_Release/pmc_multiply.o ../build/x86_Release/pmc_onecompliment_and_bitwiseand.o ../build/x86_Release/pmc_parse.o ../build/x86_Release/pmc_parserstate.o ../build/x86_Release/pmc_pow.o ../build/x86_Release/pmc_resourceholder.o ../build/x86_Release/pmc_resourceholder_uint.o ../build/x86_Release/pmc_round.o ../build/x86_Release/pmc_shift.o ../build/x86_Release/pmc_statistics.o ../build/x86_Release/pmc_stringio.o ../build/x86_Release/pmc_subtruct.o ../build/x86_Release/pmc_thousandseparatedstringwriter.o ../build/x86_Release/pmc_threadcontext.o ../build/x86_Release/pmc_to.o ../build/x86_Release/pmc_tostring.o ../build/x86_Release/pmc_tostringformatter.o ../build/x86_Release/pmc_tostringformattercustom.o ../build/x86_Release/pmc_tostringformattertypec.o ../build/x86_Release/pmc_tostringformattertyped.o ../build/x86_Release/pmc_tostringformattertypee.o ../build/x86_Release/pmc_tostringformattertypef.o ../build/x86_Release/pmc_tostringformattertypeg.o ../build/x86_Release/pmc_tostringformattertypen.o ../build/x86_Release/pmc_tostringformattertypep.o ../build/x86_Release/pmc_tostringformattertypex.o ../build/x86_Release/pmc_uint_cppinterface.o ../build/x86_Release/pmc___unit_type_array_chainbuffertag.o ../build/x86_Release/version.o

../../dist/Release/x86/Palmtree.Math.Core.Uint.dll: $(OBJS) ../Palmtree.Math.Core.Uint.def
	mkdir -p ../../dist/Release/x86
	g++ -o ../../dist/Release/x86/Palmtree.Math.Core.Uint.dll $(OBJS) ../Palmtree.Math.Core.Uint.def -shared -static -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x86_Release/Palmtree.Math.Core.Uint.map 

../build/x86_Release/pmc_add.o: ../pmc_add.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_add.o ../pmc_add.cpp

../build/x86_Release/pmc_atoi.o: ../pmc_atoi.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_atoi.o ../pmc_atoi.cpp

../build/x86_Release/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x86_Release/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x86_Release/pmc_bytes.o: ../pmc_bytes.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_bytes.o ../pmc_bytes.cpp

../build/x86_Release/pmc_compare.o: ../pmc_compare.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_compare.o ../pmc_compare.cpp

../build/x86_Release/pmc_cpuid.o: ../pmc_cpuid.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_cpuid.o ../pmc_cpuid.cpp

../build/x86_Release/pmc_divrem.o: ../pmc_divrem.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_divrem.o ../pmc_divrem.cpp

../build/x86_Release/pmc_dllmain.o: ../pmc_dllmain.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x86_Release/pmc_equals.o: ../pmc_equals.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_equals.o ../pmc_equals.cpp

../build/x86_Release/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x86_Release/pmc_from.o: ../pmc_from.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_from.o ../pmc_from.cpp

../build/x86_Release/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x86_Release/pmc_initialize.o: ../pmc_initialize.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_initialize.o ../pmc_initialize.cpp

../build/x86_Release/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x86_Release/pmc_internaltest.o: ../pmc_internaltest.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_internaltest.o ../pmc_internaltest.cpp

../build/x86_Release/pmc_itoa.o: ../pmc_itoa.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_itoa.o ../pmc_itoa.cpp

../build/x86_Release/pmc_lock.o: ../pmc_lock.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_lock.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_lock.o ../pmc_lock.cpp

../build/x86_Release/pmc_log.o: ../pmc_log.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_log.o ../pmc_log.cpp

../build/x86_Release/pmc_memory.o: ../pmc_memory.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../pmc_threadcontext.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_memory.o ../pmc_memory.cpp

../build/x86_Release/pmc_modpow.o: ../pmc_modpow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_modpow.o ../pmc_modpow.cpp

../build/x86_Release/pmc_multiply.o: ../pmc_multiply.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_multiply.o ../pmc_multiply.cpp

../build/x86_Release/pmc_onecompliment_and_bitwiseand.o: ../pmc_onecompliment_and_bitwiseand.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_onecompliment_and_bitwiseand.o ../pmc_onecompliment_and_bitwiseand.cpp

../build/x86_Release/pmc_parse.o: ../pmc_parse.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_string.h  ../pmc_parserstate.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_parse.o ../pmc_parse.cpp

../build/x86_Release/pmc_parserstate.o: ../pmc_parserstate.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_parserstate.h  ../pmc_parser.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_parserstate.o ../pmc_parserstate.cpp

../build/x86_Release/pmc_pow.o: ../pmc_pow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_pow.o ../pmc_pow.cpp

../build/x86_Release/pmc_resourceholder.o: ../pmc_resourceholder.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc_inline_func.h  ../pmc___unit_type_array_chainbuffertag.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_resourceholder.o ../pmc_resourceholder.cpp

../build/x86_Release/pmc_resourceholder_uint.o: ../pmc_resourceholder_uint.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_resourceholder_uint.o ../pmc_resourceholder_uint.cpp

../build/x86_Release/pmc_round.o: ../pmc_round.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_round.o ../pmc_round.cpp

../build/x86_Release/pmc_shift.o: ../pmc_shift.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_shift.o ../pmc_shift.cpp

../build/x86_Release/pmc_statistics.o: ../pmc_statistics.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_statistics.o ../pmc_statistics.cpp

../build/x86_Release/pmc_stringio.o: ../pmc_stringio.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_stringio.o ../pmc_stringio.cpp

../build/x86_Release/pmc_subtruct.o: ../pmc_subtruct.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x86_Release/pmc_thousandseparatedstringwriter.o: ../pmc_thousandseparatedstringwriter.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_thousandseparatedstringwriter.o ../pmc_thousandseparatedstringwriter.cpp

../build/x86_Release/pmc_threadcontext.o: ../pmc_threadcontext.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_threadcontext.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_threadcontext.o ../pmc_threadcontext.cpp

../build/x86_Release/pmc_to.o: ../pmc_to.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_to.o ../pmc_to.cpp

../build/x86_Release/pmc_tostring.o: ../pmc_tostring.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_tostringformattercustom.h  ../pmc_tostringformattertypec.h  ../pmc_tostringformattertyped.h  ../pmc_tostringformattertypee.h  ../pmc_tostringformattertypef.h  ../pmc_tostringformattertypeg.h  ../pmc_tostringformattertypen.h  ../pmc_tostringformattertypep.h  ../pmc_tostringformattertypex.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostring.o ../pmc_tostring.cpp

../build/x86_Release/pmc_tostringformatter.o: ../pmc_tostringformatter.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformatter.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformatter.o ../pmc_tostringformatter.cpp

../build/x86_Release/pmc_tostringformattercustom.o: ../pmc_tostringformattercustom.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformattercustom.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattercustom.o ../pmc_tostringformattercustom.cpp

../build/x86_Release/pmc_tostringformattertypec.o: ../pmc_tostringformattertypec.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypec.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypec.o ../pmc_tostringformattertypec.cpp

../build/x86_Release/pmc_tostringformattertyped.o: ../pmc_tostringformattertyped.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertyped.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertyped.o ../pmc_tostringformattertyped.cpp

../build/x86_Release/pmc_tostringformattertypee.o: ../pmc_tostringformattertypee.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypee.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypee.o ../pmc_tostringformattertypee.cpp

../build/x86_Release/pmc_tostringformattertypef.o: ../pmc_tostringformattertypef.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypef.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypef.o ../pmc_tostringformattertypef.cpp

../build/x86_Release/pmc_tostringformattertypeg.o: ../pmc_tostringformattertypeg.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypeg.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypeg.o ../pmc_tostringformattertypeg.cpp

../build/x86_Release/pmc_tostringformattertypen.o: ../pmc_tostringformattertypen.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypen.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypen.o ../pmc_tostringformattertypen.cpp

../build/x86_Release/pmc_tostringformattertypep.o: ../pmc_tostringformattertypep.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypep.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypep.o ../pmc_tostringformattertypep.cpp

../build/x86_Release/pmc_tostringformattertypex.o: ../pmc_tostringformattertypex.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypex.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_tostringformattertypex.o ../pmc_tostringformattertypex.cpp

../build/x86_Release/pmc_uint_cppinterface.o: ../pmc_uint_cppinterface.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_uint_cppinterface.h  ../pmc_resourceholder_uint.h  ../pmc_string.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc_uint_cppinterface.o ../pmc_uint_cppinterface.cpp

../build/x86_Release/pmc___unit_type_array_chainbuffertag.o: ../pmc___unit_type_array_chainbuffertag.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	g++ -c -save-temps=obj -Werror -D_M_IX86 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z  -o ../build/x86_Release/pmc___unit_type_array_chainbuffertag.o ../pmc___unit_type_array_chainbuffertag.cpp

../build/x86_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x86_Release
	windres -c 65001 -o ../build/x86_Release/version.o ../version.rc

