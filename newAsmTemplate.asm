    #include <xc.inc>
    global   _TxSpiSW
    
    TxByte   equ    0x7E0
    SPIcnt   equ    0x7E1
    SDOPort  equ    PORTC 
    SCLPort  equ    PORTB 
    SDOPin   equ    7
    SCLPin   equ    1  
  
 PSECT    code  
_TxSpiSW:
    banksel  TxByte
    movwf    TxByte
    movlw    8
    movwf    SPIcnt
_StartTx:    
    dcfsnz   SPIcnt,1, 1
    return
    bcf      SCLPort, SCLPin, 1
    btfsc    TxByte, 7, 1
    goto     _SDOset
    goto     _SDOclr 
    
_SDOset:
    banksel  PORTC
    bsf      SDOPort, SDOPin, 1
    rlncf    TxByte, 1, 1
    bsf      SCLPort, SCLPin, 1
    goto     _StartTx
_SDOclr:    
    banksel  PORTC
    bcf      SDOPort, SDOPin, 1
    rlncf    TxByte, 1, 1
    bsf      SCLPort, SCLPin, 1
    goto     _StartTx
    
end
