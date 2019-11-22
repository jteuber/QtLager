#pragma once

#include <QObject>

#define XSTR(x) #x
#define STR(x) XSTR(x)
#include STR(ACTIONS_HEADER)
#include STR(MODEL_HEADER)

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
