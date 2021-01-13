#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

/**
 * @brief Start window where the player can input their name and game length.
 */

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief StartDialog constructor.
     * @param parent Parent widget.
     */
    explicit StartDialog(QWidget *parent = nullptr);

    /**
     * @brief ~StartDialog destructor.
     */
    virtual ~StartDialog();

    /**
     * @brief useName gets the player's name input.
     * @pre -
     * @post Player's name is send as a signal.
     */
    void useName();

signals:
    /**
     * @brief gameTimeGiven sends given game length as a signal.
     * @param sec Given seconds.
     * @param min Given minutes.
     */
    void gameTimeGiven(int sec, int min);

    /**
     * @brief nameGiven sends given name as a signal.
     * @param name Given name.
     */
    void nameGiven(QString name);

private slots:
    /**
     * @brief useGivenTime gets the game lenght input and sends gameTimeGiven signal.
     * @pre -
     * @post Game length is send as a signal.
     */
    void useGivenTime();

    /**
     * @brief useDefault sets the game lenght as default (30 sec) and sends gameTimeGiven signal.
     * @pre -
     * @post Game length is send as a signal.
     */
    void useDefault();


private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_HH
