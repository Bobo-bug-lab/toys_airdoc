#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include "tar.h"
//#include "xattrs.h"
//#include "common.h"
//#include "arith.h"
//#include "backupfile.h"
//#include "libtar.h"

using namespace std;



class tarfile
{
public:
typedef int (*M)(int, char **);
	tarfile(void);
	~tarfile(void);
	int tarzip(char* func,char* parm,char* input, char* output);
    char command[50];
	char chmod[50];
};

tarfile::tarfile(void)
{
 
}
 
tarfile::~tarfile(void)
{
 
}

int tarfile::tarzip(char* func,char* parm,char* input, char* output)
{
    void *handle=dlopen("libtar.so",RTLD_LAZY);
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    M tarmain=NULL;
    *(void **)(&tarmain)=dlsym(handle,"tarmain");
    char aa[15]; strcpy(aa, func);
    char a[15]; strcpy(a, parm);
    char b[15]; strcpy(b, output);
    char c[15]; strcpy(c, input);
    char* cc [4]= {aa,a,b,c};
    tarmain(4,cc);
    return 0;

}

int main()
{
	tarfile tar;
    tar.tarzip("tar","-czvf","./testjson","a.tar.gz");


    return 0;
}






