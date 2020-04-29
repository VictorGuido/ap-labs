//Victor Jaret Guido Alvarado
//clockWall
package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

func clockConection(conn net.Conn) {
	for {
		hour := make([]byte, 11)
		_, err := conn.Read(hour)
		if err != nil {
			conn.Close()
			log.Print(err)
		} else {
			fmt.Printf(" %s", hour)
		}
	}
}

func main() {
  args := os.Args[1:]
	if (len(args) < 1) {
		fmt.Println("Expected input: go run clockWall.go conection1 conection2 ....")
		os.Exit(1)
	}
	for i := 0; i < len(args); i++ {
		connInfo := strings.Split(os.Args[i+1], "=")
		if len(connInfo) != 2 {
			fmt.Println("Input error")
		}
		conn, err := net.Dial("tcp", connInfo[1])
		if err != nil {
			log.Fatal(err)
		}
		go clockConection(conn)
	}
	for {
	} 
}
