# This file is generated by gyp; do not edit.

export builddir_name ?= trunk/src/voice_engine/$(OBJDIR)/media/webrtc/out
.PHONY: all
all:
	$(MAKE) -C ../.. voice_engine_core voe_auto_test voe_cmd_test
