# EINT Examples

Here we exemplify the basic usage of the ``eint`` binary as well as the usage of the API for ``libeint.so``.

The next sections assume a successful installation of the package.

## Binary usage
<details>
<summary>Click me</summary>

By default, the binary will wait for user input,
```
>$ eint

```
The user shall provide valid (space- or comma-separated) CSV data. The stream will be terminated after pressing ``ENTER`` over an empty line. For example, assuming we want to calculate $`\int_0^1 dx\; x`$ using 5 points,
```
>$ eint
0.00
0.25
0.50
0.75
1.00
```
returns
```
5.0000000000e-01
```
By default, it integrates column by column,
```
>$ eint
0.00 1.00
0.25 1.25
0.50 1.50
0.75 1.75
1.00 2.00
```

```
5.0000000000e-01 1.5000000000e+00
```
This behaviour can be altered by the ``-t`` option, so it integrates row by row,
```
>$ eint -t
0.00 0.25 0.50 0.75 1.00
```

```
5.0000000000e-01
```
A CSV file can be fed by redirecting the standard input,
```
>$ eint < CSV.dat
```
or by employing the ``-f`` option,
```
>$ eint -f CSV.dat
```
The accuracy of the method depends on the number of discretisation points $N$: given a prime factorisation of $N-1$, $N-1 = 2^{n_2}3^{n_3}\cdots$, the user can employ a custom prime base $p$ by employing the ``-b`` option. If $p^{n_p}$ is a factor of $N-1$, then the expected accuracy of the result will be $\mathcal{O}(h^{2n_p})$. The default value is $p=2$.

For example, the following computes $`I = (10-1)^{-1}\int_1^{10} dx\; x^2 = 37`$ using $N = 10 = 3^2 + 1$ points,
```
eint -t -b 3
1 4 9 16 25 36 49 64 81 100
```
returns the exact result:
```
3.7000000000e+01
```
</details>

## API usage
<details>
<summary>Click me</summary>
The library includes the following functions:

```c
float extrapolation_float(float *array,
                          size_t sz,
                          int base);

double extrapolation_double(double *array,
                            size_t sz,
                            int base);
```
A basic usage can be found in the file ``Example.c``. This program can be compiled by running
```
export LD_LIBRARY_PATH=/usr/local/lib
gcc Example.c -o Run_Example -I/usr/local/include -leint -lm
./Run_Example
```
</details>
