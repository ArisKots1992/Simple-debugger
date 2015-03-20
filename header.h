#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <string>
#include <fcntl.h>

using namespace std;

#ifdef __x86_64__
#define ORIGIN_R_EAX  (8 * ORIG_RAX)
#define R_EAX (8 * RAX)
#else
#define ORIGIN_R_EAX  (4 * ORIG_EAX)
#define R_EAX (4 * EAX)
#endif

#define NUM 99999999
#define READ 0
#define WRITE 1


bool go(string path,string name,int trace_category,bool block_mode, int trace_limit,bool,bool,bool,string[]);
int words(string);
void help();
bool equal(string,string);
int trace_test(string);
int block(string);
int limit(string);
int redirect(string,string[]);
void f(int);
void f1(int);
void f2(int);
void f3(int);

