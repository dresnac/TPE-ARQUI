sudo docker start TPE_ARQUI
sudo docker exec -it TPE_ARQUI make clean -C /root/Toolchain
sudo docker exec -it TPE_ARQUI make clean -C /root/
sudo docker exec -it TPE_ARQUI make -C /root/Toolchain
sudo docker exec -it TPE_ARQUI make -C /root/
sudo docker stop TPE_ARQUI 