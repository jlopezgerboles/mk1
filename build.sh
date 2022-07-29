set echo on

mkdir bin

CFiles=$(find . -type f -name "*.c")
echo "Files found to be compiled:" $CFiles

echo "Building mk1 initialized"
assembly="game"
compilerflags="-g"
includeflags="-I$VULKAN_SDK/include"
linkerflags="-Lvulkan -L$VULKAN_SDK/Lib -lX11 -L/usr/X11R6/lib -no-pie"
echo "Compilation is using the Compiler flags: " $compilerflags
echo "Compilation is using the include flags: " $includeflags
echo "Compilation is using the linkerflags: " $linkerflags

echo "Building $assembly..."

echo gcc $CFiles $compilerflags $includeflags $linkerflags -o bin/$assembly
gcc $CFiles $compilerflags $includeflags $linkerflags -o bin/$assembly
