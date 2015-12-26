// compile and run
#gcc -o tcp_net_server tcp_net_server.c tcp_net_socket.c
#gcc -o tcp_net_client tcp_net_client.c tcp_net_socket.c
#./tcp_net_server 192.168.0.164 8888
#./tcp_net_client 192.168.0.164 8888


// look for current computer ip
#sudo ifconfig -a
eg: 192.168.140.128
