//---------------------------------------------------------------------------

#include "comm_protocol.h"

//---------------------------------------------------------------------------

comm_protocol::comm_protocol(){
   s_index=false;
   buf_wr_ptr=0;
   buf_rd_ptr=0;
   data_count=0;
   pbuf_ptr=0;
   PER_acc=0;
   error_count=0;
   packet_count=0;
   PER_ptr.index=0;
   PER=0;
}

//---------------------------------------------------------------------------

comm_protocol::~comm_protocol(){
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size){
   uint8_t sync;

   if (!s_index) sync=CMD_SYNC1;
   else sync=CMD_SYNC2;

   s_index=!s_index;

   buffer[SYNC_INDEX]=sync;
   buffer[D_ADDR_INDEX]=header.d_address;
   buffer[S_ADDR_INDEX]=header.s_address;
   buffer[CMD_INDEX]=header.cmd;
   buffer[PSIZE_INDEX]=p_size;
   memcpy(&buffer[PARAM_INDEX], param, p_size);

   *size=SYNC_SIZE+sizeof(packet_header)+PSIZE_SIZE+p_size;

   buffer[*size]=calcCRC8(buffer, *size);
   (*size)++;
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t *buffer, uint16_t *size){
   encode(header, (uint8_t*)NULL, (uint8_t)0, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, char *text, uint8_t *buffer, uint16_t *size){
   uint8_t i=0;

   while (text[i]!=0) i++;
   i++;

   encode(header, (uint8_t*)text, i, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param, uint8_t *buffer, uint16_t *size){
   encode(header, &param, (uint8_t)1, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint16_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size){
   encode(header, (uint8_t*)param, p_size*2, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, int16_t *param, uint8_t p_size, uint8_t *buffer, uint16_t *size){
   encode(header, (uint8_t*)param, p_size*2, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint16_t param, uint8_t *buffer, uint16_t *size){
   encode(header, (uint8_t*)&param, (uint8_t)2, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, int16_t param, uint8_t *buffer, uint16_t *size){
   encode(header, (uint8_t*)&param, (uint8_t)2, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, uint16_t param2, uint8_t *buffer, uint16_t *size){
   union{
      uint16_t data16;
      uint8_t data8[2];
   } data;
   uint8_t temp[3];

   data.data16=param2;
   temp[0]=param1;
   temp[1]=data.data8[0];
   temp[2]=data.data8[1];

   encode(header, temp, (uint8_t)3, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, int16_t *param2, uint16_t p_size, uint8_t *buffer, uint16_t *size){
   uint8_t *ptr;
   uint16_t p_size_b;

   p_size_b=p_size*sizeof(int16_t);
   ptr=(uint8_t*)malloc(p_size_b+1);

   ptr[0]=param1;
   memcpy(&ptr[1], (uint8_t*)param2, p_size_b);

   encode(header, ptr, (uint8_t)(p_size_b+1), buffer, size);
   free(ptr);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, uint8_t param2, uint16_t param3, uint8_t *buffer, uint16_t *size){
   union{
      uint16_t data16[2];
      uint8_t data8[4];
   } data;

   data.data8[0]=param1;
   data.data8[1]=param2;
   data.data16[1]=param3;

   encode(header, data.data8, (uint8_t)4, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, uint8_t param2, int16_t param3, uint8_t param4, uint8_t *buffer, uint16_t *size){
   struct{
      uint8_t data1[2];
      int16_t data2;
      uint8_t data3;
   } data;

   data.data1[0]=param1;
   data.data1[1]=param2;
   data.data2=param3;
   data.data3=param4;

   encode(header, (uint8_t*)&data, (uint8_t)5, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, float param2, uint8_t *buffer, uint16_t *size){
   union{
      uint8_t data8[sizeof(float)];
      float data_f;
   } data;
   uint8_t temp[1+sizeof(float)];

   data.data_f=param2;

   temp[0]=param1;
   memcpy(&temp[1], data.data8, sizeof(float));

   encode(header, data.data8, (uint8_t)5, buffer, size);
}

//---------------------------------------------------------------------------

void comm_protocol::encode(packet_header header, uint8_t param1, float *param2, uint8_t p_size, uint8_t *buffer, uint16_t *size){
   uint8_t *ptr;
   uint16_t p_size_b;

   p_size_b=p_size*sizeof(float);
   ptr=(uint8_t*)malloc(p_size_b+1);

   ptr[0]=param1;
   memcpy(&ptr[1], (uint8_t*)param2, p_size_b);

   encode(header, ptr, (uint8_t)(p_size_b+1), buffer, size);
   free(ptr);
}

//---------------------------------------------------------------------------

uint16_t comm_protocol::getBufFreeSpace(void){
   return BUF_SIZE-data_count;
}

//---------------------------------------------------------------------------

uint16_t comm_protocol::getBufUsedSpace(void){
   return data_count;
}

//---------------------------------------------------------------------------

bool comm_protocol::addData(uint8_t *data, uint16_t size){
   uint16_t i;

   if ((data_count+size)>BUF_SIZE)
      return false;

   for (i=0; i<size; i++){
      buffer[buf_wr_ptr]=data[i];
      if (buf_wr_ptr<(BUF_SIZE-1)) buf_wr_ptr++;
      else buf_wr_ptr=0;
      data_count++;
   }

   return true;
}

//---------------------------------------------------------------------------

bool comm_protocol::getData(uint8_t *data, uint16_t size){
   uint16_t i;

   if (data_count<size)
      return false;

   for (i=0; i<size; i++){
      data[i]=buffer[buf_rd_ptr];
      if (buffer[buf_rd_ptr]==0) buffer[buf_rd_ptr]=0xFF;
      if (buf_rd_ptr<(BUF_SIZE-1)) buf_rd_ptr++;
      else buf_rd_ptr=0;
      data_count--;
   }

   return true;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getPacket(uint8_t *data, uint16_t *size){
   uint8_t status;
   int index=0;
   uint8_t crc;
   uint8_t cmd;
   uint8_t p_size;

   status=hasValidPacket();
   if (status!=COMM_OK){
      //getData(&data[index], 1);
      return status;
   }

   //procura sincronismo
   data[index]=CMD_NOP;
   while (data[index]!=CMD_SYNC1 && data[index]!=CMD_SYNC2){
      getData(&data[index], 1);
   }

   //cata endereço de destino
   index++;
   getData(&data[index], 1);

   //cata endereço de origem
   index++;
   getData(&data[index], 1);

   //cata comando
   index++;
   getData(&data[index], 1);

   cmd=data[index];

   //cata tamanho do parâmetros
   index++;
   getData(&data[index], 1);

   p_size=data[index];

   //cata parâmetros
   index++;
   getData(&data[index], p_size);
   index+=p_size;

   //*size=SYNC_SIZE+sizeof(packet_header)+PSIZE_SIZE+p_size;

   //cata CRC
   getData(&data[index], 1);

   crc=calcCRC8((uint8_t*)data, index);

   *size=index;

   //anula o pacote caso haja falha na checagem do CRC
   if (crc!=data[index]){
      *size=0;
      setPERCount(true);
      return COMM_CRC_ERROR;
   }
   else{
      (*size)++;
      setPERCount(false);
      return COMM_OK;
   }
}

//---------------------------------------------------------------------------

void comm_protocol::setPacket(uint8_t *buffer, uint16_t size){
   pbuf_ptr=0;
   memcpy(packet_buf, buffer, size);
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getDAddr(void){
   uint8_t ret;

   pbuf_ptr=D_ADDR_INDEX;
   ret=packet_buf[pbuf_ptr];
   pbuf_ptr+=sizeof(uint8_t);

   return ret;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getSAddr(void){
   uint8_t ret;

   pbuf_ptr=S_ADDR_INDEX;
   ret=packet_buf[pbuf_ptr];
   pbuf_ptr+=sizeof(uint8_t);

   return ret;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getCmd(void){
   uint8_t ret;

   pbuf_ptr=CMD_INDEX;
   ret=packet_buf[pbuf_ptr];
   pbuf_ptr+=sizeof(uint8_t);

   return ret;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getPSize(void){
   uint8_t ret;

   pbuf_ptr=PSIZE_INDEX;
   ret=packet_buf[pbuf_ptr];
   pbuf_ptr+=sizeof(uint8_t);

   return ret;
}

//---------------------------------------------------------------------------

char *comm_protocol::getParamText(void){
   char *ret;
   uint16_t n;

   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;
   ret=(char*)&packet_buf[pbuf_ptr];
   n=strlen(ret);

   pbuf_ptr+=(sizeof(char)*(n+1));

   return ret;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::getParamByte(void){
   uint8_t ret;

   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;
   ret=packet_buf[pbuf_ptr];
   pbuf_ptr+=sizeof(uint8_t);

   return ret;
}

//---------------------------------------------------------------------------

uint16_t comm_protocol::getParamWord(void){
   union{
      uint8_t data8[sizeof(uint16_t)];
      uint16_t data16;
   } ret;

   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;
   ret.data8[0]=packet_buf[pbuf_ptr];
   ret.data8[1]=packet_buf[pbuf_ptr+1];
   pbuf_ptr+=sizeof(uint16_t);

   return ret.data16;
}

//---------------------------------------------------------------------------

float comm_protocol::getParamFloat(void){
   union{
      uint8_t data8[sizeof(float)];
      float data_f;
   } ret;
   //int i;

   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;

   //for (i=0; i<sizeof(float); i++) ret.data8[i]=packet_buf[pbuf_ptr+i];
   memcpy(ret.data8, (uint8_t*)&packet_buf[pbuf_ptr], sizeof(float));

   pbuf_ptr+=sizeof(float);

   return ret.data_f;
}

//---------------------------------------------------------------------------

void comm_protocol::getParamByteBuffer(uint8_t *buffer, uint16_t size){
   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;
   memcpy(buffer, (uint8_t*)&packet_buf[pbuf_ptr], size);
   pbuf_ptr+=size;
}

//---------------------------------------------------------------------------

void comm_protocol::getParamWordBuffer(uint16_t *buffer, uint16_t size){
   uint16_t n;

   if (pbuf_ptr<PARAM_INDEX) pbuf_ptr=PARAM_INDEX;
   n=sizeof(uint16_t)*size;
   memcpy(buffer, (uint8_t*)&packet_buf[pbuf_ptr], n);
   pbuf_ptr+=n;
}

//---------------------------------------------------------------------------

char *comm_protocol::getCmdDescription(uint8_t cmd){
   return (char*)CMD_DESCRIPTION[cmd];
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::hasValidPacket(void){
   bool s_ok=false;
   uint8_t sync;
   uint8_t cmd;
   uint16_t size;
   uint16_t rd_ptr;
   uint16_t i=2;


   rd_ptr=buf_rd_ptr;

   do{
      if (data_count<(PARAM_INDEX+1)) return COMM_NO_DATA;
      sync=buffer[rd_ptr];
      incPtr(&rd_ptr);
      if (sync!=CMD_SYNC1 && sync!=CMD_SYNC2){
         if (!getData(&sync, 1)) return COMM_SYNC_ERROR;
      }
      else s_ok=true;
   }
   while (!s_ok);

   //if (data_count<(PARAM_INDEX-1)) return false;

   //pula endereços
   incPtr(&rd_ptr);
   if (rd_ptr==buf_wr_ptr) return COMM_HEADER_ERROR;
   incPtr(&rd_ptr);
   if (rd_ptr==buf_wr_ptr) return COMM_HEADER_ERROR;

   cmd=buffer[rd_ptr];

   incPtr(&rd_ptr);
   size=buffer[rd_ptr];
   if (data_count<(size+PARAM_INDEX+CRC_SIZE)) return COMM_PARAM_SIZE_ERROR;

   incPtr(&rd_ptr);
   if (rd_ptr==buf_wr_ptr) return COMM_PARAM_SIZE_ERROR;

   if (cmd==CMD_TEXT){
      while (buffer[rd_ptr]!=0){
         incPtr(&rd_ptr);
         if (rd_ptr==buf_wr_ptr) return COMM_PARAM_SIZE_ERROR;
         i++;
      }
      if (data_count<(i+PARAM_INDEX+CRC_SIZE))
         return COMM_PARAM_SIZE_ERROR;
   }

   return COMM_OK;
}

//---------------------------------------------------------------------------

void comm_protocol::incPtr(uint16_t *ptr){
   //if (((*ptr)+1)==BUF_SIZE) *ptr=0;
   //else (*ptr)++;

   *ptr=(*ptr+1)%BUF_SIZE;
}

//---------------------------------------------------------------------------

uint8_t comm_protocol::calcCRC8(uint8_t *data, uint16_t size){
   uint8_t crc;
   uint16_t i;

   crc=size;

   for (i=0; i<size; i++) crc^=data[i];

   return crc;
}

//---------------------------------------------------------------------------

void comm_protocol::setPERCount(bool error){
   error_count+=error;
   setErrorBuf(error);

   if (packet_count<PER_LENGTH){
      packet_count++;
      PER=(float)error_count/(float)packet_count;
   }
   else PER=(float)error_count/(float)PER_LENGTH;

   error_count-=getErrorBuf();
}

//---------------------------------------------------------------------------

void comm_protocol::setErrorBuf(bool error){
   uint8_t mask;

   mask=(1<<PER_ptr.split.bit_index);

   if (error) PER_buf[PER_ptr.split.byte_index]|=mask;
   else PER_buf[PER_ptr.split.byte_index]&=~mask;

   PER_ptr.index=(PER_ptr.index+1)%PER_LENGTH;

}

//---------------------------------------------------------------------------

bool comm_protocol::getErrorBuf(void){
   uint8_t mask;
   bool error;

   mask=(1<<PER_ptr.split.bit_index);

   if ((PER_buf[PER_ptr.split.byte_index]&mask)==0) error=false;
   else error=true;

   //PER_ptr.index=(PER_ptr.index+1)%PER_LENGTH;

   return error;
}

//---------------------------------------------------------------------------





