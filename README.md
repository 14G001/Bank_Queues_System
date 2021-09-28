# Bank-Queues-System
Is the simulation of a bank client queues system, that automatically attends the client who corresponds to be served.
Two queues are available in this bank; Premium and Standard.
Clients will be attended depending on the following factors:

-If the client is a woman and is pregnant, she will go to the front of the corresponding queue (Premium or Standard).
-If the premium customer queue has more than two customers waiting, the turn will be assigned to a premium customer.
-When the premium clients queue has less than 3 clients waiting, the allocation of shifts will alternate between Premium and Standard customer queue.
-If a pregnant woman is found in either of the two queues, she should have priority over all other clients, and among pregnant women, the first to
have reached the queue will have priority.


MENU OPTIONS:

1) Add a new client.
2) Attend a client.
3) View queues status.
4) View specific client info.
5) Exit.



To add a new client, you will have to write his data on the "Client Input" file with the following format:


Name (George Emmerson)

id (44392883)

operation (1 or 0)

Amount of money (32423.333)

type (C, P, E o M)
