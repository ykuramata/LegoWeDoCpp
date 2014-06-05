/*
 Y.Kuramata Jun. 2014
 http://enthusiastickcoding.blogspot.com/
 I referred to http://www.crimson-systems.com/tips/t085a.htm
*/

#include <commctrl.h>
#include <pshpack1.h>

//difinitions for setupapi.dll
#define DIGCF_DEFAULT			0x00000001
#define DIGCF_PRESENT			0x00000002
#define DIGCF_ALLCLASSES		0x00000004
#define DIGCF_PROFILE			0x00000008
#define DIGCF_DEVICEINTERFACE	0x00000010

typedef struct {
	DWORD cbSize;
	GUID ClassGuid;
	DWORD DevInst;
	ULONG_PTR Reserved;
}SP_DEVINFO_DATA, *PSP_DEVINFO_DATA;

typedef struct {
	DWORD cbSize;
	GUID InterfaceClassGuid;
	DWORD Flags;
	ULONG_PTR Reserved;
}SP_DEVICE_INTERFACE_DATA, *PSP_DEVICE_INTERFACE_DATA;

typedef struct {
	DWORD cbSize;
	CHAR DevicePath[1];
}SP_DEVICE_INTERFACE_DETAIL_DATA_A, *PSP_DEVICE_INTERFACE_DETAIL_DATA_A;

typedef SP_DEVICE_INTERFACE_DETAIL_DATA_A SP_DEVICE_INTERFACE_DETAIL_DATA, *PSP_DEVICE_INTERFACE_DETAIL_DATA;
typedef struct dummy_HDEVINFO_struct const *HDEVINFO;
typedef HDEVINFO __stdcall SETUPDIGETCLASSDEVS(LPGUID ClassGuid, PCTSTR Enumerator, HWND hwndParent, DWORD Flags);
typedef BOOL __stdcall SETUPDIENUMDEVICEINTERFACES(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, LPGUID InterfaceClassGuid, DWORD MemberIndex, PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData );
typedef BOOL __stdcall SETUPDIGETDEVICEINTERFACEDETAL(HDEVINFO DeviceInfoSet, PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData, PSP_DEVICE_INTERFACE_DETAIL_DATA_A DeviceInterfaceDetailData, DWORD DeviceInterfaceDetailDataSize, PDWORD RequiredSize, PSP_DEVINFO_DATA DeviceInfoData );
typedef BOOL __stdcall SETUPDIDESTROYDEVICEINFOLIST(HDEVINFO DeviceInfoSet);

//difinitions fo hid.dll 
#define CREATE_NEW			1
#define CREATE_ALWAYS		2
#define OPEN_EXISTING		3
#define OPEN_ALWAYS			4
#define TRUNCATE_EXISTING	5

#define FILE_FLAG_WRITE_THROUGH			0x80000000
#define FILE_FLAG_OVERLAPPED				0x40000000
#define FILE_FLAG_NO_BUFFERING			0x20000000
#define FILE_FLAG_RANDOM_ACCESS			0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN		0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE		0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS		0x02000000
#define FILE_FLAG_POSIX_SEMANTICS		0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT	0x00200000
#define FILE_FLAG_OPEN_NO_RECALL			0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE	0x00080000

#define INVALID_HANDLE_VALUE (HANDLE)-1

#define FILE_SHARE_READ		0x00000001
#define FILE_SHARE_WRITE	0x00000002
#define FILE_SHARE_DELETE	0x00000004

typedef struct _HIDD_ATTRIBUTES {
	ULONG   Size;			// = sizeof (struct _HIDD_ATTRIBUTES)
	USHORT  VendorID;
	USHORT  ProductID;
	USHORT  VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

typedef BOOL __stdcall HIDD_GETHIDGUID(GUID *pGuid); //Get GUID
typedef BOOL __stdcall HIDD_GETATTRIBUTES(HANDLE HidDeviceObject, PHIDD_ATTRIBUTES Attributes);// Get Vender ID and Product ID
typedef BOOL __stdcall HIDD_GETSERIALNUMBERSTRING(HANDLE HidDeviceObject, PVOID Buffer, ULONG BufferLength);// Get Serial Number.
