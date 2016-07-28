#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("HelloWin");

    // A window is always created based on a window class
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  // Redraw if horizontal/vertical size changes
    wndclass.lpfnWndProc = WndProc;  // Address of window procedure used (to process messages)
    wndclass.cbClsExtra = 0; // the number of extra bytes to allocate following the window class struct
    wndclass.cbWndExtra = 0; // the number of extra bytes to allocate following the window instance
    wndclass.hInstance = hInstance; // A handle to the instance that contains the winproc for the class
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Loads an icon for use by the program (NULL indicates we want predefined icon)
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  // Loads a cursor for use by the program (NULL indicates we want predefined cursor)
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);  // obtains a graphic object, in this case a brush
    wndclass.lpszMenuName = NULL;   // the name of the class menu (we have no application menu, so NULL)
    wndclass.lpszClassName = szAppName;  // Specifies the window class name

    // Register the class (or display error)
    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    // Create the window based on the window class
    HWND hwnd;
    hwnd = CreateWindow(
        szAppName,  // window class name
        TEXT("The Hello Program"), // window caption
        WS_OVERLAPPEDWINDOW,  // window style (specifically, an overlapped window)
        CW_USEDEFAULT,  // initial x-pos
        CW_USEDEFAULT,  // initial y-pos
        CW_USEDEFAULT,  // width
        CW_USEDEFAULT,  // height
        NULL,  // parent window handle (child window is drawn on surface of parent)
        NULL,  // window menu handle
        hInstance,  // program instance handle
        NULL  // creation parameters
        );

    ShowWindow(hwnd, iCmdShow); // Show the window, given the parameters passed (i.e. normal, minimized, maximized, etc)
    UpdateWindow(hwnd); // Cause the client area (the drawable surface of the window) to be painted


    // GetMessage waits for and retreives message from message queue
    // NOTE: WM_QUIT causes GetMessage to return 0
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // passes msg back to windows for keyboard translation
        DispatchMessage(&msg);  // passes msg back to windows which passes to appropriate window procedure
    }

    // Returns the value passed to the PostQuitMessage function
    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd,  //The handle to the window which the message is directed to
    UINT message,  // A number that identifies the message
    WPARAM wParam, LPARAM lParam  // parameters that provide more info on the msg (usage depends on the msg)
)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message) {
    case WM_CREATE:
        // Make sure to link to windows multimedia library (winmm.lib)
        PlaySound(
            TEXT("hellowin.wav"),  // the name of the soundfile
            NULL, // only used if the sound is a resource
            SND_FILENAME | SND_ASYNC  // indicates first arg is filename, and to play sound asynchronously
        );
        return 0;
    
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);  // Begin painting
        GetClientRect(hwnd, &rect); // get the 4 array of the rect coordinates
        DrawText(
            hdc,  // handle to the device context returned from BeginPaint 
            TEXT("Hello Windows!"), // Text to draw
            -1, // Indicates that the text string is terminated by a 0
            &rect, // the client rectangle in which we will draw
            DT_SINGLELINE | DT_CENTER | DT_VCENTER  // Text displayed as single line centered horizontally/vertically
        );

        EndPaint(hwnd, &ps);  // End painting
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0); // Inserts WM_QUIT in program's message queue
        return 0;
    }

    // Call default Window Procedure for all message types not handled above
    return DefWindowProc(hwnd, message, wParam, lParam);
}