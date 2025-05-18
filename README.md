zd

zd is a lightweight terminal tool written in C that lets you link multiple files and edit them in a single nano session. After saving, zd automatically updates the original files and deletes the temporary file.

Built for Termux. Built for speed. Built for chaos editing without the chaos.

---

Why?

Because editing 10 files one-by-one in Termux is slow, boring, and makes your soul leave your body.

---

Features

- Edit multiple files at once (up to 10)
- Temporary merge into output.zd
- Auto-sync changes back to original files
- Auto-delete the temporary file after saving
- Nano-based, so no learning curve
- Perfect for Termux and other low-resource terminals
- Written in pure C with no dependencies

---

Installation (Termux or Linux)

pkg install clang
clang zd.c -o zd

Or if you're on a desktop:

gcc zd.c -o zd

Copy it to your bin folder if you wanna call it from anywhere:

mv zd ~/../usr/bin/
chmod +x ~/../usr/bin/zd

Note: If you're using a different architecture than ARM64 (like x86 or x86_64), download the C source and compile it yourself. Precompiled Termux binaries might not vibe with your system.

---

Usage

zd file1.txt link file2.txt file3.txt

This creates a file called output.zd that looks like this:

file1: file1.txt
[contents of file1.txt]

file2: file2.txt
[contents of file2.txt]

file3: file3.txt
[contents of file3.txt]

After you edit and save:

- All the original files are updated.
- output.zd is deleted.
- You feel powerful.

---

Example

touch a.txt b.txt c.txt
zd a.txt link b.txt c.txt

Edit all 3 files in one nano session.

---

Notes

- Max 10 files at once (change #define MAX_FILES 10 in the source to increase)
- The output.zd format is strict—don't mess up the headers like file1: filename
- Works best with text files (.txt, .json, .md, etc.)
- Doesn’t back up files—make copies if you're scared

---

To-Do / Ideas

- Add --backup mode
- Add filetype detection
- Add --unlink command (reverse link)
- Add compatibility with other editors besides nano

---


# Install
to install on termux 
```
pkg install git clang make # optional
git clone https://github.com/srhs1723/zd/
clang zd/C/zd.c -o zd
mv zd $PREFIX/bin
```

To install in Ubuntu 
```
sudo apt install git gcc
git clone https://github.com/srhs1723/zd/
clang /path/to/zd/C/zd.c -o zd
mv /path/to/zd /usr/bin
```


---

# License

MIT License
Use it. Share it. Break your files with it. Just don’t blame me.
