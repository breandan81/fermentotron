#!/usr/bin/perl

while(true)
{
print `./fetchtemp.pl`;

`sshpass -p '0mgz0mb33s' scp /home/breandan/freezerlog breandan81\@avrthing.com:/home/breandan81/avrthing.com/freezerlog`;
sleep(5);
}

