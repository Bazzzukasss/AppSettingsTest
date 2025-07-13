#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

namespace astg {

class ISettingModel;

} // namespace astg

class View : public QMainWindow
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    ~View();

private:
    void initialize();
    void save();
    void load();

private:
    astg::ISettingModel* m_rootSetting{nullptr};
};

#endif // VIEW_H
