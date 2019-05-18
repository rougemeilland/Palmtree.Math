all: ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll

clean:
	rm -f ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll ../build/x64_Release/Palmtree.Math.Core.Uint.map
	rm -r -f ../build/x64_Release

OBJS = ../build/x64_Release/pmc_add.o ../build/x64_Release/pmc_atoi.o ../build/x64_Release/pmc_basic.o ../build/x64_Release/pmc_basic_add.o ../build/x64_Release/pmc_basic_bitwiseand.o ../build/x64_Release/pmc_basic_bitwiseor.o ../build/x64_Release/pmc_basic_compare.o ../build/x64_Release/pmc_basic_divrem.o ../build/x64_Release/pmc_basic_equals.o ../build/x64_Release/pmc_basic_exclusiveor.o ../build/x64_Release/pmc_basic_greatestcommondivisor.o ../build/x64_Release/pmc_basic_multiply.o ../build/x64_Release/pmc_basic_multiply_classic.o ../build/x64_Release/pmc_basic_multiply_karatsuba.o ../build/x64_Release/pmc_basic_multiply_schonHagestrassen.o ../build/x64_Release/pmc_basic_multiply_toomcook.o ../build/x64_Release/pmc_basic_onecompliment_and_bitwiseand.o ../build/x64_Release/pmc_basic_shift.o ../build/x64_Release/pmc_basic_subtruct.o ../build/x64_Release/pmc_bitwiseand.o ../build/x64_Release/pmc_bitwiseor.o ../build/x64_Release/pmc_bytes.o ../build/x64_Release/pmc_compare.o ../build/x64_Release/pmc_cpuid.o ../build/x64_Release/pmc_divideexactly.o ../build/x64_Release/pmc_divrem.o ../build/x64_Release/pmc_dllmain.o ../build/x64_Release/pmc_equals.o ../build/x64_Release/pmc_exclusiveor.o ../build/x64_Release/pmc_from.o ../build/x64_Release/pmc_greatestcommondivisor.o ../build/x64_Release/pmc_initialize.o ../build/x64_Release/pmc_interface_csharp.o ../build/x64_Release/pmc_internaltest.o ../build/x64_Release/pmc_itoa.o ../build/x64_Release/pmc_lock.o ../build/x64_Release/pmc_log.o ../build/x64_Release/pmc_memory.o ../build/x64_Release/pmc_modpow.o ../build/x64_Release/pmc_multiply.o ../build/x64_Release/pmc_onecompliment_and_bitwiseand.o ../build/x64_Release/pmc_parse.o ../build/x64_Release/pmc_parserstate.o ../build/x64_Release/pmc_pow.o ../build/x64_Release/pmc_random.o ../build/x64_Release/pmc_resourceholder.o ../build/x64_Release/pmc_resourceholder_uint.o ../build/x64_Release/pmc_round.o ../build/x64_Release/pmc_shift.o ../build/x64_Release/pmc_statistics.o ../build/x64_Release/pmc_stringio.o ../build/x64_Release/pmc_subtruct.o ../build/x64_Release/pmc_thousandseparatedstringwriter.o ../build/x64_Release/pmc_threadcontext.o ../build/x64_Release/pmc_to.o ../build/x64_Release/pmc_tostring.o ../build/x64_Release/pmc_tostringformatter.o ../build/x64_Release/pmc_tostringformattercustom.o ../build/x64_Release/pmc_tostringformattertypec.o ../build/x64_Release/pmc_tostringformattertyped.o ../build/x64_Release/pmc_tostringformattertypee.o ../build/x64_Release/pmc_tostringformattertypef.o ../build/x64_Release/pmc_tostringformattertypeg.o ../build/x64_Release/pmc_tostringformattertypen.o ../build/x64_Release/pmc_tostringformattertypep.o ../build/x64_Release/pmc_tostringformattertypex.o ../build/x64_Release/pmc_uint_cppinterface.o ../build/x64_Release/pmc___unit_type_array_chainbuffertag.o ../build/x64_Release/version.o ../../dist/Release/x64/Palmtree.Math.Core.Sfmt.dll

