/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent,
                       std::shared_ptr<Common::IGameRunner> gameRunner,
                        std::shared_ptr<Student::Galaxy> galaxy):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    galaxy_ = galaxy;
    gamerunner_ = gameRunner;
    player_ = new Student::Player();
    statistics_ = new Student::Statistics();
    playerActions_ = new Student::PlayerActions(statistics_);
    hud_ = new Ui::GameHUD();

    screenWidth = 1200;
    screenHeight = 800;

    hud_->getScreenSize(screenWidth, screenHeight);
    hud_->update();

    // get offsetX_, offsetY_ and gridSize_ initial values from player
    // currently player starts from SOL (0,0)
    updatePlayerPos();

    ui->setupUi(this);

    // Create all scenes and set startscene to graphicsView
    startScene = new QGraphicsScene(this);
    gameScene = new QGraphicsScene(this);
    gamePausedScene = new QGraphicsScene(this);
    gameWonScene = new QGraphicsScene(this);
    gameOverScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(startScene);

    // Set scenes to fixed size and give them backgrounds
    startScene->setSceneRect(0,0,screenWidth,screenHeight);
    startScene->setBackgroundBrush(
                QBrush(QImage(":/gfx/Assets/galaxyqbg1.png")));

    gameScene->setSceneRect(0,0,screenWidth,screenHeight);
    gameScene->setBackgroundBrush(
                QBrush(QImage(":/gfx/Assets/game-bg-1.png")));

    gamePausedScene->setSceneRect(0,0,screenWidth,screenHeight);
    gamePausedScene->setBackgroundBrush(
                QBrush(QImage(":/gfx/Assets/game-bg-1.png")));

    gameWonScene->setSceneRect(0,0,screenWidth,screenHeight);
    gameWonScene->setBackgroundBrush(
                QBrush(QImage(":/gfx/Assets/game-bg-1.png")));

    gameOverScene->setSceneRect(0,0,screenWidth,screenHeight);
    gameOverScene->setBackgroundBrush(
                QBrush(QImage(":/gfx/Assets/game-bg-1.png")));

    // Draw GUIs for scenes (only once)
    drawStartAndPauseSceneUI();
    drawGameSceneUI();
    drawEndingScenesUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOT: Clicking "Start game" changes the scene and initializes the game area
void MainWindow::initgame()
{
    ui->graphicsView->setScene(gameScene);
    drawGalaxy();
    gamerunner_->spawnShips(50);
    gamerunner_->createActions();
    updateTooltips();
    moveAllGraphicsWithPlayer();
}

// SLOT
void MainWindow::pauseGame()
{
    ui->graphicsView->setScene(gamePausedScene);
}

// SLOT
void MainWindow::resumeGame()
{
    ui->graphicsView->setScene(gameScene);
}

// SLOT: Clicking "Options" shows help dialog
void MainWindow::showHelpDialog()
{

    helpDialogi = new HelpDialog(this);
    helpDialogi->setWindowTitle("Options and Help");
    helpDialogi->show();

}

// Draw all the GUI elements of the Start menu and Pause -
// scenes, must be called only once
void MainWindow::drawStartAndPauseSceneUI()
{
    // Ownership of each graphics object is given to scene
    // "startScene" or scene "gamePausedScene"

    // Title picture
    otsikkokuva = new Ui::MtBackgroundItem(
                QPixmap(":/gfx/Assets/gameotsikko.png"));
    startScene->addItem(otsikkokuva);
    otsikkokuva->setPos(((screenWidth - TITLE_W)/2),TITLE_POS_Y);

    // MAINMENU (Start, Options, Quit)
    QPixmap madonnappula_kuva_s(":/gfx/Assets/newgame.png");
    startMenuStartButton = new Ui::MtMenuButton(
                madonnappula_kuva_s, ((screenWidth - BUTTON_W)/2) , 305);
    startScene->addWidget(startMenuStartButton);
    connect(startMenuStartButton, SIGNAL(clicked()), this, SLOT(initgame()));

    QPixmap madonnappula_kuva_o(":/gfx/Assets/options.png");
    startMenuOptionsButton = new Ui::MtMenuButton(
                madonnappula_kuva_o, ((screenWidth - BUTTON_W)/2), 365);
    startScene->addWidget(startMenuOptionsButton);
    connect(startMenuOptionsButton, SIGNAL(clicked()),
            this, SLOT(showHelpDialog()));

    QPixmap madonnappula_kuva_q(":/gfx/Assets/quit.png");
    startMenuQuitButton = new Ui::MtMenuButton(
                madonnappula_kuva_q, ((screenWidth - BUTTON_W)/2), 425);
    startScene->addWidget(startMenuQuitButton);
    connect(startMenuQuitButton, SIGNAL(clicked()), this, SLOT(close()));

    // PAUSED TITLE
    gamePausedTitle = new Ui::MtBackgroundItem(
                QPixmap(":/gfx/Assets/gamepausedtitle.png"));
    gamePausedScene->addItem(gamePausedTitle);
    gamePausedTitle->setPos(((screenWidth - TITLE_W)/2),TITLE_POS_Y);

    // Pausemenu (Continue, Quit) - New game choice could be added later.
    QPixmap continueButton_kuva(":/gfx/Assets/continue.png");
    continueButton = new Ui::MtMenuButton(
                continueButton_kuva, ((screenWidth - BUTTON_W)/2) , 305);
    gamePausedScene->addWidget(continueButton);
    connect(continueButton, SIGNAL(clicked()), this, SLOT(resumeGame()));

    pauseSceneQuitButton = new Ui::MtMenuButton(
                madonnappula_kuva_q, ((screenWidth - BUTTON_W)/2), 365);
    gamePausedScene->addWidget(pauseSceneQuitButton);
    connect(pauseSceneQuitButton, SIGNAL(clicked()), this, SLOT(close()));

}

