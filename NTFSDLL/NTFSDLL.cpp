#include <iostream>
#include "pch.h"
#include <string>
#include <windows.h>
#include "NTFSDLL.h"


void NTFS_function(std::string NameDisk) {
	std::string fsName = getVolumeFileSystemName(NameDisk);
	if (checkVolumeFS(fsName) and fsName != "null") {
		NTFS volume;
		if (getMBRInf(NameDisk, &volume)) {
			showFAT32MBR(volume);
		}
	}
	else {
		printf("Unsupported file system! \n");
		return;
	}
}

std::string getVolumeFileSystemName(std::string NameDisk) {
	char NameBuffer[MAX_PATH];
	char SysNameBuffer[MAX_PATH];
	DWORD VSNumber;
	DWORD MCLength;
	DWORD FileSF;

	bool dataReceived = GetVolumeInformationA((NameDisk + ":\\").c_str(), NameBuffer, sizeof(NameBuffer),
		&VSNumber, &MCLength, &FileSF, SysNameBuffer, sizeof(SysNameBuffer));

	return SysNameBuffer;
}

bool checkVolumeFS(std::string fsName)
{
	if (fsName.find("NTFS") == std::string::npos) return false;
	return true;
}

bool getMBRInf(std::string NameDisk, NTFS* volume) {
	BYTE Buffer[512];
	memset(Buffer, 0, 512);
	DWORD dwBytesRead(0);

	std::string NameDiskFormat = "\\\\.\\" + NameDisk + ":";

	HANDLE handleFile = CreateFileA(NameDiskFormat.c_str(), GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, 0, NULL);

	if (handleFile == INVALID_HANDLE_VALUE) return false;

	ReadFile(handleFile, Buffer, 512, &dwBytesRead, NULL);
	CloseHandle(handleFile);

	*volume = *reinterpret_cast<NTFS*>(Buffer);
	return true;
}

//This from master

void showFAT32MBR(NTFS volume) {
	printf("NTFS Disk Information: \n");
	printf("Bytes per sector: %d\n", volume.bytesPerSector);
	printf("Sector per cluster: %d\n", volume.sectorPerCluster);
	printf("Media Type: %d\n", volume.MediaType);
	printf("Sectors Per Track: %d\n", volume.sectorPerTrack);
	printf("Number Of Heads: %d\n", volume.numOfHeaders);
	printf("Number of sectors in volume: %lld\n", volume.NumbSectorsInVolume);
	printf(" Cluster Number of MFT: %lld\n", volume.MFTStartupCluster);
	printf("Cluster Number of MFTCopy: %lld\n", volume.MFTCopyStartupCluster);
	printf("Clusters Per MFT record: %d\n", volume.ClustersPerMFTRecord);
	printf("Clusters Per index: %d\n", volume.ClusterPerIndex);
	printf("Serial Number: %lld\n", volume.SerialNumber);
}
