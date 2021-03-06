enum CobraSocketError {
  COBRA_SOCKET_OK,
  COBRA_SOCKET_ERR_ALREADY_OPENED,
  COBRA_SOCKET_ERR_ALREADY_CLOSED,
  COBRA_SOCKET_ERR_NOT_CONNECTED,
  COBRA_SOCKET_ERR_NOT_CLOSED,
  COBRA_SOCKET_ERR_RESOLVING,
  COBRA_SOCKET_ERR_CONNECTING,
  COBRA_SOCKET_ERR_WRONG_DATA,
  COBRA_SOCKET_ERR_QUEUE_FULL,
  COBRA_SOCKET_ERR_QUEUE_OVERFLOW,
  COBRA_SOCKET_ERR_UNKNOWN_WRITE_ERROR,
  COBRA_SOCKET_ERR_UNREACHABLE,
}

class CobraSocketException implements Exception {
  final CobraSocketError error;

  CobraSocketException(
    int code,
  ) : error = CobraSocketError.values[code];

  @override
  String toString() => "CobraSocketException: $error";
}
