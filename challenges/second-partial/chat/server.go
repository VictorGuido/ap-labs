//Victor Jaret Guido Alvarado
//main.go
// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"

	//"os"
	"time"
)

var Users = make(map[string]string)
var kicked = make(map[string]string)
var uIps = make(map[string]net.Conn)
var first int = 0
var admin string

//!+broadcaster
type client chan<- string // an outgoing message channel

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
	kicking  = make(chan client)
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}

		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)

		case cli := <-kicking:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn, usr string) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)
	who := conn.RemoteAddr().String()
	usr = usr[0 : len(usr)-1]
	_, usrChecker := Users[usr]
	if usrChecker {
		ch <- "Please select another nickname"
		conn.Close()
		return
	}

	Users[usr] = who
	uIps[usr] = conn

	fmt.Println("New connected user [" + usr + "]")
	ch <- "Welcome to the Simple IRC Server"
	ch <- "Your user [" + usr + "] is succesfully logged"

	messages <- "New connected user [" + usr + "]"
	if first == 0 {
		fmt.Println("[" + usr + "] was promoted as the channel ADMIN")
		admin = usr
		messages <- "[" + usr + "] was promoted as the channel ADMIN"
		first = 1
    ch <- "Congrats, you were the first user"
    ch <- "You're THE IRC Server ADMIN"
	}
	entering <- ch

	input := bufio.NewScanner(conn)
	fmt.Println(input.Text())
	var foundUser = 0
	for input.Scan() {
		if len(input.Text()) == 0 {
			ch <- "Please write something on the channel"
		} else {
			var msg []string
			msg = strings.Fields(input.Text())
			switch msg[0] {
			case "/users":
				ch <- "Active users"
				for i, _ := range Users {
					ch <- i + ", "
				}
				ch <- "-------------"
			case "/msg":
				//ch <- msg[0]
				if len(msg) > 2 {
					//aqui se imprime el mensaje
					//fmt.Println("Mensaje en 0"+ msg[0])
					//fmt.Println("Mensaje de 1 en adelante: %i", len(msg))
					if _, found := uIps[usr]; found {
						//fmt.Println(uc[strings.Trim(s[1], " ")], user + ">" + u)
						//fmt.Fprintln(uIps[msg[1]],"%s > %s : %s", usr,msg[2:len(msg)])
						fmt.Fprintln(uIps[msg[1]], "Private message from :"+usr+" ", msg[2:len(msg)])
						//fmt.Fprintln(uIps[msg[1]],+ usr, msg[2:len(msg)])
					} else {
						ch <- "user not found"
					}
				} else {
					ch <- "Please use format /msg [user] [msg]"
				}
			case "/time":
				if len(msg) == 1 {
					loc, _ := time.LoadLocation("America/Mexico_City")
					ch <- "irc-server > Local Time: America/Mexico_City " + time.Now().In(loc).Format(time.Kitchen)
				} else {
					ch <- "Please follow format /time"
				}
			case "/user":
				if len(msg) > 1 {
					for i, z := range Users {
						if msg[1] == i {
							ch <- "Username: " + msg[1] + ", IP:" + z
							foundUser = 1
						}
					}
					if foundUser == 0 {
						ch <- "User not Found"
					}
				} else {
					ch <- "Please use format /user [user]"
				}
				foundUser = 0
			case "/kick":
				//ch <- who
				if len(msg) == 2 {
					if usr == admin {
						ch <- "You are allowed to kick users"
						messages <- msg[1] + " was kicked from the server"
            fmt.Println(msg[1], "was kicked from the server")
						uIps[msg[1]].Close()
						delete(Users, msg[1])
						delete(uIps, msg[1])
					} else {
						ch <- "You are not the admin"
					}
				} else {
					ch <- "Please follow the format /kick [user]"
				}

				/*var a =0;
				  for i, z:= range Users{
				    if(a==0){
				      if(who == admin){//if admin
				        for x, w:= range Users{
				          if(x== msg[1]){
				            i=i
				            z=z
				            w=w
				          }
				        }
				      }else{
				        ch <- "You are not the admin"
				      }
				    }
				    a=1
				  }
				  if(len(msg)!=2){
				  }*/
			default:
				messages <- usr + ">" + input.Text()
			}
		}

	}
	// NOTE: ignoring potential errors from input.Err()
	leaving <- ch
	messages <- usr + " has left"
	fmt.Println("[" + usr + "] left")
	delete(Users, usr)
	delete(uIps, usr)
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {
	listener, err := net.Listen("tcp", "localhost:9000")
	fmt.Println("Simple IRC Server started at localhost:9000")
	fmt.Println("Ready for receiving new clients")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		msg, _ := bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn, string(msg))
	}
}

//!-main

