/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH
#include "starsystem.hh"
#include "ship.hh"
#include "point.hh"
#include "ieventhandler.hh"
#include "mainwindow.hh"

/**
 * @file
 * @brief Handles events which are called from the course's side
 * to affect graphical presentation
 */

namespace Student {
/**
 * @brief The EventHandler class calls mainwindow to change graphical
 * representation. Inherited from IEventhandler.
 */
class EventHandler: public Common::IEventHandler
{
public:
    /**
     * @brief Constructor.
     */
    EventHandler();
    /**
     * @brief Destructor.
     **/
    ~EventHandler();
    /**
     * @brief Call mainwindow to draw the ship.
     * @param ship The ship in question.
     * @post Exception guarantee: nothrow
     */
    void shipSpawned(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Call mainwindow to remove the ship's graphical presentation.
     * @param ship the ship in question.
     * @post Exception guarantee: nothrow
     */
    void shipRemoved(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Relocates the ship.
     * @param ship The ship in question.
     * @param starSystem The star system where the ship will be relocated.
     * @post Exception guarantee: nothrow
     */
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);
    /**
     * @brief Call mainwindow to move the graphical presentation of the ship.
     * @param ship The ship which will be moved.
     * @param origin The point of origin from the ship moves.
     * @param target The point where the ship will be moved.
     * @post Exception guarantee: nothrow
     */
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    /**
     * @brief Something went wrong in ship's actions.
     * @param ship The ship with the exception.
     * @param msg The exception message.
     * @post Exception guarantee: nothrow
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship,
                              std::string const& msg);
    /**
     * @brief Call mainwindow to turn on the distress signal in graphical
     * presentation.
     * @param ship The ship which turned distress signal on.
     * @post Exception guarantee: nothrow
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Call mainwindow to turn off the distress signal in graphical
     * presentation.
     * @param ship The ship which turned distress signal off.
     * @post Exception guarantee: nothrow
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Call mainwindow to remove ship from graphical presentation.
     * @param ship The ship which was abandoned.
     * @post Exception guarantee: nothrow
     */
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief Sets the pointer to MainWindow to mainwindow_.
     * @param mainwindow Pointer to MainWindow.
     */
    void setMainwindow(MainWindow *mainwindow);
private:
    /**
     * @brief mainwindow_ MainWindow where all the graphical
     * presentation starts.
     */
    MainWindow *mainwindow_;
};
}

#endif // EVENTHANDLER_HH
