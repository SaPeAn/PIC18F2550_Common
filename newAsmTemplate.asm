
    global   _TxSpiSW
    
    TxByte   equ    0x000
    SPIcnt   equ    0x001
    SDOPort  equ    0xF82 ;PortC
    SCLPort  equ    0xF81 ;PortB
    SDOPin   equ    7
    SCLPin   equ    1  
  
_TxSpiSW:
    movwf    TxByte
    movlw    8
    movwf    SPIcnt
_StartTx:    
    dcfsnz   SPIcnt,1
    return
    bcf      SCLPort, SCLPin
    btfsc    TxByte, 7
    goto     _SDOset
    goto     _SDOclr 
    
_SDOset:
    bsf      SDOPort, SDOPin
    rlncf    TxByte, 1
    bsf      SCLPort, SCLPin
    goto     _StartTx
_SDOclr:    
    bcf      SDOPort, SDOPin
    rlncf    TxByte, 1
    bsf      SCLPort, SCLPin
    goto     _StartTx
    

