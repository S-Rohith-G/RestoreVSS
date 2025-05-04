
# VSSRestoreUtility

## Overview
This utility is designed to restore data from a VSS snapshot of an NTFS volume to an empty partition using fast block-based copying in C++ on Windows 11.

## Build Dependencies
- Windows 11
- Visual Studio 2022
- C++ Desktop Development workload

## Build Instructions
1. Open `VSSRestoreUtility.sln` in Visual Studio 2022.
2. Build the solution in `Release | x64` configuration.

## Usage
```bash
VSSRestoreUtility.exe <ShadowVolumePath> <TargetPartitionPath>
```

### Example:
```bash
VSSRestoreUtility.exe \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1 \\.\E:
```

### Path Format Details:
- `<ShadowVolumePath>` must be a valid NTFS volume shadow copy path, e.g.:
  ```
  \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1
  ```

- `<TargetPartitionPath>` must be a raw NTFS volume, e.g.:
  ```
  \\.\E:
  ```

**Note**: Run the utility with administrative privileges for proper access to system volumes.

## How It Works
- Opens the VSS snapshot volume as a read-only file.
- Writes block-wise data to the empty partition.
- Buffer size is set to 1 MB for efficient performance.

## Validation Instructions
- Use `diskpart` to create an empty partition.
- Use PowerShell or VSS tools to create a snapshot.
- Compare checksums of source and target partitions after restore.

## Skills Demonstrated
- Windows storage access using WinAPI
- Block-based I/O
- Error handling and robust C++ design
