
#ifndef _CUFTPD_H
#define _CUFTPD_H

#define CUFTPD_DEBUG(fmt, ...)        cuftpd_debug(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define CUFTPD_ARR_LEN(arr)                (sizeof(arr)/sizeof(arr[0]))

#define CUFTPD_VER                                "1.0"
#define CUFTPD_DEF_SRV_PORT                21
#define CUFTPD_LISTEN_QU_LEN        8
#define CUFTPD_LINE_END                        "\r\n"

#define CUFTPD_OK        0
#define CUFTPD_ERR        (-1)

#define CUFTPD_CHECK_LOGIN()  \
        do { \
                if (!cuftpd_cur_user) { \
                        cuftpd_send_resp(ctrlfd, 530, "first please"); \
                        return CUFTPD_ERR; \
                } \
        } while(0)

struct cuftpd_cmd_struct {
        char *cmd_name;
        int (*cmd_handler)(int ctrlfd, char *cmd_line);
};

struct cuftpd_user_struct {
        char user[128];
        char pass[128];
};


#endif

