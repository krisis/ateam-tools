#! /bin/bash

for i in {1..10};
do
time /root/write-osync-file /home/sas/smallfile $1/file$i
done


