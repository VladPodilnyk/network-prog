# TCP/UDP server and client implementation

This porject demonstrates realization of server-client communication
based on different protocols: UDP or TCP.

## Getting Started

### Download the project

```
$ git clone https://github.com/VladPodilnyk/network-prog
```

### Build project

Use make to build server and client. These examples below 
shows different variant of usage Makefile.
```
$ make            # buld all
$ make server     # build server
$ make client     # build client
$ make del_server # delete client
$ make del_client # delete client
$ make clean      # delete all
```

### Enjoy

In order to debug you should run server and debug.sh in separate terminals using commands below.
```
$./server
$./debug.sh set_timeout_here_in_sec
```
