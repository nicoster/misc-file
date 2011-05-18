/* The code of interest is in the subroutine GetDriveGeometry. The 
   code in main shows how to interpret the results of the IOCTL call. */

#include <windows.h>
#include <stdio.h>
#include <winioctl.h>

BOOL
GetDriveGeometry(DISK_GEOMETRY *pdg)
{
  HANDLE hDevice;               // handle to the drive to be examined 
  BOOL bResult;                 // results flag
  DWORD junk;                   // discard results

  hDevice = CreateFile("\\\\.\\PhysicalDrive0", // drive to open
                       0,       // don't need any access to the drive
                       FILE_SHARE_READ | FILE_SHARE_WRITE,  // share mode
                       NULL,    // default security attributes
                       OPEN_EXISTING,  // disposition
                       0,       // file attributes
                       NULL);   // don't copy any file's attributes

  if (hDevice == INVALID_HANDLE_VALUE) // we can't open the drive
  {
    return (FALSE);
  }

  bResult = DeviceIoControl(hDevice,  // device we are querying
      IOCTL_DISK_GET_DRIVE_GEOMETRY,  // operation to perform
                             NULL, 0, // no input buffer, so pass zero
                            pdg, sizeof(*pdg),  // output buffer
                            &junk, // discard count of bytes returned
                            (LPOVERLAPPED) NULL);  // synchronous I/O

  CloseHandle(hDevice);         // we're done with the handle

  return (bResult);
}

int
main(int argc, char *argv[])
{
  DISK_GEOMETRY pdg;            // disk drive geometry structure
  BOOL bResult;                 // generic results flag
  ULONGLONG DiskSize;           // size of the drive, in bytes

  bResult = GetDriveGeometry (&pdg);

  if (bResult) 
  {
    printf("Cylinders = %I64d\n", pdg.Cylinders);
    printf("Tracks per cylinder = %ld\n", (ULONG) pdg.TracksPerCylinder);
    printf("Sectors per track = %ld\n", (ULONG) pdg.SectorsPerTrack);
    printf("Bytes per sector = %ld\n", (ULONG) pdg.BytesPerSector);

    DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder *
      (ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
    printf("Disk size = %I64d (Bytes) = %I64d (Mb)\n", DiskSize,
           DiskSize / (1024 * 1024));
  } else {
    printf ("Attempt to get drive geometry failed. Error %ld.\n",
            GetLastError ());
  }

  return ((int)bResult);
}