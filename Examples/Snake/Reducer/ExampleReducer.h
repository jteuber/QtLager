#pragma once

#include "Actions.h"
#include "Model.h"

#include <Interfaces/IReducer.h>

class Reducer
    : public QObject
    , public QtLager::IReducer
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IReducer_iid)
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(QtLager::IReducer)

public:
    virtual Model update(Model m, Actions action) override;
};
