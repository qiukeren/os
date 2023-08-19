package main

import (
	"log"
)

type PartContent interface {
	HeaderToBytes() []byte
	ContentToBytes() []byte
	GetHeader() PartHeader
}

// Version total 4 * 3 = 12 Byte
type Version struct {
	MajorVersion uint32
	MinorVersion uint32
	Revision     uint32
}

func (v *Version) ToBytes() []byte {
	//log.Println(v.MajorVersion, v.MinorVersion, v.Revision)
	var b []byte
	b = append(b, toBytes32(v.MajorVersion)...)
	b = append(b, toBytes32(v.MinorVersion)...)
	b = append(b, toBytes32(v.Revision)...)
	return b
}

type FixedHeader struct {
	Magic uint32
	Size  uint64
}

func (h *FixedHeader) MakeHeader(size uint64) {
	h.Magic = magic
	h.Size = size
}

func (h *FixedHeader) _ToBytes() []byte {
	var b []byte
	b = append(b, toBytes32(h.Magic)...)
	b = append(b, toBytes64(h.Size)...)
	return b
}

// PartHeader 12 bytes
type PartHeader struct {
	Type PartType
	Size uint64
}

func (v *PartHeader) ToBytes() []byte {
	var b []byte
	b = append(b, toBytes32(uint32(v.Type))...)
	b = append(b, toBytes64(v.Size)...)
	return b
}

type XpmPackage struct {
	FixedHeader FixedHeader
	Contents    []PartContent
}

func (x *XpmPackage) ToBytes() []byte {

	var b []byte

	for _, v := range x.Contents {
		v.HeaderToBytes()
		log.Printf("package %s, size %d", ToType(v.GetHeader().Type), v.GetHeader().Size)
		b = append(b, v.HeaderToBytes()...)
		b = append(b, v.ContentToBytes()...)
	}

	x.FixedHeader.MakeHeader(uint64(len(b)))
	b = append(x.FixedHeader._ToBytes(), b...)

	return b
}
