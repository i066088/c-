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
  gcc cpu-branch-test.c -o cpu-branch-test
  perf record -e branch-misses:u,branch-instructions:u ./cpu-branch-test
  perf report
  
 Output:
  Events: 39  branches
    83.43%  test4  test4              [.] normal_loop                                                                                                                                        ↑
    15.76%  test4  test4              [.] unroll_loop                                                                                                                                        ▮
     0.63%  test4  ld-2.11.3.so       [.] do_lookup_x                                                                                                                                        ▒
     0.16%  test4  ld-2.11.3.so       [.] _dl_init_paths                                                                                                                                     ▒
     0.02%  test4  ld-2.11.3.so       [.] _dl_start                                                                                                                                          ▒
     0.00%  test4  ld-2.11.3.so       [.] _start                                                                                                                                             ▒
     0.00%  test4  [kernel.kallsyms]  [k] page_fault 

*/
