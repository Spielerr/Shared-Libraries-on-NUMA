#!/bin/zsh 
sudo x86_64-softmmu/qemu-system-x86_64  \
-machine hmat=on \
-boot c \
-enable-kvm \
-m 4G,slots=2,maxmem=6G \
-object memory-backend-ram,size=2G,id=m0 \
-object memory-backend-ram,size=2G,id=m1 \
-numa node,nodeid=0,memdev=m0 \
-numa node,nodeid=1,memdev=m1 \
-smp 4,sockets=4,maxcpus=4  \
-numa cpu,node-id=0,socket-id=0 \
-numa cpu,node-id=0,socket-id=1 \
-numa cpu,node-id=1,socket-id=2 \
-numa cpu,node-id=1,socket-id=3 \
-numa dist,src=0,dst=1,val=20 \
-net nic \
-net user \
-hda testing.img \
-numa hmat-lb,initiator=0,target=0,hierarchy=memory,data-type=access-latency,latency=5 \
-numa hmat-lb,initiator=0,target=0,hierarchy=memory,data-type=access-bandwidth,bandwidth=200M \
-numa hmat-lb,initiator=0,target=1,hierarchy=memory,data-type=access-latency,latency=20 \
-numa hmat-lb,initiator=0,target=1,hierarchy=memory,data-type=access-bandwidth,bandwidth=50M \
-numa hmat-lb,initiator=1,target=0,hierarchy=memory,data-type=access-latency,latency=20 \
-numa hmat-lb,initiator=1,target=0,hierarchy=memory,data-type=access-bandwidth,bandwidth=50M \
-numa hmat-lb,initiator=1,target=1,hierarchy=memory,data-type=access-latency,latency=5 \
-numa hmat-lb,initiator=1,target=1,hierarchy=memory,data-type=access-bandwidth,bandwidth=200M \
-cdrom ubuntu-18.04.3-desktop-amd64.iso
