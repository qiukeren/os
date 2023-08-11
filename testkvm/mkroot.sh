#!/bin/bash

set -x

### Parse command line arguments. Clear and set up environment variables.

# Show usage for any unknown argument, ala "./mkroot.sh --help"
if [ "${1:0:1}" == '-' ] && [ "$1" != '-n' ] && [ "$1" != '-d' ] && [ "$1" != "-l" ]
then
  echo "usage: $0 [-n] [VAR=VALUE...] [MODULE...]"
  echo
  echo Create root filesystem in '$ROOT'
  echo
  echo "-n	Don't rebuild "'$ROOT, just build module(s) over it'
  echo "-d	Don't build, just download/verify source packages."
  echo "-l	Log every command run during build in cmdlog.txt"

  exit 1
fi

# Clear environment variables by restarting script w/bare minimum passed through
[ -z "$NOCLEAR" ] &&
  exec env -i NOCLEAR=1 HOME="$HOME" PATH="$PATH" $(env | grep -i _proxy=) \
    CROSS_COMPILE="$CROSS_COMPILE" CROSS_SHORT="$CROSS_SHORT" "$0" "$@"

# Loop collecting initial -x arguments. (Simple, can't collate ala -nl .)
while true
do
  [ "$1" == "-n" ] && N=1 && shift ||
  [ "$1" == "-d" ] && D=1 && shift ||
  [ "$1" == "-l" ] && WRAPDIR=wrap && shift || break
done

