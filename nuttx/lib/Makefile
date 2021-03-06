############################################################################
# lib/Makefile
#
#   Copyright (C) 2007-2012 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###########################################################################

-include $(TOPDIR)/Make.defs
include stdio/Make.defs
include stdlib/Make.defs
include unistd/Make.defs
include sched/Make.defs
include string/Make.defs
include pthread/Make.defs
include semaphore/Make.defs
include signal/Make.defs
include mqueue/Make.defs
include math/Make.defs
include net/Make.defs
include time/Make.defs
include libgen/Make.defs
include dirent/Make.defs
include termios/Make.defs
include queue/Make.defs
include misc/Make.defs

ASRCS = 
AOBJS = $(ASRCS:.S=$(OBJEXT))

CSRCS = $(STDIO_SRCS) $(STDLIB_SRCS) $(UNISTD_SRCS)  $(SCHED_SRCS) \
		  $(STRING_SRCS) $(PTHREAD_SRCS) $(SEM_SRCS) $(SIG_SRCS) $(MQUEUE_SRCS) \
		  $(MATH_SRCS) $(NET_SRCS) $(TIME_SRCS) $(LIBGEN_SRCS) \
		  $(DIRENT_SRCS) $(TERMIOS_SRCS) \
		  $(QUEUE_SRCS) $(MISC_SRCS) $(REGEX_SRCS) $(CRC_SRCS) $(DBG_SRCS) 
COBJS = $(CSRCS:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS)
OBJS = $(AOBJS) $(COBJS)

ROOTDEPPATH	= --dep-path .
STDIODEPPATH = --dep-path stdio
STDLIBDEPPATH = --dep-path stdlib
UNISTDDEPPATH = --dep-path unistd
SCHEDDEPPATH = --dep-path sched
STRINGDEPPATH = --dep-path string
PTHREADDEPPATH = --dep-path pthread
SEMDEPPATH = --dep-path semaphore
SIGDEPPATH = --dep-path signal
MQDEPPATH = --dep-path mqueue
MATHDEPPATH = --dep-path math
NETDEPPATH = --dep-path net
TIMEDEPPATH = --dep-path time
LIBGENDEPPATH = --dep-path libgen
DIRENTDEPPATH = --dep-path dirent
TERMIOSDEPPATH = --dep-path termios
QUEUEDEPPATH = --dep-path queue
MISCDEPPATH = --dep-path misc

VPATH  = stdio:stdlib:unistd:sched:string:pthread:semaphore:signal:mqueue
VPATH += :math:net:time:libgen:dirent:termios:queue:misc

UBIN = libulib$(LIBEXT)
KBIN = libklib$(LIBEXT)
BIN  = liblib$(LIBEXT)

all: $(BIN)

$(AOBJS): %$(OBJEXT): %.S
	$(call ASSEMBLE, $<, $@)

$(COBJS): %$(OBJEXT): %.c
	$(call COMPILE, $<, $@)

$(BIN):	$(OBJS)
	@( for obj in $(OBJS) ; do \
		$(call ARCHIVE, $@, $${obj}); \
	done ; )

ifneq ($(BIN),$(UBIN))
.userlib:
	@$(MAKE) $(UBIN) BIN=$(UBIN) TOPDIR=$(TOPDIR) EXTRADEFINES=$(EXTRADEFINES)
	@touch .userlib

$(UBIN): kclean .userlib
endif

ifneq ($(BIN),$(KBIN))
.kernlib:
	@$(MAKE) $(KBIN) BIN=$(KBIN) TOPDIR=$(TOPDIR) EXTRADEFINES=$(EXTRADEFINES)
	@touch .kernlib

$(KBIN): uclean .kernlib
endif

.depend: Makefile $(SRCS)
	@$(MKDEP) $(ROOTDEPPATH) $(STDIODEPPATH) $(STDLIBDEPPATH) \
	  $(UNISTDDEPPATH) $(SCHEDDEPPATH) $(STRINGDEPPATH) $(PTHREADDEPPATH) \
	  $(SEMDEPPATH) $(SIGDEPPATH) $(MQDEPPATH) $(MATHDEPPATH) $(NETDEPPATH)  \
	  $(TIMEDEPPATH) $(LIBGENDEPPATH) $(DIRENTDEPPATH) $(TERMIOSDEPPATH) \
	  $(QUEUEDEPPATH) $(MISCDEPPATH) \
	  $(CC) -- $(CFLAGS) -- $(SRCS) >Make.dep
	@touch $@

depend: .depend

# Clean Targets:
# Clean user-mode temporary files (retaining the UBIN binary)

uclean:
ifneq ($(OBJEXT),)
	@( if [ -f .userlib ]; then rm -f *$(OBJEXT); fi )
endif
	@rm -f .userlib *~ .*.swp

# Clean kernel-mode temporary files (retaining the KBIN binary)

kclean:
ifneq ($(OBJEXT),)
	@( if [ -f .kernlib ]; then rm -f *$(OBJEXT); fi )
endif
	@rm -f .kernlib *~ .*.swp

# Really clean everything

clean: uclean kclean
	@rm -f $(BIN) $(UBIN) $(KBIN) *~ .*.swp
	$(call CLEAN)

# Deep clean -- removes all traces of the configuration

distclean: clean
	@rm -f Make.dep .depend

-include Make.dep
