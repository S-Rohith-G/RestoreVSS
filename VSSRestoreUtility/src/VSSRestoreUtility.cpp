#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

bool CopyVolumeData(const std::wstring& sourcePath, const std::wstring& targetPath, size_t bufferSize = 1024 * 1024) {
    HANDLE hSource = CreateFileW(sourcePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    HANDLE hTarget = CreateFileW(targetPath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hSource == INVALID_HANDLE_VALUE || hTarget == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to open volume(s): " << GetLastError() << std::endl;
        return false;
    }

    std::vector<char> buffer(bufferSize);
    DWORD bytesRead = 0, bytesWritten = 0;

    while (ReadFile(hSource, buffer.data(), bufferSize, &bytesRead, NULL) && bytesRead > 0) {
        if (!WriteFile(hTarget, buffer.data(), bytesRead, &bytesWritten, NULL) || bytesWritten != bytesRead) {
            std::wcerr << L"Failed during write: " << GetLastError() << std::endl;
            CloseHandle(hSource);
            CloseHandle(hTarget);
            return false;
        }
    }

    CloseHandle(hSource);
    CloseHandle(hTarget);
    return true;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 3) {
        std::wcerr << L"Usage: VSSRestoreUtility.exe <ShadowVolumePath> <TargetPartitionPath>" << std::endl;
        return 1;
    }

    std::wstring shadowPath = argv[1];
    std::wstring targetPath = argv[2];

    if (!CopyVolumeData(shadowPath, targetPath)) {
        std::wcerr << L"Copy failed." << std::endl;
        return 1;
    }

    std::wcout << L"Restore completed successfully." << std::endl;
    return 0;
}
