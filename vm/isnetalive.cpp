#include <windows.h>
#include <Sensapi.h>
#include <iostream.h>
#pragma comment(lib, "Sensapi.lib")
void main()
{
  
DWORD   flags;//������ʽ 
BOOL   bOnline=TRUE;//�Ƿ�����  

bOnline=IsNetworkAlive(&flags);   
if(bOnline)//����   
{   
   if ((flags & NETWORK_ALIVE_LAN) ==NETWORK_ALIVE_LAN)
   {
    cout<<"���ߣ�NETWORK_ALIVE_LAN\n";
   }
   if ((flags & NETWORK_ALIVE_WAN) ==NETWORK_ALIVE_WAN)
   {
    cout<<"���ߣ�NETWORK_ALIVE_WAN\n";
   }
   if ((flags & NETWORK_ALIVE_AOL) ==NETWORK_ALIVE_AOL)
   {
    cout<<"���ߣ�NETWORK_ALIVE_AOL\n";
   }
}
else
   cout<<"������\n";
}
