```bash
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_PREFIX_PATH="C:/Qt/6.9.1/mingw_64" -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
#set PATH to qt bin before deploy (example - C:/Qt/6.9.1/mingw_64/bin)
windeployqt src/.
```
