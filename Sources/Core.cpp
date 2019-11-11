#include "Core.h"

#include <random>
#include <utility>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>

#include <lager/event_loop/qapplication.hpp>

#include "Model.h"

namespace QtLager {

int Core::run(int argc, char** argv)
{
    QApplication app{argc, argv};
    m_engine = new QQmlApplicationEngine;

    Model initial_state;
    auto reducers = [this] (Model m, Actions a)
    {
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
                                    lager::with_qapplication_event_loop{app});
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
    m_reducerLoaders = loadLibrariesInFolder("Reducers");
}

void Core::loadViewPlugins()
{
    m_viewLoaders = loadLibrariesInFolder("Views");
}

void Core::startReducers()
{
    for(auto& loader : m_reducerLoaders)
    {
        auto instance = loader.instance();
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
        auto plugin = qobject_cast<IView*>( instance );
        if( plugin )
        {
            m_views.push_back( plugin );
            plugin->init(m_engine->rootContext(), m_context);
        }
    }
}

std::list<QPluginLoader> Core::loadLibrariesInFolder(QString folderName)
{
    std::list<QPluginLoader> ret;
    QDir libraryDir(folderName);
    libraryDir.setFilter( QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks );

    for( auto& entry : libraryDir.entryList() )
    {
        if( QLibrary::isLibrary( entry ) )
        {
            ret.emplace_back( libraryDir.absoluteFilePath(entry) );
            auto error = ret.back().errorString();
            if( !error.isEmpty() )
            {
                qWarning() << "Error loading plugin: " << error;
            }
        }
    }

    return ret;
}

void Core::reloadReducers()
{
    for(auto reducer : m_reducers)
    {
        delete reducer;
    }
    m_reducers.clear();

    startReducers();
}

void Core::reloadViews()
{
    for(auto reducer : m_views)
    {
        delete reducer;
    }
    m_views.clear();

    startViews();
}

} // namespace QtLager
