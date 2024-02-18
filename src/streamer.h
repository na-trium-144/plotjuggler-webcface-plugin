#pragma once
#include <webcface/webcface.h>
#include <QtPlugin>
#include "PlotJuggler/datastreamer_base.h"
#include <optional>

class DataStreamWebCFace : public PJ::DataStreamer {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "facontidavide.PlotJuggler3.DataStreamer")
    Q_INTERFACES(PJ::DataStreamer)

  public:
    DataStreamWebCFace();

    virtual bool start(QStringList *) override;

    virtual void shutdown() override;

    virtual bool isRunning() const override { return wcli.has_value(); }

    virtual ~DataStreamWebCFace() override;

    virtual const char *name() const override { return _name.c_str(); }

    virtual bool isDebugPlugin() override { return false; }

    virtual bool xmlSaveState(QDomDocument &doc,
                              QDomElement &parent_element) const override {
        return true;
    }

    virtual bool xmlLoadState(const QDomElement &parent_element) override {
        return true;
    }

  private:
    std::optional<webcface::Client> wcli;
    std::string _name;
};
