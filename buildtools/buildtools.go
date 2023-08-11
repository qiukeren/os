package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"os/exec"
	"path"
	"path/filepath"

	figure "github.com/common-nighthawk/go-figure"
	"github.com/olekukonko/tablewriter"
	log "github.com/sirupsen/logrus"
	"gopkg.in/yaml.v3"
)

const buildName = "build.yaml"

type File struct {
	File   string
	Target string
}

type Build struct {
	Project string   `json:"project"`
	Scripts []string `json:"scripts"`
	Files   []File   `json:"files"`
}

func main() {
	os.Setenv("GOOS", "linux")
	os.Setenv("GOARCH", "amd64")
	os.Setenv("CGO_ENABLED", "0")

	os.Remove("target")
	os.Mkdir("target", 0755)
	os.Mkdir("target/bin", 0755)
	os.Mkdir("target/etc", 0755)
	os.Mkdir("target/etc/services", 0755)

	err := filepath.Walk(".", func(pathStr string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if info.IsDir() {
			return nil
		}
		if path.Base(pathStr) != buildName {
			return nil
		}
		buildPack(pathStr)
		return nil
	})
	if err != nil {
		log.Println(err)
	}
}

func buildPack(pathStr string) {
	var dir = path.Dir(pathStr)
	var err error
	var buildFile []byte
	buildFile, err = ioutil.ReadFile(pathStr)
	if err != nil {
		log.Println(err)
		return
	}
	var b = Build{}
	err = yaml.Unmarshal(buildFile, &b)
	if err != nil {
		log.Println("error: %v", err)
		return
	}
	figure.NewFigure(b.Project, "doom", true).Print()

	for _, cmdStr := range b.Scripts {
		log.Println("bash", "-c", cmdStr)
		cmd := exec.Command("bash", "-c", cmdStr)
		cmd.Dir = dir
		cmd.Stdout = os.Stdout
		cmd.Stderr = os.Stderr
		cmd.Run()
	}

	var outBuffer = bytes.Buffer{}
	table := tablewriter.NewWriter(&outBuffer)
	table.SetHeader([]string{"Project", "FileName", "Target", "Size"})

	for _, file := range b.Files {
		var sourceFile = path.Join(dir, file.File)
		var targetFile = path.Join("target", file.Target)
		err := CopyFile(sourceFile, targetFile)
		if err != nil {
			log.Fatalln(err)
		}

		table.Append([]string{
			b.Project, file.File, file.Target, ByteCountIEC(Size(targetFile)),
		})
	}
	table.Render()
	fmt.Println(outBuffer.String())
}

func ByteCountIEC(b int64) string {
	const unit = 1024
	if b < unit {
		return fmt.Sprintf("%d B", b)
	}
	div, exp := int64(unit), 0
	for n := b / unit; n >= unit; n /= unit {
		div *= unit
		exp++
	}
	return fmt.Sprintf("%.1f %ciB",
		float64(b)/float64(div), "KMGTPE"[exp])
}

func Size(f string) int64 {
	s, _ := os.Stat(f)
	if s == nil {
		return 0
	}
	return s.Size()
}

func CopyFile(src, dst string) (err error) {
	sfi, err := os.Stat(src)
	if err != nil {
		return
	}
	if !sfi.Mode().IsRegular() {
		// cannot copy non-regular files (e.g., directories,
		// symlinks, devices, etc.)
		return fmt.Errorf("CopyFile: non-regular source file %s (%q)", sfi.Name(), sfi.Mode().String())
	}
	dfi, err := os.Stat(dst)
	if err != nil {
		if !os.IsNotExist(err) {
			return
		}
	} else {
		if !(dfi.Mode().IsRegular()) {
			return fmt.Errorf("CopyFile: non-regular destination file %s (%q)", dfi.Name(), dfi.Mode().String())
		}
		if os.SameFile(sfi, dfi) {
			return
		}
	}
	if err = os.Link(src, dst); err == nil {
		return
	}
	err = copyFileContents(src, dst)
	return
}

// copyFileContents copies the contents of the file named src to the file named
// by dst. The file will be created if it does not already exist. If the
// destination file exists, all it's contents will be replaced by the contents
// of the source file.
func copyFileContents(src, dst string) (err error) {
	in, err := os.Open(src)
	if err != nil {
		return
	}
	defer in.Close()
	out, err := os.Create(dst)
	if err != nil {
		return
	}
	defer func() {
		cerr := out.Close()
		if err == nil {
			err = cerr
		}
	}()
	if _, err = io.Copy(out, in); err != nil {
		return
	}
	err = out.Sync()
	return
}
