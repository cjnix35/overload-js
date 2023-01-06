#pragma once

#ifdef _WIN32
#include <malloc.h>
#define alloca _alloca
#endif

#include <src/sio_client.h>
#include <thread>
#include <condition_variable>

using namespace sio;

namespace over {

    namespace net {

        class connection_listener {

            protected:
                sio::client& handler;
                std::mutex _lock;
                bool connect_finish;
                std::condition_variable_any _cond;

            public:
                connection_listener(sio::client& h) : handler(h) {
                }

                void lock();
                void unlock();
                bool isConnFinished();
                void wait();
                void onConnected();
                void onClose(const client::close_reason& reason);
                void onFail();
        };

        class socketio {

            protected:
                socket::ptr current_socket;
                sio::client h;
                connection_listener l;

            public:
                socketio(bool default_settings = true) : l(h) {

                    if (default_settings) {

                        h.set_open_listener(
                            std::bind(&connection_listener::onConnected, &l));
                        h.set_close_listener(
                            std::bind(&connection_listener::onClose, &l,
                                      std::placeholders::_1));
                        h.set_fail_listener(
                            std::bind(&connection_listener::onFail, &l));
                    }
                }

                enum logLevel {

                    Default,
                    Quiet,
                    Verbose

                };

                void setLogLevel(logLevel lvl);
                void connect(std::string address);
                void set_onClose(
                    const std::function<void(const sio::client::close_reason&)>
                        on_close);
                void set_onConnected(
                    const sio::client::con_listener& on_connected);

                void set_onDisconnected(
                    const sio::client::close_listener& on_disconnected);

                void set_onReconnect(
                    const sio::client::reconnect_listener& on_reconnect);


                void set_onFail(const sio::client::con_listener& on_fail);
                void setEvent(std::string name,
                              const sio::socket::event_listener_aux& func);
                void emit(std::string name, std::string data);
                void set_onError(const sio::socket::error_listener& on_error);
                std::string getNamespace();

                void closeConnection();
                void closeSyncConnection();
                bool isOpened();
                template <typename T> void setReconnectAttempts(T attempts);
                template <typename T> void setReconnectDelay(T millis);
        };

    }; // namespace net


}; // namespace over
