/*
 Y.Kuramata June 2014
 http://enthusiastickcoding.blogspot.jp/
 
 This requires hid.dll and setupapi.dll.
 If you have a strange error, check the encoding of this file..
*/

#include "hid.h"

#define WEDO_PID 3
#define WEDO_VID 1684

typedef unsigned char uchar;
typedef signed char schar;

/*
 
 */

/*
 A function to find WeDo-Hub connected to the PC.
 Params
  retHandles: Array of pointers to HANDLE
  max: Length of retHandles
 Return
  Number of WeDo-Hub actually found

 HANDLEs stored in retHnadles must be closed elsewhere.
*/

int findWedo(HANDLE *retHandles, int max);

int findWedo(HANDLE *retHandles, int max){
	//dll handler
	HINSTANCE hDll;
	HINSTANCE setupapiDll;
	//Pointers to function in hid.dll
	HIDD_GETHIDGUID *HidD_GetHidGuid;
	HIDD_GETATTRIBUTES *HidD_GetAttributes;
	HIDD_GETSERIALNUMBERSTRING *HidD_GetSerialNumberString;
	//Pointers to function in setupapi.dll
	SETUPDIGETCLASSDEVS *SetupDiGetClassDevs;
	SETUPDIENUMDEVICEINTERFACES *SetupDiEnumDeviceInterfaces;
	SETUPDIGETDEVICEINTERFACEDETAL *SetupDiGetDeviceInterfaceDetail;
	SETUPDIDESTROYDEVICEINFOLIST *SetupDiDestroyDeviceInfoList;
	//vars
	GUID hidGuid;
	HDEVINFO hDevInfo;
	HIDD_ATTRIBUTES Attributes;
	SP_DEVICE_INTERFACE_DATA spDid;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pspDidd;
	HANDLE hDevHandle;
	int wedo_count = 0;
			
	//Load hid.dll
	hDll = LoadLibrary("HID.DLL");
	HidD_GetHidGuid = (HIDD_GETHIDGUID*)GetProcAddress(hDll, "HidD_GetHidGuid");
	HidD_GetAttributes = (HIDD_GETATTRIBUTES *)GetProcAddress(hDll, "HidD_GetAttributes");
	HidD_GetSerialNumberString = (HIDD_GETSERIALNUMBERSTRING *)GetProcAddress(hDll, "HidD_GetSerialNumberString");
	if(!HidD_GetHidGuid || !HidD_GetAttributes || !HidD_GetSerialNumberString){
		return -1;
	}

	//Load setupapi.dll
	setupapiDll = LoadLibrary("SETUPAPI.DLL");
	
	SetupDiGetClassDevs = (SETUPDIGETCLASSDEVS *)GetProcAddress(setupapiDll, "SetupDiGetClassDevsA");
	SetupDiEnumDeviceInterfaces = (SETUPDIENUMDEVICEINTERFACES *)GetProcAddress(setupapiDll, "SetupDiEnumDeviceInterfaces");
	SetupDiGetDeviceInterfaceDetail = (SETUPDIGETDEVICEINTERFACEDETAL *)GetProcAddress(setupapiDll, "SetupDiGetDeviceInterfaceDetailA");
	SetupDiDestroyDeviceInfoList = (SETUPDIDESTROYDEVICEINFOLIST *)GetProcAddress(setupapiDll, "SetupDiDestroyDeviceInfoList");
	if(!SetupDiGetClassDevs || !SetupDiEnumDeviceInterfaces || !SetupDiDestroyDeviceInfoList || !SetupDiGetDeviceInterfaceDetail){
		return -1;
	}
	HidD_GetHidGuid(&hidGuid);//GUIDの取得
	//dprintf("%x,%x,%x,%x\n",hidGuid.Data1,hidGuid.Data2,hidGuid.Data3,hidGuid.Data4);
	hDevInfo = SetupDiGetClassDevs(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE | DIGCF_ALLCLASSES );// HIDクラスのデバイスリストへのハンドルを取得
	DWORD dwIndex = 0;

	while(TRUE) {
		memset(&spDid, 0, sizeof(SP_DEVICE_INTERFACE_DATA) );
		spDid.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		if (SetupDiEnumDeviceInterfaces(hDevInfo,NULL,&hidGuid,dwIndex,&spDid)) {
			DWORD dwRequiredLength = 0;
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &spDid, NULL, 0, &dwRequiredLength, NULL );

			pspDidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwRequiredLength);
			pspDidd->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			if ( SetupDiGetDeviceInterfaceDetail( hDevInfo, &spDid, pspDidd, dwRequiredLength, &dwRequiredLength, NULL ) ) {
				hDevHandle = CreateFile( pspDidd->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH,NULL );
				if ( hDevHandle != INVALID_HANDLE_VALUE ){
					//Get Vender ID, Product ID and version from the device's attribute.
					Attributes.Size = sizeof(Attributes);
					if ( HidD_GetAttributes( hDevHandle, &Attributes ) ) {
						if(Attributes.VendorID==WEDO_VID && Attributes.ProductID==WEDO_PID){
							if(wedo_count<max){ retHandles[wedo_count] =  hDevHandle; }
							wedo_count++;
						} else {
							CloseHandle( hDevHandle );
						}
					}
				}
			}
			free(pspDidd);
			dwIndex++;
		} else {
			if( GetLastError() == ERROR_NO_MORE_ITEMS ){ break; }
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	FreeLibrary(hDll);
	FreeLibrary(setupapiDll);
	return wedo_count;
}
