#pragma once

#include <QPluginLoader>
#include <QQmlApplicationEngine>

#include <lager/store.hpp>

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

    void internalReducer(actions action);

    std::list<QPluginLoader> loadPluginsInFolder(QString folderName);

private:
    std::list<QPluginLoader> m_reducerLoaders;
    std::list<QPluginLoader> m_viewLoaders;

    std::list<reducer*> m_reducers;
    std::list<view*> m_views;

    QQmlApplicationEngine* m_engine;
    lager::context<actions> m_context;

private slots:
    void reloadReducers();
    void reloadViews();
};

} // namespace QtLager
