#define OP_ADC_IMMEDIATE 0x69
#define OP_ADC_ZERO_0 0x65
#define OP_ADC_ZERO_X 0x75
#define OP_ADC_ABSOLUTE_0 0x6d
#define OP_ADC_ABSOLUTE_X 0x7d
#define OP_ADC_ABSOLUTE_Y 0x79
#define OP_ADC_INDIRECT_X 0x61
#define OP_ADC_INDIRECT_Y 0x71

#define OP_AND_IMMEDIATE 0x29
#define OP_AND_ZERO_0 0x25
#define OP_AND_ZERO_X 0x35
#define OP_AND_ABSOLUTE_0 0x2d
#define OP_AND_ABSOLUTE_X 0x3d
#define OP_AND_ABSOLUTE_Y 0x39
#define OP_AND_INDIRECT_X 0x21
#define OP_AND_INDIRECT_Y 0x31

#define OP_ASL_A 0x0a
#define OP_ASL_ZERO_0 0x06
#define OP_ASL_ZERO_X 0x16
#define OP_ASL_ABSOLUTE_0 0x0e
#define OP_ASL_ABSOLUTE_X 0x1e

#define OP_BCC 0x90
#define OP_BCS 0xb0
#define OP_BEQ 0xf0

#define OP_BIT_ZERO 0x24
#define OP_BIT_ABSOLUTE 0x2c

#define OP_BMI 0x30
#define OP_BNE 0xd0
#define OP_BPL 0x10
#define OP_BRK 0x00
#define OP_BVC 0x50
#define OP_BVS 0x70
#define OP_CLC 0x18
#define OP_CLD 0xd8
#define OP_CLI 0x58
#define OP_CLV 0xb8

#define OP_CMP_IMMEDIATE 0xc9
#define OP_CMP_ZERO_0 0xc5
#define OP_CMP_ZERO_X 0xd5
#define OP_CMP_ABSOLUTE_0 0xcd
#define OP_CMP_ABSOLUTE_X 0xdd
#define OP_CMP_ABSOLUTE_Y 0xd9
#define OP_CMP_INDIRECT_X 0xc1
#define OP_CMP_INDIRECT_Y 0xd1

#define OP_CPX_IMMEDIATE 0xe0
#define OP_CPX_ZERO 0xe4
#define OP_CPX_ABSOLUTE 0xec

#define OP_CPY_IMMEDIATE 0xc0
#define OP_CPY_ZERO 0xc4
#define OP_CPY_ABSOLUTE 0xcc

#define OP_DEC_ZERO_0 0xc6
#define OP_DEC_ZERO_X 0xd6
#define OP_DEC_ABSOLUTE_0 0xce
#define OP_DEC_ABSOLUTE_X 0xde

#define OP_DEX 0xca
#define OP_DEY 0x88

#define OP_EOR_IMMEDIATE 0x49
#define OP_EOR_ZERO_0 0x45
#define OP_EOR_ZERO_X 0x55
#define OP_EOR_ABSOLUTE_0 0x4d
#define OP_EOR_ABSOLUTE_X 0x5d
#define OP_EOR_ABSOLUTE_Y 0x59
#define OP_EOR_INDIRECT_X 0x41
#define OP_EOR_INDIRECT_Y 0x51

#define OP_INC_ZERO_0 0xe6
#define OP_INC_ZERO_X 0xf6
#define OP_INC_ABSOLUTE_0 0xee
#define OP_INC_ABSOLUTE_X 0xfe

#define OP_INX 0xe8
#define OP_INY 0xc8

#define OP_JMP_ABSOLUTE 0x4c
#define OP_JMP_INDIRECT 0x6c

#define OP_JSR 0x20

#define OP_LDA_IMMEDIATE 0xa9
#define OP_LDA_ZERO_0 0xa5
#define OP_LDA_ZERO_X 0xb5
#define OP_LDA_ABSOLUTE_0 0xad
#define OP_LDA_ABSOLUTE_X 0xbd
#define OP_LDA_ABSOLUTE_Y 0xb9
#define OP_LDA_INDIRECT_X 0xa1
#define OP_LDA_INDIRECT_Y 0xb1

#define OP_LDX_IMMEDIATE 0xa2
#define OP_LDX_ZERO_0 0xa6
#define OP_LDX_ZERO_Y 0xb6
#define OP_LDX_ABSOLUTE_0 0xae
#define OP_LDX_ABSOLUTE_Y 0xbe

#define OP_LDY_IMMEDIATE 0xa0
#define OP_LDY_ZERO_0 0xa4
#define OP_LDY_ZERO_X 0xb4
#define OP_LDY_ABSOLUTE_0 0xac
#define OP_LDY_ABSOLUTE_X 0xbc

#define OP_LSR_A 0x4a
#define OP_LSR_ZERO_0 0x46
#define OP_LSR_ZERO_X 0x56
#define OP_LSR_ABSOLUTE_0 0x4e
#define OP_LSR_ABSOLUTE_X 0x5e

#define OP_NOP 0xea

#define OP_ORA_IMMEDIATE 0x09
#define OP_ORA_ZERO_0 0x05
#define OP_ORA_ZERO_X 0x15
#define OP_ORA_ABSOLUTE_0 0x0d
#define OP_ORA_ABSOLUTE_X 0x1d
#define OP_ORA_ABSOLUTE_Y 0x19
#define OP_ORA_INDIRECT_X 0x01
#define OP_ORA_INDIRECT_Y 0x11

#define OP_PHA 0x48
#define OP_PHP 0x08
#define OP_PLA 0x68
#define OP_PLP 0x28

#define OP_ROL_A 0x2a
#define OP_ROL_ZERO_0 0x26
#define OP_ROL_ZERO_X 0x36
#define OP_ROL_ABSOLUTE_0 0x2e
#define OP_ROL_ABSOLUTE_X 0x3e

#define OP_ROR_A 0x6a
#define OP_ROR_ZERO_0 0x66
#define OP_ROR_ZERO_X 0x76
#define OP_ROR_ABSOLUTE_0 0x6e
#define OP_ROR_ABSOLUTE_X 0x7e

#define OP_RTI 0x40
#define OP_RTS 0x60

#define OP_SBC_IMMEDIATE 0xe9
#define OP_SBC_ZERO_0 0xe5
#define OP_SBC_ZERO_X 0xf5
#define OP_SBC_ABSOLUTE_0 0xed
#define OP_SBC_ABSOLUTE_X 0xfd
#define OP_SBC_ABSOLUTE_Y 0xf9
#define OP_SBC_INDIRECT_X 0xe1
#define OP_SBC_INDIRECT_Y 0xf1

#define OP_SEC 0x38
#define OP_SED 0xf8
#define OP_SEI 0x78

#define OP_STA_ZERO_0 0x85
#define OP_STA_ZERO_X 0x95
#define OP_STA_ABSOLUTE_0 0x8d
#define OP_STA_ABSOLUTE_X 0x9d
#define OP_STA_ABSOLUTE_Y 0x99
#define OP_STA_INDIRECT_X 0x81
#define OP_STA_INDIRECT_Y 0x91

#define OP_STX_ZERO_0 0x86
#define OP_STX_ZERO_Y 0x96
#define OP_STX_ABSOLUTE 0x8e

#define OP_STY_ZERO_0 0x84
#define OP_STY_ZERO_X 0x94
#define OP_STY_ABSOLUTE 0x8c

#define OP_TAX 0xaa
#define OP_TAY 0xa8
#define OP_TSX 0xba
#define OP_TXA 0x8a
#define OP_TXS 0x9a
#define OP_TYA 0x98

