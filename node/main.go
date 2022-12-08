package main

import (
	"fmt"
	"net"
)

/*
the following code asks the user if he wants to connect to the server and if he does it asks for the ip address and the port number
the code then creates a socket and tries to connect to the server
if the connection is successful the code will send a register request to the server
if the connection is not successful the code will ask the user if he wants to try again


after the connection is established the code will start a goroutine that will listen to the server and will handle the messages that it receives and also will let the user send messages to the server

*/

//library's already imported

// a function that converts a string to the message struct
func StringToMessage(msg string) Message {
	//create the message struct
	message := Message{
		Code:    230,
		Length:  uint32(len(msg)),
		Data:    []byte(msg),
		IsValid: true,
	}

	//return the message
	return message
}

// a function that converts a message struct to a string
func MessageToString(msg Message) string {
	//return the string
	return string(msg.Data)
}

// a function that handles the connection to the server
func ConnectToServer() {
	//ask the user if he wants to connect to the server
	fmt.Println("Do you want to connect to the server? (y/n)")
	var answer string
	fmt.Scanln(&answer)

	//check if the user wants to connect to the server
	if answer == "y" {
		//ask the user for the ip address and the port number
		fmt.Println("Please enter the ip address and the port number of the server")
		var ip string
		var port string
		fmt.Scanln(&ip, &port)

		//create the socket
		socket, err := net.Dial("tcp", ip+":"+port)
		if err != nil {
			fmt.Println("Error: ", err)
			return
		}

		//send a register request to the server
		_, err = socket.Write([]byte{210})
		if err != nil {
			fmt.Println("Error: ", err)
			return
		}

		//start a goroutine that will listen to the server
		go ListenToServer(socket)

		//start a goroutine that will let the user send messages to the server
		go SendToServer(socket)
	}
}

// a function that will listen to the server
func ListenToServer(socket net.Conn) {
	//create a buffer
	buffer := make([]byte, 1024)

	//start a loop that will listen to the server
	for {
		//read the message
		_, err := socket.Read(buffer)
		if err != nil {
			fmt.Println("Error: ", err)
			return
		}

		//deserialize the message
		message, err := DeserializeMessage(buffer)
		if err != nil {
			fmt.Println("Error: ", err)
			return
		}

		//check the code of the message
		if message.Code == 210 {
			//the message is a register response
			fmt.Println("The server has registered you")
		}

		if message.Code == 230 {
			//the message is a message from the server
			fmt.Println("Server: ", MessageToString(message))
		}

	}
}

// a function that will let the user send messages to the server
func SendToServer(socket net.Conn) {
	//start a loop that will let the user send messages to the server
	for {
		//ask the user for a message
		fmt.Println("Please enter a message")
		var msg string
		fmt.Scanln(&msg)

		//convert the message to a message struct
		message := StringToMessage(msg)

		//serialize the message
		serializedMessage, _ := SerializeMessage(message)

		//send the message to the server
		_, err := socket.Write(serializedMessage)
		if err != nil {
			fmt.Println("Error: ", err)
			return
		}
	}
}

// the main function
func main() {
	//connect to the server
	ConnectToServer()
}
