#ifndef CLICKABLELINEEDIT_H
#define CLICKABLELINEEDIT_H
#include <QLineEdit>

class ClickableLineEdit : public QLineEdit
{
    Q_OBJECT

    protected:

    void focusInEvent(QFocusEvent* e);
};

#endif // CLICKABLELINEEDIT_H
