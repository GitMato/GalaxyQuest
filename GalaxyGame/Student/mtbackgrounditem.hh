/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef MTBACKGROUNDITEM_HH
#define MTBACKGROUNDITEM_HH

#include <QGraphicsPixmapItem>

/**
 * @file
 * @brief MtBackgroundItem Class is responsible for drawing non-interactable
 * graphical background items.
 */
namespace Ui
{

/**
 * @brief MtBackgroundItem Class is responsible for drawing non-interactable
 * graphical background items, eg. background of the HUD and other GUI items.
 * It inherits from Qt's QGraphicsPixmapItem class.
 */
class MtBackgroundItem : public QGraphicsPixmapItem
{

public:
    /**
     * @brief Constructor.
     * @param pixmap QPixmap which is used to draw the image
     * @param parent Pointer to QGraphicsItem object.
     */
    explicit MtBackgroundItem(const QPixmap &pixmap,
                              QGraphicsItem *parent = 0);

    /**
     * @brief Virtual QPainterPath, for future use togerther
     * with collision detection.
     * @return QPainterPath information about the path and its elements
     */
    virtual QPainterPath shape() const;

};
}

#endif // MTBACKGROUNDITEM_HH
