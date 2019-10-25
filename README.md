# QuestLab
This repo is for both the final project of the class CPE 490 Information Systems as well as the Stevens' QuEST Lab.

The project is a three part local area network to demonstrate multiple systems.<br>
First there is a TCP server running on a Linux laptop that is looking for data to print to a terminal.<br>
There is a Zedboard, a development kit with a Xilinx Zynq-7000 all programmable SoC. This has a TCP client running on the processing system sending out random data over its ethernet port.<br>
Last is a second laptop that sniffs and alters the traffic going between the client and server. This is used to simulate a man in the middle attack of the data transfered between the TCP server/client conneciton.<br>
All three devices are connected to a single switch via RJ-45 ethernet connections.<br>

### Demo
Link to demo video: https://youtu.be/8AsDUdhbFmc
