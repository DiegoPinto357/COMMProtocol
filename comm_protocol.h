//---------------------------------------------------------------------------

#ifndef comm_protocolH
#define comm_protocolH

//---------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "comm_protocol_defs.h"

//---------------------------------------------------------------------------

#define SYNC_INDEX                            0
#define D_ADDR_INDEX                          1
#define S_ADDR_INDEX                          2
#define CMD_INDEX                             3
#define PSIZE_INDEX                           4
#define PARAM_INDEX                           5

#define SYNC_SIZE                             1
#define PSIZE_SIZE                            1
#define CRC_SIZE                              1

#define BUF_SIZE                              64

#define PER_LENGTH                            128

//---------------------------------------------------------------------------

//getPacket returns
#define COMM_OK                               0x00
#define COMM_NO_DATA                          0x01
#define COMM_SYNC_ERROR                       0x02
#define COMM_HEADER_ERROR                     0x03
#define COMM_PARAM_SIZE_ERROR                 0x04
#define COMM_CRC_ERROR                        0x05

//---------------------------------------------------------------------------

struct packet_header{
   uint8_t d_address;
   uint8_t s_address;
   uint8_t cmd;
};

//---------------------------------------------------------------------------

class comm_protocol{
   public:

      comm_protocol();
      ~comm_protocol();

      void encode(packet_header header, uint8_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size);

      void encode(packet_header header, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, char *text, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint16_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, int16_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint16_t param, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, int16_t param, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, uint16_t param2, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, int16_t *param2, uint16_t p_size, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, uint8_t param2, uint16_t param3, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, uint8_t param2, int16_t param3, uint8_t param4, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, float param2, uint8_t *buffer, uint16_t *size);
      void encode(packet_header header, uint8_t param1, float *param2, uint8_t p_size, uint8_t *buffer, uint16_t *size);

      uint16_t getBufFreeSpace(void);
      uint16_t getBufUsedSpace(void);
      bool addData(uint8_t *data, uint16_t size);
      //bool getData(uint8_t *data, uint16_t size);
      uint8_t getPacket(uint8_t *data, uint16_t *size);

      void setPacket(uint8_t *buffer, uint16_t size);
      uint8_t getDAddr(void);
      uint8_t getSAddr(void);
      uint8_t getCmd(void);
      uint8_t getPSize(void);

      char *getParamText(void);
      uint8_t getParamByte(void);
      uint16_t getParamWord(void);
      float getParamFloat(void);
      void getParamByteBuffer(uint8_t *buffer, uint16_t size);
      void getParamWordBuffer(uint16_t *buffer, uint16_t size);

      //uint16_t getCmdSize(uint8_t cmd);
      char *getCmdDescription(uint8_t cmd);

   private:

      bool s_index;

      uint8_t buffer[BUF_SIZE];
      uint16_t buf_wr_ptr;
      uint16_t buf_rd_ptr;
      uint16_t data_count;

      uint8_t packet_buf[BUF_SIZE];
      uint16_t pbuf_ptr;

      uint16_t PER_acc;
      uint16_t error_count;
      uint16_t packet_count;

      union{
         uint16_t index;
         struct{
            uint8_t bit_index:3;
            uint16_t byte_index:13;
         } split;
      } PER_ptr;

      uint8_t PER_buf[PER_LENGTH/8];

      float PER;

      bool getData(uint8_t *data, uint16_t size);
      uint8_t hasValidPacket(void);
      void incPtr(uint16_t *ptr);

      uint8_t calcCRC8(uint8_t *data, uint16_t size);

      void setPERCount(bool error);
      void setErrorBuf(bool error);
      bool getErrorBuf(void);
};

//---------------------------------------------------------------------------
#endif
