/* SPDX-License-Identifier: MIT */
// go build -o libadd2.go.dll -buildmode=c-shared  main.go 
package main
import "C"

//export add2
func add2(x float64, y float64) float64 {
    return x + y
}

func main() {}
