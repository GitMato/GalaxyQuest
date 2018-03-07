/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef MTSTARSYSTEM_HH
#define MTSTARSYSTEM_HH

#include <QIcon>
#include <QPixmap>
#include <QStyle>
#include <QPushButton>
#include "galaxy.hh"
#include <string>
#include "player.hh"

class MainWindow;

/**
 * @file
 * @brief MtStarSystem handles graphical representation and functionality
 * of the star systems in the game.
 */
namespace Student
{
// luokka jonka tehtävä on piirtää starsystem saatuihin koordinaatteihin
// MtStarSystem-class is responsible for drawing the starsystems to the screen
/**
 * @brief MtStarSystem Class handles graphical representation
 * of the star systems in the game UI. eg. creating and updating tooltips,
 * and graphical indication if there are ships in distress inside
 * the starsystem. The Class inherits the public members of
 * Qt's QPushButton class.
 *
 * Has a custom click signal and a custom slot.
 */
class MtStarSystem: public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param galaxy Shared pointer to the Galaxy object
     * @param starsystem Shared pointer to the StarSystem
     * object which MtStarSystem represents.
     * @param player Pointer to Player object
     * @param mainwindow Pointer to MainWindow object
     * @param parent Pointer to QWidget object.
     */
    MtStarSystem(std::shared_ptr<Student::Galaxy> galaxy,
                 std::shared_ptr<Common::StarSystem> starsystem,
                 Student::Player *player,
                 MainWindow *mainwindow,
                 QWidget *parent = 0);

    /**
     * @brief Update the list of ships, tooltip and image of the starsystem
     * based on the list of ships in the system.
     */
    void updateShipsInSystem();

    // For knowing which MtStarSystems need the red halo.
    /**
     * @brief Set distress on in MtStarSystem.
     * @post Exception guarantee: nothrow
     */
    void shipsInDistressON();
    /**
     * @brief Set distress off in MtStarSystem.
     * @post Exception guarantee: nothrow
     */
    void shipsInDistressOFF();

    /**
     * @brief Update offsets from player position.
     * @post grid size, offsetX and offsetY is set.
     */
    void updatePlayerPos();
    /**
     * @brief Move MtStarSystem object according to the player's position
     */
    void moveStarSystemWithPlayer();

    /**
     * @return Shared pointer to StarSystem object which
     * MtStarSystem object graphically represents.
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Common::StarSystem> getStarsystem();

    /**
     * @brief Get screen size (width and height).
     * @param screenWidth Screen width
     * @param screenHeight Screen height
     * @post screenWidth and screenHeight are set.
     */
    void getScreenSize(int screenWidth, int screenHeight);

signals:
    /**
     * @brief Signal to transfer StarSystem
     * @param starsystem Shared pointer to StarSystem object
     */
    void starsystemClickedSignal(
            std::shared_ptr<Common::StarSystem> starsystem);

private slots:
    /**
     * @brief starsystemClicked Set new offsets to player.
     * Update those offsets and grid size.
     * Emit starSystemClickedSignal with StarSystem.
     */
    void starsystemClicked();

private:
    int screenWidth_;
    int screenHeight_;

    /**
     * @brief Boolean - true if there is a ship in distress in a StarSystem,
     * false otherwise.
     */
    bool inDistress;
    /**
     * @brief Player position in X axis.
     */
    int offsetX_;
    /**
     * @brief Player position in Y axis.
     */
    int offsetY_;
    /**
     * @brief Gridsize (multiplier of coordinates)
     */
    int gridSize_;
    /**
     * @brief Offset to center the screen in X axis.
     */
    int centerOffsetX_;
    /**
     * @brief Offset to center the screen in Y axis.
     */
    int centerOffsetY_;

    /**
     * @brief Pointer to the Player object.
     */
    Student::Player *player_;
    /**
     * @brief Vector which contains all the ships currently in the star system
     */
    Common::IGalaxy::ShipVector shipsInSystem_;
    /**
     * @brief Pointer to the StarSystem object which this
     * MtStarSystem object represents.
     */
    std::shared_ptr<Common::StarSystem> starsystem_;
    /**
     * @brief Pointer to the Galaxy object
     */
    std::shared_ptr<Student::Galaxy> galaxy_;

    /**
     * @brief mainwindow_ Pointer to the MainWindow object.
     */
    MainWindow *mainwindow_;
};
}

#endif // MTSTARSYSTEM_HH