// Draw all the GUI elements of the Game - Scene, must be called only once
void MainWindow::drawGameSceneUI()
{
    // Ownership of each graphics object is given to scene "gameScene"

    // GAME SCENE
    // Background item: HUD / GUI Base
    gameHUD = new Ui::MtBackgroundItem(QPixmap(":/gfx/Assets/GQ-GUI-v4.png"));
    gameScene->addItem(gameHUD);
    gameHUD->setPos(((screenWidth - HUD_W)/2),
                    screenHeight - HUD_H - HUD_BOT_MARGIN);

    // HUD End Turn - Button
    QPixmap endturnbutton_kuva(":/gfx/Assets/HUDendturn.png");
    Ui::MtMenuButton *endturnbutton = new Ui::MtMenuButton(
                endturnbutton_kuva,
                ((screenWidth - HUD_W)/2) + HUDB_POS_X,
                (screenHeight - HUD_H - HUD_BOT_MARGIN) + HUDB_POS_Y
                );

    endturnbutton->resize(HUDBUTTON_W, HUDBUTTON_H);
    gameScene->addWidget(endturnbutton);
    connect(endturnbutton, SIGNAL(clicked()), this, SLOT(endTurnOperation()));

    // HUD Pause / Menu - Button
    QPixmap menubutton_kuva(":/gfx/Assets/HUDpause.png");
    Ui::MtMenuButton *menubutton = new Ui::MtMenuButton(
                menubutton_kuva,
                ((screenWidth - HUD_W)/2) + HUDB_POS_X,
                (screenHeight - HUD_H - HUD_BOT_MARGIN) +
                HUDB_POS_Y + HUDB_MARGIN + HUDBUTTON_H
                ); // I like math. These calculate each hud
                   // button placement according to screensize.

    menubutton->resize(HUDBUTTON_W, HUDBUTTON_H);
    gameScene->addWidget(menubutton);
    connect(menubutton, SIGNAL(clicked()), this, SLOT(pauseGame()));

    // HUD Quit - Button
    QPixmap quitbutton_kuva(":/gfx/Assets/HUDquit.png");
    Ui::MtMenuButton *quitbutton = new Ui::MtMenuButton(
                quitbutton_kuva,
                ((screenWidth - HUD_W)/2) + HUDB_POS_X,
                (screenHeight - HUD_H - HUD_BOT_MARGIN) +
                HUDB_POS_Y + HUDB_MARGIN*2 + HUDBUTTON_H*2
                ); // HUDBUTTON_MARGIN and HEIGHT * 2
                   // because 2 buttons are above quit button.

    quitbutton->resize(HUDBUTTON_W, HUDBUTTON_H);
    gameScene->addWidget(quitbutton);
    connect(quitbutton, SIGNAL(clicked()), this, SLOT(close()));

    // Draw Player Ship
    playerShip = new Ui::MtBackgroundItem(
                QPixmap(":/gfx/Assets/playership.png"));
    gameScene->addItem(playerShip);
    playerShip->setPos((screenWidth/2 + 15), (screenHeight-HUD_H)/2 + 15);

    // HUD Information display
    gameScene->addItem(hud_);

}

