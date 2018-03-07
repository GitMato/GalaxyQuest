/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "mtmenubutton.hh"

Ui::MtMenuButton::MtMenuButton(QPixmap icon, int pos_x,
                               int pos_y, QWidget *parent) :
    QPushButton(parent)

{
    this->setIcon(QIcon(icon));
    this->setIconSize(icon.rect().size());
    this->setStyleSheet("QPushButton{ "
                            "background-color: rgba(255, 255, 255, 0); "
                            "border: none; }"
                        "QPushButton:hover{ "
                            "background-color: rgba(0, 250, 255, 190); }"
                        "QPushButton:pressed{ "
                            "background-color: rgba(250, 172, 0, 255); }");
    this->move(pos_x, pos_y);
    this->resize(BUTTON_W,BUTTON_H); // Most buttons are all same fixed size
}

