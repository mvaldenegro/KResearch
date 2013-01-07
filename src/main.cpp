#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KMessageBox>
#include <KLocale>

#include "MainWindow.h"

#include <QDebug>
#include <library/LibraryManager.h>
#include <pdfwidget/PDFDocumentDialog.h>

int main (int argc, char *argv[])
{
    KAboutData aboutData("kresearch", 0, ki18n("KResearch"), "0.0.1",
                         ki18n("A Research paper organizer"), KAboutData::License_GPL,
                         ki18n("Copyright (c) 2012 Matias Valdenegro T."),
                         ki18n("Some text..."),
                         "http://example.com/",
                         "submit@bugs.kde.org");
 
    KCmdLineArgs::init(argc, argv, &aboutData);
    KApplication app;

    LibraryManager *libmanager = new LibraryManager();

    MainWindow *window = new MainWindow();
    window->show();

    int ret = app.exec();

    delete libmanager;

    return ret;
}
