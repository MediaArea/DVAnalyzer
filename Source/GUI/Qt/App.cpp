#include <QtGui/QApplication>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "GUI/Qt/App.h"
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include "ZenLib/Conf.h"
#include <vector>
using namespace std;

#ifdef __MACOSX__
    #include <ApplicationServices/ApplicationServices.h>
#endif //__MACOSX__

int main (int argc, char** argv)
{
    #ifdef __MACOSX__
        ProcessSerialNumber PSN;
        GetCurrentProcess(&PSN);
        TransformProcessType(&PSN, kProcessTransformToForegroundApplication);
    #endif //__MACOSX__

    setlocale(LC_ALL, "");

    QApplication App(argc, argv);
    Core C;

    GUI_Main Window(&C);
    Window.show();
    return App.exec();
}
