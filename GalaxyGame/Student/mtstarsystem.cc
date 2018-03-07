/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "mtstarsystem.hh"

Student::MtStarSystem::MtStarSystem(std::shared_ptr<Student::Galaxy> galaxy,
                           std::shared_ptr<Common::StarSystem> starsystem,
                           Student::Player *player, MainWindow *mainwindow,
                                    QWidget *parent) :
    QPushButton(parent)
{

    inDistress = false;

    galaxy_ = galaxy;
    starsystem_ = starsystem;
    player_ = player;
    mainwindow_ = mainwindow;

    centerOffsetX_ = player_->getCenterOffsetX();
    centerOffsetY_ = player_->getCenterOffsetY();

    // initial values for screen size, can change later.
    screenWidth_ = 1200;
    screenHeight_ = 800;

    // get player's location and gridsize
    updatePlayerPos();

    this->setStyleSheet(
                "QPushButton{ "
                    "image: url(:/gfx/Assets/starsystem29.png);"
                    "background-color: rgba(255, 255, 255, 0); "
                    "border: none; }"
                "QPushButton:hover{ "
                    "image: url(:/gfx/Assets/starsystem29-blue.png);}"
                "QPushButton:pressed{ "
                    "image: url(:/gfx/Assets/starsystem29-white.png); }");
    this->move((centerOffsetX_ + (starsystem_->getCoordinates().x-offsetX_))*
               gridSize_,
               (centerOffsetY_ + (starsystem_->getCoordinates().y-offsetY_))*
               gridSize_);
    this->resize(gridSize_,gridSize_);

    updateShipsInSystem();

    connect(this, SIGNAL(clicked()), this, SLOT(starsystemClicked()));

}

void Student::MtStarSystem::updateShipsInSystem()
{
    // Clear old ships in the system
    shipsInSystem_.clear();
    shipsInSystem_ = galaxy_->getShipsInStarSystem(starsystem_->getName());

    // Tooltip
    std::string name = starsystem_->getName();
    std::string systemTooltip = name;
    if (shipsInSystem_.size() > 0){
        for (unsigned int i = 0; i < shipsInSystem_.size(); i++){
            if (i == 0){
                systemTooltip += "\n    Ships In System:";
            }
            if (shipsInSystem_[i]->isAbandoned()){
                systemTooltip += "\n        " +
                        shipsInSystem_[i]->getName() + " [ Abandoned ]";
            } else {
                systemTooltip += "\n        " +
                        shipsInSystem_[i]->getName();
            }
        }
    }
    this->setToolTip(QString::fromStdString(systemTooltip));

    // Change image according to inDistress boolean
    if (this->inDistress){
        this->setStyleSheet(
                    "QPushButton{ "
                        "image: url(:/gfx/Assets/starsystem29-red.png);"
                        "background-color: rgba(255, 255, 255, 0); "
                        "border: none; }"
                    "QPushButton:hover{ "
                        "image: url(:/gfx/Assets/starsystem29-blue.png); }"
                    "QPushButton:pressed{ "
                        "image: url(:/gfx/Assets/starsystem29-white.png); }");
    } else {
        this->setStyleSheet(
                    "QPushButton{ "
                        "image: url(:/gfx/Assets/starsystem29.png);"
                        "background-color: rgba(255, 255, 255, 0); "
                        "border: none; }"
                    "QPushButton:hover{ "
                        "image: url(:/gfx/Assets/starsystem29-blue.png); }"
                    "QPushButton:pressed{ "
                        "image: url(:/gfx/Assets/starsystem29-white.png); }");
    }
}


void Student::MtStarSystem::shipsInDistressON()
{
    inDistress = true;
}

void Student::MtStarSystem::shipsInDistressOFF()
{
    inDistress = false;
}

// Get information of player's location
void Student::MtStarSystem::updatePlayerPos()
{
    offsetX_ = player_->getOffsetX();
    offsetY_ = player_->getOffsetY();
    gridSize_ = player_->getGridsize(); // for zoom in/out feature
    Q_ASSERT(gridSize_ == player_->getGridsize());
    Q_ASSERT(offsetX_ == player_->getOffsetX());
    Q_ASSERT(offsetY_ == player_->getOffsetY());
}

void Student::MtStarSystem::moveStarSystemWithPlayer()
{
    int absoluteScreenPosX = (centerOffsetX_ +
                              (starsystem_->getCoordinates().x-offsetX_))*
                                gridSize_;
    int absoluteScreenPosY = (centerOffsetY_ +
                              (starsystem_->getCoordinates().y-offsetY_))*
                                gridSize_;
    // Move star systems according to player's new location
    this->move(absoluteScreenPosX, absoluteScreenPosY);

    // Check drawing area, Hide starsystem if it's on top of HUD
    if (absoluteScreenPosY > 570){
        this->hide();
    } else {
        this->show();
    }
}

std::shared_ptr<Common::StarSystem> Student::MtStarSystem::getStarsystem()
{
    return starsystem_;
}

void Student::MtStarSystem::getScreenSize(int screenWidth, int screenHeight)
{
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
    Q_ASSERT(screenWidth_ == screenWidth);
    Q_ASSERT(screenHeight_ == screenHeight);
}

// SLOT
void Student::MtStarSystem::starsystemClicked()
{
    player_->setOffsets(starsystem_);
    updatePlayerPos();
    player_->setPlayerLocation(starsystem_);

    emit starsystemClickedSignal(starsystem_);
}

