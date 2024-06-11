typedef	unsigned char		__uint8_t;

#ifndef	uint8_t
typedef	__uint8_t	uint8_t;
#define	uint8_t		__uint8_t
#endif

typedef enum {

    SPI_ID_1 = 0,
    SPI_ID_2,
    SPI_ID_3,
    SPI_ID_4,
    SPI_ID_5,
    SPI_ID_6,
    SPI_NUMBER_OF_MODULES

} SPI_MODULE_ID;

#define _SFR_WRITE(reg,val)  ( *((SFR_TYPE *)(reg))  =  (val) )



#define _SPI5CON_SRXISEL_POSITION                0x00000000
#define _SPI5CON_SRXISEL_MASK                    0x00000003
#define _SPI5CON_SRXISEL_LENGTH                  0x00000002

#define _SPI5CON_STXISEL_POSITION                0x00000002
#define _SPI5CON_STXISEL_MASK                    0x0000000C
#define _SPI5CON_STXISEL_LENGTH                  0x00000002

#define _SPI5CON_DISSDI_POSITION                 0x00000004
#define _SPI5CON_DISSDI_MASK                     0x00000010
#define _SPI5CON_DISSDI_LENGTH                   0x00000001

#define _SPI5CON_MSTEN_POSITION                  0x00000005
#define _SPI5CON_MSTEN_MASK                      0x00000020
#define _SPI5CON_MSTEN_LENGTH                    0x00000001

#define _SPI5CON_CKP_POSITION                    0x00000006
#define _SPI5CON_CKP_MASK                        0x00000040
#define _SPI5CON_CKP_LENGTH                      0x00000001

#define _SPI5CON_SSEN_POSITION                   0x00000007
#define _SPI5CON_SSEN_MASK                       0x00000080
#define _SPI5CON_SSEN_LENGTH                     0x00000001

#define _SPI5CON_CKE_POSITION                    0x00000008
#define _SPI5CON_CKE_MASK                        0x00000100
#define _SPI5CON_CKE_LENGTH                      0x00000001

#define _SPI5CON_SMP_POSITION                    0x00000009
#define _SPI5CON_SMP_MASK                        0x00000200
#define _SPI5CON_SMP_LENGTH                      0x00000001

#define _SPI5CON_MODE16_POSITION                 0x0000000A
#define _SPI5CON_MODE16_MASK                     0x00000400
#define _SPI5CON_MODE16_LENGTH                   0x00000001

#define _SPI5CON_MODE32_POSITION                 0x0000000B
#define _SPI5CON_MODE32_MASK                     0x00000800
#define _SPI5CON_MODE32_LENGTH                   0x00000001

#define _SPI5CON_DISSDO_POSITION                 0x0000000C
#define _SPI5CON_DISSDO_MASK                     0x00001000
#define _SPI5CON_DISSDO_LENGTH                   0x00000001

#define _SPI5CON_SIDL_POSITION                   0x0000000D
#define _SPI5CON_SIDL_MASK                       0x00002000
#define _SPI5CON_SIDL_LENGTH                     0x00000001

#define _SPI5CON_ON_POSITION                     0x0000000F
#define _SPI5CON_ON_MASK                         0x00008000
#define _SPI5CON_ON_LENGTH                       0x00000001

#define _SPI5CON_ENHBUF_POSITION                 0x00000010
#define _SPI5CON_ENHBUF_MASK                     0x00010000
#define _SPI5CON_ENHBUF_LENGTH                   0x00000001

#define _SPI5CON_SPIFE_POSITION                  0x00000011
#define _SPI5CON_SPIFE_MASK                      0x00020000
#define _SPI5CON_SPIFE_LENGTH                    0x00000001

#define _SPI5CON_MCLKSEL_POSITION                0x00000017
#define _SPI5CON_MCLKSEL_MASK                    0x00800000
#define _SPI5CON_MCLKSEL_LENGTH                  0x00000001

#define _SPI5CON_FRMCNT_POSITION                 0x00000018
#define _SPI5CON_FRMCNT_MASK                     0x07000000
#define _SPI5CON_FRMCNT_LENGTH                   0x00000003

#define _SPI5CON_FRMSYPW_POSITION                0x0000001B
#define _SPI5CON_FRMSYPW_MASK                    0x08000000
#define _SPI5CON_FRMSYPW_LENGTH                  0x00000001

#define _SPI5CON_MSSEN_POSITION                  0x0000001C
#define _SPI5CON_MSSEN_MASK                      0x10000000
#define _SPI5CON_MSSEN_LENGTH                    0x00000001

