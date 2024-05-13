#include "define.h"

typedef struct tag_MOPS {

    struct {

        union {

            struct {
                unsigned int info[3]; // ����������������� �������: ��� �������, ������ ��������, ������ �����
                unsigned int status[num_zone_mops]; // ������� ���
                unsigned int hold_status[num_zone_mops]; // ����������� ������� ���
                unsigned int current[num_zone_mops + 1]; // ���� ���
            };
            unsigned int read[num_zone_mops * 3 + 4]; // ������� ������
        };

        union {

            struct {
                unsigned int command[num_zone_mops]; // ������� ���
                unsigned int type[num_zone_mops]; // ���� ���: �������, �������� � �� � ��� ��
                unsigned int limit1[num_zone_mops]; // ������ ���� - ����� ��� ���� ���
                unsigned int limit2[num_zone_mops]; // ������ ����� - �������� ��� ���� ���
                unsigned int limit3[num_zone_mops]; // ������ �������� - ����� ��� ���� ���
                unsigned int limit4[num_zone_mops]; // ������ ����� - �� ��� ���� ���
                unsigned int timer1[num_zone_mops]; // ������������� ������� ���� ���
                unsigned int timer2[num_zone_mops];
                unsigned int timer3[num_zone_mops];
                unsigned int timer4[num_zone_mops];
            };
            unsigned int write[num_zone_mops * 10];
        };
    };
    unsigned int main_area[num_zone_mops * 13 + 4];
} MOPS, MOPS_swap;