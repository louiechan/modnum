# modnum

## 简介
  加入模的一些运算。
  项目结构如下：
```
.
├── CMakeLists.txt
├── README.md
├── include
│   ├── Matrix.h
│   ├── Utils.h
│   └── modnum.h
├── src
│   ├── Matrix.cpp
│   └── Utils.cpp
└── test
    └── PSE.cpp
```

## 安装
```shell
cd modnum
cmake .
make
make install
```
test中有一个n=3的多表替换加密的测代码
```shell
g++ PSE.cpp -l modnum -o PSE
./PSE
```
