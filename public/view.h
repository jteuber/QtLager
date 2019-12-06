#pragma once

#include <QQmlContext>

#include <lager/store.hpp>

#include "model_actions.h"

namespace QtLager {

class view
{
public:
    virtual ~view() = default;

    virtual bool init(QQmlContext* qmlContext,
                      lager::context<action_t> context) = 0;
    virtual void update(model_t old, model_t state)     = 0;
};

} // namespace QtLager

#define VIEW_IID "org.QtLager.View"

Q_DECLARE_INTERFACE(QtLager::view, VIEW_IID)
