LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

# modify SRC_URI from "" to "file://*"
SRC_URI = "file://*"

# add this line.
# P.S. S => The location in the Build Directory where unpacked recipe source code resides.
S = "${WORKDIR}"

do_configure () {
}
do_compile () {
 oe_runmake
}
do_install () {
 oe_runmake install 'DESTDIR=${D}'
}
