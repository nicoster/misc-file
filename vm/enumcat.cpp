#include <stdio.h>
#include <ActivScp.h>
#include <comcat.h>

#pragma comment(lib, "ole32.lib")


//CATID CATID_ActiveScript = '{F0B7A1A1-9847-11cf-8F20-00805F2CD064}';
void DisplayEngines(void)
 {
 // get the component category manager for this machine
     ICatInformation *pci = 0;
     HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
                                   0, CLSCTX_SERVER,
                                   IID_ICatInformation,
                                   (void**)&pci);
     if (SUCCEEDED(hr))
     {
 // get the list of parseable script engines
         CATID rgcatidImpl[1];
         rgcatidImpl[0] = CATID_ActiveScriptParse;
         IEnumCLSID *pec = 0;
         hr = pci->EnumClassesOfCategories(1, rgcatidImpl, 0, 0, 
                                           &pec);
         if (SUCCEEDED(hr))
         {
 // print the list of CLSIDs to the console as ProgIDs
             enum {CHUNKSIZE = 16};
             CLSID rgclsid[CHUNKSIZE];
             ULONG cActual;
             do
             {
                 hr = pec->Next(CHUNKSIZE, rgclsid, &cActual);
                 if (FAILED(hr))
                     break;
                 if (hr == S_OK)
                     cActual = CHUNKSIZE;
                 for (ULONG i = 0; i < cActual; i++)
                 {
                     OLECHAR *pwszProgID = 0;
                     if (SUCCEEDED(ProgIDFromCLSID(rgclsid[i], &pwszProgID)))
                     {
                         printf("%S\n", pwszProgID);
                         CoTaskMemFree(pwszProgID);
                     }
                 }
             }
             while (hr != S_FALSE);
             pec->Release();
         }
         pci->Release();
     }
     else
         printf("###error: couldn't load category manager\n");
}

void main()
{
		DisplayEngines();
}