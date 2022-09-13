#pragma once

#include <glslang/glslang_c_interface.h>


#if !defined(_DEBUG) && !defined(DEBUG) 
 
#pragma comment(lib,"OSDependent.lib")
#pragma comment(lib,"HLSL.lib")
#pragma comment(lib,"glslang.lib")
#pragma comment(lib,"SPVRemapper.lib")
#pragma comment(lib,"SPIRV.lib")
#pragma comment(lib,"OGLCompiler.lib")
#pragma comment(lib,"MachineIndependent.lib")
#pragma comment(lib,"GenericCodeGen.lib")
#pragma comment(lib,"glslang-default-resource-limits.lib")

#else

#pragma comment(lib,"glslangd.lib")
#pragma comment(lib,"MachineIndependentd.lib")
#pragma comment(lib,"GenericCodeGend.lib")
#pragma comment(lib,"OSDependentd.lib")
#pragma comment(lib,"SPVRemapperd.lib")
#pragma comment(lib,"SPIRVd.lib")
#pragma comment(lib,"HLSLd.lib")
#pragma comment(lib,"OGLCompilerd.lib")
#pragma comment(lib,"glslang-default-resource-limitsd.lib")

#endif