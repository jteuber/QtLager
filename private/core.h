#pragma once

#include <QPluginLoader>
#include <QQmlApplicationEngine>

#include <lager/store.hpp>

#include "../public/effect_dispatcher.h"
#include "../public/reducer.h"
#include "../public/view.h"

namespace QtLager {

class core : public QObject
{
    Q_OBJECT

public:
    int run(int argc, char** argv);

private:
    void loadReducerPlugins();
    void loadViewPlugins();

    void startReducers();
    void startViews();

    void internalReducer(action_t action);

    std::list<QPluginLoader> loadPluginsInFolder(QString folderName);

private:
    std::list<QPluginLoader> m_viewLoaders;
    std::list<QPluginLoader> m_reducerLoaders;

    std::list<view*> m_views;
    std::list<reducer*> m_reducers;
    std::list<effect_dispatcher*> m_effectDispatchers;

    QQmlApplicationEngine* m_engine;
    lager::context<action_t> m_context;

private slots:
    void reloadReducers();
    void reloadViews();
};

} // namespace QtLager