../../dist/Release/x64/Palmtree.Math.Core.Uint.dll: $(OBJS) ../Palmtree.Math.Core.Uint.def
	mkdir -p ../../dist/Release/x64
	g++ -o ../../dist/Release/x64/Palmtree.Math.Core.Uint.dll $(OBJS) ../Palmtree.Math.Core.Uint.def -shared -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Release/Palmtree.Math.Core.Uint.map -LZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/dist/Release/x64/

../build/x64_Release/pmc_add.o: ../pmc_add.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_add.o ../pmc_add.cpp

../build/x64_Release/pmc_atoi.o: ../pmc_atoi.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_atoi.o ../pmc_atoi.cpp

../build/x64_Release/pmc_basic.o: ../pmc_basic.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic.o ../pmc_basic.cpp

../build/x64_Release/pmc_basic_add.o: ../pmc_basic_add.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../pmc_autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_add.o ../pmc_basic_add.cpp

../build/x64_Release/pmc_basic_bitwiseand.o: ../pmc_basic_bitwiseand.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_bitwiseand.o ../pmc_basic_bitwiseand.cpp

../build/x64_Release/pmc_basic_bitwiseor.o: ../pmc_basic_bitwiseor.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_bitwiseor.o ../pmc_basic_bitwiseor.cpp

../build/x64_Release/pmc_basic_compare.o: ../pmc_basic_compare.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_compare.o ../pmc_basic_compare.cpp

../build/x64_Release/pmc_basic_divrem.o: ../pmc_basic_divrem.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_autogenerated_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_divrem.o ../pmc_basic_divrem.cpp

../build/x64_Release/pmc_basic_equals.o: ../pmc_basic_equals.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_equals.o ../pmc_basic_equals.cpp

../build/x64_Release/pmc_basic_exclusiveor.o: ../pmc_basic_exclusiveor.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_exclusiveor.o ../pmc_basic_exclusiveor.cpp

../build/x64_Release/pmc_basic_greatestcommondivisor.o: ../pmc_basic_greatestcommondivisor.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_greatestcommondivisor.o ../pmc_basic_greatestcommondivisor.cpp

../build/x64_Release/pmc_basic_multiply.o: ../pmc_basic_multiply.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../pmc_basic_multiply_classic.h  ../pmc_basic_multiply_karatsuba.h  ../pmc_basic_multiply_toomcook.h  ../pmc_basic_multiply_schonHagestrassen.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_multiply.o ../pmc_basic_multiply.cpp

../build/x64_Release/pmc_basic_multiply_classic.o: ../pmc_basic_multiply_classic.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic_multiply_classic.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_multiply_classic.o ../pmc_basic_multiply_classic.cpp

../build/x64_Release/pmc_basic_multiply_karatsuba.o: ../pmc_basic_multiply_karatsuba.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_basic_multiply_karatsuba.h  ../pmc_basic_multiply_classic.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_multiply_karatsuba.o ../pmc_basic_multiply_karatsuba.cpp

../build/x64_Release/pmc_basic_multiply_schonHagestrassen.o: ../pmc_basic_multiply_schonHagestrassen.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic_multiply_schonHagestrassen.h  ../pmc_basic_multiply_toomcook.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_multiply_schonHagestrassen.o ../pmc_basic_multiply_schonHagestrassen.cpp

../build/x64_Release/pmc_basic_multiply_toomcook.o: ../pmc_basic_multiply_toomcook.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic_multiply_toomcook.h  ../pmc_basic_multiply_karatsuba.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_multiply_toomcook.o ../pmc_basic_multiply_toomcook.cpp

../build/x64_Release/pmc_basic_onecompliment_and_bitwiseand.o: ../pmc_basic_onecompliment_and_bitwiseand.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_onecompliment_and_bitwiseand.o ../pmc_basic_onecompliment_and_bitwiseand.cpp

../build/x64_Release/pmc_basic_shift.o: ../pmc_basic_shift.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_shift.o ../pmc_basic_shift.cpp

../build/x64_Release/pmc_basic_subtruct.o: ../pmc_basic_subtruct.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../pmc_autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_basic_subtruct.o ../pmc_basic_subtruct.cpp

../build/x64_Release/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x64_Release/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x64_Release/pmc_bytes.o: ../pmc_bytes.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_bytes.o ../pmc_bytes.cpp

