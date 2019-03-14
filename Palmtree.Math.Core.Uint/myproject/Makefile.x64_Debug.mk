all: ../../dist/Debug/x64/Palmtree.Math.Core.Uint.dll

clean:
	rm -f ../../dist/Debug/x64/Palmtree.Math.Core.Uint.dll ../build/x64_Debug/Palmtree.Math.Core.Uint.map
	rm -r -f ../build/x64_Debug

OBJS = ../build/x64_Debug/cpuid.o ../build/x64_Debug/dllmain.o ../build/x64_Debug/pmc_add.o ../build/x64_Debug/pmc_bitwiseand.o ../build/x64_Debug/pmc_bitwiseor.o ../build/x64_Debug/pmc_bytes.o ../build/x64_Debug/pmc_compare.o ../build/x64_Debug/pmc_divrem.o ../build/x64_Debug/pmc_equals.o ../build/x64_Debug/pmc_exclusiveor.o ../build/x64_Debug/pmc_from.o ../build/x64_Debug/pmc_greatestcommondivisor.o ../build/x64_Debug/pmc_initialize.o ../build/x64_Debug/pmc_interface_csharp.o ../build/x64_Debug/pmc_log.o ../build/x64_Debug/pmc_memory.o ../build/x64_Debug/pmc_modpow.o ../build/x64_Debug/pmc_multiply.o ../build/x64_Debug/pmc_parse.o ../build/x64_Debug/pmc_pow.o ../build/x64_Debug/pmc_shift.o ../build/x64_Debug/pmc_statistics.o ../build/x64_Debug/pmc_subtruct.o ../build/x64_Debug/pmc_to.o ../build/x64_Debug/pmc_tostring.o ../build/x64_Debug/version.o

../../dist/Debug/x64/Palmtree.Math.Core.Uint.dll: $(OBJS) ../Palmtree.Math.Core.Uint.def
	mkdir -p ../../dist/Debug/x64
	g++ -o ../../dist/Debug/x64/Palmtree.Math.Core.Uint.dll $(OBJS) ../Palmtree.Math.Core.Uint.def -shared -static -lkernel32 -luser32 -mwindows -Wl,--enable-stdcall-fixup -Wl,-Map=../build/x64_Debug/Palmtree.Math.Core.Uint.map 

../build/x64_Debug/cpuid.o: ../cpuid.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/cpuid.o ../cpuid.cpp

../build/x64_Debug/dllmain.o: ../dllmain.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/dllmain.o ../dllmain.cpp

../build/x64_Debug/pmc_add.o: ../pmc_add.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_add.o ../pmc_add.cpp

../build/x64_Debug/pmc_bitwiseand.o: ../pmc_bitwiseand.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_bitwiseand.o ../pmc_bitwiseand.cpp

../build/x64_Debug/pmc_bitwiseor.o: ../pmc_bitwiseor.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_bitwiseor.o ../pmc_bitwiseor.cpp

../build/x64_Debug/pmc_bytes.o: ../pmc_bytes.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_bytes.o ../pmc_bytes.cpp

../build/x64_Debug/pmc_compare.o: ../pmc_compare.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_compare.o ../pmc_compare.cpp

../build/x64_Debug/pmc_divrem.o: ../pmc_divrem.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_divrem.o ../pmc_divrem.cpp

../build/x64_Debug/pmc_equals.o: ../pmc_equals.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_equals.o ../pmc_equals.cpp

../build/x64_Debug/pmc_exclusiveor.o: ../pmc_exclusiveor.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_exclusiveor.o ../pmc_exclusiveor.cpp

../build/x64_Debug/pmc_from.o: ../pmc_from.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_from.o ../pmc_from.cpp

../build/x64_Debug/pmc_greatestcommondivisor.o: ../pmc_greatestcommondivisor.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_greatestcommondivisor.o ../pmc_greatestcommondivisor.cpp

../build/x64_Debug/pmc_initialize.o: ../pmc_initialize.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_initialize.o ../pmc_initialize.cpp

../build/x64_Debug/pmc_interface_csharp.o: ../pmc_interface_csharp.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_exception.h  ../pmc_uint_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_interface_csharp.o ../pmc_interface_csharp.cpp

../build/x64_Debug/pmc_log.o: ../pmc_log.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_log.o ../pmc_log.cpp

../build/x64_Debug/pmc_memory.o: ../pmc_memory.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_memory.o ../pmc_memory.cpp

../build/x64_Debug/pmc_modpow.o: ../pmc_modpow.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_modpow.o ../pmc_modpow.cpp

../build/x64_Debug/pmc_multiply.o: ../pmc_multiply.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_multiply.o ../pmc_multiply.cpp

../build/x64_Debug/pmc_parse.o: ../pmc_parse.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_parse.o ../pmc_parse.cpp

../build/x64_Debug/pmc_pow.o: ../pmc_pow.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_pow.o ../pmc_pow.cpp

../build/x64_Debug/pmc_shift.o: ../pmc_shift.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_shift.o ../pmc_shift.cpp

../build/x64_Debug/pmc_statistics.o: ../pmc_statistics.cpp  ../pmc.h  ../pmc_cpuid.h  ../pmc_internal.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_statistics.o ../pmc_statistics.cpp

../build/x64_Debug/pmc_subtruct.o: ../pmc_subtruct.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_inline_func.h  ../pmc_resourceholder_uint.h  ../autogenerated_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_subtruct.o ../pmc_subtruct.cpp

../build/x64_Debug/pmc_to.o: ../pmc_to.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_to.o ../pmc_to.cpp

../build/x64_Debug/pmc_tostring.o: ../pmc_tostring.cpp  ../pmc.h  ../pmc_exception.h  ../pmc_cpuid.h  ../pmc_uint.h  ../pmc_internal.h  ../pmc_resourceholder.h  ../pmc_uint_internal.h  ../pmc_stringio.h  ../pmc_resourceholder_uint.h  ../pmc_inline_func.h  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	g++ -c -save-temps=obj -Werror -DENABLED_PERFORMANCE_COUNTER -fextended-identifiers -D_M_X64 -g -D_DEBUG  -o ../build/x64_Debug/pmc_tostring.o ../pmc_tostring.cpp

../build/x64_Debug/version.o: ../version.rc  ../mymakefile.xml
	mkdir -p ../build/x64_Debug
	windres -c 65001 -o ../build/x64_Debug/version.o ../version.rc

