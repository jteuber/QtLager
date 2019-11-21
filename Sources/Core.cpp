#include "Core.h"

#include <random>
#include <utility>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QDebug>

#include <lager/event_loop/qt.hpp>

#include "Model.h"

namespace QtLager {

int Core::run(int argc, char** argv)
{
    QApplication app{argc, argv};
    m_engine = new QQmlApplicationEngine;

    Model initial_state;
    auto reducers = [this] (Model m, Actions a)
    {
        internalReducer(a);
        for( auto reducer : m_reducers )
            m = reducer->update(m, a);
        return m;
    };
    auto views = [this] (auto&& old, auto&& state)
    {
        for( auto view : m_views )
            view->update(old, state);
    };

    auto store = lager::make_store<Actions>(std::move(initial_state), reducers,
                                    lager::with_qt_event_loop{app});
    watch(store, views);

    m_context = store;

    loadReducerPlugins();
    loadViewPlugins();

    startReducers();
    startViews();

    m_engine->load("qrc:/main.qml");

    return app.exec();
}

void Core::loadReducerPlugins()
{
    m_reducerLoaders = loadPluginsInFolder("Reducers");
}

void Core::loadViewPlugins()
{
    m_viewLoaders = loadPluginsInFolder("Views");
}

void Core::startReducers()
{
    for(auto& loader : m_reducerLoaders)
    {
        auto instance = loader.instance();
        if( !instance )
        {
            qWarning() << "Error loading plugin " << loader.fileName()
                       << ":" << loader.errorString();
            continue;
        }

        auto plugin = qobject_cast<IReducer*>( instance );
        if( plugin )
        {
            m_reducers.push_back( plugin );
        }
    }
}

void Core::startViews()
{
    for(auto& loader : m_viewLoaders)
    {
        auto instance = loader.instance();
        if( !instance )
        {
            qWarning() << "Error loading plugin " << loader.fileName()
                       << ":" << loader.errorString();
            continue;
        }

        auto plugin = qobject_cast<IView*>( instance );
        if( plugin )
        {
            m_views.push_back( plugin );
            plugin->init(m_engine->rootContext(), m_context);
        }
    }
}

void Core::internalReducer(Actions action)
{
    if( std::holds_alternative<ReservedActions>(action) )
    {
        std::visit(
                    lager::visitor{
                        [&](reload_views) {
                            reloadViews();
                        },
                        [&](reload_reducers) {
                            reloadReducers();
                        }
                    }, std::get<ReservedActions>(action) );
    }

}

std::list<QPluginLoader> Core::loadPluginsInFolder(QString folderName)
{
    std::list<QPluginLoader> ret;

    // To make plugin-hot-reloading possible on windows and safer on other platforms we have to work on copies
    QString workFolderName = "."+folderName+"Copy";
    // so create a folder for those copies
    QDir libraryWorkDir(workFolderName);
    // but if it already exists remove it first
    libraryWorkDir.removeRecursively();
    QDir(".").mkdir(workFolderName);

    // now open the original plugin folder
    QDir libraryDir(folderName);
    libraryDir.setFilter( QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks );

    // copy all plugins to the work folder and open the copies
    for( auto& entry : libraryDir.entryList() )
    {
        if( QLibrary::isLibrary( entry ) )
        {
            if( !QFile::copy(libraryDir.absoluteFilePath(entry),
                             libraryWorkDir.absoluteFilePath(entry)) )
            {
                qWarning() << "Error copying plugin:" << libraryDir.absoluteFilePath(entry);
            }

            ret.emplace_back( libraryWorkDir.absoluteFilePath(entry) );
            ret.back().setLoadHints(QLibrary::LoadHints());
        }
    }

    return ret;
}

void Core::reloadReducers()
{
    qInfo() << "Core: reloading reducers";
    for(auto& loader : m_reducerLoaders )
    {
        if( !loader.unload() )
        {
            qWarning() << "Error unloading reducer plugin: " << loader.errorString();
        }
    }
    m_reducers.clear();
    m_reducerLoaders.clear();

    loadReducerPlugins();
    startReducers();
}

void Core::reloadViews()
{
    qInfo() << "Core: reloading views";
    for(auto& loader : m_viewLoaders )
    {
        if( !loader.unload() )
        {
            qWarning() << "Error unloading view plugin: " << loader.errorString();
        }
    }
    m_views.clear();
    m_viewLoaders.clear();

    loadViewPlugins();
    startViews();
}

} // namespace QtLager
