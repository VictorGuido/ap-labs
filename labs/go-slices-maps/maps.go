package main

import (
	"strings"
	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	words := strings.Fields(s)
	counter := make(map[string]int)
	for w := range words {		
		counter[words[w]] = counter[words[w]] + 1
	}
	return counter
}

func main() {
	wc.Test(WordCount)
}
