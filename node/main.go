package main

import "node/communicator"

func main() {
	communicator := communicator.NewCommunicator(3)
	go communicator.Listen()
	defer communicator.Delete()

}
