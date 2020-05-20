call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang-cl.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang-cl.exe" -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja ./ "-DCMAKE_LINKER:FILEPATH=C:/Program Files/LLVM/bin/lld-link.exe"
ninja script_engine
