#include "view.h"
#include "SettingView.h"
#include "SettingTreeModel.h"
#include "SettingTreeView.h"
#include "SettingItem.h"
#include "SettingModel.h"
#include "SettingDelegate.h"
#include "IniSerializer.h"

#include <QVBoxLayout>

using namespace astg;

View::View(QWidget *parent)
    : QMainWindow{parent}
{
    initialize();
}

View::~View()
{
    save();
}

void View::initialize()
{
    // Settings
    auto strSetting = new StringSettingModel({"value","default"}, "strSetting", "strSetting", this);
    auto intSetting = new IntNumberSettingModel({8, 1, 10, 5}, "intSetting", "intSetting", this);

    auto settingsGroup2 = new SettingGroupModel("Group2", "Group2", this);
    settingsGroup2->addSettings({strSetting, intSetting});

    auto settingsGroup1 = new SettingGroupModel("Group1", "Group1", this);
    settingsGroup1->addSettings({strSetting, intSetting});

    m_rootSetting = new SettingGroupModel("RootGroup", "RootGroup", this);
    m_rootSetting->addSettings({settingsGroup1, settingsGroup2});

    // Model
    auto model = new SettingTreeModel(this);
    auto treeView = new SettingTreeView(this);
    auto delegate = new SettingDelegate(this);

    model->setRootSetting(m_rootSetting);
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

    load();
}

void View::save()
{
    serializer::IniSerializer sr("settings.ini");
    m_rootSetting->rw(&sr);
}

void View::load()
{
    serializer::IniDeserializer sr("settings.ini");
    m_rootSetting->rw(&sr);
}
