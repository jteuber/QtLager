#pragma once

#include <QPluginLoader>
#include <QQmlApplicationEngine>

#include <lager/store.hpp>

#include "../Interfaces/IReducer.h"
#include "../Interfaces/IView.h"

namespace QtLager {

class Core : public QObject
{
    Q_OBJECT

public:
    int run(int argc, char** argv);

private:
    void loadReducerPlugins();
    void loadViewPlugins();

    void startReducers();
    void startViews();

    void internalReducer(Actions action);

    std::list<QPluginLoader> loadPluginsInFolder(QString folderName);

private:
    std::list<QPluginLoader> m_reducerLoaders;
    std::list<QPluginLoader> m_viewLoaders;

    std::list<IReducer*> m_reducers;
    std::list<IView*> m_views;

    QQmlApplicationEngine* m_engine;
    lager::context<Actions> m_context;

private slots:
    void reloadReducers();
    void reloadViews();
};

}