# Parse remaining args: assign NAME=VALUE to env vars, collect rest in $MODULES
while [ $# -ne 0 ]
do
  X="${1/=*/}"
  Y="${1#*=}"
  [ "${1/=/}" != "$1" ] && eval "export $X=\"\$Y\"" || MODULES="$MODULES $1"
  shift
done

# If we're cross compiling, set appropriate environment variables.
if [ -z "$CROSS_COMPILE" ]
then
  echo "Building natively"
  if ! cc --static -xc - -o /dev/null <<< "int main(void) {return 0;}"
  then
    echo "Warning: host compiler can't create static binaries." >&2
    sleep 3
  fi
else
  echo "Cross compiling"
  CROSS_PATH="$(dirname "$(which "${CROSS_COMPILE}cc")")"
  CROSS_BASE="$(basename "$CROSS_COMPILE")"
  [ -z "$CROSS_SHORT" ] && CROSS_SHORT="${CROSS_BASE/-*/}"
  if [ -z "$CROSS_PATH" ]
  then
    echo "no ${CROSS_COMPILE}cc in path" >&2
    exit 1
  fi
fi

# Work out absolute paths to working dirctories (can override on cmdline)
TOP="$PWD"
[ -z "$BUILD" ] && BUILD="$TOP/build"
[ -z "$DOWNLOAD" ] && DOWNLOAD="$TOP/download"
[ -z "$AIRLOCK" ] && AIRLOCK="$TOP/airlock"
[ -z "$OUTPUT" ] && OUTPUT="$TOP/output/${CROSS_SHORT:-host}"
[ -z "$ROOT" ] && ROOT="$OUTPUT/${CROSS_BASE}root"

[ -z "$N" ] && rm -rf "$ROOT"
MYBUILD="$BUILD/${CROSS_BASE:-host-}tmp"
mkdir -p "$MYBUILD" "$DOWNLOAD" || exit 1

### Functions to download, extract, and clean up after source packages.

# This is basically "wget $2"
download()
{
  # Grab source package from URL, confirming SHA1 hash.
  # You can stick extracted source in $DOWNLOAD and build will use that instead
  # Usage: download HASH URL

  FILE="$(basename "$2")"
  [ -d "$DOWNLOAD/${FILE/-*/}" ] && echo "$FILE" local && return 0

  X=0
  while true
  do
    [ "$(sha1sum "$DOWNLOAD/$FILE" 2>/dev/null | awk '{print $1}')" == "$1" ] &&
      echo "$FILE" confirmed &&
      break
    rm -f $DOWNLOAD/${FILE/-[0-9]*/}-[0-9]*
    [ $X -eq 1 ] && break
    X=1
    wget "$2" -O "$DOWNLOAD/$FILE"
  done
}

# This is basically "tar xvzCf $MYBUILD $DOWNLOAD/$1.tar.gz && cd $NEWDIR"
setupfor()
{
  # Extract source tarball (or snapshot a repo) to create disposable build dir.
  # Usage: setupfor PACKAGE

  PACKAGE="$(basename "$1")"
  echo === "$PACKAGE"

  cd "$MYBUILD" &&
  if [ $(ls "$MYBUILD" |grep "$PACKAGE"-) ]
  then
    echo "skip existing package"
    cd "$PACKAGE"-* || exit 1
  else
    #tar xvaf "$DOWNLOAD/$PACKAGE"-*.tar.* > /dev/null &&
    tar xvaf "$DOWNLOAD/$PACKAGE"-*.tar.* &&
    cd "$PACKAGE"-* || exit 1
  fi
}

# This is basically "rm -rf $NEWDIR" (remembered from setupfor)
cleanup()
{
  # Delete directory most recent setupfor created, or exit if build failed
  # Usage: cleanup

  [ $? -ne 0 ] && exit 1
  [ -z "$PACKAGE" ] && exit 1
  [ ! -z "$NO_CLEANUP" ] && return
  cd .. && rm -rf "$PACKAGE"* || exit 1
}


# -n skips rebuilding base system, adds to existing $ROOT
if [ ! -z "$N" ]
then
  if [ ! -d "$ROOT" ] || [ -z "$MODULES" ]
  then
    echo "-n needs an existing $ROOT and build files"
    exit 1
  fi

# -d skips everything but downloading packages
elif [ -z "$D" ]
then

### Create files and directories

rm -rf "$ROOT" &&
mkdir -p "$ROOT"/{etc,tmp,proc,sys,dev,home,mnt,root,usr/{bin,sbin,lib},var} &&
chmod a+rwxt "$ROOT"/tmp &&
ln -s usr/bin "$ROOT/bin" &&
ln -s usr/sbin "$ROOT/sbin" &&
ln -s usr/lib "$ROOT/lib" &&
ln -s usr/lib "$ROOT/lib64" &&

cat > "$ROOT"/init << 'EOF' &&
#!/bin/sh

export HOME=/home
export PATH=/bin:/sbin

mountpoint -q proc || mount -t proc proc proc
mountpoint -q sys || mount -t sysfs sys sys
if ! mountpoint -q dev
then
  mount -t devtmpfs dev dev || mdev -s
  mkdir -p dev/pts
  mountpoint -q dev/pts || mount -t devpts dev/pts dev/pts
fi

if [ $$ -eq 1 ]
then
  # Don't allow deferred initialization to crap messages over the shell prompt
  echo 3 3 > /proc/sys/kernel/printk

  # Setup networking for QEMU (needs /proc)
  ifconfig eth0 10.0.2.15
  route add default gw 10.0.2.2
  [ "$(date +%s)" -lt 1000 ] && rdate 10.0.2.2 # or time-b.nist.gov
  [ "$(date +%s)" -lt 10000000 ] && ntpd -nq -p north-america.pool.ntp.org

  [ -z "$CONSOLE" ] &&
    CONSOLE="$(sed -rn 's@(.* |^)console=(/dev/)*([[:alnum:]]*).*@\3@p' /proc/cmdline)"

  [ -z "$HANDOFF" ] && HANDOFF=/bin/sh && echo Type exit when done.
  [ -z "$CONSOLE" ] && CONSOLE=console
  #exec /sbin/oneit -c /dev/"$CONSOLE" $HANDOFF
  /bin/sh
else
  /bin/sh
  umount /dev/pts /dev /sys /proc
fi
EOF
chmod +x "$ROOT"/init &&



cat > "$ROOT"/etc/inittab << 'EOF' &&
# /etc/inittab init(8) configuration for BusyBox
#
# Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
#
#
# Note, BusyBox init doesn't support runlevels.  The runlevels field is
# completely ignored by BusyBox init. If you want runlevels, use sysvinit.
#
#
# Format for each entry: <id>:<runlevels>:<action>:<process>
#
# <id>: WARNING: This field has a non-traditional meaning for BusyBox init!
#
#	The id field is used by BusyBox init to specify the controlling tty for
#	the specified process to run on.  The contents of this field are
#	appended to "/dev/" and used as-is.  There is no need for this field to
#	be unique, although if it isn't you may have strange results.  If this
#	field is left blank, then the init's stdin/out will be used.
#
# <runlevels>: The runlevels field is completely ignored.
#
# <action>: Valid actions include: sysinit, wait, once, respawn, askfirst,
#                                  shutdown, restart and ctrlaltdel.
#
#	sysinit actions are started first, and init waits for them to complete.
#	wait actions are started next, and init waits for them to complete.
#	once actions are started next (and not waited for).
#
#	askfirst and respawn are started next.
#	For askfirst, before running the specified process, init displays
#	the line "Please press Enter to activate this console"
#	and then waits for the user to press enter before starting it.
#
#	shutdown actions are run on halt/reboot/poweroff, or on SIGQUIT.
#	Then the machine is halted/rebooted/powered off, or for SIGQUIT,
#	restart action is exec'ed (init process is replaced by that process).
#	If no restart action specified, SIGQUIT has no effect.
#
#	ctrlaltdel actions are run when SIGINT is received
#	(this might be initiated by Ctrl-Alt-Del key combination).
#	After they complete, normal processing of askfirst / respawn resumes.
#
#	Note: unrecognized actions (like initdefault) will cause init to emit
#	an error message, and then go along with its business.
#
# <process>: Specifies the process to be executed and it's command line.
#
# Note: BusyBox init works just fine without an inittab. If no inittab is
# found, it has the following default behavior:
#	::sysinit:/etc/init.d/rcS
#	::askfirst:/bin/sh
#	::ctrlaltdel:/sbin/reboot
#	::shutdown:/sbin/swapoff -a
#	::shutdown:/bin/umount -a -r
#	::restart:/sbin/init
#	tty2::askfirst:/bin/sh
#	tty3::askfirst:/bin/sh
#	tty4::askfirst:/bin/sh
#
# Boot-time system configuration/initialization script.
# This is run first except when booting in single-user mode.
#
::sysinit:/etc/init.d/rcS

# /bin/sh invocations on selected ttys
#
# Note below that we prefix the shell commands with a "-" to indicate to the
# shell that it is supposed to be a login shell.  Normally this is handled by
# login, but since we are bypassing login in this case, BusyBox lets you do
# this yourself...
#
# Start an "askfirst" shell on the console (whatever that may be)
::askfirst:-/bin/sh
# Start an "askfirst" shell on /dev/tty2-4
tty2::askfirst:-/bin/sh
tty3::askfirst:-/bin/sh
tty4::askfirst:-/bin/sh

# /sbin/getty invocations for selected ttys
tty4::respawn:/sbin/getty 38400 tty5
tty5::respawn:/sbin/getty 38400 tty6

# Example of how to put a getty on a serial line (for a terminal)
#::respawn:/sbin/getty -L ttyS0 9600 vt100
#::respawn:/sbin/getty -L ttyS1 9600 vt100
#
# Example how to put a getty on a modem line.
#::respawn:/sbin/getty 57600 ttyS2

# Stuff to do when restarting the init process
::restart:/sbin/init

# Stuff to do before rebooting
::ctrlaltdel:/sbin/reboot
::shutdown:/bin/umount -a -r
::shutdown:/sbin/swapoff -a

EOF

cp inittab "$ROOT"/etc/inittab

cat > "$ROOT"/etc/passwd << 'EOF' &&
root::0:0:root:/root:/bin/sh
guest:x:500:500:guest:/home/guest:/bin/sh
nobody:x:65534:65534:nobody:/proc/self:/dev/null
EOF

cat > "$ROOT"/etc/group << 'EOF' &&
root:x:0:
guest:x:500:
EOF

echo "nameserver 8.8.8.8" > "$ROOT"/etc/resolv.conf || exit 1

# todo: eliminate busybox

fi # skipped by -n or -d

### Build modules listed on command line

for STAGE_NAME in $MODULES
do
  cd "$TOP" || exit 1
  if [ -z "$D" ]
  then
    . module/"$STAGE_NAME" || exit 1
  else
    eval "$(sed -n '/^download[^(]/{/\\$/b a;b b;:a;N;:b;p}' module/"$STAGE_NAME")"
  fi
done


# Remove build directory if it's empty.
#rmdir "$MYBUILD" "$BUILD" 2>/dev/null
exit 0


