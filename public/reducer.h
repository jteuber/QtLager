#pragma once

#include <QObject>

#include "model_actions.h"

namespace QtLager {

class reducer
{
public:
    virtual ~reducer() = default;

    virtual model update(model m, actions action) = 0;
};

} // namespace QtLager

#define REDUCER_IID "org.QtLager.reducer"

Q_DECLARE_INTERFACE(QtLager::reducer, REDUCER_IID)