../build/x64_Release/pmc_compare.o: ../pmc_compare.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_compare.o ../pmc_compare.cpp

../build/x64_Release/pmc_cpuid.o: ../pmc_cpuid.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_cpuid.o ../pmc_cpuid.cpp

../build/x64_Release/pmc_divideexactly.o: ../pmc_divideexactly.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_divideexactly.o ../pmc_divideexactly.cpp

../build/x64_Release/pmc_divrem.o: ../pmc_divrem.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_divrem.o ../pmc_divrem.cpp

../build/x64_Release/pmc_dllmain.o: ../pmc_dllmain.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_dllmain.o ../pmc_dllmain.cpp

../build/x64_Release/pmc_equals.o: ../pmc_equals.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_equals.o ../pmc_equals.cpp

../build/x64_Release/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x64_Release/pmc_from.o: ../pmc_from.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_from.o ../pmc_from.cpp

../build/x64_Release/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x64_Release/pmc_initialize.o: ../pmc_initialize.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_initialize.o ../pmc_initialize.cpp

../build/x64_Release/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x64_Release/pmc_internaltest.o: ../pmc_internaltest.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_internaltest.o ../pmc_internaltest.cpp

../build/x64_Release/pmc_itoa.o: ../pmc_itoa.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_stringio.h  ../pmc_uint_internal.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_string.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_itoa.o ../pmc_itoa.cpp

../build/x64_Release/pmc_lock.o: ../pmc_lock.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_lock.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_lock.o ../pmc_lock.cpp

../build/x64_Release/pmc_log.o: ../pmc_log.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_log.o ../pmc_log.cpp

../build/x64_Release/pmc_memory.o: ../pmc_memory.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../pmc_threadcontext.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_memory.o ../pmc_memory.cpp

../build/x64_Release/pmc_modpow.o: ../pmc_modpow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_modpow.o ../pmc_modpow.cpp

../build/x64_Release/pmc_multiply.o: ../pmc_multiply.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_multiply.o ../pmc_multiply.cpp

../build/x64_Release/pmc_onecompliment_and_bitwiseand.o: ../pmc_onecompliment_and_bitwiseand.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_onecompliment_and_bitwiseand.o ../pmc_onecompliment_and_bitwiseand.cpp

../build/x64_Release/pmc_parse.o: ../pmc_parse.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_resourceholder_uint.h  ../pmc_parser.h  ../pmc_string.h  ../pmc_parserstate.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_parse.o ../pmc_parse.cpp

../build/x64_Release/pmc_parserstate.o: ../pmc_parserstate.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_parserstate.h  ../pmc_parser.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_parserstate.o ../pmc_parserstate.cpp

../build/x64_Release/pmc_pow.o: ../pmc_pow.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_pow.o ../pmc_pow.cpp

../build/x64_Release/pmc_random.o: ../pmc_random.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_random.o ../pmc_random.cpp

../build/x64_Release/pmc_resourceholder.o: ../pmc_resourceholder.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc_inline_func.h  ../pmc___unit_type_array_chainbuffertag.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_resourceholder.o ../pmc_resourceholder.cpp

../build/x64_Release/pmc_resourceholder_uint.o: ../pmc_resourceholder_uint.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_lock.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_basic.h  ../../Palmtree.Math.Core.Sfmt/pmc_sfmt.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_resourceholder_uint.o ../pmc_resourceholder_uint.cpp

../build/x64_Release/pmc_round.o: ../pmc_round.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_round.o ../pmc_round.cpp

../build/x64_Release/pmc_shift.o: ../pmc_shift.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_shift.o ../pmc_shift.cpp

../build/x64_Release/pmc_statistics.o: ../pmc_statistics.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_statistics.o ../pmc_statistics.cpp

../build/x64_Release/pmc_stringio.o: ../pmc_stringio.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_stringio.o ../pmc_stringio.cpp

../build/x64_Release/pmc_subtruct.o: ../pmc_subtruct.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x64_Release/pmc_thousandseparatedstringwriter.o: ../pmc_thousandseparatedstringwriter.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_thousandseparatedstringwriter.o ../pmc_thousandseparatedstringwriter.cpp