#define _SPI5CON_FRMPOL_POSITION                 0x0000001D
#define _SPI5CON_FRMPOL_MASK                     0x20000000
#define _SPI5CON_FRMPOL_LENGTH                   0x00000001

#define _SPI5CON_FRMSYNC_POSITION                0x0000001E
#define _SPI5CON_FRMSYNC_MASK                    0x40000000
#define _SPI5CON_FRMSYNC_LENGTH                  0x00000001

#define _SPI5CON_FRMEN_POSITION                  0x0000001F
#define _SPI5CON_FRMEN_MASK                      0x80000000
#define _SPI5CON_FRMEN_LENGTH                    0x00000001

#define _SPI5CON_w_POSITION                      0x00000000
#define _SPI5CON_w_MASK                          0xFFFFFFFF
#define _SPI5CON_w_LENGTH                        0x00000020

#define _SPI5STAT_SPIRBF_POSITION                0x00000000
#define _SPI5STAT_SPIRBF_MASK                    0x00000001
#define _SPI5STAT_SPIRBF_LENGTH                  0x00000001

#define _SPI5STAT_SPITBF_POSITION                0x00000001
#define _SPI5STAT_SPITBF_MASK                    0x00000002
#define _SPI5STAT_SPITBF_LENGTH                  0x00000001

#define _SPI5STAT_SPITBE_POSITION                0x00000003
#define _SPI5STAT_SPITBE_MASK                    0x00000008
#define _SPI5STAT_SPITBE_LENGTH                  0x00000001

#define _SPI5STAT_SPIRBE_POSITION                0x00000005
#define _SPI5STAT_SPIRBE_MASK                    0x00000020
#define _SPI5STAT_SPIRBE_LENGTH                  0x00000001

#define _SPI5STAT_SPIROV_POSITION                0x00000006
#define _SPI5STAT_SPIROV_MASK                    0x00000040
#define _SPI5STAT_SPIROV_LENGTH                  0x00000001

#define _SPI5STAT_SRMT_POSITION                  0x00000007
#define _SPI5STAT_SRMT_MASK                      0x00000080
#define _SPI5STAT_SRMT_LENGTH                    0x00000001

#define _SPI5STAT_SPITUR_POSITION                0x00000008
#define _SPI5STAT_SPITUR_MASK                    0x00000100
#define _SPI5STAT_SPITUR_LENGTH                  0x00000001

#define _SPI5STAT_SPIBUSY_POSITION               0x0000000B
#define _SPI5STAT_SPIBUSY_MASK                   0x00000800
#define _SPI5STAT_SPIBUSY_LENGTH                 0x00000001

#define _SPI5STAT_FRMERR_POSITION                0x0000000C
#define _SPI5STAT_FRMERR_MASK                    0x00001000
#define _SPI5STAT_FRMERR_LENGTH                  0x00000001

#define _SPI5STAT_TXBUFELM_POSITION              0x00000010
#define _SPI5STAT_TXBUFELM_MASK                  0x001F0000
#define _SPI5STAT_TXBUFELM_LENGTH                0x00000005

#define _SPI5STAT_RXBUFELM_POSITION              0x00000018
#define _SPI5STAT_RXBUFELM_MASK                  0x1F000000
#define _SPI5STAT_RXBUFELM_LENGTH                0x00000005

#define _SPI5STAT_w_POSITION                     0x00000000
#define _SPI5STAT_w_MASK                         0xFFFFFFFF
#define _SPI5STAT_w_LENGTH                       0x00000020

#define _SPI5CON2_AUDMOD_POSITION                0x00000000
#define _SPI5CON2_AUDMOD_MASK                    0x00000003
#define _SPI5CON2_AUDMOD_LENGTH                  0x00000002

#define _SPI5CON2_AUDMONO_POSITION               0x00000003
#define _SPI5CON2_AUDMONO_MASK                   0x00000008
#define _SPI5CON2_AUDMONO_LENGTH                 0x00000001

#define _SPI5CON2_AUDEN_POSITION                 0x00000007
#define _SPI5CON2_AUDEN_MASK                     0x00000080
#define _SPI5CON2_AUDEN_LENGTH                   0x00000001

#define _SPI5CON2_IGNTUR_POSITION                0x00000008
#define _SPI5CON2_IGNTUR_MASK                    0x00000100
#define _SPI5CON2_IGNTUR_LENGTH                  0x00000001

#define _SPI5CON2_IGNROV_POSITION                0x00000009
#define _SPI5CON2_IGNROV_MASK                    0x00000200
#define _SPI5CON2_IGNROV_LENGTH                  0x00000001

