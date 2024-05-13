#include "define.h"

typedef struct tag_MOPS {

    struct {

        union {

            struct {
                unsigned int info[3]; // идентификационна€ область: тип прибора, верси€ прошивки, верси€ платы
                unsigned int status[num_zone_mops]; // статусы зон
                unsigned int hold_status[num_zone_mops]; // запомненные статусы зон
                unsigned int current[num_zone_mops + 1]; // токи зон
            };
            unsigned int read[num_zone_mops * 3 + 4]; // область чтени€
        };

        union {

            struct {
                unsigned int command[num_zone_mops]; // команды зон
                unsigned int type[num_zone_mops]; // типы зон: обычна€, пожарна€ с ѕ« и без ѕ«
                unsigned int limit1[num_zone_mops]; // пороги обыв - норма дл€ всех зон
                unsigned int limit2[num_zone_mops]; // пороги норма - внимание дл€ всех зон
                unsigned int limit3[num_zone_mops]; // пороги внимание - пожар дл€ всех зон
                unsigned int limit4[num_zone_mops]; // пороги пожар -  « дл€ всех зон
                unsigned int timer1[num_zone_mops]; // настраиваемые таймера всех зон
                unsigned int timer2[num_zone_mops];
                unsigned int timer3[num_zone_mops];
                unsigned int timer4[num_zone_mops];
            };
            unsigned int write[num_zone_mops * 10];
        };
    };
    unsigned int main_area[num_zone_mops * 13 + 4];
} MOPS, MOPS_swap;