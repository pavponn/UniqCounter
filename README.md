# UniqCounter
Implementation of HyperLogLog algorithm to count number of unique elements in data stream. Project for VK Internship 2019.
 
Article: https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/40671.pdf
## Сборка и запуск 
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./UniqCounter
```

## Задание

Необходимо написать алгоритм, который приблизительно подсчитывает количество различных чисел в массиве, используя константный объём памяти. 

Более формально, надо реализовать класс с двумя функциями:

- `void add(int x);` — добавить число x к набору;
- `int get_uniq_num();` — возвращает приблизительное количество различных чисел, которые были переданы в функцию add.

Ваш класс должен использовать не более 32 Кб памяти. 
