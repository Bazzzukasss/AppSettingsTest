#ifndef DATA_H
#define DATA_H

namespace astg {

class StringSettingModel;
class IntNumberSettingModel;
class DoubleNumberSettingModel;

}

struct UserRecord {
    astg::StringSettingModel* strSetting{nullptr};
    astg::IntNumberSettingModel* intSettig{nullptr};
    astg::DoubleNumberSettingModel* doubleSettig{nullptr};

    void rw()
    {

    }
};

#endif // DATA_H
