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
f //para cada bloco, a soma das for�as externas que agem nele - float
xa xb k //para cada mola, os dois blocos na qual est� conectada, seguido pela constante el�stica, - int int float
        //uma mola sempre conecta-se por cima em um bloco e por baixo em outro. xa � por baixo, xb � por cima
c //n�mero de rela��es
b [mixed]  //rela��es: b � o n�mero de molas envolvidas. [mixed] representa as rela��es
  //4 1 2 + 3 = 4 = : indica que s�o 4 molas, x1 + x2 = x3 = x4 
```

