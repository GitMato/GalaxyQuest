/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef PLAYER_HH
#define PLAYER_HH

#include "starsystem.hh"
#include <QObject>

/**
 * @file
 * @brief Player Class handles and stores player position on the map.
 */
namespace Student{

/**
 * @brief Player Class handles and stores player position on the map.
 * @invariant centerOffsetX_ and centerOffsetY_ have
 * to be > 0. Also, 1 < gridSize_ < 50.
 */
class Player: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     */
    Player();

    /**
     * @return Player position in X axis in units. The Number defines
     * how many units the graphical grid must be moved to center it
     * on the player.
     * @post Exception guarantee: nothrow
     */
    int getOffsetX();
    /**
     * @return Player position in Y axis in units. The Number defines
     * how many units the graphical grid must be moved to center it on
     * the player.
     * @post Exception guarantee: nothrow
     */
    int getOffsetY();
    /**
     * @return Size of the drawn single coordinate grid in pixels.
     * @post Exception guarantee: nothrow
     */
    int getGridsize();
    /**
     * @return Screen center in units in X Axis. The Value is used in
     * centering the graphical map to the true center of the screen.
     * @post Exception guarantee: nothrow
     */
    int getCenterOffsetX();
    /**
     * @return Screen center in units in Y Axis. The Value is used in
     * centering the graphical map to the true center of the screen.
     * @post Exception guarantee: nothrow
     */
    int getCenterOffsetY();

    /**
     * @brief Set the player's position (x, y) to offsetX_ and offsetY_.
     * @param starsystem Shared pointer to starsystem where the player is.
     * @post Exception guarantee: nothrow
     */
    void setOffsets(std::shared_ptr<Common::StarSystem> starsystem);

    /**
     * @brief Set the player's current star system to location_.
     * @param location Player's current location as a StarSystem.
     * @post Player's new location is set.
     * @post Exception guarantee: nothrow
     */
    void setPlayerLocation(std::shared_ptr<Common::StarSystem> location);
    /**
     * @brief Return player's current location (starSystem).
     * @return Shared pointer to player's current starsystem.
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Common::StarSystem> getPlayerLocation();

private:
    /**
     * @brief HUD_H Heads Up Display's height in pixels. Used in calculating
     * allowed drawing area.
     */
    const int HUD_H = 192;
    const int HUD_BOT_MARGIN = 8;
    // in future update this can be changed with mouse scroll
    // to create zoom effect.
    /**
     * @brief Size of the drawn single coordinate grid in pixels.
     * Each coordinate is multiplied by gridsize.
     */
    int gridSize_;
    // in future update this will change when screensize changes
    /**
     * @brief Screen center in units. Used in centering the graphical
     * map to true center of the screen. Works together with player
     * position X.
     */
    int centerOffsetX_;
    // in future update this will change when screensize changes
    /**
     * @brief Screen center in units. Used in centering the graphical
     * map to true center of the screen. Works together with player
     * position Y.
     */
    int centerOffsetY_;

    /**
     * @brief Player position in X axis. Defines how many units the graphical
     * grid must be moved to center it on the player.
     */
    int offsetX_;
    /**
     * @brief Player position in Y axis. Defines how many units the graphical
     * grid must be moved to center it on the player.
     */
    int offsetY_;

    int screenWidth_;
    int screenHeight_;

    int allowedDrawingAreaW_;
    int allowedDrawingAreaH_;

    /**
     * @brief Shared pointer to StarSystem
     */
    std::shared_ptr<Common::StarSystem> location_;

    /**
     * @brief Invariant for Player class.
     * centerOffsetX_ and centerOffsetY_ > 0
     */
    void playerInvariant() const;

};
}

#endif // PLAYER_HH
