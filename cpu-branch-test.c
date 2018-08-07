#define N 5000000
static int array[N] = { 0 };
void normal_loop(int a) {
    int i;
    for (i = 0; i < N; i++)
        array[i] = array[i]+a;
}
void unroll_loop(int a) {
    int i;
    for (i = 0; i < N; i+=5){
        array[i] = array[i]+1;
        array[i+1] = array[i+1]+a;
        array[i+2] = array[i+2]+a;
        array[i+3] = array[i+3]+a;
        array[i+4] = array[i+4]+a;
    }
}
int main() {
    normal_loop(1);
    unroll_loop(1);
    return 0;
}


/*
Command:
  gcc cpu-branch-test.c -o test4
  perf record -e branch-misses:u,branch-instructions:u ./test4
  perf report
  
 Output:
 
 Events: 4  branch-misses
    98.86%  test4  ld-2.11.3.so  [.] _dl_next_ld_env_entry                                                                                                                                   ↑
     1.14%  test4  ld-2.11.3.so  [.] _dl_start 
   
  Events: 39  branches
    83.43%  test4  test4              [.] normal_loop                                                                                                                                        ↑
    15.76%  test4  test4              [.] unroll_loop                                                                                                                                        ▮
     0.63%  test4  ld-2.11.3.so       [.] do_lookup_x                                                                                                                                        ▒
     0.16%  test4  ld-2.11.3.so       [.] _dl_init_paths                                                                                                                                     ▒
     0.02%  test4  ld-2.11.3.so       [.] _dl_start                                                                                                                                          ▒
     0.00%  test4  ld-2.11.3.so       [.] _start                                                                                                                                             ▒
     0.00%  test4  [kernel.kallsyms]  [k] page_fault 

Command:
gcc -pg ./cpu-branch-test.c -o test4
gprof ./test4 | less

Output:

Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total
 time   seconds   seconds    calls  ms/call  ms/call  name
 66.67      0.02     0.02        1    20.00    20.00  normal_loop
 33.33      0.03     0.01        1    10.00    10.00  unroll_loop

                    Call graph (explanation follows)


granularity: each sample hit covers 4 byte(s) for 33.33% of 0.03 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    0.03                 main [1]
                0.02    0.00       1/1           normal_loop [2]
                0.01    0.00       1/1           unroll_loop [3]
-----------------------------------------------
                0.02    0.00       1/1           main [1]
[2]     66.7    0.02    0.00       1         normal_loop [2]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[3]     33.3    0.01    0.00       1         unroll_loop [3]

*/
