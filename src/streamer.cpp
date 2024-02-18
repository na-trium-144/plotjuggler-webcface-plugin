#include "streamer.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <chrono>
#include <sstream>

using namespace PJ;

DataStreamWebCFace::DataStreamWebCFace() {
    std::stringstream ss;
    ss << "WebCFace Streamer (" << webcface::version_s << ")";
    _name = ss.str();
}

bool DataStreamWebCFace::start(QStringList *) {
    wcli.emplace();
    wcli->onMemberEntry().appendListener([this](const webcface::Member &m) {
        auto initial_time = std::chrono::high_resolution_clock::now();
        m.onValueEntry().appendListener([this, initial_time](
                                            const webcface::Value &v) {
            std::string v_name = v.name();
            while (v_name.find(".") != std::string::npos) {
                v_name[v_name.find(".")] = '/';
            }
            auto &plot =
                dataMap().addNumeric(v.member().name() + "/" + v_name)->second;
            v.appendListener([this, &plot,
                              initial_time](const webcface::Value &v) {
                plot.pushBack(
                    {std::chrono::duration_cast<std::chrono::duration<double>>(
                         v.time() - initial_time)
                         .count(),
                     v.get()});
                emit dataReceived();
            });
        });
        m.onTextEntry().appendListener([this,
                                        initial_time](const webcface::Text &t) {
            std::string v_name = t.name();
            while (v_name.find(".") != std::string::npos) {
                v_name[v_name.find(".")] = '/';
            }
            auto &series =
                dataMap()
                    .addStringSeries(t.member().name() + "/" + v_name)
                    ->second;
            t.appendListener([this, &series,
                              initial_time](const webcface::Text &t) {
                series.pushBack(
                    {std::chrono::duration_cast<std::chrono::duration<double>>(
                         t.time() - initial_time)
                         .count(),
                     t.get()});
                emit dataReceived();
            });
        });
    });
    wcli->start();
    return true;
}

void DataStreamWebCFace::shutdown() {
    if (wcli) {
        wcli->close();
    }
    wcli.reset();
}

DataStreamWebCFace::~DataStreamWebCFace() {}
