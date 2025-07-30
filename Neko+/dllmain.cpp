#include <Windows.h>
#include "Client/Client.h"
#include "winrt/Windows.UI.Core.h"
#include "winrt/windows.system.h"
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include "winrt/windows.applicationmodel.core.h"
#include "winrt/Windows.UI.ViewManagement.h"
#include "winrt/Windows.Foundation.h"

void setWindowTitle(const std::wstring& title) {
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().DispatcherQueue().TryEnqueue([title]() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(title);
        });
}

DWORD WINAPI initClient(LPVOID lpParameter) {
    setWindowTitle(L"");

    Client::getInstance().initialize();

    setWindowTitle(L"Neko+");

    while (Client::getInstance().isInitialized()) {
        Sleep(50);
    }

    Sleep(25);
    FreeLibraryAndExitThread((HMODULE)lpParameter, 1);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule); 
        CreateThread(nullptr, 0, initClient, hModule, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        Client::getInstance().shutdown();
        break;
    }
    return TRUE;
}
