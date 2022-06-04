#include "protocol.h"


PDU *mkPDU(uint msgLen)
{
    uint PDULen = sizeof(PDU) +  msgLen;
    PDU *pdu = (PDU*)malloc(PDULen);
    if(NULL == pdu){
        exit(EXIT_FAILURE);
    }
    memset(pdu,0,PDULen);

    pdu->caPDULen = PDULen;
    pdu->caMsgLen = msgLen;
    return pdu;
}
