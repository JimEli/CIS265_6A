# Pima CC CIS265 Week #6 Project A

Write the following function:
```C
  double inner_product(const double *a, const double *b, int n);
  ```
a and b both point to arrays of length n. The function should return:
```
  a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1]
  ```
  Use pointer arithmetic-not subscripting-to visit array elements. Your program should prompt the user to enter two lists of double types  of equal size (list "a" and list "b").

Notes:
* Compiled with MS Visual Studio 2017 Community (v141), using C language options.
* Added extensive floating point validity checks.
* Unfortunately MS VS 2017 C language doesn't support VLAs.
