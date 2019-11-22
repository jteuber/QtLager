#pragma once

#include <QQmlContext>

#include <lager/store.hpp>

#define XSTR(x) #x
#define STR(x) XSTR(x)
#include STR(ACTIONS_HEADER)
#include STR(MODEL_HEADER)

namespace QtLager {

class IView
{
public:
    virtual ~IView() = default;

    virtual bool init(QQmlContext* qmlContext,
                      lager::context<Actions> context) = 0;
    virtual void update(Model old, Model state)        = 0;
};

} // namespace QtLager

#define IView_iid "org.QtLager.View"

Q_DECLARE_INTERFACE(QtLager::IView, IView_iid)
