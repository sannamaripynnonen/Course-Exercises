#ifndef RESULTDIALOG_HH
#define RESULTDIALOG_HH

#include <QDialog>

/**
 * @brief Result window where the top list is shown after the game ends.
 */

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ResultDialog constructor.
     * @param parent Parent widget.
     * @param results Game results in "name>points" format.
     */
    explicit ResultDialog(QWidget *parent, std::list<std::string>& results);

    /**
     * @brief ~ResultDialog destructor.
     */
    virtual ~ResultDialog();

private:
    Ui::ResultDialog *ui;
    std::list<std::string>& results_;
};

#endif // RESULTDIALOG_HH
