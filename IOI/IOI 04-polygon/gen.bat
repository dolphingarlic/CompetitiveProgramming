g++ -Wall -DEVAL -static polygon.cpp -O2 -o polygon
FOR %%X in (01 02 03 04 05 06 07 08 09 10 11) DO polygon.exe < %%X > %%X.out