// Draw all the GUI elements of the Game Won / Game Over -
// Scenes, must be called only once
void MainWindow::drawEndingScenesUI()
{
    // Ownership of each graphics object is given to their
    // corresponding scenes.
    // Game Over and Game Won are different scenes for future, more unique use.

    // TITLE - Happy ending!
    voititpelinkuva = new Ui::MtBackgroundItem(
                QPixmap(":/gfx/Assets/voititpelin_placeholder.png"));
    gameWonScene->addItem(voititpelinkuva);
    voititpelinkuva->setPos(((screenWidth - TITLE_W)/2),TITLE_POS_Y);

    // Quit button for Happy ending
    QPixmap quitbutton_kuva(":/gfx/Assets/quit.png");
    Ui::MtMenuButton *endQuitButton = new Ui::MtMenuButton(
                quitbutton_kuva, ((screenWidth - BUTTON_W)/2) , 305);
    gameWonScene->addWidget(endQuitButton);
    connect(endQuitButton, SIGNAL(clicked()), this, SLOT(close()));


    // TITLE - Sad ending :(
    gameOverTitle = new Ui::MtBackgroundItem(
                QPixmap(":/gfx/Assets/gameover-otsikko.png"));
    gameOverScene->addItem(gameOverTitle);
    gameOverTitle->setPos(((screenWidth - TITLE_W)/2),TITLE_POS_Y);

    // Quit button for Sad ending, QWidgets can have only one parent,
    // so we have to create another quit button.
    Ui::MtMenuButton *endQuitButtonSad = new Ui::MtMenuButton(
                quitbutton_kuva, ((screenWidth - BUTTON_W)/2) , 305);
    gameOverScene->addWidget(endQuitButtonSad);
    connect(endQuitButtonSad, SIGNAL(clicked()), this, SLOT(close()));

}

void MainWindow::drawGalaxy()
{

    Common::StarSystem::StarSystemVector starsystemsInGalaxy =
            galaxy_->getStarsystems();
    unsigned int system_amount = starsystemsInGalaxy.size();

    Student::MtStarSystem *new_starsystem;
    for (unsigned int i = 0; i < system_amount; i++){
        new_starsystem = new Student::MtStarSystem(
                    galaxy_, starsystemsInGalaxy[i], player_, this);
        starsystemsInScene_[starsystemsInGalaxy[i]] = new_starsystem;
        gameScene->addWidget(new_starsystem);
        new_starsystem->getScreenSize(screenWidth, screenHeight);
        connect(new_starsystem,
                SIGNAL(starsystemClickedSignal(
                           std::shared_ptr<Common::StarSystem>)),
                this,
                SLOT(starSystemClicked(
                               std::shared_ptr<Common::StarSystem>)));
    }

}

void MainWindow::drawNPCShips(std::shared_ptr<Common::Ship> ship)
{

    Student::MtNPCShip *new_npcship;
    new_npcship = new Student::MtNPCShip(ship, player_);
    shipsInScene_[ship] = new_npcship;
    gameScene->addWidget(new_npcship);
    new_npcship->getScreenSize(screenWidth, screenHeight);

}

// Go through starsystems and ships to update their tooltips
void MainWindow::updateTooltips()
{

    for (auto const& starsystem : starsystemsInScene_){
        starsystem.second->updateShipsInSystem();
    }
    for (auto const& ship : shipsInScene_){
        ship.second->updateShipTooltip();
    }
}

// Give current statistics for GameHUD to display
void MainWindow::giveStatisticsForHUD()
{

    hud_->setStatisticsForHUD(statistics_->getPoints(),
                              statistics_->getCreditBalance(),
                              statistics_->getSavedShips(),
                              statistics_->getLostShips());

}

void MainWindow::giveNearbyShipsForHUD(
        std::shared_ptr<Common::StarSystem> starSystem)
{

    hud_->resetNearbyShipsMap();
    Common::StarSystem::StarSystemVector starSystemsInRange =
            galaxy_->getSystemsInRange(starSystem, 5);

    for (unsigned int i = 0; i < starSystemsInRange.size(); i++){

        for (auto const& ship : shipsInScene_){
            if (ship.first->getLocation() == starSystemsInRange[i]){
                hud_->setNearbyShipsForHUD(ship.first->getName(),
                                           starSystemsInRange[i]->getName());
            } else if (ship.first->getLocation() == starSystem){
                hud_->setNearbyShipsForHUD(ship.first->getName(),
                                           starSystem->getName());
            }
        }
    }
}


void MainWindow::removeShip(std::shared_ptr<Common::Ship> ship)
{

    shipsInScene_.erase(ship);
    galaxy_->removeShip(ship);
    updateTooltips();

}

void MainWindow::relocateShip(std::shared_ptr<Common::Ship> ship,
                              std::shared_ptr<Common::StarSystem>)
{
    // Parameter starSystem is not used, because it is not needed.
    // updateShipPos() function does the job.

    Student::MtNPCShip *shipToRelocate = shipsInScene_.find(ship)->second;

    shipToRelocate->updateShipPos();
    shipToRelocate->moveWithPlayer();
}

