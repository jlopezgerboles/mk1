set echo on

#mkdir bin

CFiles=$(find . -type f -name "*.c")
echo "Files found to be compiled:" $CFiles

echo "Building game initialized"
assembly="game"
compilerflags="-g -fPIC"
includeflags="-Idev/mk1 -I$VULKAN_SDK/include"
linkerflags="-g -shared -Lvulkan -L$VULKAN_SDK/Lib -lX11 -L/usr/X11R6/lib -no-pie"
echo "Compilation is using the Compiler flags: " $compilerflags
echo "Compilation is using the include flags: " $includeflags
echo "Compilation is using the linkerflags: " $linkerflags

echo "Building $assembly..."

echo gcc $CFiles $compilerflags $includeflags $linkerflags -o $assembly
gcc $CFiles $compilerflags $includeflags $linkerflags -o $assembly
