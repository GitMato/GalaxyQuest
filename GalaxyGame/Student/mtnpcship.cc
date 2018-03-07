/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "mtnpcship.hh"

Student::MtNPCShip::MtNPCShip(std::shared_ptr<Common::Ship> ship,
                              Student::Player *player, QWidget *parent) :
    QPushButton(parent)
{
    ship_ = ship;
    player_ = player;
    centerOffsetX_ = player_->getCenterOffsetX();
    centerOffsetY_ = player_->getCenterOffsetY();
    inDistress_ = false;

    // initial values for screensize, before requesting update.
    screenWidth_ = 1200;
    screenHeight_ = 800;

    // Get gridsize, offsetX and offsetY from player
    updatePlayerPos();

    this->setStyleSheet("QPushButton{ "
                            "image: url(:/gfx/Assets/npcship.png);"
                            "background-color: rgba(255, 255, 255, 0); "
                            "border: none; }"
                        "QPushButton:hover{ "
                            "image: url(:/gfx/Assets/npcship-hover.png); }"
                        "QPushButton:pressed{ "
                            "image: url(:/gfx/Assets/npcship-white.png); }");

    std::shared_ptr<Common::StarSystem> starsystem = ship_->getLocation();
    this->move((centerOffsetX_ + (starsystem->getCoordinates().x-offsetX_))
               *gridSize_,
               (centerOffsetY_ + (starsystem->getCoordinates().y-offsetY_))
               *gridSize_);
    this->resize(17,17);
    updateShipTooltip();
    updateShipPos();
}

void Student::MtNPCShip::updatePlayerPos()
{
    gridSize_ = player_->getGridsize();
    offsetX_ = player_->getOffsetX();
    offsetY_ = player_->getOffsetY();
    Q_ASSERT(gridSize_ == player_->getGridsize());
    Q_ASSERT(offsetX_ == player_->getOffsetX());
    Q_ASSERT(offsetY_ == player_->getOffsetY());
}

void Student::MtNPCShip::updateShipTooltip()
{
    std::string shipTooltip = ship_->getName() + " [ HP: ";
    this->setToolTip(QString::fromStdString(shipTooltip)
                     + QString::number(ship_->getEngine()->getHealth()) + "/"
                     + QString::number(
                         ship_->getEngine()->getMaxHealth()) + " ]");
}

void Student::MtNPCShip::moveWithPlayer()
{
    // Moves on screen according to the player
    int absoluteScreenPosX = (centerOffsetX_ +(shipPosX_-offsetX_))*gridSize_;
    int absoluteScreenPosY = (centerOffsetY_ +(shipPosY_-offsetY_))*gridSize_;
    this->move(absoluteScreenPosX, absoluteScreenPosY);

    // Hides if ship is in front of the HUD
    if (absoluteScreenPosY > 570){
        this->hide();
    } else {
        this->show();
    }
}

void Student::MtNPCShip::updateShipPos()
{
    if (ship_->getLocation() != nullptr){
        shipPosX_ = ship_->getLocation()->getCoordinates().x;
        shipPosY_ = ship_->getLocation()->getCoordinates().y;
    }
}

void Student::MtNPCShip::setShipPos(int posX, int posY)
{
    shipPosX_ = posX;
    shipPosY_ = posY;
}

void Student::MtNPCShip::shipInDistressON()
{
    Q_ASSERT(ship_->getEngine()->isBroken());
    inDistress_ = true;
}

void Student::MtNPCShip::shipInDistressOFF()
{
    inDistress_ = false;
}

bool Student::MtNPCShip::getPossibleDistress()
{
    return inDistress_;
}

std::shared_ptr<Common::StarSystem> Student::MtNPCShip::getShipLocation()
{
    return ship_->getLocation();
}

void Student::MtNPCShip::getScreenSize(int screenWidth, int screenHeight)
{
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
    Q_ASSERT(screenWidth_ == screenWidth);
    Q_ASSERT(screenHeight_ == screenHeight);
}


