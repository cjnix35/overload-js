#include "socketio.hpp"

namespace over {

    namespace net {

        void connection_listener::lock() {

            _lock.lock();
        }

        void connection_listener::unlock() {

            _lock.unlock();
        }

        bool connection_listener::isConnFinished() {

            return connect_finish;
        }

        void connection_listener::wait() {

            _cond.wait(_lock);
        }

        void connection_listener::onConnected() {
            _lock.lock();
            _cond.notify_all();
            connect_finish = true;
            _lock.unlock();
        }
        void connection_listener::onClose(const client::close_reason& reason) {
        }

        void connection_listener::onFail() {
        }


        void socketio::setLogLevel(logLevel lvl) {

            if (lvl == logLevel::Quiet) h.set_logs_quiet();
            else if (lvl == logLevel::Verbose) h.set_logs_verbose();
            else h.set_logs_default();
        }

        void socketio::connect(std::string address) {

            h.connect(address);
            l.lock();
            if (!l.isConnFinished()) { l.wait(); }
            l.unlock();
            current_socket = h.socket();
        }

        void socketio::set_onClose(
            const std::function<void(const sio::client::close_reason&)>
                on_close) {

            h.set_close_listener(on_close);
        }

        void socketio::set_onConnected(
            const sio::client::con_listener& on_connected) {

            h.set_open_listener(on_connected);
        }

        void socketio::set_onFail(const sio::client::con_listener& on_fail) {

            h.set_fail_listener(on_fail);
        }

        void
            socketio::set_onError(const sio::socket::error_listener& on_error) {

            current_socket->on_error(on_error);
        }


        void socketio::setEvent(std::string name,
                                const sio::socket::event_listener_aux& func) {

            current_socket->on(name, func);
        }

        void socketio::emit(std::string name, std::string data) {

            current_socket->emit(name, data);
        }

        std::string socketio::getNamespace() {

            return current_socket->get_namespace();
        }

        void socketio::set_onDisconnected(
            const sio::client::close_listener& on_disconnected) {

            h.set_close_listener(on_disconnected);
        }

        void socketio::set_onReconnect(
            const sio::client::reconnect_listener& on_reconnect) {

            h.set_reconnect_listener(on_reconnect);
        }

        void socketio::closeConnection() {

            current_socket->close();
        }
        void socketio::closeSyncConnection() {

            h.sync_close();
        }
        bool socketio::isOpened() {

            return h.opened();
        }
        template <typename T> void socketio::setReconnectAttempts(T attempts) {

            h.set_reconnect_attempts(attempts);
        }
        template <typename T> void socketio::setReconnectDelay(T millis) {

            h.set_reconnect_delay(millis);
        }


    }; // namespace net

}; // namespace over
