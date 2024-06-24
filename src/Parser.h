#ifndef EMBEDDED_PROTO_PARSER_H
#define EMBEDDED_PROTO_PARSER_H

#include "stdint.h"
#include "Framing.h"

#include <Errors.h>
#include <MessageInterface.h>

namespace protobuf_framer {
  
struct ProtobufParserResult{
  type == SERIAL FORMAT 1
  packet_size_
  uint8_t file_id;
  uint8_t proto_id;
}

template <size_t buffer_size> class ProtobufParser {
public:
  bool parseBuffer(uint8_t byte) {
    switch (state_) {
    case FramerState::WAITING_FOR_START_BYTE1:
      if (byte == SERIAL_FORMAT_START_BYTE_1) {
        byte_index = 0;
        buffer[byte_index++] = byte;
        state_ = FramerState::WAITING_FOR_FILE_ID;
      }
      break;

    case FramerState::WAITING_FOR_START_BYTE2:
      buffer[byte_index++] = byte;
      if (byte == SERIAL_FORMAT_1_START_BYTE_2) {
        state_ = FramerState::WAITING_FOR_SYS_ID;
      } else if (byte == SERIAL_FORMAT_1_START_BYTE_2) {
        state_ = FramerState::WAITING_FOR_FILE_ID;
      } else {
        state_ = FramerState::WAITING_FOR_START_BYTE1;
      }
      break;

    case FramerState::WAITING_FOR_SYS_ID:
      buffer[byte_index++] = byte;
      state_ = FramerState::WAITING_FOR_FILE_ID;
      break;

    case FramerState::WAITING_FOR_FILE_ID:
      buffer[byte_index++] = byte;
      state_ = FramerState::WAITING_FOR_MSG_ID;
      break;

    case FramerState::WAITING_FOR_MSG_ID:
      buffer[byte_index++] = byte;
      state_ = FramerState::WAITING_FOR_MSG_ID;
      break;

    case FramerState::WAITING_FOR_LENGTH:
      buffer[byte_index++] = byte;
      state_ = FramerState::WAITING_FOR_PAYLOAD;
      packet_size_ = byte_index + byte;
      break;
    
    case FramerState::WAITING_FOR_PAYLOAD:
      buffer[byte_index++] = byte;
      if (byte_index == packet_size_){
        state_ = FramerState::WAITING_FOR_START_BYTE1;
        if (checkChecksum(buffer, packet_size_)){
          return true
        }
        return false;
      }
    break;

    default:
      break;
    }
    return false;
  }

private:
  enum class FramerState {
    WAITING_FOR_START_BYTE1,
    WAITING_FOR_START_BYTE2,
    WAITING_FOR_SYS_ID,
    WAITING_FOR_FILE_ID,
    WAITING_FOR_MSG_ID,
    WAITING_FOR_LENGTH,
    WAITING_FOR_PAYLAOD,
  };
  FramerState state_;
  uint8_t buffer[buffer_size];
  uint8_t packet_size_;
};



} // namespace protobuf_framer
#endif // EMBEDDED_PROTO_PARSER_H