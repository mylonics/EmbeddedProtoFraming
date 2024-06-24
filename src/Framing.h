#ifndef EMBEDDED_PROTO_FRAMING_H
#define EMBEDDED_PROTO_FRAMING_H

#define SERIAL_FORMAT_START_BYTE_1 0xA2

#define SERIAL_FORMAT_1_START_BYTE_2 0x90
#define SERIAL_FORMAT_2_START_BYTE_2 0x91

#include "stdint.h"

#include <Errors.h>
#include <MessageInterface.h>

namespace protobuf_framer {

struct checksum_t {
  uint8_t byte1;
  uint8_t byte2;
};

struct checksum_t fletcher_checksum_calculation(uint8_t *buffer,
                                                uint8_t data_length);

static bool checkChecksum(uint8_t *buffer, uint8_t data_length);

::EmbeddedProto::Error encode_checksum(::EmbeddedProto::WriteBufferInterface& buffer);

} // namespace protobuf_framer
#endif // EMBEDDED_PROTO_FRAMING_H