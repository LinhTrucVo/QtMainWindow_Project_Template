## Getting Started

### Clone the Repository

To clone this repository with all submodules:

```bash
git clone --recurse-submodules https://github.com/LinhTrucVo/QtMainWindow_Project_Template.git
cd QtMainWindow_Project_Template
```

If you already cloned the repository without submodules, initialize them:

```bash
git submodule update --init --recursive
```

or update them:

```bash
git submodule update --remote --recursive
```

After update submodule:

```bash
git add src/lib/QtLib_Project_Template
git commit -m "updare submodule"
git push
```

## Submodules

This project uses the following submodules:

- **QtLib_Project_Template**: Core PyQt threading and messaging library
  - Repository: https://github.com/LinhTrucVo/QtLib_Project_Template.git
  - Path: `src/QtLib_Project_Template`

## Deploy

```bash
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_PREFIX_PATH="C:/Qt/6.9.1/mingw_64" -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
#set PATH to qt bin before deploy (example - C:/Qt/6.9.1/mingw_64/bin)
windeployqt src/.
```

## Create Code
```sh
cd src/lib/QtLib_Project_Template/tool
python create_client_code.py
```
<img width="267" height="182" alt="image" src="https://github.com/user-attachments/assets/1ff44df0-d6a1-4413-9d37-5b907d91ca37" />
