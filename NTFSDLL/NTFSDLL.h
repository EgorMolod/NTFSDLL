#pragma once

#ifdef NTFS_Info_EXPORTS
#define NTFS_Info_API __declspec(dllexport)
#else
#define NTFS_Info_API __declspec(dllimport)
#endif

#include <windows.h>

#pragma pack(1)
typedef struct {
	unsigned char BootCode[3];
	BYTE signatureNTFS[8];
	WORD bytesPerSector;
	BYTE sectorPerCluster;
	BYTE MustBeZero[7];
	BYTE MediaType;
	WORD MustBeZero1;
	WORD sectorPerTrack;
	WORD numOfHeaders;
	DWORD hiddenSectors;
	DWORD EmptyBytes;
	DWORD EmptyBytes1;
	ULONGLONG NumbSectorsInVolume;
	ULONGLONG MFTStartupCluster;
	ULONGLONG MFTCopyStartupCluster;
	BYTE ClustersPerMFTRecord;
	BYTE MustBeZero3[3];
	BYTE ClusterPerIndex;
	BYTE MustBeZero4[3];
	ULONGLONG SerialNumber;
	DWORD checksum;
	BYTE bootstrap[426];
	WORD endMarker;
}NTFS;

