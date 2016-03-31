#include <rtthread.h>
#include <lwip/sockets.h> /* ʹ��BSD socket����Ҫ��sockets.hͷ�ļ� */

#define BUFSZ   1024

void udpserv(void *paramemter)
{
    int sock;
    int bytes_read;
    char *recv_data;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;

    /* ��������õ����ݻ��� */
    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        /* �����ڴ�ʧ�ܣ����� */
        rt_kprintf("No memory\n");
        return;
    }

    /* ����һ��socket��������SOCK_DGRAM,UDP���� */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        rt_kprintf("Socket error\n");

        /* �ͷŽ����õ����ݻ��� */
        rt_free(recv_data);
        return;
    }

    /* ��ʼ������˵�ַ */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* ��socket������˵�ַ */
    if (bind(sock, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        /* ��ʧ�� */
        rt_kprintf("Bind error\n");

        /* �ͷŽ����õ����ݻ��� */
        rt_free(recv_data);
        return;
    }

    addr_len = sizeof(struct sockaddr);
    rt_kprintf("UDPServer Waiting for client on port 5000...\n");

    while (1)
    {
        /* ��socket����ȡ���BUFSZ-1�ֽ����� */
        bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                              (struct sockaddr *)&client_addr, &addr_len);
        /* UDP��ͬ��TCP�����������������ȡ������ʧ�ܵ��������������
        	��ʱ�ȴ� */

        recv_data[bytes_read] = '\0'; /* ��ĩ������ */

        /* ������յ����� */
        rt_kprintf("\n(%s , %d) said : ", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
        rt_kprintf("%s", recv_data);

        /* �������������exit���˳� */
        if (strcmp(recv_data, "exit") == 0)
        {
            lwip_close(sock);

            /* �ͷŽ����õ����ݻ��� */
            rt_free(recv_data);
            break;
        }
    }

    return;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(udpserv, startup udp server);
#endif
