SpringSolve
===========
Trabalho de Métodos Numéricos. Resolve um sistema de massas e molas, calculando o alongamento de cada uma.

## Modelagem
Molas em paralelo tem mesmo alongamento, molas em série tem a mesma força. Dessa forma, para cada bloco no sistema existe uma equação de equilíbrio, 
e para cada associação mais uma equação.

## Entrada
O programa lê de um arquivo chamado *in.txt* no diretório de execução. Este arquivo deve serguir o seguinte formato:

```
n m //número de molas, blocos
xa xb k //para cada mola, os dois blocos na qual está conectada, seguido pela constante elástica, int int (unsigned float)
f //para cada bloco, a soma das forças externas que agem nele (signed float)
```

