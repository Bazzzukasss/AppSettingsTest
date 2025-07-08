#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

class ISerrializer;

class View : public QMainWindow
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

private:
    void initialize();
};

#endif // VIEW_H
