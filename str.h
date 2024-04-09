#include "def.h"

//typedef struct tag_usart{
typedef struct {
	unsigned char out_buffer[OUT_SIZE];
	unsigned char in_buffer[IN_SIZE];
	unsigned short out_buffer_count;
	unsigned short in_buffer_count;
	unsigned short in_buffer_count2;
	unsigned short number_send;
	unsigned short port_type;
	unsigned short mbm_status;
	unsigned short mbm_err;
	unsigned short hl_err;
	unsigned short mbm_status_hl;
	unsigned short mbm_status_05;
	unsigned short repeat_05;
	unsigned short repeat_05_;
	struct tag_mb_statusBITS {
		unsigned modb_mode		  	:1;		// 1
		unsigned term_mode  		:1;		// 2
		unsigned modb_received 		:1;		// 3
		unsigned modb_transmited	:1;		// 4
		unsigned modb_receiving		:1;		// 5
		unsigned modb_transmiting	:1;		// 6
		unsigned tx_mode			:1;		// 7
		unsigned tx_data_rdy		:1;		// 8
		unsigned master_error		:1;		// 9
		unsigned bussy1			:1;		// 10
		unsigned bussy2			:1;		// 11
		unsigned last_byte		:1;		// 12
		unsigned byte_missing	:1;		// 13
		unsigned coll_1			:1;		// 14
		unsigned coll_2			:1;		// 15
		unsigned coll_3			:1;		// 16
		unsigned tx_start		:1;		// 17
		unsigned 				:15;		// 18-32
	} mb_status;
//} usart4, usart5;
}tag_usart;