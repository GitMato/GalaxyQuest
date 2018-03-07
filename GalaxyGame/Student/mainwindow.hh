/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gamerunner.hh"
#include "ieventhandler.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "mtmenubutton.hh"
#include "mtbackgrounditem.hh"
#include <string>
#include "mtstarsystem.hh"
#include "mtnpcship.hh"
#include "playeractions.hh"
#include "gamehud.hh"
#include "helpdialog.hh"
// tutki nämä läpi mitä tulee miltäkin mukana!

/**
 * @file
 * @brief The MainWindow Creates the main window of the game.
 * Receives and creates graphical objects and assigns them
 * to their corresponding scenes. Mainwindow also handles signals and slots to
 * move between said scenes and/or open new windows. Most objects talk to each
 * other through MainWindow.
 */

class Player;

namespace Ui {
    class MainWindow;
}
/**
 * @brief The MainWindow Receives and creates graphical objects and assigns
 * them to their corresponding scenes. Mainwindow also handles signals and
 * slots to move between said scenes and/or open new windows. Most objects
 * talk to each other through MainWindow.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Pointer to QWidget object.
     * @param gameRunner Shared pointer to Common::IGameRunner object.
     * @param galaxy Shared pointer to Student::Galaxy object.
     */
    explicit MainWindow(QWidget *parent = 0,
                        std::shared_ptr<Common::IGameRunner> gameRunner = 0,
                        std::shared_ptr<Student::Galaxy> galaxy = 0);
    /**
     * @brief Destructor.
     */
    ~MainWindow();


    /**
     * @brief Create all necessary new MtStarSystem objects and add them to
     * the gameScene
     */
    void drawGalaxy();
    /**
     * @brief drawNPCShips Create MtNPCShip object and add it to scene
     * @param ship The ship which the new MtNPCShip represents.
     */
    void drawNPCShips(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief Update all tooltips (starsystems and ships)
     */
    void updateTooltips();
    /**
     * @brief Give statistics (points, credit, savedShips and lostShips)
     * for GameHUD object.
     */
    void giveStatisticsForHUD();
    /**
     * @brief Give all ships nearby a starsystem for HUD (in range of 5)
     * @param starSystem The starsystem which acts as an origin
     */
    void giveNearbyShipsForHUD(
            std::shared_ptr<Common::StarSystem> starSystem);

    // These functions are called from eventhandler
    /**
     * @brief Remove ship from graphical representation
     * @param ship The ship to be removed.
     */
    void removeShip(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Relocate the graphical representation of a ship.
     * @param ship The graphical representation of a ship to be relocated
     * @param starSystem StarSystem where to ship is to be relocated.
     */
    void relocateShip(std::shared_ptr<Common::Ship> ship,
                      std::shared_ptr<Common::StarSystem> starSystem);
    /**
     * @brief Move a ship to a certain target (x, y)
     * @param ship The ship to be moved.
     * @param origin The origin where the ship was. (not needed in student's
     * side in our case)
     * @param target The target (x, y) where to ship should go.
     */
    void moveShip(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    /**
     * @brief Inform about an exception in ships execution.
     * @param ship The ship with the exception.
     * @param msg Message concerning that exception.
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship,
                              std::string const& msg);
    /**
     * @brief Set the MtNPCShip objects's distress on.
     * @param ship The ship which the MtNPCShip object represents.
     */
    void shipdistressOn(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Set the MtNPCShip objects's distress off.
     * @param ship The ship which the MtNPCShip object represents.
     */
    void shipdistressOff(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief abandonShip Hide MtNPCShip object.
     * @param ship The ship which the MtNPCShip object represents.
     */
    void abandonShip(std::shared_ptr<Common::Ship> ship);

    // Graphic Functions related to player movement and actions
    /**
     * @brief updatePlayerPos Updates offsets and grid size from the
     * Player object.
     */
    void updatePlayerPos();
    /**
     * @brief Move all the graphics which needs to be moved according
     * to the player position.
     */
    void moveAllGraphicsWithPlayer();
    /**
     * @brief Save a ship in a starsystem if there is one to save.
     */
    void savePossibleShipInDistress();

private slots:
    /**
     * @brief Initialize the game. Ask gamerunner to spawn 50 ships,
     * draw the galaxy and change scene to gameScene.
     */
    void initgame();
    /**
     * @brief "Pause" the game by changing the scene from gameScene
     * to gamePausedScene
     */
    void pauseGame();
    /**
     * @brief Resume the game by changing from gamePausedScene to gameScene.
     * game continues where it was left.
     */
    void resumeGame();
    /**
     * @brief Create and show a HelpDialog window-object.
     */
    void showHelpDialog();
    /**
     * @brief endTurnOperation Do every operation needed for end turn:
     * actions for ships, move graphics, update tooltips and HUD and
     * check if win or loss conditions are met.
     */
    void endTurnOperation();
    /**
     * @brief starSystemClicked According to clicked starsystem:
     * move graphics and update HUD
     * @param starsystem The clicked star system
     */
    void starSystemClicked(std::shared_ptr<Common::StarSystem> starsystem);

private:

    // Constants for calculating the positions of graphical items.
    // These will never change, not even in resolution scaling mode
    // All values are in pixels
    /**
     * @brief HUD_W Heads Up Display's width in pixels. Used in calculating
     * HUD placement.
     */
    const int HUD_W = 1170;
    /**
     * @brief HUD_H Heads Up Display's height in pixels. Used in calculating
     * HUD placement.
     */
    const int HUD_H = 192;
    const int HUD_BOT_MARGIN = 8;
    /**
     * @brief TITLE_W Title width, used in calculating the centering for
     * titles.
     */
    const int TITLE_W = 780;
    const int TITLE_POS_Y = 210;
    const int BUTTON_W = 390;
    /**
     * @brief HUDBUTTON_W HUD Button's width in pixels.
     */
    const int HUDBUTTON_W = 209;
    /**
     * @brief HUDBUTTON_H HUD Button's height in pixels, used in calculating
     * HUD button placements
     */
    const int HUDBUTTON_H = 33;
    /**
     * @brief HUDB_MARGIN Margin between HUD Buttons, used in calculating HUD
     * button placement.
     */
    const int HUDB_MARGIN = 11;
    const int HUDB_POS_X = 946;
    const int HUDB_POS_Y = 42;

    // Scene GUI drawing functions
    /**
     * @brief drawStartAndPauseSceneUI Creates all QPixmap, MtMenuButton
     * and MtBackground items which the Start Menu Scene and Pause Scene
     * GUIs constitute of.
     * Assigns ownership of each said item to their corresponding scenes.
     * Also calculates the X and Y position of each said item using constants
     * and screensize.
     * Connects each created buttons' signals to mainwindow slots.
     */
    void drawStartAndPauseSceneUI();
    /**
     * @brief drawGameSceneUI Creates all QPixmap, MtMenuButton
     * and MtBackground items which the Game Scene constitutes of.
     * Assigns ownership of each said item to the gameScene.
     * Also Places gameHUD object on the gameScene and draws the player ship.
     * Connects each created buttons' signals to mainwindow slots.
     */
    void drawGameSceneUI();
    /**
     * @brief drawEndingScenesUI Creates all QPixmap, MtMenuButton
     * and MtBackground items which the Game over and Game won scene
     * GUIs constitute of.
     * Assigns ownership of each said item to their corresponding scenes.
     * Also calculates the X and Y position of each said item using constants
     * and screensize.
     * Connects each created buttons' signals to mainwindow slots.
     */
    void drawEndingScenesUI();

    Ui::MainWindow *ui;
    HelpDialog *helpDialogi;

    /**
     * @brief startScene takes ownership of all graphical objects assigned to
     * startScene. startScene is the first scene to be shown in QGraphicsView
     * in MainWindow.
     */
    QGraphicsScene *startScene;
    /**
     * @brief gameScene takes ownership of all graphical objects assigned to
     * gameScene. This scene is the surface of the actual game.
     */
    QGraphicsScene *gameScene;
    /**
     * @brief gameWonScene takes ownership of all graphical objects assigned
     * to gameWonScene. This scene is shown if player wins the game.
     * This scene acts as an end game menu and can be configured
     * to have more options in future updates.
     */
    QGraphicsScene *gameWonScene;
    /**
     * @brief gamePausedScene takes ownership of all graphical objects
     * assigned to gamePausedScene. This scene is shown if player clicks the
     * pause button in gameScene. This scene acts as a midgame menu and can
     * be configured to have more options in future updates.
     */
    QGraphicsScene *gamePausedScene;
    /**
     * @brief gameOverScene takes ownership of all graphical objects assigned
     * to gameOverScene. This scene is shown if player loses the game.
     * This scene acts as an end game menu and can be configured
     * to have more options in future updates.
     */
    QGraphicsScene *gameOverScene;

    // START MENU GUI graphics
    /**
     * @brief otsikkokuva Start Menu -
     * Scene's title background graphics object.
     */
    Ui::MtBackgroundItem *otsikkokuva;
    Ui::MtMenuButton *startMenuStartButton;
    Ui::MtMenuButton *startMenuOptionsButton;
    Ui::MtMenuButton *startMenuQuitButton;

    // GAME SCENE GUI graphics
    /**
     * @brief gameHUD Background graphics for Heads up display.
     */
    Ui::MtBackgroundItem *gameHUD;
    Ui::MtMenuButton *endturnbutton;
    Ui::MtMenuButton *menubutton;
    Ui::MtMenuButton *quitbutton;
    /**
     * @brief hud_ Functional graphics of the Heads up display,
     * drawn on top of background graphics.
     */
    Ui::GameHUD *hud_;

    // GAME PAUSED SCENE graphics
    /**
     * @brief gamePausedTitle Pause -
     * Scene's title background graphics object.
     */
    Ui::MtBackgroundItem *gamePausedTitle;
    Ui::MtMenuButton *continueButton;
    Ui::MtMenuButton *pauseSceneQuitButton;

    // GAME WON & GAME OVER SCENE graphics
    /**
     * @brief voititpelinkuva Game Won -
     * Scene's title background graphics object.
     */
    Ui::MtBackgroundItem *voititpelinkuva;
    Ui::MtBackgroundItem *gameOverTitle;
    Ui::MtMenuButton *endQuitButton;
    Ui::MtMenuButton *endQuitButtonSad;

    // Other Graphics
    /**
     * @brief playerShip Player's ship graphical object. Currently player
     * Ship is always in the center of the map, and everything else moves
     * when player moves. So there's no need to move the player ship
     * graphical object.
     */
    Ui::MtBackgroundItem *playerShip;

    // Other Objects and pointers
    Student::Player *player_;
    Student::PlayerActions *playerActions_;
    Student::Statistics *statistics_;

    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gamerunner_;

    // Game object containers
    std::map<std::shared_ptr<Common::StarSystem>,
    Student::MtStarSystem*> starsystemsInScene_;
    std::map<std::shared_ptr<Common::Ship>,
    Student::MtNPCShip*> shipsInScene_;

    // Player position storage
    /**
     * @brief Player position in X axis. Defines how many units the graphical
     * grid must be moved to center it on the player.
     * Given by the player class.
     */
    int offsetX_;
    /**
     * @brief Player position in Y axis. Defines how many units the graphical
     * grid must be moved to center it on the player.
     * Given by the player class.
     */
    int offsetY_;
    /**
     * @brief Size of the drawn single coordinate grid in pixels.
     * Each coordinate is multiplied by gridsize. Given by the player class.
     */
    int gridSize_;

    // Player ship position stores reserved for future use
    // These will be used in together with offsets to calculate
    // more complicated player movement
    int playerShipPosStoreX;
    int playerShipPosStoreY;

    /**
     * @brief screenWidth Stores the screen width in pixels.
     */
    int screenWidth;
    /**
     * @brief screenHeight Stores the screen height in pixels.
     */
    int screenHeight;

};

#endif // MAINWINDOW_HH
