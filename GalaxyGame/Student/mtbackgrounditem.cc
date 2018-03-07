/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "mtbackgrounditem.hh"

// luokka kuvien piirtämiseen (background item) joiden kanssa EI interractata
Ui::MtBackgroundItem::MtBackgroundItem(const QPixmap &pixmap,
                                       QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{

}

// Used to contain complex shapes.
// Will be used for future collision detection.
QPainterPath Ui::MtBackgroundItem::shape() const
{
    return QPainterPath();
}
