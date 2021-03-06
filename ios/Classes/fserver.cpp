#include "fserver.hpp"
#include <cobra.h>

void on_server_connection(cobra_server_t *server, cobra_socket_t *socket) {
    Dart_CObject object;
    object.type = Dart_CObject_kInt64;
    object.value.as_int64 = (int64_t) socket;

    auto *data = static_cast<fserver_data *>(cobra_server_get_data(server));
    data->post_obj_func(data->port, &object);
}

void on_server_close(cobra_server_t *server, cobra_server_err_t error) {
    Dart_CObject object;
    object.type = Dart_CObject_kInt32;
    object.value.as_int32 = error;

    Dart_CObject result;
    Dart_CObject* array[] = {&object};
    result.type = Dart_CObject_kArray;
    result.value.as_array.values = array;
    result.value.as_array.length = 1;

    auto *data = static_cast<fserver_data *>(cobra_server_get_data(server));
    data->post_obj_func(data->port, &result);
}

extern "C"
cobra_server_t *fserver_bind(
        char *host,
        char *port,
        int write_queue_length,
        Dart_Port events_port,
        Dart_PostCObject_Type post_obj_func
) {
    auto *data = new fserver_data;
    data->post_obj_func = post_obj_func;
    data->port = events_port;

    cobra_server_t *server = cobra_server_create(write_queue_length);
    cobra_server_set_callbacks(server, on_server_connection, on_server_close);
    cobra_server_set_data(server, data);
    cobra_server_listen(server, host, port);

    return server;
}

extern "C"
void fserver_destroy(cobra_server_t *server) {
    delete static_cast<fserver_data *>(cobra_server_get_data(server));
    cobra_server_destroy(server);
}

extern "C"
void fserver_close(cobra_server_t *server) {
    cobra_server_close(server);
}