#define _SPI5CON2_SPITUREN_POSITION              0x0000000A
#define _SPI5CON2_SPITUREN_MASK                  0x00000400
#define _SPI5CON2_SPITUREN_LENGTH                0x00000001

#define _SPI5CON2_SPIROVEN_POSITION              0x0000000B
#define _SPI5CON2_SPIROVEN_MASK                  0x00000800
#define _SPI5CON2_SPIROVEN_LENGTH                0x00000001

#define _SPI5CON2_FRMERREN_POSITION              0x0000000C
#define _SPI5CON2_FRMERREN_MASK                  0x00001000
#define _SPI5CON2_FRMERREN_LENGTH                0x00000001

#define _SPI5CON2_SPISGNEXT_POSITION             0x0000000F
#define _SPI5CON2_SPISGNEXT_MASK                 0x00008000
#define _SPI5CON2_SPISGNEXT_LENGTH               0x00000001

#define _SPI5CON2_AUDMOD0_POSITION               0x00000000
#define _SPI5CON2_AUDMOD0_MASK                   0x00000001
#define _SPI5CON2_AUDMOD0_LENGTH                 0x00000001

#define _SPI5CON2_AUDMOD1_POSITION               0x00000001
#define _SPI5CON2_AUDMOD1_MASK                   0x00000002
#define _SPI5CON2_AUDMOD1_LENGTH                 0x00000001

#define _SPI5CON2_w_POSITION                     0x00000000
#define _SPI5CON2_w_MASK                         0xFFFFFFFF
#define _SPI5CON2_w_LENGTH                       0x00000020





PLIB_INLINE SFR_TYPE* _SPI_RECEIVE_FIFO_STATUS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_5 :
            return &SPI5STAT;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

PLIB_INLINE SFR_DATA _SPI_RECEIVE_FIFO_STATUS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_5 :
            return _SPI5STAT_SPIRBE_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :     return (SFR_DATA)-1;
    }
}

PLIB_TEMPLATE bool SPI_ReceiverFIFOIsEmpty_Default( SPI_MODULE_ID index )
{
    return( _SFR_BIT_READ( _SPI_RECEIVE_FIFO_STATUS_VREG( index ),
                           _SPI_RECEIVE_FIFO_STATUS_POS( index ) ) );
}

PLIB_INLINE_API bool PLIB_SPI_ReceiverFIFOIsEmpty(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_5 :
            return SPI_ReceiverFIFOIsEmpty_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :       return (bool)0;
    }
}

inline unsigned char SPI_BufferRead(SPI_MODULE_ID MODULE_ID)
{
    while (PLIB_SPI_ReceiverFIFOIsEmpty(MODULE_ID));
    return PLIB_SPI_BufferRead(MODULE_ID);
}    
   /////////////////////////////////////////////////////////////////////// 



PLIB_INLINE SFR_TYPE* _SPI_TRANSMIT_BUFFER_FULL_STATUS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_5 :
            return &SPI5STAT;
        case SPI_NUMBER_OF_MODULES :
        default :    return (SFR_TYPE*)-1;
    }
}
PLIB_INLINE SFR_DATA _SPI_TRANSMIT_BUFFER_FULL_STATUS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_5 :
            return _SPI5STAT_SPITBF_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :    return (SFR_DATA)-1;
    }
}
  
PLIB_TEMPLATE void SPI_BufferWrite_Default( SPI_MODULE_ID index , uint8_t data )
{
    _SFR_WRITE( _SPI_BUFFER_VREG(index),
                (uint8_t)(data) );
}

PLIB_INLINE_API void PLIB_SPI_BufferWrite(SPI_MODULE_ID index, uint8_t data)
{
    switch (index) {
        case SPI_ID_5 :
            SPI_BufferWrite_Default(index, data);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :    break;
    }
}

PLIB_TEMPLATE bool SPI_TransmitBufferIsFull_Default( SPI_MODULE_ID index )
{
    return( _SFR_BIT_READ( _SPI_TRANSMIT_BUFFER_FULL_STATUS_VREG( index ),
                           _SPI_TRANSMIT_BUFFER_FULL_STATUS_POS( index ) ) );
}

PLIB_INLINE_API bool PLIB_SPI_TransmitBufferIsFull(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_5 :
            return SPI_TransmitBufferIsFull_Default(index);
        default :       return (bool)0;
    }
} 
 
    inline void SPI_BufferWrite(SPI_MODULE_ID MODULE_ID, unsigned char a)
{
    while (PLIB_SPI_TransmitBufferIsFull(MODULE_ID));
    PLIB_SPI_BufferWrite(MODULE_ID, a);
}   