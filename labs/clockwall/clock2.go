//Victor Jaret Guido Alvarado
// clock2.go
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

func handleConn(c net.Conn, timeZ string) {
	defer c.Close()
	for {
		_, tErr := time.LoadLocation(timeZ)
		if tErr != nil {
			fmt.Println("Error while loading " + timeZ + " timezone")
			log.Print(tErr)
			break
		}
		_, err := io.WriteString(c, timeZ+" "+time.Now().Format("15:04:05\n"))
		if err != nil {
			log.Print(err)
			return
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {
	args := os.Args[1:]
	if len(args) < 2 {
		fmt.Println("Expected input: go run clock2.go -port #port")
		os.Exit(1)
	}
	localPort := "localhost:" + args[1]
	listener, err := net.Listen("tcp", localPort)
	if err != nil {
		log.Fatal(err)
	}

	timeZ := os.Getenv("TZ")
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, timeZ) // handle connections concurrently
	}
}
