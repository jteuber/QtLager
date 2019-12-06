#pragma once

#include <QObject>

#include <lager/store.hpp>

#include "model_actions.h"

namespace QtLager {

class effect_dispatcher
{
public:
    virtual ~effect_dispatcher() = default;

    virtual lager::effect<action_t> dispatch(model_t m, action_t action) = 0;
};

} // namespace QtLager

#define EFFECT_DISPATCHER_IID "org.QtLager.effect_dispatcher"

Q_DECLARE_INTERFACE(QtLager::effect_dispatcher, EFFECT_DISPATCHER_IID)
