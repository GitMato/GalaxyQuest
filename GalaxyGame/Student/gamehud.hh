/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef GAMEHUD_HH
#define GAMEHUD_HH

#include <QPainter>
#include <QGraphicsItem>
#include <QFontDatabase>
class MainWindow;

/**
 * @file
 * @brief GameHUD is responsible for drawing statistics and other
 * relevant information on screen.
 */
namespace Ui
{
// TODO: HUD widthistä ja screen widthistä constantit/vakiot
/**
 * @brief The GameHUD class draws game statistics, nearby ship information
 * and star system details of the chosen starsystem on the heads up display.
 * (HUD)
 *
 * GameHUD inherits public members of the QGraphicsItem class.
 */
class GameHUD: public QGraphicsItem
{
public:
    /**
     * @brief Constructor.
     * @param parent Pointer to QGraphicsObject object.
     */
    GameHUD(QGraphicsObject *parent = 0);

    /**
     * @return Returns the bounding rectangle of the QGraphicsItem.
     */
    QRectF boundingRect() const;

    /**
     * @brief paint is inherited from the abstract class QGraphicsItem.
     * Everything inside paint will be drawn on screen on every update call.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    /**
     * @brief setStarSystemInfoForHUD Sets given starsystem information
     * ready for painter to paint on the screen.
     * When a starsystem is clicked, mainwindow sends
     * star system information by calling this function.
     * @param starSystemName QString Name of the clicked starsystem.
     * @param starSystemPopulation QString Population of
     * the clicked starsystem.
     * @param typeID Int economy type of the given starsystem.
     * @param starSystemCoordX Starsystem X coordinate.
     * @param starSystemCoordY Starsystem Y coordinate.
     */
    void setStarSystemInfoForHUD(QString starSystemName,
                                 QString starSystemPopulation,
                                 int typeID,
                                 int starSystemCoordX,
                                 int starSystemCoordY
                                 );
    /**
     * @brief setStatisticsForHUD Sets given statistics ready for painter to
     * paint on the screen. Mainwindow sends statistic information by calling
     * this function.
     * @param score Current score of the player.
     * @param credits Current credits of the player.
     * @param savedShips Current amount of saved ships.
     * @param lostShips Current amount of lost ships.
     */
    void setStatisticsForHUD(int score, int credits,
                             int savedShips, int lostShips);
    /**
     * @brief setNearbyShipsForHUD Gets nearby ship information from
     * mainwindow and puts it in a map.
     * @param shipName Name of the given ship.
     * @param starSystemName Starsystem where the given ship currently is.
     */
    void setNearbyShipsForHUD(std::string shipName,
                              std::string starSystemName);
    /**
     * @brief resetNearbyShipsMap Clears the nearby ships - map.
     * @post nearbyShips_ map is empty
     */
    void resetNearbyShipsMap();

    /**
     * @brief getScreenSize Get screen size (width and height).
     * @param screenWidth Screen width
     * @param screenHeight Screen height
     * @post screenWidth and screenHeight are set.
     */
    void getScreenSize(int screenWidth, int screenHeight);

private:
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

    QString starSystemName_;
    QString starSystemCoordinates_;
    QString starSystemPopulation_;
    QString starSystemEconomy_;

    QString scoreText_;
    QString creditsText_;
    QString savedShipsText_;
    QString lostShipsText_;

    /**
     * @brief starSystemEconomyTypeMap_ Stores information about the possible
     * economy types of the starsystems.
     */
    std::map<int, QString> starSystemEconomyTypeMap_;

    int screenWidth_;
    int screenHeight_;

    /**
     * @brief hudPosX Is calculated by formula
     * (( screenWidth - hudWidth ) / 2).
     * Such formula centers the HUD into the middle of the screen in X axis.
     */
    int hudPosX;
    /**
     * @brief hudPosY Is calculated by formula
     * (( screenHeight - hudHeight ) - bottomMargin)
     */
    int hudPosY;

    /**
     * @brief nearbyShips_ Stores information of the nearby ships.
     */
    std::map<std::string, std::string> nearbyShips_;

};
}

#endif // GAMEHUD_HH
