    #include <xc.inc>
    
    TxByte   equ    0x01
    SPIcnt   equ    0x02
    SDOPort  equ    PORTC 
    SCLPort  equ    PORTB 
    SDOPin   equ    7
    SCLPin   equ    1 
   
    PSECT TxSpiSW,class=CODE,reloc=2,optim=inline
    
    global   _TxSpiSW
    
    
_TxSpiSW:
    movwf    TxByte, 0
    movlw    9
    movwf    SPIcnt, 0
_StartTx: 
    dcfsnz   SPIcnt,1, 0
    return
    bcf      SCLPort, SCLPin, 0
    btfsc    TxByte, 7, 0
    goto     _SDOset
    goto     _SDOclr 
    
_SDOset:
    bsf      SDOPort, SDOPin, 0
    rlncf    TxByte, 1, 0
    nop
    bsf      SCLPort, SCLPin, 0
    goto     _StartTx
_SDOclr:    
    bcf      SDOPort, SDOPin, 0
    rlncf    TxByte, 1, 0
    nop
    bsf      SCLPort, SCLPin, 0
    goto     _StartTx
    
end
