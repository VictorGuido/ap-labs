Simple IRC Server
=================

In order to fully conect with the IRC Server please follow these requierements
------------------------------------------------------------------------------


- 1 terminal that will work as the main server
- as many other terminals that will work as clients

ex: A chat for 3 people
- 1 terminal as server
- 3 terminals as clients
- total terminals = 4

To run the IRC SERVER pleake make sure to be in che chat folder to run these commands

Server comand
-------------

go run server.go -host localhost -port 9000


Client command
--------------

go run client.go -user [username] -server localhost:9000

*please make sure to replace [username] with the username you will want to be joining the server


DO NOT SEND MESSAGES OR  KICK USERS THAT ARE NOT CURRENTLY IN THE SERVER OTHERWISE IT WILL CHRASH
--------------------------------------------------------------------------------------------------
