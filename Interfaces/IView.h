#pragma once

#include <QQmlContext>

#include <lager/store.hpp>

#include "../Sources/Actions.h"
#include "../Sources/Model.h"

namespace QtLager {

class IView
{
public:
    virtual ~IView() = default;

    virtual bool init(QQmlContext* qmlContext, lager::store<Actions, Model>& store) = 0;
    virtual void setModel(Model model) = 0;
};

} // namespace QtLager

#define IView_iid "org.QtLager.View"

Q_DECLARE_INTERFACE(QtLager::IView, IView_iid)
