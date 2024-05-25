#include <windows.h>
#include <commctrl.h>

#define IDC_BUTTON1 101
#define IDC_BUTTON2 102
#define IDC_LISTVIEW 103

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void InitListViewColumns(HWND hWndListView) {
    LVCOLUMN lvColumn;
    lvColumn.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvColumn.cx = 150;
    lvColumn.pszText = const_cast<LPSTR>("Column 1");
    ListView_InsertColumn(hWndListView, 0, &lvColumn);

    lvColumn.pszText = const_cast<LPSTR>("Column 2");
    ListView_InsertColumn(hWndListView, 1, &lvColumn);
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    const char CLASS_NAME[] = "SampleWindowClass";
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "WinAPI Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
        );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndButton1, hwndButton2, hwndListView;

    switch (uMsg) {
    case WM_CREATE:
        hwndButton1 = CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Button 1",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            0, 0, 100, 30,   // Initial position and size
            hwnd,       // Parent window
            (HMENU)IDC_BUTTON1,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton2 = CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "Button 2",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            0, 0, 100, 30,   // Initial position and size
            hwnd,       // Parent window
            (HMENU)IDC_BUTTON2,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndListView = CreateWindow(WC_LISTVIEW, "",
                                    WS_CHILD | WS_VISIBLE | LVS_REPORT,
                                    10, 50, 460, 300,
                                    hwnd, (HMENU)IDC_LISTVIEW, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        InitListViewColumns(hwndListView);

        break;

    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED) {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // Center the buttons horizontally
            int buttonWidth = 100;
            int buttonHeight = 30;
            int buttonSpacing = 10;
            int totalButtonWidth = (buttonWidth * 2) + buttonSpacing;
            int xOffset = (rect.right - totalButtonWidth) / 2;

            MoveWindow(hwndButton1, xOffset, 10, buttonWidth, buttonHeight, TRUE);
            MoveWindow(hwndButton2, xOffset + buttonWidth + buttonSpacing, 10, buttonWidth, buttonHeight, TRUE);

            // Resize the ListView
            MoveWindow(hwndListView, 10, 50, rect.right - 20, rect.bottom - 60, TRUE);
        }
        break;

    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* mmi = (MINMAXINFO*)lParam;
        mmi->ptMinTrackSize.x = 550; // Minimum width
        mmi->ptMinTrackSize.y = 400; // Minimum height
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1:
            MessageBox(hwnd, "Button 1 Clicked", "Info", MB_OK);
            break;

        case IDC_BUTTON2:
            MessageBox(hwnd, "Button 2 Clicked", "Info", MB_OK);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
