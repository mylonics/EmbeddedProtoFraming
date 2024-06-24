#include <Framing.h>

namespace protobuf_framer {

struct checksum_t protobuf_framer::fletcher_checksum_calculation(uint8_t *buffer,
                                                uint8_t data_length) {
  checksum_t checksum{};

  for (int i = 0; i < data_length; i++) {
    checksum.byte1 += buffer[i];
    checksum.byte2 += checksum.byte1;
  }
  return checksum;
}

static bool protobuf_framer::checkChecksum(uint8_t *buffer, uint8_t data_length) {
  checksum_t checksum = fletcher_checksum_calculation(buffer, data_length - 2);
  return (checksum.byte1 == buffer[data_length - 2] &&
          checksum.byte1 == buffer[data_length - 1]);
}

::EmbeddedProto::Error protobuf_framer::encode_checksum(::EmbeddedProto::WriteBufferInterface& buffer) {
  protobuf_framer::checksum_t checksum =
      protobuf_framer::fletcher_checksum_calculation(buffer.get_data(),
                                                     buffer.get_size());
  if (buffer.push(checksum.byte1)) {
    if (buffer.push(checksum.byte2)) {
      return ::EmbeddedProto::Error::NO_ERRORS;
    }
  }
  return ::EmbeddedProto::Error::BUFFER_FULL;
}

} // namespace protobuf_framer