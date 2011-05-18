#include <windows.h>
#include <Sensapi.h>
#include <iostream.h>
#pragma comment(lib, "Sensapi.lib")
void main()
{
  
DWORD   flags;//上网方式 
BOOL   bOnline=TRUE;//是否在线  

bOnline=IsNetworkAlive(&flags);   
if(bOnline)//在线   
{   
   if ((flags & NETWORK_ALIVE_LAN) ==NETWORK_ALIVE_LAN)
   {
    cout<<"在线：NETWORK_ALIVE_LAN\n";
   }
   if ((flags & NETWORK_ALIVE_WAN) ==NETWORK_ALIVE_WAN)
   {
    cout<<"在线：NETWORK_ALIVE_WAN\n";
   }
   if ((flags & NETWORK_ALIVE_AOL) ==NETWORK_ALIVE_AOL)
   {
    cout<<"在线：NETWORK_ALIVE_AOL\n";
   }
}
else
   cout<<"不在线\n";
}
