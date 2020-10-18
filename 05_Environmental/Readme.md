Для сборки без UTF поддержки:
```
mkdir build
cd build
cmake ..  && make
```

Для сборки с UTF поддержкой:
```
mkdir build
cd build
cmake .. -DCMAKE_CXX_FLAGS="$(CMAKE_CXX_FLAGS) -DPCRE2_UCP=1"  && make
```

Также работает
```
make clean
```
