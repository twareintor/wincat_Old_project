#include <cstdlib>
#include <iostream>
#include <windows.h>
#define  SEC_SIZE   0x1000000
using namespace std;


short ReadSect(
               const char     *filInp,    // disk to access
               char           *bufInp,         // buffer where sector will be stored
               LONG            nsect,   // sector number, starting with 0
               PLONG           offset // sector offset
               );

int TEST__ReadSect();          // is testing the "ReadSect()" function

int main(int argc, char *argv[])
{
    if(TEST__ReadSect()==0)
        cout<<"Success"<<endl;                       
    system("PAUSE");
    return EXIT_SUCCESS;
}


short ReadSect(
               const char     *filInp,    // disk to access
               char           *bufInp,         // buffer where sector will be stored
               LONG            nsect,   // sector number, starting with 0
               PLONG           offset // sector offset
               )
{
    DWORD           dwRead;   
    HANDLE          hFile;
    
    hFile=CreateFile(filInp,GENERIC_READ,FILE_SHARE_VALID_FLAGS,0,OPEN_EXISTING,0,0);
    if(filInp==INVALID_HANDLE_VALUE) // this may happen if another program is already reading from disk
    {  
        printf("file %s not found\n", filInp); 
        CloseHandle(hFile);
        return 0x12;
    }
    SetFilePointer((char*)filInp,nsect*SEC_SIZE,offset,FILE_BEGIN); // which sector to read
    ReadFile((char*)filInp,bufInp,SEC_SIZE,&dwRead,0);  // read sector
    CloseHandle(hFile);
    return 0;
    
}


int TEST__ReadSect()
{
    // is testing the ReadSector Function
    char          bufInp[0x10000000];
    
    ReadSect(
             "d:\\tmp\\DataCable.jpg",
             bufInp,
             0,
             0
             );
             
    cout<<bufInp;
    return 0;
    
}
