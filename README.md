[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.17390545.svg)](https://doi.org/10.5281/zenodo.17390545)
# EINT

Numerically integrate data employing the extrapolation method.

## Build

### Dependencies:
- ``make``,
- ``gcc``, and
- ``gfortran``.

### Installing:
```
make
sudo make install PREFIX=/usr/local
```
Default installation in ``/usr/local``. Installs:
- ``eint``: executable program which processes CSV data to compute integrals numerically,
- ``libeint.so``: shared library providing the functions ``extrapolation_float``, and ``extrapolation_double``;
- ``EINT_C.h``: C header file for ``libeint.so``, and
- ``EINT_F.h``: Fortran header file for ``libeint.so``.
### Uninstalling
```
sudo make uninstall PREFIX=/usr/local
```

### Parallel build

<details>
<summary>Click me</summary>

We provide a makefile for a OpenMP-parallelised build. The parallelisation target is the computation of the trapezoidal rule sums.

To employ this option, use
```
cp profiles/parallel.make Makefile
```
and then follow the instructions for a regular installation.

</details>

## Description

EINT computes integrals of the form

$$
I = \frac{1}{b-a}\int_{a}^{b}f(x)dx,
$$

using the extrapolation (a.k.a. Romberg integration) method. We assume that the $[a, b]$ interval is discretised as

$$
x \to x_i = a + (b-a)\frac{i-1}{N-1} = a + (i-1)h : i\in[1, N],
$$

and that the array of values $`\{f(x_i): i\in[1, N]\}`$ is known. We call $N$ the number of discretisation points, and $h$ the "step size". EINT returns the integral $I$ after entering the array of values $`\{f(x_i)\}`$.

The accuracy of the method depends on $N$. Given a prime factorisation of $N-1$, $N-1 = 2^{n_2}3^{n_3}\cdots$, the extrapolation method can be applied with an arbitrary prime base $p$. If $p^{n_p}$ is a factor of $N-1$, then the expected accuracy of the result will be $\mathcal{O}(h^{2n_p})$.

## Usage

After installation, the manual page is available

```
man eint
```

Additional resources, use cases and examples can be found in the ``example/`` directory.

### Quick example

Compute $`\int_0^1 dx\; x`$ using $N = 5$.
```
echo "0.0 0.25 0.5 0.75 1.0" | eint -t
```

## Testing

<details>
<summary>Click me</summary>

### Dependencies:

- ``make``,
- ``gcc``,
- ``gfortran``,
- ``clang``,
- ``clang-format`` (>= ``v20.1``),
- ``clang-tidy`` (>= ``v20.1``),
- ``fypp``,
- ``pre-commit``,
- ``valgrind``,
- ``gcov``,
- ``lcov``, and
- ``genhtml``.

Install ``pre-commit``:
```
pre-commit install
```

Updating the source code:
```
fypp src/EINT_Core.fypp src/EINT_Core.F90
fypp src/Prime_Factors.fypp src/Prime_Factors.F90
```

Testing:
```
make test
```

``LCOV`` report:
```
firefox test/report/index.html
```

``valgrind`` runs (serial and parallel):
```
code test/report/valgrind_s_run.log
code test/report/valgrind_p_run.log
```

Static analysis:
```
make static_analysis
code test/static_analysis_reports/*.rpt
```
</details>
