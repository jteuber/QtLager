#pragma once

#include <public/reducer.h>

class Reducer
    : public QObject
    , public QtLager::reducer
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID REDUCER_IID)
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(QtLager::reducer)

public:
    virtual model_t update(model_t m, action_t action) override;
};
