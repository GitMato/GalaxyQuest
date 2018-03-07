/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "player.hh"

// Player-Class handles and stores player position on the map
Student::Player::Player()
{
    // Initial values for screen size, these will be requested from
    // mainWindow in the future, to perform updated calculations
    screenWidth_ = 1200;
    screenHeight_ = 800;

    // set or calculate allowed drawing area for ships and star system.
    // do not draw them on top of HUD.
    allowedDrawingAreaW_ = screenWidth_;
    allowedDrawingAreaH_ = screenHeight_ - HUD_H - HUD_BOT_MARGIN;

    // Changing gridsize zooms map in and out.
    gridSize_ = 30;

    // Calculated center of the screen. changes together with screen size.
    centerOffsetX_ = allowedDrawingAreaW_ / gridSize_ / 2; // 20 if SW=1200
    centerOffsetY_ = allowedDrawingAreaH_ / gridSize_ / 2; // 10 if SH=800

    // Player starting position x and y.
    // Changing these values moves the map/player
    offsetX_ = 0;
    offsetY_ = 0;

}

// Other classes can ask for current player position X and Y
int Student::Player::getOffsetX()
{
    return offsetX_;
}

int Student::Player::getOffsetY()
{
    return  offsetY_;
}

// Other classes can ask for current Gridsize.
// (If player has zoomed in or out)
int Student::Player::getGridsize()
{
    playerInvariant();
    return gridSize_;
}

// Other classes can ask for a new screen center.
// Initially and when screensize changes.
int Student::Player::getCenterOffsetX()
{
    playerInvariant();
    return centerOffsetX_;
}

int Student::Player::getCenterOffsetY()
{
    playerInvariant();
    return centerOffsetY_;
}


// When player moves, it sets new offsets.
void Student::Player::setOffsets(
        std::shared_ptr<Common::StarSystem> starsystem)
{

    offsetX_ = starsystem->getCoordinates().x;
    offsetY_ = starsystem->getCoordinates().y;

}

void Student::Player::setPlayerLocation(
        std::shared_ptr<Common::StarSystem> location)
{
    location_ = location;
    Q_ASSERT(location_ == location);
}

std::shared_ptr<Common::StarSystem> Student::Player::getPlayerLocation()
{
    return location_;
}

void Student::Player::playerInvariant() const
{
    Q_ASSERT(centerOffsetX_ > 0);
    Q_ASSERT(centerOffsetY_ > 0);
    Q_ASSERT(gridSize_ > 1 && gridSize_ < 50);
}


// Future update: lisäominaisuus - kontrollit
// jos player painaa A/D/W/S, galaksinpiirtämisen offset muuttuu

