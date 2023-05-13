#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_DEPRECATE
#define __INCLUDE_CRYPTOGRAPHY__
#define __STORMLIB_SELF__                   // Don't use StormLib.lib
#include <stdio.h>

#include "../src/StormLib.h"
#include "../src/StormCommon.h"

#define check(b, err) if(!(b)){printf(err); return -1;}

int _tmain(int argc, TCHAR * argv[])
{
    if(argc <= 1){
        printf("no mpq path param\n");
        return -1;
    }
    LPCTSTR szFullPath = argv[1];
    printf("open mpq %s\n", szFullPath);

    HANDLE hMpq = NULL;
    HANDLE hFile = NULL;
    SFILE_FIND_DATA sf;

    check(SFileOpenArchive(szFullPath, 0, 0, &hMpq), "open failed\n")

    hFile = SFileFindFirstFile(hMpq, "*", &sf, NULL);
    if(hFile != NULL){
        do{
            if(argc >= 3){
                TCHAR outpath[MAX_PATH];
                outpath[0] = 0;
                StringCat(outpath, _countof(outpath), argv[2]);
                StringCat(outpath, _countof(outpath),"/");
                StringCat(outpath, _countof(outpath), sf.cFileName);
                for(size_t i=0; i<strlen(outpath); i++){
                    if(outpath[i] == '\\' || outpath[i] == '/'){
                        outpath[i] = 0;
                        mkdir(outpath, S_IRWXU);
                        outpath[i] = '/';
                    }
                }
                if(!SFileExtractFile(hMpq, sf.cFileName, outpath, 0)){
                    printf("extract failed %s\n", outpath);
                    return -1;
                }
            }
        }
        while(SFileFindNextFile(hFile, &sf));
        SFileFindClose(hFile);
    }

    printf("all scucess \n");
    check(SFileCloseArchive(hMpq), "close failed\n")
    return 0;

}
