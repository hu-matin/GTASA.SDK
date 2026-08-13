#include <windows.h>
#include <commdlg.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <memory>

namespace GTASA::SDK::Launcher
{
    constexpr const wchar_t* kDllName = L"GTASA_SDK.dll";

    // RAII deleter to prevent handlee leaks during injection
    struct HandleDeleter {
        void operator()(HANDLE h) const noexcept {
            if (h && h != INVALID_HANDLE_VALUE) ::CloseHandle(h);
        }
    };
    using UniqueHandle = std::unique_ptr<void, HandleDeleter>;

    std::filesystem::path getCurrentDirectoryPath()
    {
        std::wstring exePath(32767, L'\0');
        // safer size cast for Win32 API parameters
        const DWORD len = GetModuleFileNameW(nullptr, exePath.data(), static_cast<DWORD>(exePath.size()));
        if (len > 0 && len < exePath.size())
        {
            exePath.resize(len);
            return std::filesystem::path(exePath).parent_path();
        }

        return std::filesystem::current_path();
    }

    std::wstring openBrowser()
    {
        OPENFILENAMEW ofn{}; // initialization instead of ZeroMemory
        wchar_t szFile[260] = {0};

        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = static_cast<DWORD>(_countof(szFile));

        ofn.lpstrFilter = L"Executable Files\0*.exe\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameW(&ofn) == TRUE) return std::wstring(szFile);

        return std::wstring();
    }

    bool launchSuspendedProcess(const std::wstring& exePath, const std::wstring& gameDir,
                                PROCESS_INFORMATION& processInfo)
    {
        STARTUPINFOW startupInfo{};
        startupInfo.cb = sizeof(startupInfo);
        return CreateProcessW(exePath.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL,
                              gameDir.c_str(), &startupInfo, &processInfo) == TRUE;
    }

    bool injectDll(HANDLE processHandle, const std::wstring& dllPath)
    {
        HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
        if (!hKernel32) return false;

        LPTHREAD_START_ROUTINE pLoadLibraryW =
            reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(hKernel32, "LoadLibraryW"));
        if (!pLoadLibraryW) return false;

        const SIZE_T dllPathBytes = (dllPath.length() + 1) * sizeof(wchar_t);
        LPVOID allocatedMem = VirtualAllocEx(processHandle, nullptr, dllPathBytes,
                                             MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (!allocatedMem) return false;

        SIZE_T bytesWritten = 0;
        if (!WriteProcessMemory(processHandle, allocatedMem, dllPath.c_str(), dllPathBytes,
                                &bytesWritten) ||
            bytesWritten != dllPathBytes)
        {
            VirtualFreeEx(processHandle, allocatedMem, 0, MEM_RELEASE);
            return false;
        }

        UniqueHandle remoteThread(CreateRemoteThread(processHandle, nullptr, 0, pLoadLibraryW, allocatedMem, 0, nullptr));
        if (!remoteThread)
        {
            VirtualFreeEx(processHandle, allocatedMem, 0, MEM_RELEASE);
            return false;
        }

        const DWORD waitResult = WaitForSingleObject(remoteThread.get(), 15000); // Wait up to 15 seconds
        DWORD remoteExitCode = 0;
        const bool gotExitCode = (waitResult == WAIT_OBJECT_0) &&
                                 (GetExitCodeThread(remoteThread.get(), &remoteExitCode) == TRUE);

        VirtualFreeEx(processHandle, allocatedMem, 0, MEM_RELEASE);
        return gotExitCode && (remoteExitCode != 0);
    }
}

using namespace GTASA::SDK::Launcher;

int main()
{
    auto currentDir = getCurrentDirectoryPath();
    std::wstring dllPath = (currentDir / kDllName).wstring();

    std::cout << "[*] Welcome to the Custom Launcher!\n";

    if (!std::filesystem::exists(std::filesystem::path(dllPath)))
    {
        std::wcout << L"[-] ERROR: DLL file not found at: " << dllPath << L"\n";
        std::cout << "[*] Please make sure the DLL is in the correct directory.\n";
        std::cout << "[*] Press Enter to exit...\n";
        std::cin.get();
        return 1;
    }

    std::wcout << L"[+] Excellent! DLL found successfully at: " << dllPath << L"\n";

    std::cout << "[*] Please select the GTA San Andreas executable (gta_sa.exe) to launch.\n";
    std::wstring exePath = openBrowser();

    if (exePath.empty())
    {
        std::cout << "[-] Selection canceled.\n";
        std::cout << "[*] Press Enter to exit...\n";
        std::cin.get();
        return 1;
    }

    std::wstring gameDir = std::filesystem::path(exePath).parent_path().wstring();

    std::wcout << L"[*] Selected file path: " << exePath << std::endl;

    std::cout << "[*] Starting Custom Launcher (Suspended Mode)...\n";

    PROCESS_INFORMATION pi{}; // standard block initialization

    if (!launchSuspendedProcess(exePath, gameDir, pi))
    {
        std::wcout << L"[-] Failed to start process: " << exePath << L" (GetLastError="
                   << GetLastError() << L")\n";
        std::cout << "[*] Press Enter to exit...\n";
        std::cin.get();
        return 1;
    }

    // Added unique smart handles to securely manage memory tracking
    UniqueHandle hProcess(pi.hProcess);
    UniqueHandle hThread(pi.hThread);

    std::cout << "[*] Injecting GTASA_SDK.dll before game wakes up...\n";

    if (!injectDll(hProcess.get(), dllPath))
    {
        TerminateProcess(hProcess.get(), 1);
        std::cout << "[*] Press Enter to exit...\n";
        std::cin.get();
        return 1;
    }

    std::cout << "[+] DLL Injected.\n";

    std::cout << "[*] Waking up the game...\n";
    ResumeThread(hThread.get());
    return 0;
}
