const net = require('net');

// Set the address and port of the server you want to connect to
const serverAddress = '127.0.0.1';
const serverPort = 34435;

// Create a client socket and connect to the server
const client = net.createConnection({host: serverAddress, port: serverPort}, () => {
  console.log('Connected to server!');
});

// Listen for data received from the server
client.on('data', (data) => {
  console.log(`Received data from server: ${data.toString()}`);
  displayMessage(data.toString(), 'received');
});

// Listen for errors that occur while connecting to the server
client.on('error', (err) => {
  console.error(`Error connecting to server: ${err}`);
});

// Listen for the connection to close
client.on('close', () => {
  console.log('Connection to server closed.');
});

// Function to send a message to the server
function sendMessage(message) {
  client.write(message);
  displayMessage(message, 'sent');
}

// Function to display a message in the chat log
function displayMessage(message, type) {
  const chatlog = document.getElementById('chatlog');
  const messageEl = document.createElement('div');
  messageEl.className = type;
  messageEl.textContent = message;
  chatlog.appendChild(messageEl);
}

// Listen for the submit event on the chatbox form
const chatbox = document.getElementById('chatbox');
const messageInput = document.getElementById('messageInput');
chatbox.addEventListener('submit', (event) => {
  event.preventDefault();
  const message = messageInput.value;
  sendMessage(message);
  messageInput.value = '';
});