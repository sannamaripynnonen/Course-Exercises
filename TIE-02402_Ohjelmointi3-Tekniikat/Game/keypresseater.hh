#ifndef KEYPRESSEATER_HH
#define KEYPRESSEATER_HH

#include <QObject>
#include <QEvent>
#include "gamewindow.hh"

// Tämä luokka tarvitaan, jotta saadaan space-painike toimimaan peli-ikkunassa.
/**
 * @brief Catches key events and sends thems as a signal.
 */

class KeyPressEater : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief KeyPressEater constructor.
     * @param parent
     */
    explicit KeyPressEater(QObject *parent = nullptr);

    /**
     * @brief ~KeyPressEater destructor.
     */
    virtual ~KeyPressEater();

    /**
     * @brief eventFilter catches key events and sends thems as a signal.
     */
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    /**
     * @brief sendKeyEvent sends key events as a signal.
     * @param keyEvent
     */
    void sendKeyEvent(QKeyEvent* keyEvent);

};

#endif // KEYPRESSEATER_HH
