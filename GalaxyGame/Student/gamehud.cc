/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "gamehud.hh"

Ui::GameHUD::GameHUD(QGraphicsObject *parent) :
    QGraphicsItem(parent)
{
    // initial values for screensize
    screenWidth_ = 1200;
    screenHeight_ = 800;

    hudPosX = (screenWidth_-HUD_W)/2;
    hudPosY = (screenHeight_-HUD_H)-HUD_BOT_MARGIN;

    // initial values for all drawn HUD info
    starSystemName_ = QString::fromStdString("[Click a Starsystem]");
    starSystemCoordinates_ = QString::fromStdString("( x, y )");
    starSystemPopulation_ = QString::fromStdString("Population: unknown");
    starSystemEconomy_ = QString::fromStdString("Economy: unknown");

    scoreText_ = QString::number(0);
    creditsText_ = QString::number(0);
    savedShipsText_ = QString::number(0);
    lostShipsText_ = QString::number(0);

    starSystemEconomyTypeMap_ = {
        { 0, QString::fromStdString("Refinery")},
        { 1, QString::fromStdString("Extraction")},
        { 2, QString::fromStdString("HiTech")},
        { 3, QString::fromStdString("Industrial")},
        { 4, QString::fromStdString("Tourism")},
        { 5, QString::fromStdString("Agriculture")},
        { 6, QString::fromStdString("Service")},
        { 7, QString::fromStdString("Military")},
        { 8, QString::fromStdString("Terraforming")},
        { 9, QString::fromStdString("Colony")},
        { 10, QString::fromStdString("None")}
    };
}

// When screensize changes, boundingRect must be updated with news
// HudPos values.
QRectF Ui::GameHUD::boundingRect() const
{
    // bounding Rect is the position and size of our HUD
    return QRectF(hudPosX,hudPosY,HUD_W,HUD_H);

}

// Everything that is painted on screen in every update call.
void Ui::GameHUD::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *,
                        QWidget *)
{

    //painter->drawRect(boundingRect()); // test drawing area

    // I can do custom font now but it causes terrible lag,
    // so will leave it out.
    // Embedding a custom font for hud text display, for future use:
    //    int mtFontID =
    //    QFontDatabase::addApplicationFont(":/fonts/Assets/consolas.ttf");
    //    QString mtFontFamily =
    //    QFontDatabase::applicationFontFamilies(mtFontID).at(0);
    //    QFont consoleMonospaceFont(mtFontFamily);
    //    consoleMonospaceFont.setPixelSize(12);
    //    painter->setFont(consoleMonospaceFont);

    QFont mtfont("Monospace");
    // style hint for windows users, where typewriter is a monospace font.
    mtfont.setStyleHint(QFont::TypeWriter);
    mtfont.setPixelSize(12);
    painter->setFont(mtfont);

    // Create new custom colors and use them to draw text on QGraphicsItem
    QColor mtnaturalwhite(230,225,213);
    QColor mtcyan(60,244,234);
    QColor mtlightorange(250,190,100);
    QPen lightpen(mtnaturalwhite,1);
    QPen cyanpen(mtcyan,1);
    QPen lorangepen(mtlightorange,1);

    painter->setPen(lightpen);

    // Hudpos X and Y can change, but other values here must be absolute.
    painter->drawText(hudPosX+718,hudPosY+58, starSystemName_);
    painter->drawText(hudPosX+718,hudPosY+77, starSystemCoordinates_);
    painter->drawText(hudPosX+740,hudPosY+99, starSystemPopulation_);
    painter->drawText(hudPosX+740,hudPosY+116, starSystemEconomy_);

    painter->drawText(hudPosX+145,hudPosY+65, scoreText_);
    painter->drawText(hudPosX+145,hudPosY+92, creditsText_);
    painter->drawText(hudPosX+145,hudPosY+119, savedShipsText_);
    painter->drawText(hudPosX+145,hudPosY+147, lostShipsText_);

    // Draw information about closest ships in systems,
    // title and loop through shipmap
    painter->setPen(cyanpen);
    painter->drawText(hudPosX+252,hudPosY+58,
                      QString::fromStdString("Ships near ")
                      + starSystemName_ + QString::fromStdString(":"));

    int i = 0;
    for (auto const& nearbyship : nearbyShips_){
        // I want to show only first 4 ships in the map,
        // even though map could have more.
        if (i>3){
            break;
        }
        mtfont.setPixelSize(11);
        painter->setFont(mtfont);
        painter->setPen(lightpen);
        painter->drawText(hudPosX+287,hudPosY+74+(i*13*2),
                          QString::fromStdString(nearbyship.first));

        painter->setPen(lorangepen);
        mtfont.setPixelSize(10);
        painter->setFont(mtfont);
        painter->drawText(hudPosX+307,hudPosY+86+(i*13*2),
                          QString::fromStdString(" in ")
                          + QString::fromStdString(nearbyship.second));
        i++;
    }

}

void Ui::GameHUD::setStarSystemInfoForHUD(QString starSystemName,
                                          QString starSystemPopulation,
                                      int typeID, int starSystemCoordX,
                                          int starSystemCoordY)
{
    // Create a stylized string from starsystem x and y coordinates
    std::string starSystemCoordsStr =
            "( " + std::to_string(starSystemCoordX) + ", "
            + std::to_string(starSystemCoordY) + " )";

    // Create a stylized string from given economy type
    QString starSystemEconomyQStr = QString::fromStdString("Economy: ")
            + starSystemEconomyTypeMap_[typeID];

    // Set all strings for HUD to draw in the next update
    starSystemName_ = starSystemName;
    starSystemCoordinates_ = QString::fromStdString(starSystemCoordsStr);
    starSystemEconomy_ = starSystemEconomyQStr;
    starSystemPopulation_ = starSystemPopulation;
}

void Ui::GameHUD::setStatisticsForHUD(int score, int credits,
                                      int savedShips, int lostShips)
{
    scoreText_ = QString::number(score);
    creditsText_ = QString::number(credits);
    savedShipsText_ = QString::number(savedShips);
    lostShipsText_ = QString::number(lostShips);
}

void Ui::GameHUD::setNearbyShipsForHUD(std::string shipName,
                                       std::string starSystemName)
{
    nearbyShips_[shipName] = starSystemName;
}

void Ui::GameHUD::resetNearbyShipsMap()
{
    nearbyShips_.clear();
    Q_ASSERT(nearbyShips_.size() == 0);
}

void Ui::GameHUD::getScreenSize(int screenWidth, int screenHeight)
{
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
    Q_ASSERT(screenWidth_ == screenWidth);
    Q_ASSERT(screenHeight_ == screenHeight);
}
