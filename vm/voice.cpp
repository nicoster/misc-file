#include <dvoice.h>
#pragma  comment(lib,"dxguid.lib")
void main()
{
 // TODO: Add your control notification handler code here
 IDirectPlayVoiceTest* pTest;
 HRESULT hr=CoCreateInstance(CLSID_DirectPlayVoiceTest,NULL,CLSCTX_INPROC_SERVER,IID_IDirectPlayVoiceTest,(void**)&pTest);
 if(SUCCEEDED(hr))
 {
  pTest->CheckAudioSetup(&DSDEVID_DefaultVoicePlayback,&DSDEVID_DefaultCapture,NULL,DVFLAGS_ALLOWBACK);
  pTest->Release();
 }
