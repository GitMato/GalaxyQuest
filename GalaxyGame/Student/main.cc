/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"
#include "mainwindow.hh"
#include <QApplication>
#include <memory>
#include <time.h>
#include <ioexception.hh>
#include <formatexception.hh>
#include "stateexception.hh"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        a.setOverrideCursor(QCursor(QPixmap(":/gfx/Assets/cursor.png"),0,0));
        // 0,0 in the end sets cursor's hotspot correctly to point 0,0 -
        // Very important!

        std::shared_ptr<Common::IEventHandler> handler =
                std::make_shared<Student::EventHandler>();

        std::shared_ptr<Student::Galaxy> galaxy =
                std::make_shared<Student::Galaxy>();

        std::shared_ptr<Common::IGameRunner> gameRunner =
                Common::getGameRunner(galaxy, handler);

        Common::utilityInit(time(NULL));

        // Create MainWindow object
        MainWindow galaxyGameWindow(0, gameRunner, galaxy);
        std::dynamic_pointer_cast<Student::EventHandler>(handler)->
                setMainwindow(&galaxyGameWindow);
        galaxyGameWindow.show();

        return a.exec();

    }
    catch (Common::IoException const& virhe)
    {
        qDebug() << "Caught IoException in getGameRunner(): " <<
                    QString::fromStdString(virhe.msg());
    }
    catch (Common::FormatException const& virhe)
    {
        qDebug() << "Caught FormatException in getGameRunner(): " <<
                    QString::fromStdString(virhe.msg());
    }

}
