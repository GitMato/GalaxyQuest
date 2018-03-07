/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef MTNPCSHIP_HH
#define MTNPCSHIP_HH

#include <QPushButton>
#include "ship.hh"
#include "player.hh"

/**
 * @file
 * @brief MtNPCShip handles graphical representation and
 * functionality NPC ships in the game.
 */
namespace Student
{

// Future update: mtnpcship and mtstarsystem classes can
// inherit common features from one superclass.
/**
 * @brief MtNPCShip class handles graphical representation of the NPC ships
 * in the game UI, eg. graphical movement of the NPC ships, creating and
 * updating ship tooltips and keeping track on ship distress calls.
 * It inherits the public members of Qt's QPushButton class.
 */
class MtNPCShip: public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param ship Shared pointer to the Ship object
     * which MtNPCShip represents.
     * @param player Pointer to Player object.
     * @param parent Pointer to QWidget object.
     */
    MtNPCShip(std::shared_ptr<Common::Ship> ship,Student::Player *player,
              QWidget *parent = 0);

    /**
     * @brief Update offsets from player position.
     * @post grid size, offsetX and offsetY are set.
     */
    void updatePlayerPos();
    /**
     * @brief Update ship's tooltip
     */
    void updateShipTooltip();
    /**
     * @brief Move the graphical representation of the
     * ship according to the player
     */
    void moveWithPlayer();
    /**
     * @brief Update ship's location from a starsystem if it is in one.
     */
    void updateShipPos();
    /**
     * @brief Set ship's position
     * @param posX Position on X axis.
     * @param posY Position on Y axis.
     */
    void setShipPos(int posX, int posY);

    /**
     * @brief Set inDistress_ boolean to true.
     * @post Exception guarantee: nothrow
     */
    void shipInDistressON();
    /**
     * @brief Set inDistress_ boolean to false.
     * @pre Ship's Engine is broken.
     * @post Exception guarantee: nothrow
     */
    void shipInDistressOFF();
    /**
     * @return true if the ship which mtnpcship represents is in distress.
     * false if it is not.
     * @post Exception guarantee: nothrow
     */
    bool getPossibleDistress();

    /**
     * @return Shared pointer to the StarSystem object where the ship is.
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Common::StarSystem> getShipLocation();

    /**
     * @brief getScreenSize Get screen size (width and height).
     * @param screenWidth Screen width
     * @param screenHeight Screen height
     * @post screenWidth and screenHeight are set.
     */
    void getScreenSize(int screenWidth, int screenHeight);

private:
    int screenWidth_;
    int screenHeight_;

    /**
     * @brief Grid size (multiplier of coordinates)
     */
    int gridSize_;
    /**
     * @brief Player position in X axis.
     */
    int offsetX_;
    /**
     * @brief Player position in Y axis.
     */
    int offsetY_;
    /**
     * @brief Offset to center the screen in X axis.
     */
    int centerOffsetX_;
    /**
     * @brief Offset to center the screen in Y axis.
     */
    int centerOffsetY_;

    /**
     * @brief Boolean - true if a ship is in distress
     * which mtnpcship represents. false if it is not.
     */
    bool inDistress_;

    /**
     * @brief Ship's position on X axis.
     */
    int shipPosX_;
    /**
     * @brief Ship's postition on Y axis.
     */
    int shipPosY_;
    /**
     * @brief Pointer to the Player object.
     */
    Student::Player *player_;
    /**
     * @brief Shared pointer to the Ship object.
     */
    std::shared_ptr<Common::Ship> ship_;

};
}

#endif // MTNPCSHIP_HH
