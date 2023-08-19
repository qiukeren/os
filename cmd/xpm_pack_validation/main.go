package main

import (
	"bytes"
	"crypto/md5"
	"encoding/binary"
	"encoding/hex"
	"io"
	"io/ioutil"
	"log"
	"time"
)

func main() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
	x, _ := ioutil.ReadFile("test.xpm")
	b := bytes.NewReader(x)

	log.Printf("magic is %x", readUint32(b))
	log.Printf("total size %d", readUint64(b))

	for {
		log.Println("============")
		head := readUint32(b)
		log.Printf("type %d", head)
		length := readUint64(b)
		log.Printf("length %d", length)

		bf := readBytes(b, length)

		switch head {
		case 1:
			log.Println("1")
			parsePackageMeta(bf)
			break
		case 2:
			log.Println("2")
			parseFileMeta(bf)
			break
		case 3:
			log.Println("3")
			break
		default:
			log.Println("unknown")
			break
		}
	}
}

func readUint32(b io.Reader) uint32 {
	var buf = [4]byte{}
	_, err := b.Read(buf[:])
	if err != nil {
		panic("exit")
	}
	return binary.BigEndian.Uint32(buf[:])
}

func readUint64(b io.Reader) uint64 {
	var buf = [8]byte{}
	_, err := b.Read(buf[:])
	if err != nil {
		panic("exit")
	}
	return binary.BigEndian.Uint64(buf[:])
}

func readBytes(b io.Reader, size uint64) []byte {
	var buf = make([]byte, size)
	_, err := b.Read(buf[:])
	if err != nil {
		panic("exit")
	}
	return buf
}

// Version Version
//
// Name        [32]byte
// Description []byte
func parsePackageMeta(bs []byte) {
	b := bytes.NewReader(bs)
	{
		v := readBytes(b, 12)
		log.Printf("%#v", v)
	}
	{
		v := readBytes(b, 32)
		log.Printf("%s", v)
	}
	{
		s := readUint32(b)
		log.Printf("%s", readBytes(b, uint64(s)))
	}
}

func parseFileMeta(bs []byte) {
	b := bytes.NewReader(bs)
	{
		log.Printf("stat %o", readUint32(b))
		log.Printf("uid %d", readUint32(b))
		log.Printf("gid %d", readUint32(b))

		{
			as := readUint64(b)
			an := readUint64(b)
			t := time.Unix(int64(as), int64(an))
			log.Printf("as %s", t.Format(time.RFC3339Nano))
		}

		{
			as := readUint64(b)
			an := readUint64(b)
			t := time.Unix(int64(as), int64(an))
			log.Printf("ms %s", t.Format(time.RFC3339Nano))
		}
		{
			as := readUint64(b)
			an := readUint64(b)
			t := time.Unix(int64(as), int64(an))
			log.Printf("cs %s", t.Format(time.RFC3339Nano))
		}
	}
	{
		log.Printf("MD5 readed %s", readBytes(b, 32))
		{
			s := readUint32(b)
			c := readBytes(b, uint64(s))
			log.Printf("name %s", c)
		}
		{
			s := readUint64(b)
			c := readBytes(b, uint64(s))
			//log.Printf("content %s", c)
			log.Printf("MD5 calc %s", strMd5(c))
		}
	}
}

func strMd5(str []byte) (retMd5 string) {
	h := md5.New()
	h.Write(str)
	return hex.EncodeToString(h.Sum(nil))
}
