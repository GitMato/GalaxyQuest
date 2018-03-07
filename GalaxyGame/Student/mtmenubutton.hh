/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef MTMENUBUTTON_HH
#define MTMENUBUTTON_HH

#include <QPushButton>
#include <QPixmap>
#include <QIcon>

/**
 * @file
 * @brief MtMenuButton Class is responsible for drawing
 * custom QPushButtons on screen.
 */
namespace Ui
{

/**
 * @brief The MtMenuButton Class inherits from Qt's QPushButton class.
 * It is used to create QPushButtons with custom features,
 * personalized stylesheet and fixed size.
 * It also simplifies the placing of the buttons on a scene or a widget.
 */
class MtMenuButton:public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param icon QPixmap icon which is used in the button.
     * @param x Button position X coordinate.
     * @param y Button position Y coordinate.
     * @param parent Pointer to QWidget object.
     */
    MtMenuButton(QPixmap icon, int x, int y, QWidget *parent = 0);

private:
    const int BUTTON_W = 390;
    const int BUTTON_H = 60;

};
}

#endif // MTMENUBUTTON_HH
