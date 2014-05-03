SpringSolve
===========
Trabalho de M�todos Num�ricos. Resolve um sistema de massas e molas, calculando o alongamento de cada uma.

## Modelagem
Molas em paralelo tem mesmo alongamento, molas em s�rie tem a mesma for�a. Dessa forma, para cada bloco no sistema existe uma equa��o de equil�brio, 
e para cada associa��o mais uma equa��o.

## Entrada
O programa l� de um arquivo chamado *in.txt* no diret�rio de execu��o. Este arquivo deve serguir o seguinte formato:

```
n m //n�mero de molas, blocos
xa xb k //para cada mola, os dois blocos na qual est� conectada, seguido pela constante el�stica, int int (unsigned float)
f //para cada bloco, a soma das for�as externas que agem nele (signed float)
```

