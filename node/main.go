package main

import (
	"fmt"
	"node/encodersAndDecoders"
)

func main() {
	//communicator := communicator.NewCommunicator(1)
	//communicator.Listen()
	//defer communicator.Delete()
	key := encodersAndDecoders.GenerateAESKey()
	plaintext := []byte("Hello World")
	aesManager := encodersAndDecoders.NewAESManager(key)
	ciphertext := aesManager.Encrypt(plaintext)
	fmt.Println("ciphertext: ", ciphertext)
	plaintext = aesManager.Decrypt(ciphertext)
	fmt.Println("plaintext: ", (string)(plaintext))


