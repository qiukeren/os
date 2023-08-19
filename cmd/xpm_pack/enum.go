package main

var magic uint32 = 0x075BCD15

type PartType uint32

const (
	TypeMeta          PartType = 1
	TypeFile          PartType = 2
	TypeInstantScript PartType = 3
)

func ToType(t PartType) string {
	if t == TypeMeta {
		return "TypeMeta"
	}
	if t == TypeFile {
		return "TypeFile"
	}
	if t == TypeInstantScript {
		return "TypeInstantScript"
	}
	return "TypeUnknown"
}
