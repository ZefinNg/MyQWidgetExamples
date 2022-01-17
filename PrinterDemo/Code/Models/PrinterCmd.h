#ifndef PRINTERCMD_H
#define PRINTERCMD_H

#define LINE_TOTAL_LENGTH                32

#define INIT_PRINTER                     "\x1B\x40"

#define QUERY_TRANSPORT_DEVICE_STATUS    "\x10\x04\x01"
#define QUERY_OFFLINE_STATUS             "\x10\x04\x02"
#define QUERY_ERROR_STATUS               "\x10\x04\x03"
#define QUERY_PAPER_STATUS               "\x10\x04\x04"

#define SET_ROTATION_ANGLE_0             "\x1c\x49\x00"
#define SET_ROTATION_ANGLE_90            "\x1c\x49\x01"
#define SET_ROTATION_ANGLE_180           "\x1c\x49\x02"
#define SET_ROTATION_ANGLE_270           "\x1c\x49\x03"

#define HORIZONTAL_ZOOM_1_TIMES          "\x1B\x55\x01"
#define HORIZONTAL_ZOOM_4_TIMES          "\x1B\x55\x04"

#define EXEC_LEVEL_TABULATION            "\x09"
#define CMD_WRAP                         "\x0A"
#define CMD_ENTER                        "\x0D"

#define CMD_HTAB1                        "\x1B\x44\x01\x00"
#define CMD_HTAB2                        "\x1B\x44\x01\x10\x00"

#define CMD_ANTI_WHITE_ON                "\x1B\x69\x01"
#define CMD_ANTI_WHITE_OFF               "\x1B\x69\x10"

#define SCALE_MIN_TIMES (1)
#define SCALE_MAX_TIMES (8)

#define CMD_SELECT_CODE_PAGE             "\x1B\x74\x11"

#define STRLEN(S)                   sizeof(S)-1

#endif // PRINTERCMD_H
