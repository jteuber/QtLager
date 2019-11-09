#pragma once

#include <QObject>

#include "../Sources/Actions.h"
#include "../Sources/Model.h"

namespace QtLager {

class IReducer
{
public:
    virtual ~IReducer() = default;

    virtual Model update(Model m, Actions action) = 0;
};

} // namespace QtLager

#define IReducer_iid "org.QtLager.Reducer"

Q_DECLARE_INTERFACE(QtLager::IReducer, IReducer_iid)
