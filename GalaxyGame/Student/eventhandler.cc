/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "eventhandler.hh"

Student::EventHandler::EventHandler()
{
}

Student::EventHandler::~EventHandler()
{
}

void Student::EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
    mainwindow_->drawNPCShips(ship);
}

void Student::EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    mainwindow_->removeShip(ship);
}

void Student::EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship,
                                          std::shared_ptr<Common::StarSystem>
                                          starSystem)
{
    mainwindow_->relocateShip(ship, starSystem);
}

void Student::EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship,
                                      Common::Point origin,
                                      Common::Point target)
{
    mainwindow_->moveShip(ship, origin, target);
}

void Student::EventHandler::exceptionInExecution(
        std::shared_ptr<Common::Ship> ship, const std::__cxx11::string &msg)
{
    mainwindow_->exceptionInExecution(ship, msg);
}

void Student::EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    mainwindow_->shipdistressOn(ship);
}

void Student::EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    mainwindow_->shipdistressOff(ship);
}

void Student::EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    mainwindow_->abandonShip(ship);
}

void Student::EventHandler::setMainwindow(MainWindow *mainwindow)
{
    mainwindow_ = mainwindow;
}
