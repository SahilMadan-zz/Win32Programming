/** 
 * Master file, includes (among others)...
 *     WINDEF.h: Basic type definitions
 *     WINNT.h: Type definitions for unicode support
 *     WINBASE.h: Kernel functions
 *     WINUSER.h: User interface functions
 *     WINGDI.h: Graphics device interface functions
 **/
 #include <Windows.h>


// The main entry point for a Windows program is WinMain

int WINAPI WinMain(  // WINAPI defines that the arguements should be placed left-->right on the stack
    HINSTANCE hInstance,  // An instance handle of the program
    HINSTANCE hPrevInstance, // The last opened instance of this program. Now always NULL
    LPSTR lpCmdLine,  // The command line used to run the program
    int nShowCmd  // How the program should be initially displayed (normal, maximized, minimized to task bar, etc.)
    )
{
    // NOTE: MessageBox calls MessageBoxA or MessageBoxW depending on wchar support
    MessageBox(
        NULL,  // The Window Handle
        TEXT("Hello World!"),  // Text to display in the message box (TEXT macro makes TCHAR string literal) 
        TEXT("Hello World Alert!"),  // Text to display in the title
        MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_ICONEXCLAMATION  // Type of dialog box, default button, icon 
    );

    return 0;
}