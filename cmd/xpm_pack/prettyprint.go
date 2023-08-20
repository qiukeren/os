package main

import (
	"fmt"
	"io"
)

// Print a byte array in hex format - 16 bytes per line
func Pretty(b []byte, out io.Writer) {

	var offset int = 32

	if offset > len(b) {
		offset = len(b)
	}

	for idx := 0; idx < len(b); idx += 16 {

		out.Write([]byte(fmt.Sprintf("% 0x", b[idx:offset])))
		out.Write([]byte(" "))
		for _, v := range b[idx:offset] {
			out.Write([]byte(toAscii(v)))
		}

		out.Write([]byte{'\n'})
		if offset += 16; offset > len(b) {
			offset = offset - (offset - len(b))
		}
	}
}

var asciiTable = map[byte]string{
	0:  ".",
	1:  ".",
	2:  ".",
	3:  ".",
	4:  ".",
	5:  ".",
	6:  ".",
	7:  ".",
	8:  ".",
	9:  ".",
	10: ".",
	11: ".",
	12: ".",
	13: ".",
	14: ".",
	15: ".",
	16: ".",
	17: ".",
	18: ".",
	19: ".",
	20: ".",
	21: ".",
	22: ".",
	23: ".",
	24: ".",
	25: ".",
	26: ".",
	27: ".",
	28: ".",
	29: ".",
	30: ".",
	31: ".",
	32: " ",

	33:  "!",
	34:  "\"",
	35:  "#",
	36:  "$",
	37:  "%",
	38:  "&",
	39:  "`",
	40:  "(",
	41:  ")",
	42:  "*",
	43:  "+",
	44:  ",",
	45:  "-",
	46:  ".",
	47:  "/",
	48:  "0",
	49:  "1",
	50:  "2",
	51:  "3",
	52:  "4",
	53:  "5",
	54:  "6",
	55:  "7",
	56:  "8",
	57:  "9",
	58:  ":",
	59:  ";",
	60:  "<",
	61:  "=",
	62:  ">",
	63:  "?",
	64:  "@",
	65:  "A",
	66:  "B",
	67:  "C",
	68:  "D",
	69:  "E",
	70:  "F",
	71:  "G",
	72:  "H",
	73:  "I",
	74:  "J",
	75:  "K",
	76:  "L",
	77:  "M",
	78:  "N",
	79:  "O",
	80:  "P",
	81:  "Q",
	82:  "R",
	83:  "S",
	84:  "T",
	85:  "U",
	86:  "V",
	87:  "W",
	88:  "X",
	89:  "Y",
	90:  "Z",
	91:  "[",
	92:  "\\",
	93:  "]",
	94:  "^",
	95:  "_",
	96:  "`",
	97:  "a",
	98:  "b",
	99:  "c",
	100: "d",
	101: "e",
	102: "f",
	103: "g",
	104: "h",
	105: "i",
	106: "j",
	107: "k",
	108: "l",
	109: "m",
	110: "n",
	111: "o",
	112: "p",
	113: "q",
	114: "r",
	115: "s",
	116: "t",
	117: "u",
	118: "v",
	119: "w",
	120: "x",
	121: "y",
	122: "z",
	123: "{",
	124: "|",
	125: "}",
	126: "~",

	127: "DEL",
}

func toAscii(b byte) string {
	if v, ok := asciiTable[b]; ok {
		return v
	}
	return "."
}