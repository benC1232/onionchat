package encodersAndDecoders

import (
	"crypto/aes"
	"crypto/ecdsa"
	"crypto/rand"
	"crypto/sha256"
)

// GenerateAESKey make aes key in the size 16 Bytes (aes.BlockSize)
func GenerateAESKey() []byte {
	key := make([]byte, aes.BlockSize)
	rand.Read(key)
	return key
}

// ECCPointTo256BitKey converts an ECC point to a 256-bit key
func ECCPointTo256BitKey(point *ecdsa.PublicKey) ([]byte, error) {

	// Hash the point
	hash := sha256.New()
	hash.Write(point.X.Bytes())
	hash.Write(point.Y.Bytes())
	hashed := hash.Sum(nil)

	// Convert to 256-bit key
	key := make([]byte, 32)
	copy(key, hashed)

	return key, nil
}
