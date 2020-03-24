package main

import (
	"fmt"
	"os"
	"path/filepath"
)

var myDir = ""

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
  var directs =0;
  var symbolic =0;
  var devices=0;
  var sockets =0;
  var other =0;
  var ff = func(pathX string, infoX os.FileInfo, errX error) error {
  if errX != nil {
	fmt.Printf("error 「%v」 at a path 「%q」\n", errX, pathX)
	return errX
  }
  if infoX.IsDir() {
      directs++;
  } else if infoX.Mode()&os.ModeSocket!= 0{
      sockets++
  } else if infoX.Mode()&os.ModeDevice!= 0{
      devices++
  } else if infoX.Mode()&os.ModeSymlink!= 0{
      symbolic++
  } else{
      other++
    }
    return nil
 }
  err := filepath.Walk(dir, ff)
  if err != nil {
	fmt.Printf("error walking the path %q: %v\n", dir, err)
  }
  fmt.Printf("+-------------------------+------+")
  fmt.Printf("\n| Path                    |%s |", dir)
  fmt.Printf("\n+-------------------------+------+")
  fmt.Printf("\n| Directories             |  %d   |", directs)
  fmt.Printf("\n| Symbolic Links          |  %d   |", symbolic)
  fmt.Printf("\n| Devices                 |  %d   |", devices)
  fmt.Printf("\n| Sockets                 |  %d   |", sockets)
  fmt.Printf("\n| Other files             |  %d   |", other)
  fmt.Printf("\n+-------------------------+------+")
  return nil
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}
	 myDir := os.Args[1]
	scanDir(myDir)
}