../build/x64_Release/pmc_threadcontext.o: ../pmc_threadcontext.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_threadcontext.h  ../pmc_exception.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_threadcontext.o ../pmc_threadcontext.cpp

../build/x64_Release/pmc_to.o: ../pmc_to.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_to.o ../pmc_to.cpp

../build/x64_Release/pmc_tostring.o: ../pmc_tostring.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_tostringformattercustom.h  ../pmc_tostringformattertypec.h  ../pmc_tostringformattertyped.h  ../pmc_tostringformattertypee.h  ../pmc_tostringformattertypef.h  ../pmc_tostringformattertypeg.h  ../pmc_tostringformattertypen.h  ../pmc_tostringformattertypep.h  ../pmc_tostringformattertypex.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostring.o ../pmc_tostring.cpp

../build/x64_Release/pmc_tostringformatter.o: ../pmc_tostringformatter.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformatter.h  ../pmc_resourceholder_uint.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformatter.o ../pmc_tostringformatter.cpp

../build/x64_Release/pmc_tostringformattercustom.o: ../pmc_tostringformattercustom.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_tostringformattercustom.h  ../pmc_threadcontext.h  ../pmc_string.h  ../pmc_lock.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattercustom.o ../pmc_tostringformattercustom.cpp

../build/x64_Release/pmc_tostringformattertypec.o: ../pmc_tostringformattertypec.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypec.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypec.o ../pmc_tostringformattertypec.cpp

../build/x64_Release/pmc_tostringformattertyped.o: ../pmc_tostringformattertyped.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertyped.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertyped.o ../pmc_tostringformattertyped.cpp

../build/x64_Release/pmc_tostringformattertypee.o: ../pmc_tostringformattertypee.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypee.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypee.o ../pmc_tostringformattertypee.cpp

../build/x64_Release/pmc_tostringformattertypef.o: ../pmc_tostringformattertypef.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypef.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypef.o ../pmc_tostringformattertypef.cpp

../build/x64_Release/pmc_tostringformattertypeg.o: ../pmc_tostringformattertypeg.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypeg.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypeg.o ../pmc_tostringformattertypeg.cpp

../build/x64_Release/pmc_tostringformattertypen.o: ../pmc_tostringformattertypen.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypen.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypen.o ../pmc_tostringformattertypen.cpp

../build/x64_Release/pmc_tostringformattertypep.o: ../pmc_tostringformattertypep.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_tostringformatter.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_tostringformattertypep.h  ../pmc_resourceholder_uint.h  ../pmc_thousandseparatedstringwriter.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypep.o ../pmc_tostringformattertypep.cpp

../build/x64_Release/pmc_tostringformattertypex.o: ../pmc_tostringformattertypex.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_inline_func.h  ../pmc_tostringformattertypex.h  ../pmc_resourceholder_uint.h  ../pmc_basic.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_tostringformattertypex.o ../pmc_tostringformattertypex.cpp

../build/x64_Release/pmc_uint_cppinterface.o: ../pmc_uint_cppinterface.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_bidirectionallistheader.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_thousandseparatedstringwriter.h  ../pmc_uint_cppinterface.h  ../pmc_resourceholder_uint.h  ../pmc_string.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc_uint_cppinterface.o ../pmc_uint_cppinterface.cpp

../build/x64_Release/pmc___unit_type_array_chainbuffertag.o: ../pmc___unit_type_array_chainbuffertag.cpp  ../pmc.h  ../pmc_uint.h  ../pmc_bidirectionallistheader.h  ../pmc_cpuid.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc___unit_type_array_chainbuffertag.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	g++ -c -save-temps=obj -Werror -D_M_X64 -DENABLED_PERFORMANCE_COUNTER -DPALMTREEMATHCOREUINT_EXPORTS -O2 -std=c++1z -IZ:/Sources/Lunor/Repos/rougemeilland/Palmtree.Math/Palmtree.Math.Core.Sfmt/ -o ../build/x64_Release/pmc___unit_type_array_chainbuffertag.o ../pmc___unit_type_array_chainbuffertag.cpp

../build/x64_Release/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x64_Release
	windres -c 65001 -o ../build/x64_Release/version.o ../version.rc

