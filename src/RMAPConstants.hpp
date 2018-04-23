#ifndef RMAP_CONSTANTS_HPP
#define RMAP_CONSTANTS_HPP

/* 
 * SpaceWire transmit descriptor
 * word 0
 * 		31:20		RESERVED
 * 		19:18		CRC type
 * 		17			Append data CRC
 * 		16			Append header CRC
 * 		15			Link error
 * 		14			Interrupt enable
 * 		13			Wrap
 * 		12			Enable
 *		11:8		Non-CRC bytes
 *		7:0			Header length
 *
 * word 1
 * 		31:0		Header address
 *
 * word 2
 * 		31:24		RESERVED
 * 		23:0		Data length
 *
 * word 3
 * 		31:0		Data address
 */

/*
 * SpaceWire receive descriptor
 * word 0
 * 		31			Truncated
 * 		30			Data CRC
 * 		29			Header CRC
 * 		28			EEP termination
 * 		27			Interrupt enable
 * 		26			Wrap
 * 		25			Enable
 * 		24:0		Packet length
 *
 * word 1
 * 		31:0		Packet address
 */

#define SPW_TRANSMIT_DESC_HEADER_MASK 0x000000FF
#define SPW_TRANSMIT_DESC_NONCRC_MASK 0x00000F00
#define SPW_TRANSMIT_DESC_APPEND_HEADER_CRC_MASK 0x00010000
#define SPW_TRANSMIT_DESC_APPEND_DATA_CRC_MASK 0x00020000
#define SPW_TRANSMIT_DESC_CRC_TYPE_MASK 0x000C0000
#define SPW_TRANSMIT_DESC_DATA_LEN_MASK 0x00FFFFFF

#endif
