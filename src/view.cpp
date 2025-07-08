#include "view.h"
#include "SettingView.h"
#include "SettingTreeModel.h"
#include "SettingTreeView.h"
#include "SettingItem.h"
#include "SettingDelegate.h"
#include "IniSerializer.h"

#include <QVBoxLayout>

using namespace astg;

View::View(QWidget *parent)
    : QMainWindow{parent}
{
    initialize();
}

void View::initialize()
{
    // Settings
    auto strSetting = new StringSettingModel({"value","default"}, "DataString", "strSetting", this);
    auto intSetting = new IntNumberSettingModel({8, 1, 10, 5}, "DataInt", "intSetting", this);

    // Items
    auto rootItem = new astg::SettingItem("Root");
    auto strItem = new astg::SettingItem("String", strSetting, rootItem);
    auto intItem = new astg::SettingItem("Int", intSetting, rootItem);

    auto subItem1 = new astg::SettingItem("Sub1", rootItem);
    auto strItem1 = new astg::SettingItem("String", strSetting, subItem1);
    auto intItem1 = new astg::SettingItem("Int", intSetting, subItem1);

    subItem1->addItems({strItem1, intItem1});
    rootItem->addItems({strItem, intItem, subItem1});

    // Model
    auto model = new SettingTreeModel(this);
    auto treeView = new SettingTreeView(this);
    auto delegate = new SettingDelegate(this);

    model->setRootItem(rootItem);
    treeView->setModel(model);
    treeView->setItemDelegate(delegate);

    // Views
    auto strView = new StringSettingView(strSetting, this);
    auto intView = new IntNumberSettingView(intSetting, this);
    //strView->resetModel(strSetting);
    //intView->resetModel(intSetting);

    // Main window
    auto mainWidget = new QWidget(this);
    auto layout = new QVBoxLayout();
    layout->addWidget(treeView);
    layout->addWidget(strView);
    layout->addWidget(intView);

    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);

    serializer::IniSerializer sr("settings.ini");
    intSetting->rw(&sr);
    strSetting->rw(&sr);
}