void MainWindow::moveShip(std::shared_ptr<Common::Ship> ship,
                          Common::Point, Common::Point target)
{
    // Parameter origin is not needed. Ship will move to the target location
    // without the information where it came.

    Student::MtNPCShip *shipToMove = shipsInScene_.find(ship)->second;
    shipToMove->move((target.x+offsetX_)*gridSize_,
                     (target.y+offsetY_)*gridSize_); //target
    int x = target.x;
    int y = target.y;
    shipToMove->setShipPos(x, y);

}

void MainWindow::exceptionInExecution(std::shared_ptr<Common::Ship>,
                                      const std::string &)
{
    // Not implemented
}

void MainWindow::shipdistressOn(std::shared_ptr<Common::Ship> ship)
{

    // Find the MtStarSystem object and set distress on
    std::shared_ptr<Common::StarSystem> starsystem = ship->getLocation();
    if (starsystem != nullptr){
        starsystemsInScene_.find(starsystem)->second->shipsInDistressON();
    }

    // Find the MtNPCShip object and set distress on
    shipsInScene_.find(ship)->second->shipInDistressON();

}

void MainWindow::shipdistressOff(std::shared_ptr<Common::Ship> ship)
{

    // Find the MtStarSystem object and set distress off
    std::shared_ptr<Common::StarSystem> starsystem = ship->getLocation();
    if (starsystem != nullptr){
        starsystemsInScene_.find(starsystem)->second->shipsInDistressOFF();
    }

    // Find the MtNPCShip object and set distress off
    shipsInScene_.find(ship)->second->shipInDistressOFF();
    updateTooltips();

}

void MainWindow::abandonShip(std::shared_ptr<Common::Ship> ship)
{


    Student::MtNPCShip *npcShip = shipsInScene_[ship];
    shipdistressOff(ship);
    statistics_->addLostShip();
    // Abandoned ship will remain in galaxy but the graphical
    // presentation will be hidden.
    npcShip->hide();
    shipsInScene_.erase(ship);

}

// Get updated information about player position from player
void MainWindow::updatePlayerPos()
{

    gridSize_ = player_->getGridsize();
    offsetX_ = player_->getOffsetX();
    offsetY_ = player_->getOffsetY();

}

void MainWindow::moveAllGraphicsWithPlayer()
{

    for (auto const& starsystem : starsystemsInScene_){
        starsystem.second->updatePlayerPos();
        starsystem.second->moveStarSystemWithPlayer();
    }
    for (auto const& ship : shipsInScene_){
        ship.second->updatePlayerPos();
        ship.second->moveWithPlayer();
        ship.second->updateShipPos();
    }

}

// Try to save a ship if you are in the same starsystem with it.
void MainWindow::savePossibleShipInDistress()
{

    for (auto const& ship : shipsInScene_){
        // Check if ship's distress is on.
        if (ship.second->getPossibleDistress()){
            // Check if ship is in the same starsystem with the player.
            if (ship.second->getShipLocation() ==
                    player_->getPlayerLocation()){
                try
                {
                playerActions_->shipSaved(ship.first);
                }
                catch (Common::StateException const& virhe)
                {
                    qDebug() << "Caught StateException: " <<
                                QString::fromStdString(virhe.msg());
                }

                // Eventhandler is called a turn too late,
                // so shipdistressOff is called here too.
                shipdistressOff(ship.first);
            }
        }
    }
}

// SLOT
// Arguably the most important function in the game. endTurnOperation
// provides the main functionality of the game.
void MainWindow::endTurnOperation()
{

    gamerunner_->createActions();
    gamerunner_->doActions();

    moveAllGraphicsWithPlayer(); // Moves both starsystems and NPC ships
    savePossibleShipInDistress();
    updateTooltips(); // Updates both ship and starsystem tooltips
    giveStatisticsForHUD();
    hud_->update();

    // Game won! Change scene
    if(playerActions_->winCondition()){
        ui->graphicsView->setScene(gameWonScene);
    }

    // Game over! Change scene
    if(playerActions_->lossCondition()){
        ui->graphicsView->setScene(gameOverScene);
    }

}

// SLOT
void MainWindow::starSystemClicked(
        std::shared_ptr<Common::StarSystem> starsystem)
{

    moveAllGraphicsWithPlayer();
    giveStatisticsForHUD();
    giveNearbyShipsForHUD(starsystem);

    int starSystemCoordX = starsystem->getCoordinates().x;
    int starSystemCoordY = starsystem->getCoordinates().y;
    int typeID = (int)starsystem->getEconomy();

    // Gives starsystem's information for the GameHUD to draw on the screen.
    std::string populationStr =
            "Population: " + std::to_string(starsystem->getPopulation());
    hud_->setStarSystemInfoForHUD(
                QString::fromStdString(starsystem->getName()),
                QString::fromStdString(populationStr), typeID,
                starSystemCoordX, starSystemCoordY);
    hud_->update();

}
