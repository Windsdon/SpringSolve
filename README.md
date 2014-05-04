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
f //para cada bloco, a soma das forças externas que agem nele - float
xa xb k //para cada mola, os dois blocos na qual está conectada, seguido pela constante elástica, - int int float
        //uma mola sempre conecta-se por cima em um bloco e por baixo em outro. xa é por baixo, xb é por cima
c //número de relações
b [mixed]  //relações: b é o número de molas envolvidas. [mixed] representa as relações
  //4 1 2 + 3 = 4 = : indica que são 4 molas, x1 + x2 = x3 = x4 
```

