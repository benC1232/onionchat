package encodersAndDecoders

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

type AESManager struct {
	key []byte
}

// constructor CFB
func NewAESManager(key []byte) *AESManager {
	return &AESManager{key}
}

func (aesManager *AESManager) Encrypt(data []byte) []byte {
	block, err := aes.NewCipher(aesManager.key)
	if err != nil {
		panic(err)
	}

	ciphertext := make([]byte, aes.BlockSize+len(data))
	iv := ciphertext[:aes.BlockSize]
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	stream := cipher.NewCFBEncrypter(block, iv)
	stream.XORKeyStream(ciphertext[aes.BlockSize:], data)

	return ciphertext
}

func (aesManager *AESManager) Decrypt(data []byte) []byte {
	block, err := aes.NewCipher(aesManager.key)
	if err != nil {
		panic(err)
	}

	if len(data) < aes.BlockSize {
		panic("ciphertext too short")
	}
	iv := data[:aes.BlockSize]
	data = data[aes.BlockSize:]

	stream := cipher.NewCFBDecrypter(block, iv)

	stream.XORKeyStream(data, data)
	return data
}
