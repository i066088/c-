#include <stdio.h>
static char array[10000][10000];
int main (void)
{
  int i, j;
  for (i = 0; i < 10000; i++)
    for (j = 0; j < 10000; j++)
       array[i][j]++; //good performance, see output 1
       //array[j][i]++; //bad performance, see output 2
  return 0;
}


/*
command: 
    gcc cpu-cache-test.c -o cpu-cache-test
    perf stat --repeat 5 -e cache-misses,cache-references,instructions,cycles ./cpu-cache-test

output 1:

    Performance counter stats for './cpu-cache-test' (5 runs):

           1573087 cache-misses              #   86.984 % of all cache refs      ( +-  2.68% )
           1808471 cache-references                                              ( +-  0.48% )
        2005670756 instructions              #    2.10  insns per cycle          ( +-  0.00% )
         955888021 cycles                    #    0.000 GHz                      ( +-  0.12% )

       0.399979644 seconds time elapsed                                          ( +-  0.12% )

output 2:
    Performance counter stats for './cpu-cache-test' (5 runs):

           3089585 cache-misses              #    3.034 % of all cache refs      ( +-  0.72% )
         101841081 cache-references                                              ( +-  0.00% )
        2005815452 instructions              #    1.23  insns per cycle          ( +-  0.00% )
        1633817004 cycles                    #    0.000 GHz                      ( +-  0.12% )

       0.683216502 seconds time elapsed                                          ( +-  0.12% )
*/
