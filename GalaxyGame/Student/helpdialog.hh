/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef HELPDIALOG_HH
#define HELPDIALOG_HH

#include <QDialog>

/**
 * @file
 * @brief HelpDialog class creates a dialog window when
 * mainWindow calls for it.
 */
namespace Ui {
class HelpDialog;
}
/**
 * @brief The HelpDialog class creates a dialog window when
 * mainWindow calls for it.
 */
class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Pointer to QWidget object.
     */
    explicit HelpDialog(QWidget *parent = 0);
    /**
     * @brief The destructor.
     */
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_HH
